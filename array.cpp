#include <iostream>
#include "container.cpp"
using namespace std;

int main(void)
{
	array_bh<int> arr(5);
	arr[0] = 0;
	arr[1] = 1;
	cout << arr[1] + arr.at(1);
	arr[2] = 2;
	array_bh<int> arr2 = arr;
	cout << "arr�� ������ arr2�� index 1,2�� ��: "<<arr2[1] << arr2[2] << endl; //���� ������ �׽�Ʈ
	cout << "arr�� index ũ��: "<<arr.size() << endl;; // size() �Լ� �׽�Ʈ
	cout << "arr�� ��������� 1, �ƴϸ� 0: "<<arr.empty()<<endl; // empty() �Լ� �׽�Ʈ
	arr.fill(5); 
	cout << "arr[1]�� ����: " << arr[1] << ", arr2[2]�� ����: "<<arr2[2] << endl; //fill �Լ� �׽�Ʈ. ����� ���� ����� �̷������ ����
	cout << "arr�� ó�� �ε����� ����: " << arr.front() << endl; //front �Լ� �׽�Ʈ
	cout << "arr�� ������ �ε����� ����: "<<arr.back() << endl; //back �Լ� �׽�Ʈ
	//cout << arr.begin();
	return 0;
}