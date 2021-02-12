#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

template <typename T, typename K>
class node{
	private:
		T data;
		K value;
		node *left;
		node *right;
		node *father;
		int height;
		int value_obtained_by_iterator;
		int value_obtained_to_reset_iterator;


	public:	

		void change_other_node_height(){
			node *my_father = father;
			int left_height;
			int right_height;
			while (my_father != NULL){
				left_height = 0;
				right_height = 0;
				if (my_father->left != NULL) {
					left_height = my_father->left->height;
				}
				if (my_father->right != NULL) {
					right_height = my_father->right->height;
				}
				my_father->height = (left_height > right_height)?left_height:right_height;
				my_father = my_father->father;
			}	
		}

		int calculate_height(){
			int counter = 0;
			node *my_father = father;
			while ( my_father != NULL){
				my_father = my_father->get_father();
				counter++;
			}
			return counter;
		}

		node *get_left(){
			return left;
		}

		T get_data(){
			return data;
		}
		
		K get_value(){
			return value;
		}

		node *get_right(){
			return right;
		}
		
		node *get_father(){
			return father;
		}

		int get_height(){
			return height;
		}

		int get_value_obtained_by_iterator(){
			return value_obtained_by_iterator;
		}

		int get_value_obtained_to_reset_iterator(){
			return value_obtained_to_reset_iterator;
		}

		void set_left(node *Left){
			left = Left;
		}

		void set_right(node *Right){
			right = Right;
		}

		void set_father(node *Father){
			father = Father;
		}

		void set_height(int Height){
			height = Height;
		}

		void set_value_obtained_by_iterator(int Value_obtained_by_iterator){
			value_obtained_by_iterator = Value_obtained_by_iterator;
		}
		
		void set_value_obtained_to_reset_iterator(int Value_obtained_to_reset_iterator){
			value_obtained_to_reset_iterator = Value_obtained_to_reset_iterator;
		}

		node(T Data, K Value, node *Father){
			value = Value;
			data = Data;
			left = NULL;
			right = NULL;
			father = Father;
			height = calculate_height();
			value_obtained_by_iterator = 1;
			value_obtained_to_reset_iterator = 1;
		}
};

