#include <cstdlib>
#include <ctime>
#include <iostream>
#include "priority-queue.h"
#include <string>
#include <deque>
using namespace std;

int main()
{
	priority_fifo <int, deque<int> >  fifo;
	srand(time(NULL));
	for (int i=0; i < 10; i++){
		fifo.push(rand()%10);
		fifo.print();
	}
	int sz = fifo.size();
	for (int i=0; i < sz; i++){
		cout << fifo.pop() << endl;
	}
	if (fifo.is_empty()){
		cout << "empty" << endl;
	}
	return 0;
}
