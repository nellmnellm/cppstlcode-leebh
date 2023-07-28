
#include "double_linked_list.hpp"
using namespace std;


int main(void)
{
	list_bh <int> lis;
	lis.push_back(2);
	lis.push_back(2);
	lis.push_front(3);
	lis.push_front(4);
	lis.print_list();

	lis.pop_back();
	lis.pop_front();

	lis.print_list();
	lis.get_size();
	
	cout << endl; 

	
	auto it = lis.begin();
	for (auto i = it; i != lis.end(); i++)
		i->data += 1;
	lis.print_list();  //여기는 동작을 안하는 이유를 잘 모르겠음
	
	

	return 0;
}