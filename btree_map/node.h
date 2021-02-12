#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iterator>

using namespace std;

template <typename T, typename C>
class map_pair{
	private:
		T key;
		C value;

	public:

		T get_key(){
			return key;
		}

		C get_value(){
			return value;
		}
		
		void set_value(C Value){
			value = Value;
		}
		
		map_pair(T Key, C Value){
			key = Key;
			value = Value;
		}
};


template <typename T, typename C >
class node {
	private:
		node<T,C> *father;

		void delete_node(node<T,C> *cur_node){
			int i;
			int data_size = cur_node->data.size();

			for (i = 0; i < data_size; i++){
				delete cur_node->data[data_size-1-i];
			}
			int pointer_size  = cur_node->pointer.size();
			for (i = 0; i < pointer_size; i++){
				delete cur_node->pointer[pointer_size-1-i];
			}
		}

	public:
		
		vector <map_pair<T,C>* > data;
		vector <node<T,C>* > pointer;

		node<T,C> *copy_node(node<T,C> *cur_node, node<T,C> *Father){
			if (this != NULL){
				delete this;
			}
			int i;
			node<T,C> *new_node = new node<T,C>(Father);
			map_pair<T,C> *tmp; 
			for (i = 0; i < cur_node->data.size(); i++){
				tmp = new map_pair<T,C>(cur_node->data[i]->get_key(), cur_node->data[i]->get_value());
				new_node->data.push_back(tmp);
			}
			for (i = 0; i < cur_node->pointer.size(); i++){
				new_node->pointer.push_back(copy_node(cur_node->pointer[i], new_node));
			}
			return new_node;
		}


		map_pair<T,C> *find_data(T Data){
			int mid;
			int l = 0;
			int r = data.size()-1;
			while (l <= r) {
				mid = (l+r)/2;
				if (data[mid]->get_key() > Data){
					r = mid-1;
				} else if (data[mid]->get_key() < Data){
					l = mid+1;
				} else {
					return data[mid];
				}
			}
			return NULL;
		}

		int insert_data(T Data, C Value){
			int l = 0;
			int r = data.size()-1;
			int mid;
			auto iter = data.begin();
			map_pair<T,C> *tmp_map_pair = new map_pair<T,C>(Data, Value);

			while (l <= r) {
				mid = (l+r)/2;
				if (data[mid]->get_key() > Data){
					r = mid-1;
				} else {
					l = mid+1;
				}
			}

			data.insert(iter+r+1, tmp_map_pair);
			return r+1;
		}

		void node_splitting(int R){
			int i, pointer_size;
			int mid = R-1;
			int position;
			node <T,C> *part_pointer, *part2_pointer;

			if (father != NULL){
				auto iter = father->pointer.begin();
				position = father->insert_data(data[mid]->get_key(), data[mid]->get_value());
				part_pointer = new node<T,C>(father);
				for (i = mid+1; i < (2*R-1); i++){
					part_pointer->data.push_back(data[i]);
				}
				for (i = mid+1; i <pointer.size(); i++){
					part_pointer->pointer.push_back(pointer[i]);
				}
				for (i = mid; i < (2*R-1); i++){
					data.pop_back();
				}
				pointer_size = pointer.size();
				for (i = mid+1; i < pointer_size; i++){
					pointer.pop_back();
				}
				father->pointer.insert(iter+position+1, part_pointer);
				if (father->data.size() == 2*R-1){
					father->node_splitting(R);
				}
			} else {	
				part_pointer = new node<T,C>(this);
				part2_pointer = new node<T,C>(this);
				for (i = 0; i < mid; i++){
					part_pointer->data.push_back(data[i]);
				}
				for (i = 0; i < (int)(pointer.size()/2); i++){
					part_pointer->pointer.push_back(pointer[i]);
				}
				for (i = mid+1; i < (2*R-1); i++){
					part2_pointer->data.push_back(data[i]);
				}
				for (i = mid+1; i <pointer.size(); i++){
					part2_pointer->pointer.push_back(pointer[i]);
				}
				for (i = 0; i < mid; i++){
					data.erase(data.begin());
				}
				for (i = mid+1; i < (2*R-1); i++){
					data.pop_back();
				}
				pointer_size = pointer.size();
				for (i = 0; i < pointer_size; i++){
					pointer.pop_back();
				}
				pointer.push_back(part_pointer);
				pointer.push_back(part2_pointer);
			}
		}

		node<T,C> *get_father(){
			return father;
		}

		void set_father(node<T,C> *Father){
			father = Father;
		}

		
		node<T,C>& operator= (node<T,C>& Node){
			if (this == &Node) {
				return *this;
			}
			copy_node(&Node);
			return *this;
		}

		node(node<T,C> *Father){
			father = Father;
		}

		~node(){
			delete_node(this);
		}
};
