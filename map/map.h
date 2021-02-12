#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "node.h"

using namespace std;

template <typename T, typename K>
class avl_tree{
	private:
		node<T,K> *root;
		node<T,K> *iterator_node;
		int iterator_flag;
		int inside_count;
		int count;


		node<T,K> *reset_iterator_node(){
			node<T,K> *Node = root;
			while (Node->get_left() != NULL) {
				Node = Node->get_left();
			}
			iterator_node = Node;
			reset_all_value_obtained_by_iterator();
			inside_count = 0;
			return Node;
		}


		void reset_all_value_obtained_by_iterator(){
			int inside_inside_count = 0;
			iterator_flag = 1;
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 0){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
			inside_inside_count++;
			iterator_node->set_value_obtained_by_iterator(1);
			iterator_node->set_value_obtained_to_reset_iterator(0);
			}
		
//and again to reset all value_obtained_to_reset_iterator to initial state
			iterator_node = root;
			iterator_flag = 1;
			while(iterator_node->get_left() != NULL){
				iterator_node = iterator_node->get_left();
			}
			inside_inside_count = 0;
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 1){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
			inside_inside_count++;
			iterator_node->set_value_obtained_to_reset_iterator(1);
			}
		}


		node<T,K> *left_rotation(node<T,K> *A){
			node<T,K> *B = A->get_right();
			node<T,K> *L = A->get_left();
			node<T,K> *C = B->get_left();
			node<T,K> *R = B->get_right();
			node<T,K> *Father = A->get_father();
			if (Father != NULL){
				if (Father->get_left() == A){
					Father->set_left(B);
				}else {
					Father->set_right(B);
				}
			}
			if (A == root){
				root = B;
			}
			if (B != NULL){
				B->set_father(A->get_father());
			}
			A->set_father(B);	
			if (L != NULL){
				L->set_father(A);
			}
			if (C != NULL){
				C->set_father(A);
			}
			if (R != NULL){
				R->set_father(B);
			}
			A->set_left(L);
			A->set_right(C);
			B->set_left(A);
			B->set_right(R);
			A->set_height(A->calculate_height());
			A->change_other_node_height();
			if (L != NULL){
				change_subtree_height(L, 1);
			}
			if (R != NULL){
				change_subtree_height(R, -1);
			}

			if (C != NULL){
				C->change_other_node_height();
			}
			return B;
		}


		node<T,K> *big_left_rotation(node<T,K> *A){
			node<T,K> *B = A->get_right();
			node<T,K> *C = B->get_left();
			node<T,K> *L = A->get_left();
			node<T,K> *CL = C->get_left();
			node<T,K> *CR = C->get_right();
			node<T,K> *R = B->get_right();
			node<T,K> *Father = A->get_father();
				
			if (Father != NULL){
				if (Father->get_left() == A){
					Father->set_left(C);
				}else {
					Father->set_right(C);
				}
			}
			if (A == root){
				root = C;
			}
			if (C != NULL){
				C->set_father(A->get_father());
			}
			A->set_father(C);
			if (B != NULL){
				B->set_father(C);
			}
			if (L != NULL){
				L->set_father(A);
			}
			if (CL != NULL){
				CL->set_father(A);
			}
			if (CR != NULL){
				CR->set_father(B);
			}
			if (R != NULL){
				R->set_father(B);
			}
			C->set_left(A);
			C->set_right(B);
			A->set_left(L);
			A->set_right(CL);
			B->set_left(CR);
			B->set_right(R);
			A->set_height(A->calculate_height());
			B->set_height(B->calculate_height());
			A->change_other_node_height();
			if (CL != NULL){
				change_subtree_height(CL, -1);
			}
			if (CR != NULL){
				change_subtree_height(CR, -1);
			}
			if (L != NULL){
				change_subtree_height(L, 1);
			}
			if (R != NULL){
				R->change_other_node_height();
			}
			return C;
		}


		node<T,K> *right_rotation(node<T,K> *A){
			node<T,K> *B = A->get_left();
			node<T,K> *L = B->get_left();
			node<T,K> *C = B->get_right();
			node<T,K> *R = A->get_right();
			node<T,K> *Father = A->get_father();
			
			if (Father != NULL){
				if (Father->get_left() == A){
					Father->set_left(B);
				}else {
					Father->set_right(B);
				}
			}
			if (A == root){
				root = B;
			}
			if (B != NULL){
				B->set_father(A->get_father());
			}
			if (L != NULL){
				L->set_father(B);
			}
			A->set_father(B);
			if (C != NULL){
				C->set_father(A);
			}
			if (R != NULL){
				R->set_father(A);
			}
			B->set_left(L);
			B->set_right(A);
			A->set_left(C);
			A->set_right(R);
			A->set_height(A->calculate_height());
			A->change_other_node_height();
			if (R != NULL){
				change_subtree_height(R, 1);
			}
			if (L != NULL){
				change_subtree_height(L, -1);
			}
			if (C != NULL){
				C->change_other_node_height();
			}
			return B;
		}

		node<T,K> *big_right_rotation(node<T,K> *A){	
			node<T,K> *B = A->get_left();
			node<T,K> *C = B->get_right();
			node<T,K> *L = B->get_left();
			node<T,K> *CL = C->get_left();
			node<T,K> *CR = C->get_right();
			node<T,K> *R = A->get_right();
			node<T,K> *Father = A->get_father();
			
			if (Father != NULL){
				if (Father->get_left() == A){
					Father->set_left(C);
				}else {
					Father->set_right(C);
				}
			}
			if (A == root){
				root = C;
			}
			if (C != NULL){
				C->set_father(A->get_father());
			}
			A->set_father(C);
			if (B != NULL){
				B->set_father(C);
			}
			if (L != NULL){
				L->set_father(B);
			}
			if (CL != NULL){
				CL->set_father(B);
			}
			if (CR != NULL){
				CR->set_father(A);
			}
			if (R != NULL){
				R->set_father(A);
			}
			C->set_left(B);
			C->set_right(A);
			A->set_left(CR);
			A->set_right(R);
			B->set_left(L);
			B->set_right(CL);
			A->set_height(A->calculate_height());
			B->set_height(B->calculate_height());
			A->change_other_node_height();
			if (CL != NULL){
				change_subtree_height(CL, -1);
			}
			if (CR != NULL){
				change_subtree_height(CR, -1);
			}
			if (R != NULL){
				change_subtree_height(R, 1);
			}
			if (L != NULL){
				L->change_other_node_height();
			}
			return C;
		}


		void balancing(node<T,K> *cur_node){
			cur_node = cur_node->get_father();
			int left_height_lev1;
			int right_height_lev1;
			int left_height_lev2;
			int right_height_lev2;
			while (cur_node != NULL) {
				if (cur_node->get_left() != NULL){
					left_height_lev1 = cur_node->get_left()->get_height();
				} else {	
					left_height_lev1 = cur_node->calculate_height();
				}	
				if (cur_node->get_right() != NULL){
					right_height_lev1 = cur_node->get_right()->get_height();
				} else {	
					right_height_lev1 = cur_node->calculate_height();
				}	
				if ((left_height_lev1 - right_height_lev1) == 2){
					if (cur_node->get_left()->get_left() != NULL){
						left_height_lev2 = cur_node->get_left()->get_left()->get_height();
					} else {	
						left_height_lev2 = cur_node->get_left()->calculate_height();
					}	
					if (cur_node->get_left()->get_right() != NULL){
						right_height_lev2 = cur_node->get_left()->get_right()->get_height();
					} else {	
						right_height_lev2 = cur_node->get_left()->calculate_height();
					}	
					if (left_height_lev2 < right_height_lev2) {
						cur_node = big_right_rotation(cur_node);
						iterator_node = reset_iterator_node();
						return;
					}else{
						cur_node = right_rotation(cur_node);
						iterator_node = reset_iterator_node();
						return;
					}
				} else if ((right_height_lev1 - left_height_lev1) == 2){
					if (cur_node->get_right()->get_left() != NULL){
						left_height_lev2 = cur_node->get_right()->get_left()->get_height();
					} else {	
						left_height_lev2 = cur_node->get_right()->calculate_height();
					}	
					if (cur_node->get_right()->get_right() != NULL){
						right_height_lev2 = cur_node->get_right()->get_right()->get_height();
					} else {	
						right_height_lev2 = cur_node->get_right()->calculate_height();
					}
					if ( left_height_lev2 > right_height_lev2) {
						cur_node = big_left_rotation(cur_node);
						iterator_node = reset_iterator_node();
						return;
					}else{
						cur_node = left_rotation(cur_node);
						iterator_node = reset_iterator_node();
						return;
					}
				}
				cur_node = cur_node->get_father();
			}
			iterator_node = reset_iterator_node();
		}

	public:
		
		void add (T Data, K Value){
			node<T,K> *cur_node;
			int flag = 1;
			if(root == NULL){
				root = new node<T,K>(Data, Value, NULL);
				count++;
				balancing(root);

			} else {
				cur_node = root;
				while (flag) {
					if (Data < cur_node->get_data()){
						if (cur_node->get_left() == NULL){
							node<T,K> *tmp_node = new node<T,K>(Data, Value, cur_node);
							cur_node->set_left(tmp_node);
							tmp_node->change_other_node_height();
							cur_node = cur_node->get_left();
							flag = 0;
							count++;
						} else {
							cur_node = cur_node->get_left();
						} 
					} else if (Data >= cur_node->get_data()){
						if (cur_node->get_right() == NULL){
							node<T,K> *tmp_node = new node<T,K>(Data, Value, cur_node);
							cur_node->set_right(tmp_node);
							tmp_node->change_other_node_height();
							cur_node = cur_node->get_right();
							flag = 0;
							count++;
						} else {
							cur_node = cur_node->get_right();
						}
					}
				}
			balancing(cur_node);
			}
		}


		node<T,K> *next(){
			node<T,K> *Value;
			if (root == NULL) {
				return NULL;
			} else {
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_by_iterator())) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_by_iterator() == 0){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_by_iterator())) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_by_iterator())) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
				Value = iterator_node;
				inside_count++;
				iterator_node->set_value_obtained_by_iterator(0);
			}
			if (inside_count == count) {
				iterator_node = reset_iterator_node();
			}
			return Value;
		}


		void change_subtree_height(node<T,K> *subroot, int shift){
			int tmp_flag = iterator_flag;
			node<T,K> *tmp_iterator_node = iterator_node;
			iterator_node = subroot;
			while (iterator_node->get_left() != NULL) {
				iterator_node = iterator_node->get_left();
			}
			while (!((iterator_node == subroot)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0))){
				iterator_flag = 0;
				while (iterator_flag == 0){
					if (iterator_node->get_right() != NULL){
						if (iterator_node->get_right()->get_value_obtained_to_reset_iterator()) {
							iterator_node = iterator_node->get_right();
							while (iterator_node->get_left() != NULL) {
								iterator_node = iterator_node->get_left();
							}
						} else {
							iterator_flag = 1;
						}
					} else {
						iterator_flag = 1;
					}
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 0){
					if (iterator_node != subroot){
						iterator_node = iterator_node->get_father();
					}
					iterator_flag = 0;
					while (iterator_flag == 0){
						if (iterator_node->get_right() != NULL){
							if (iterator_node->get_right()->get_value_obtained_to_reset_iterator()) {
								iterator_node = iterator_node->get_right();
								while (iterator_node->get_left() != NULL) {
									iterator_node = iterator_node->get_left();
								}
							} else {
								iterator_flag = 1;
							}
						} else {
							iterator_flag = 1;
						}
					}
				}
				iterator_node->set_height(iterator_node->get_height() + shift);
				iterator_node->set_value_obtained_to_reset_iterator(0);
			}
		
