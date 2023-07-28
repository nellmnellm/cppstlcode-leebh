#include <iostream>
using namespace std;

//���� Ʈ���߿� �ڷᱸ���� �ַ� ���Ǵ� BST(���� �˻� Ʈ��)�� ������ ������.

template <typename T>
class Node { // ��� Ŭ���� ����
public:
	T data; // data�� ����
	Node* left; // ����
	Node* right; // �������� ����
	int index;
	Node(const T& value) : data(value), left(nullptr), right(nullptr), index(-1) {}
	//�̴ϼȶ������� ��� ����.
};

template <typename T>
class bst_bh // ���� ã�� Ʈ�� _ ���� Ŭ���� ����
{
private:
	Node<T>* root; //��Ʈ ����

	Node<T>* insert(Node<T>* root, const T& value) // ��� ���� �����Լ� insert�� private�� ���� 
	{
		if (root == nullptr)
		{
			return new Node<T> (value);
		}

		if (value < root->data) {   // root������ ���� �Է¹��� ���� �������
			root->left = insert(root->left, value); //������ root�� �����Ͽ� value�� ��������� ������.
		}
		else if (value > root->data) { // �ݴ��� ���
			root->right = insert(root->right, value); //  �������� root�� �Ͽ� ���ο� ��� ����.
		}
		return root;
	}

	Node<T>* findNode(Node<T>* root, const T& value) { // ��� ã�� �����Լ�.
		if (root == nullptr || root->data == value) { // value�� data�� ���ų�( ã�� ���) / �Ѹ����� �������� ��
			return root; // root�� ��ȯ�Ѵ�. (�� ���� �ּҰ��� ��ȯ�ϰų� ����(nullptr) ��ȯ)
		}

		if (value < root->data) { //value�� �� ����� data������ ������ �������� �̵�
			return findNode(root->left, value);
		}
		else {						// �ݴ��� ��� ���������� �̵�.
			return findNode(root->right, value);
		}
	}

	// ��带 ���� ��ȸ�ϸ� index���� ���� �ο��ϴ� ���� �Լ�. �� ���� ������� ���� ����.
	void calculateIndex(Node<T>* root, int& index) {
		if (root == nullptr) {				// ���� ���� ���Ұ� ���ų� ���� ������ ��� �Լ��� ����
			return;
		}

		calculateIndex(root->left, index); // ���� ������ ������ ��� (���� ���� ���� index = 0�� �ο���(public�� ���� �̸��� �Լ���)) 
		root->index = index; // ���� ������ root�� index�� �ο�����.
		cout << root->index << " " << root->data << "\n"; // index���� data���� �������.
		index++; 
		
		calculateIndex(root->right, index); //�������� ���鼭 ??? �׷��� ��������� �湮�ϴ°ǵ� �� �����?
	}

public:
	bst_bh() : root(nullptr) {}

	void insert(const T& value) { // ���� �����ϴ� �Լ�. public�� ����Ǿ� �ִ�.
		root = insert(root, value);
	}

	Node<T>* find(const T& value) { // ���� Ʈ���� ���� ã�Ƽ� �ּҰ��� ��ȯ.
		return findNode(root, value);
	}

	void calculateIndexes() { // ���� Ž�� Ʈ���� ���� ��ȸ�Ͽ� index ���� ����ϴ� �Լ�
		int index = 0; // ù index�� 0���� �ϰ� �ȴ�.
		calculateIndex(root, index); //(root,0)�������� ��������� ����ǰ� �Ǵµ� root->left���� ���������� ��� ����.
	}
};






int main(void)
{
	bst_bh<int> bs;
	bs.insert(3);
	bs.insert(4); 
	bs.insert(6);
	bs.insert(2);
	bs.insert(1);
	bs.insert(5);
	bs.insert(8);
	bs.insert(7);
	bs.insert(10);

	bs.find(1); // 
	
	bs.calculateIndexes();
	return 0;
}