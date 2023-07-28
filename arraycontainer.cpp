#pragma once

template <typename T>
class array_bh // ����_array ����
{
private: // ����Լ� ����
	T* arr;
	int arrSize;

public:
	 
	


	array_bh(int size) //������ ����
	{
		arrSize = size;  //size�� �Է¹��� ������ �ʱ�ȭ
		arr = new T[arrSize]; //size ũ���� �迭 �����Ҵ�
		for (int i = 0; i < arrSize; i++)
		{
			arr[i] = 0; // arr�� ��� ���Ҹ� 0���� �ʱ�ȭ
		}
	}

	array_bh(const array_bh<T>& other_arr)//���� ������ ����
	{									  //�ٸ� ��ü�� �ּҸ� const �����Ͽ� ���� �ٲ��� �ʰ� �� 
		
		int n = other_arr.arrSize;
		arr = new T[n];
		for (int i = 0; i < n; i++)
		{
			arr[i] = other_arr.arr[i];
		}
		arrSize = n;
	}

	~array_bh() //�Ҹ��� ����
	{
		delete[] arr;
 	}


	/* �����δ� ������ ��� �Լ����� ������ �� ���� */

	int size() const // 1.size �Լ� ����
	{
		return arrSize;
	}

	bool empty() const // 2. empty �Լ� ����
	{
		if (arrSize)
			return 0;
		else
			return 1;
	}

	void fill(int value) // 3. fill �Լ� ����
	{
		for (int i = 0; i < arrSize; i++)
			arr[i] = value;
	}


	T& at(int index) {  //4. at �Լ� ����. 
		if (index<arrSize)
			return arr[index];// arr[index]�� ���� return�ϱ� ������ T&(������ ����)���
		throw "Index out of range";
	}

	
	T& operator[](int index)//5. []�� arr �ε��� ȣ�� ����
	{
		return arr[index];
	}
	const T& operator[](int index)const
	{
		return arr[index];
	}


	T& front() { //6. front �Լ� ����
		return arr[0];
	}

	T& back() { ///7. back �Լ� ����
		return arr[arrSize - 1];
	}

	/*
	T* begin() {
		return arr.begin();
	}*/ //begin�� end�� �����غ��� ������ vector iterator�� �ʿ��Ѱ� ���� keep
};