//and again to reset all value_obtained_to_reset_iterator to initial state
			iterator_node = subroot;
			while (iterator_node->get_left() != NULL) {
				iterator_node = iterator_node->get_left();
			}
			while (!((iterator_node == subroot)&&(iterator_node->get_value_obtained_to_reset_iterator()))){
				iterator_flag = 0;
				while (iterator_flag == 0){
					if (iterator_node->get_right() != NULL){
						if (iterator_node->get_right()->get_value_obtained_to_reset_iterator()==0) {
							iterator_node = iterator_node->get_right();
							while (iterator_node->get_left() != NULL) {
								iterator_node = iterator_node->get_left();
							}
						} else {
							iterator_flag = 1;
						}
					} else {
						iterator_flag = 1;
					}
				}
				while (iterator_node->get_value_obtained_to_reset_iterator()){
					if (iterator_node != subroot){
						iterator_node = iterator_node->get_father();
					}
					iterator_flag = 0;
					while (iterator_flag == 0){
						if (iterator_node->get_right() != NULL){
							if (iterator_node->get_right()->get_value_obtained_to_reset_iterator()==0) {
								iterator_node = iterator_node->get_right();
								while (iterator_node->get_left() != NULL) {
									iterator_node = iterator_node->get_left();
								}
							} else {
								iterator_flag = 1;
							}
						} else {
							iterator_flag = 1;
						}
					}
				}
				iterator_node->set_value_obtained_to_reset_iterator(1);
			}
			iterator_flag = tmp_flag;
			iterator_node = tmp_iterator_node;
			subroot->change_other_node_height();
		}


		bool avl_property_test(){
			bool answer = true;
			int left_height, right_height;
			int tmp_iterator_flag = iterator_flag;
			node<T,K> *tmp_iterator_node = iterator_node;

			int inside_inside_count = 0;
			iterator_flag = 1;
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 0){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
			inside_inside_count++;
			if (iterator_node->get_left() == NULL){
				left_height = iterator_node->calculate_height();
			} else {
				left_height = iterator_node->get_left()->get_height();
			}
			if (iterator_node->get_right() == NULL){
				right_height = iterator_node->calculate_height();
			} else {
				right_height = iterator_node->get_right()->get_height();
			}
			if (abs(right_height-left_height)>1){
				answer = false;
			}

			iterator_node->set_value_obtained_to_reset_iterator(0);
			}
		
