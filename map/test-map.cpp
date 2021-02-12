#include <cstdlib>
#include <ctime>
#include <iostream>
#include "map.h"
#include <string>

using namespace std;

int main()
{
	int tmp_data;
	string tmp_value;
	node <int, string> *tmp_node;
	avl_tree <int, string> tree_1;
	avl_tree <int, string> tree_2;
	avl_tree <int, string> tree_3;

	srand(time(NULL));
	for (int i=0; i < 1000; i++){
		tmp_data = rand()%10;
		tmp_value = (char)(rand()%26+97);
		tree_1.add(tmp_data, tmp_value);
	}
	
	if (tree_1.property_test()){
		tree_1.tree_copy(&tree_2);
		if (!tree_2.is_empty()){
			if (tree_2.property_test()){
				cout << "tree_2 amount after test = "<<tree_2.get_amount()<<endl;
			}
		}
	}
	
	tree_2.delete_all_elements();
	cout << "tree_2 amount after delete = "<<tree_2.get_amount()<<endl;
	for (int i=0; i < 20; i++){
		tmp_value = (char)(i+97);
		tree_2.add(i, tmp_value);
	}
	cout << "tree_2 amount after adding = "<<tree_2.get_amount()<<endl;
	cout << "--------" << endl;
	for (int j=0; j < 15; j++){
		tmp_node = tree_2.next();
		cout << "data = "<<tmp_node->get_data()<<", value = "<<tmp_node->get_value()<< endl;
	}
	cout << "--------" << endl;
	tree_2.add(1, "x");
	cout << "tree_2 amount = "<<tree_2.get_amount()<<endl;
	for (int j=0; j < 15; j++){
		tmp_node = tree_2.next();
		cout << "data = "<<tmp_node->get_data()<<", value = "<<tmp_node->get_value()<< endl;
	}
	cout << "--------" << endl;
	
	if (tree_3.is_empty()){
		cout<<"tree_3 is empty"<<endl;
	}

	tree_3 = tree_2;

	tmp_node = tree_3.search_by_index(3);
	if (tmp_node != NULL){
		cout<<"element with data = 3 has value = "<<tmp_node->get_value()<<endl;
	} else {
		cout<<" element with data = 3 is not in the tree_3"<<endl;
	}

	return 0;
}
