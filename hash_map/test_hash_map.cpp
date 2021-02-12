#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <functional>
#include "hash_map.h"

using namespace std;

int main(){
	int tmp_int;
	char tmp_char;
	map_pair<int, char> *tmp_pair;
	hash_map <int, char, hash<int>> map1;	
	srand(time(NULL));

	for (int i = 0; i < 20; i++){
		tmp_int = rand()%30;
		tmp_char = rand()%26+97;
		map1.add(tmp_int, tmp_char);
		tmp_pair = map1.find(tmp_int);
		if (tmp_pair != NULL){
			cout<<"pair <"<<tmp_pair->get_key()<<","<<tmp_pair->get_value()<<">, amount = "<<map1.get_amount()<<endl;
		} else {
			cout<<"can't find element"<<endl;
			return 1;
		}
	}
	
	hash_map <int, char, hash<int>> map2 = map1;
	cout<<"map2 amount = "<<map2.get_amount()<<endl;
	if (map2[1] != NULL){
		cout<<"map2[1] = "<<map2[1]->get_value()<<endl;
		map2.delete_by_key(1);
		cout<<"map2 amount = "<<map2.get_amount()<<endl;
	} else {
		cout<<"no key 1 in map2"<<endl;
	}

	cout<<"amount of list  (critical value = "<<map2.get_critical_value()<<") = "<<map2.get_list_size()<<endl;
	map2.set_critical_value(3.0);
	cout<<"amount of list  (critical value = "<<map2.get_critical_value()<<") = "<<map2.get_list_size()<<endl;

	return 0;
}