//and again to reset all value_obtained_to_reset_iterator to initial state
			iterator_node = root;
			iterator_flag = 1;
			while(iterator_node->get_left() != NULL){
				iterator_node = iterator_node->get_left();
			}
			inside_inside_count = 0;
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 1){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
				inside_inside_count++;
				iterator_node->set_value_obtained_to_reset_iterator(1);
			}
			iterator_flag = tmp_iterator_flag;
			iterator_node = tmp_iterator_node;
			return answer;
		}


		bool binary_tree_property_test(){
			int cur_inside_count = inside_count;
			iterator_node = reset_iterator_node();
			T old_data = next()->get_data();
			T cur_data;
			for (int i = 1; i < count; i++){
				cur_data = next()->get_data();
				if (cur_data < old_data){
					return false;
				}
				old_data = cur_data;
			}
			for (int i = 0; i < cur_inside_count; i++){
				cur_data = next()->get_data();
			}
			return true;
		}


		bool property_test(){
			if (binary_tree_property_test()){
				if (avl_property_test()){
					return true;
				}
			}
			return false;
		}


		int get_amount(){
			return count;
		}


		void tree_copy(avl_tree<T,K> *tree){
			if (tree->root != NULL){
				tree->delete_all_elements();
			}
			if (root == NULL){
				return;
			}
			node<T,K> *new_node;
			int inside_inside_count = 0;
			int tmp_flag = iterator_flag;
			node<T,K> *tmp_iterator_node = iterator_node;

			iterator_flag = 1;
			iterator_node = root;
			new_node = new node<T,K>(root->get_data(),root->get_value(), NULL);
			tree->set_count(tree->get_count()+1);
			tree->root = new_node;
			while (iterator_node->get_left() != NULL) {
				iterator_node = iterator_node->get_left();
				new_node->set_left(new node<T,K>(iterator_node->get_data(), iterator_node->get_value(), new_node));
				tree->set_count(tree->get_count()+1);
				new_node = new_node->get_left();
			}
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 0){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
							new_node = new_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						new_node->set_right(new node<T,K>(iterator_node->get_data(), iterator_node->get_value(), new_node));
						new_node = new_node->get_right();
						tree->set_count(tree->get_count()+1);
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
							new_node->set_left(new node<T,K>(iterator_node->get_data(), iterator_node->get_value(), new_node));
							new_node = new_node->get_left();
							tree->set_count(tree->get_count()+1);
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator())) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
			inside_inside_count++;
			iterator_node->set_value_obtained_to_reset_iterator(0);
			}
		
