#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include "btree_map.h"

using namespace std;

int main() {
	int i, tmp_int;
	char tmp_char;
	map_pair <int, char> *tmp_pair;
	btree_map <int, char> tree1(3);
	btree_map <int, char> tree2(3);
	srand(time(NULL));

	for (i = 0; i < 1000; i++){
		tmp_int = rand()%20;
		tmp_char = rand()%26+97;
		tree1.add(tmp_int, tmp_char);
		tmp_pair = tree1.find(tmp_int);
		if (tmp_pair != NULL){
			cout<<"pair: <"<<tmp_pair->get_key()<<", "<<tmp_pair->get_value()<<">"<<endl;
		}
		if (!tree1.b_tree_property()){
			cout<<"b-tree 1 property error"<<endl;
			return 1;
		} 
	}

	cout<<"tree1 amount of elements: "<<tree1.get_count()<<endl;
	cout<<"tree2 amount of elements: "<<tree2.get_count()<<endl;
	tree2.tree_copy(&tree1);
	cout<<"tree2 amount of elements: "<<tree2.get_count()<<endl;
	tmp_pair = tree2.find(1);
	if (tmp_pair != NULL) {
		cout<<"tree1[1] before operator [] = "<<tmp_pair->get_value()<<endl;
		tree2[1]->set_value('a');
		cout<<"tree1[1] = "<<tmp_pair->get_value()<<endl;
	}
	
	tree2 = tree1;
	cout<<"tree2 amount of elements: "<<tree2.get_count()<<endl;
	if (!tree2.b_tree_property()){	
		cout<<"b-tree 2 property error"<<endl;
	} else {	
		cout<<"b-tree 2 property success"<<endl;
	}
	btree_map <int, char> tree3(tree1);
	cout<<"tree3 amount of elements: "<<tree3.get_count()<<endl;
	if (!tree3.b_tree_property()){
		cout<<"b-tree 3 property error"<<endl;
		return 1;
	} else {	
		cout<<"b-tree 3 property success"<<endl;
	}

	return 0;
}
