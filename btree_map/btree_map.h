#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "node.h"

using namespace std;

template <typename T, typename C>
class btree_map {
	private:
		node<T,C> *root;
		int t;
		int count;

		bool test_node_property(node<T,C> *cur_node){
			if (cur_node->pointer.size() > 2*t){
				return false;
			}
			if (cur_node->data.size() > 2*t-1){
				return false;
			}
			for (int i = 0; i < (cur_node->data.size()-1); i++){
				if (cur_node->data[i]->get_key() >= cur_node->data[i+1]->get_key()){
					return false;
				}
			}
			for (int i = 0; i < cur_node->pointer.size(); i++){
				if(!test_node_property(cur_node->pointer[i])){
					return false;
				}
			}
			return true;
		}

		node<T,C> *copy_node(node<T,C> *cur_node, node<T,C> *Father){
			int i;
			node<T,C> *new_node = new node<T,C>(Father);
			map_pair<T,C> *tmp; 
			for (i = 0; i < cur_node->data.size(); i++){
				tmp = new map_pair<T,C>(cur_node->data[i]->get_key(), cur_node->data[i]->get_value());
				new_node->data.push_back(tmp);
				count++;
			}
			for (i = 0; i < cur_node->pointer.size(); i++){
				new_node->pointer.push_back(copy_node(cur_node->pointer[i], new_node));
			}
			return new_node;
		}

	public:

		void tree_copy(btree_map<T,C> *new_tree){
			if (root != NULL){
				delete root;
				count = 0;
			}
			root = copy_node(new_tree->get_root(), NULL);
		}

		bool b_tree_property(){
			if (!test_node_property(root)){
				return false;
			}
			return true;
		}

		map_pair<T,C> *find(T Data){
			if (root == NULL){
				return NULL;
			}
			node<T,C> *cur_node = root;
			int i;
			map_pair<T,C> *tmp;

			while (cur_node->pointer.size() != 0){
				tmp = cur_node->find_data(Data);
				if (tmp != NULL){
					return tmp;
				}
				if (Data <= (cur_node->data[0]->get_key())){
					cur_node = cur_node->pointer[0];
				} else if (Data > cur_node->data[cur_node->data.size()-1]->get_key()){
					cur_node = cur_node->pointer[cur_node->pointer.size()-1];
				} else {
					for (i = 0; i < (cur_node->data.size()-1); i++){
						if ((Data > cur_node->data[i]->get_key())&&(Data <= cur_node->data[i+1]->get_key())){
							cur_node = cur_node->pointer[i+1];
							break;
						}
					}
				}
			}
			return(cur_node->find_data(Data));
		}

		map_pair<T,C> *add(T Data, C Value){
			node<T,C> *cur_node = root;
			int i, Pos;
			map_pair<T,C> *tmp = find(Data);
			if (tmp != NULL) {
				return tmp;
			}

			if (root == NULL){
				root = new node<T,C>(NULL);
				root->insert_data(Data, Value);
				count++;
				return root->data[0];
			} else {
				while (cur_node->pointer.size() != 0){
					if (Data <= cur_node->data[0]->get_key()){
						cur_node = cur_node->pointer[0];
					} else if (Data > cur_node->data[cur_node->data.size()-1]->get_key()){
						cur_node = cur_node->pointer[cur_node->pointer.size()-1];
					} else {
						for (i = 0; i < cur_node->data.size()-1; i++){
							if ((Data > cur_node->data[i]->get_key())&&(Data <= cur_node->data[i+1]->get_key())){
								cur_node = cur_node->pointer[i+1];
								break;
							}
						}
					}
				}		
				Pos = cur_node->insert_data(Data, Value);
				if (cur_node->data.size() == (2*t-1)){
					cur_node->node_splitting(t);
				}
				count++;
				return cur_node->data[Pos];
			}
		}
		
		int get_t(){
			return t;
		}

		void set_root(node<T,C> *Root){
			root = Root;
		}

		node<T,C> *get_root(){
			return root;
		}

		btree_map(int c){
			root = NULL;
			t = c;
			count = 0;
		}

		map_pair<T,C> * operator[] (T Data){
			return find(Data);
		}	

		btree_map<T,C>& operator= (btree_map<T,C>& Tree){
			if (this == &Tree) {
				return *this;
			}
			tree_copy(&Tree);
			return *this;
		}

		void delete_btree_map(){
			if (root != NULL){
				delete root;
				root = NULL;
			}
			count = 0;
		}

		bool is_empty(){
			if (count == 0){
				return true;
			} else {
				return false;
			}
		}

		int get_count(){
			return count;
		}

		btree_map(btree_map<T,C>&Tree){
			t = Tree.get_t();
			root = NULL;
			count = 0;
			tree_copy(&Tree);
		}

		~btree_map(){
			if (root != NULL){
				delete_btree_map();
			}
		}
};