//and again to reset all value_obtained_to_reset_iterator to initial state
			iterator_node = root;
			iterator_flag = 1;
			while(iterator_node->get_left() != NULL){
				iterator_node = iterator_node->get_left();
			}
			inside_inside_count = 0;
			while (inside_inside_count < count){
				if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
					iterator_flag = 0;
				}
				while (iterator_node->get_value_obtained_to_reset_iterator() == 1){
					if (iterator_flag) {
						if (iterator_node->get_father() != NULL){
							iterator_node = iterator_node->get_father();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						}
					} else {
						iterator_node = iterator_node->get_right();
						while (iterator_node->get_left() != NULL) {
							iterator_node = iterator_node->get_left();
						}
						if ((iterator_node->get_right() != NULL)&&(iterator_node->get_value_obtained_to_reset_iterator() == 0)) {
							iterator_flag = 0;
						} else {
							iterator_flag = 1;
						}
					}
				}
				inside_inside_count++;
				iterator_node->set_value_obtained_to_reset_iterator(1);
			}
			iterator_flag = tmp_flag;
			iterator_node = tmp_iterator_node;
			tree->set_iterator_node(tree->reset_iterator_node());	
		}


		node<T,K> *search_by_index(T Data){
			node<T,K> *cur_node = root;
			while (cur_node != NULL){
				if (cur_node->get_data() < Data){
					cur_node = cur_node->get_right();
				} else if (cur_node->get_data() > Data){
					cur_node = cur_node->get_left();
				} else {
					return cur_node;
				}
			}
			return NULL;
		}


		void delete_all_elements(){
			if (root == NULL){
				return;
			}
			node<T,K> *next_node;
			iterator_node = root;
			while (iterator_node->get_left() != NULL) {
				iterator_node = iterator_node->get_left();
			}
			while (count > 0){
				if (iterator_node->get_right() != NULL){
					iterator_node = iterator_node->get_right();
					next_node = iterator_node->get_father();
					next_node->set_right(NULL);
					while (iterator_node->get_left() != NULL) {
						iterator_node = iterator_node->get_left();
					}
				}
				if (iterator_node != root){
					next_node = iterator_node->get_father();
					delete iterator_node;
					iterator_node = next_node;
				}
				count--;
			}
			iterator_flag = 1;
			iterator_node = NULL;
			inside_count = 0;
			root = NULL;
		}


		bool is_empty(){
			if (count == 0){
				return true;
			}else{
				return false;
			}
		}


		void set_iterator_node(node<T,K> *Iterator_node){
			iterator_node = Iterator_node;
		}	

		void set_root(node<T,K> *Root){
			root = Root;
		}

		node<T,K> *get_root(){
			return root;
		}

		void set_count(int Count){
			count = Count;
		}

		int get_count(){
			return count;
		}

		avl_tree<T,K>& operator= (avl_tree<T,K> &tree){
			tree.tree_copy(this);
			return *this;
		}

		avl_tree(){
			root = NULL;
			iterator_node = NULL;
			iterator_flag = 1;
			inside_count = 0;
			count = 0;

		}
		
		~avl_tree(){
			delete_all_elements();
		}

};
