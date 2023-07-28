#pragma once
#include <iostream>


template <typename T>
class Node { // ��� Ŭ��  ����
public:
	T data; // data�� ����
	Node* next; //���� �κ��� ����Ű�� �ּҸ� ��������� ����

	template <typename T>
	Node(const T& value) : data(value), next(nullptr) {} //�̴ϼȶ������� ��� ����.
};//ī�� ����Ʈ����


template <typename T>
class FList_bh { //����_����Ʈ ����
private:
	Node<T>* head; // ����� �ּҸ� head ��� ����
public:

	FList_bh() : head(nullptr) {} //�⺻ ������
	
	FList_bh(const FList_bh& other) : head(nullptr) { //���� ������. "���� ����"�� ���� & ���
		if (other.head)  // ������ head�� ���� �����ϸ� ���ο� ��带 ������
		{
			head = new Node<T>{ other.head->data }; //���ο� node�� ���ø����� ������ data�� �־���
			auto cur = head; //iterator�� �ϰ� ����� auto �ɼ� �̿�. ���� ���� head�� ����
			auto it = other.begin(); //it�� other�� ù° ���� ��Ÿ���� �ݺ��ڷ� ����.
			while (true) 
			{
				auto tmp = it; // it�� ���� ������ �ʱ� ���� tmp ����
				++tmp;
				if (tmp == other.end()) // end�� �ɶ����� while���� ����.
					break;
				cur->next = new Node<T>{ *tmp }; //���ο� ��带 ����.
				cur = cur->next; // ���ο� node�� ���� cur�� it�� ����
				it = tmp;
			}

		}
	}

	

	FList_bh(const initializer_list<T> ilist) : head(nullptr) { //�ʱ�ȭ ����Ʈ. �� �ᵵ ������
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++)
			push_front(*it);
	}

	T operator[](size_t index) const // []�� index�� ȣ���ϱ� ���� operator ����
	{
		Node<T>* cur = head; // node�� �ּ��� current���� head�� ����
		size_t count = 0; // �̶� size_t�� �������� size �� ��Ÿ���� �����̴�. int, char ���� ��
		while (cur) 
		{
			if (count == index) 
				return cur->data; //Node<T>�� �����Ͱ��� return����
			cur = cur->next;
			++count;
		}
		throw std::out_of_range("Index out of range");
	};

	void push_front(const T val) // �տ� push���ִ� ����Լ� ����
	{
		Node<T>* new_node = new Node<T>{ val }; //����� �����Ͱ� new_node����
		if (head != nullptr)
			new_node->next = head;   // �������̹Ƿ� ->�� ����. next�� head�� ����
		head = new_node; // head���� ���ο� �� new_node ����.
	}

	void pop_front() // �տ��� pop�ϴ� ����Լ� ����
	{
		Node<T>* first = head; //�����͸� �������� head ���� �ִ´�.
		if (head) 
		{
			head = head->next;  //head���� next�� �־��� �ִ� ���� ����
			delete first; //head�� ���� �ִ� �ּҸ� ����. ���� ���� ����
		}
	}
};



