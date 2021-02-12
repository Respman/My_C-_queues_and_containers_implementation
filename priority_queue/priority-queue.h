#include <cstdlib>
#include <iostream>
#include <vector>

template <typename T, typename c = std::vector<T> >
class priority_fifo{
	private:
		std::vector <T> vec;

		void heap_down(){
			int maxchild;
			int done = 0;
			int root = 0;

			while (((root*2+1) <= (vec.size()-1)) &&(done == 0)){
				if ((root*2+1) == (vec.size()-1)){
					maxchild = root*2+1;
				} else if (vec[root*2+1]>vec[root*2+2]){
					maxchild = root*2+1;
				} else {
					maxchild = root*2+2;
				}

				if (vec[root]<vec[maxchild]){
					T tmp = vec[root];
					vec[root] = vec[maxchild];
					vec[maxchild] = tmp;
					root = maxchild;
				} else {
					done = 1;
				}
			}
		}

		void heap_up(){
			int done = 0;
			int cur_elem = vec.size()-1;

			while ((cur_elem > 0)&&(done == 0)){
				if (vec[cur_elem] > vec[(cur_elem-1)/2]){
					T tmp = vec[cur_elem];
					vec[cur_elem] = vec[(cur_elem-1)/2];
					vec[(cur_elem-1)/2] = tmp;
					cur_elem = (cur_elem-1)/2;
				} else {
					done = 1;
				}
			}
		}

	public:
		void push(T inp){
			vec.push_back(inp);
			heap_up();
		}
		T pop(){
			T out = vec[0];
			vec[0] = vec[vec.size()-1];
			vec.pop_back();
			heap_down();
			return out;
		}
		void print(){
			for (int i = 0; i < vec.size(); i++){
				std::cout << vec[i] << " ";
			}
			std::cout << std::endl;
		}
		int size(){
			return(vec.size());
		}
		int is_empty(){
			if (vec.size()>0){
				return 0;
			}else{
				return 1;
			}
		}
};

