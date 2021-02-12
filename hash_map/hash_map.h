#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <functional>
#include <iterator>

using namespace std;

template <typename K, typename V>
class map_pair{
	private:
		K key;
		V value;

	public:

		K get_key(){
			return key;
		}

		V get_value(){
			return value;
		}
		
		void set_value(V Value){
			value = Value;
		}
		
		map_pair(K Key, V Value){
			key = Key;
			value = Value;
		}
};


template <typename K, typename V, typename my_hash = hash<K> >
class hash_map{
	private:
		int amount;
		int list_size;
		float critical_value;
		my_hash Hash;


		void resize(int new_size){
			int i, j, List_i_size, new_hash;
			if (new_size>list_size){
				for (i = 0; i < (new_size-list_size); i++){
					hash_list.push_back(vector<map_pair<K,V> *>());
				}
				for (i = 0; i < list_size; i++){
					List_i_size = hash_list[i].size();
					for (j = 0; j < List_i_size; j++){
						new_hash = Hash(hash_list[i][List_i_size-1-j]->get_key())%new_size;
						if (new_hash != i){
							hash_list[new_hash].push_back(hash_list[i][List_i_size-1-j]);
							hash_list[i].erase(hash_list[i].begin()+List_i_size-1-j);
						}
					}
				}
			} else {
				for (i = (list_size-1); i >= new_size; i--){
					List_i_size = hash_list[i].size();
					for (j = 0; j < List_i_size; j++){
						new_hash = Hash(hash_list[i][List_i_size-1-j]->get_key())%new_size;
						if (new_hash != i){
							hash_list[new_hash].push_back(hash_list[i][List_i_size-1-j]);
							hash_list[i].erase(hash_list[i].begin()+List_i_size-1-j);
						}
					}
				}
			}
			list_size = new_size;
		}

	public:
		vector <vector <map_pair<K,V> *> > hash_list;


		map_pair<K,V> * operator[] (K Key){
			return find(Key);
		}	

		hash_map<K,V,my_hash>& operator= (hash_map<K,V,my_hash>& Hash_map){
			if (this == &Hash_map) {
				return *this;
			}
			hash_map_copy(&Hash_map);
			return *this;
		}

		void delete_map(){
			int List_size, List_i_size;
			List_size = hash_list.size();
			for(int i = 0; i < List_size; i++){
				List_i_size = hash_list[i].size();
				for(int j = 0; j <<List_i_size; j++){
					delete hash_list[List_size-1-i][List_i_size-1-j];
					amount--;
				}
			}
		}

		void hash_map_copy(hash_map<V,K,my_hash> *Hash_map){
			map_pair<K,V> *tmp_pair; 
			int i, j, List_i_size;
			if (amount != 0){
				delete_map();
			}
			hash_list.resize(Hash_map->get_list_size());
			for (i = 0; i < Hash_map->get_list_size(); i++){
				List_i_size = Hash_map->hash_list[i].size();
				for (j = 0; j < List_i_size; j++){
					tmp_pair = new map_pair<K,V> (Hash_map->hash_list[i][j]->get_key(), Hash_map->hash_list[i][j]->get_value());
					hash_list[i].push_back(tmp_pair);
					amount++;
				}
			}
		}

		void delete_by_key(K Key){
			int index = Hash(Key)%list_size;
			int Len = hash_list[index].size();
			
			for (int i = 0; i < Len; i++){
				if (hash_list[index][i]->get_key() == Key){
					delete hash_list[index][i];
					hash_list[index].erase(hash_list[index].begin()+i);
					amount--;
					if ((((float)(amount))/list_size)< critical_value){
						resize((int)(amount/critical_value)+1);
					}
				}
			}
		}

		map_pair<K,V> *add(K Key, V Value){
			map_pair<K,V> *tmp_pair = new map_pair<K,V> (Key, Value);
			hash_list[Hash(Key)%list_size].push_back(tmp_pair);
			amount++;
			if ((((float)(amount))/list_size) > critical_value){
				resize(2*list_size+1);
			}
			return tmp_pair;
		}

		map_pair<K,V> *find(K Key){
			int index = Hash(Key)%list_size;
			int Len = hash_list[index].size();
			
			for (int i = 0; i < Len; i++){
				if (hash_list[index][i]->get_key() == Key){
					return hash_list[index][i];
				}
			}
			return NULL;
		}

		int get_amount(){
			return amount;
		}

		int get_list_size(){
			return list_size;
		}

		void set_critical_value(float Critical_value){
			if (critical_value != 0){
				critical_value = Critical_value;
				if ((((float)(amount))/list_size)< critical_value){
					resize((int)(amount/critical_value)+1);
				}
			} else {
				cout<<"critical value can't be zero"<<endl;
			}
		}

		float get_critical_value(){
			return critical_value;
		}

		hash_map(float Critical_value = 2, int List_size = 5){
			if (critical_value != 0){
				amount = 0;
				list_size = List_size;
				critical_value = Critical_value;
				for (int i = 0; i < List_size; i++){
					hash_list.push_back(vector <map_pair<K,V> *>());
				}
			} else {
				cout<<"critical value can't be zero"<<endl;
			}

		}

		~hash_map(){
			delete_map();
		}
};
