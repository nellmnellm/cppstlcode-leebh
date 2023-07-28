#include <iostream>
#include "rbTree.hpp"

int main() {
    // Example usage
    RBTree<std::string, int> rbTree;

    rbTree.insert("apple", 5);
    rbTree.insert("banana", 3);
    rbTree.insert("orange", 7);
    rbTree.insert("remon", 6);

    std::cout << "Size of the tree: " << rbTree.size() << std::endl;

    int numApples = rbTree.find("apple");
    if (numApples != 0) {
        std::cout << "Number of apples: " << numApples << std::endl;
    }
    else {
        std::cout << "Apple not found in the tree." << std::endl;
    }

    rbTree.remove("banana");

    std::cout << "Size of the tree after removing 'banana': " << rbTree.size() << std::endl;
    
    return 0;
}

//��� ���� Red �Ǵ� Black�� ������ �����ϴ�.
//��Ʈ ���� Black�Դϴ�.
//��� ���� ���(NIL ���)�� Black�Դϴ�.
//Red ���� �� ���� Black �ڽ��� ������ �մϴ�. (Red ���� �����ؼ� ��Ÿ�� �� �����ϴ�.)
//� ���κ��� �����Ͽ� ���� ������ �����ϴ� ��� ��δ� ������ ������ Black ��带 �����ϴ�. (�̸� Black Height��� �մϴ�.)