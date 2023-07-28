#include <iostream>
using namespace std;

//����Ʈ�� ���ظ� �ϱ� ���� ����
struct Node {
    int data; //�����Ϳ� prev, next�� ����� ���۰� �� ����.
    struct Node* prev;
    struct Node* next;
};
struct Node* head = NULL; // ����ü�� �ּҰ��� head�� �����ϰ� �ϴ��� NULL ���·� ����
void insert(int newdata) { // malloc calloc realloc ���� C ��� �����޸��Ҵ� ����� �����Ұ�.
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));//����ü node�� size��ŭ�� �޸𸮰����� �Ҵ�. node�� �����ͷ� ����
    newnode->data = newdata; // ���ο� data�� �����
    newnode->prev = NULL; // ù ����� ��� ù prev���� NULL;
    newnode->next = head; // next���� newnode�� ��� �κ��� ���� �־���
    if (head != NULL)
        head->prev = newnode; //  ù ��尡 �ƴѰ�쿡�� prev null�� �ƴ϶� �� ����� head�� ��.
    head = newnode; // ����� �����Ͱ��� newnode�� �ּҰ��� �ȴ�.
}
void display() {
    struct Node* ptr; // ����� �ּҰ��� ptr�� ����
    ptr = head; // �����ʹ� �� ������ ��尪�� ���� ����Ŵ
    while (ptr != NULL) // pointer�� ������ ���� NULL�� �����ϱ���� data���� �а� ������ 
        cout << ptr->data << " ";
        ptr = ptr->next; // �̺κ��� �� ���ذ� �ȵ����� data�� ���� �� ������. ���������� ������������ �� �����غ���
    }
}
int main() {
    insert(3);
    insert(1);
    insert(7);
    insert(2);
    insert(9);
    cout << "The doubly linked list is: ";
    display();
    return 0;
}

//��ó https://www.tutorialspoint.com/cplusplus-program-to-implement-doubly-linked-list

// �̷� ���� ���� ����Ʈ�� ������ �����غ���. 