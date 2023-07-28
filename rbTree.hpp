#pragma once
enum Color { RED, BLACK };

template <typename KeyType, typename ValueType>
class RBTree {
private:
    struct Node {  //����� ��������� ����.
        KeyType key; // key�� value���� ���� ���� ����
        ValueType value;
        Color color; // ������ red�� black ���� �ϳ�. enum���� ���� �Ǿ� ����.
        Node* left;  // Ʈ�� �����̹Ƿ� node�� parent; left/right �и�
        Node* right;
        Node* parent;

        Node(const KeyType& k, const ValueType& v, Color c = RED) // ��� �⺻ ������.
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;  //RBTree class�� ���� �� �⺻ ����� �ּҸ� root�� ������

public:
    RBTree() : root(nullptr) {} // RBTree �⺻ ������.

    ~RBTree() {
        clear(root); // RBTreee �⺻ �Ҹ���.
    }

    void insert(const KeyType& key, const ValueType& value) { //����Լ� insert.
        Node* newNode = new Node(key, value); // �� ��带 ����� �ּҰ� �̸��� newNode
        insertNode(newNode); // line 90~110;
        fixInsert(newNode);
    }

    ValueType find(const KeyType& key) const {
        Node* result = findNode(root, key); //value���� return�� �� �ֵ��� ��
        return (result != nullptr) ? result->value : ValueType{}; //valueType{}�̶� �� ��ü�� �⺻���� ��ȯ�ϴ°�
    }

    void remove(const KeyType& key) {
        Node* node = findNode(root, key); //��带 ã�� ����. 
        if (node == nullptr) // ã�� ��尡 ���� ��� �Լ� ����.
            return;

        Node* fixNode; //fixNode ����
        Color fixColor = node->color;  //fixColor ����
        if (node->left == nullptr) { //����� ������ ������
            fixNode = node->right; // fixNode�� ����� ������ �ּҷ� ����
            transplant(node, node->right); // ��带 ����� ������ ������ �ٲ���
        }
        else if (node->right == nullptr) { // �������� ������ 
            fixNode = node->left;
            transplant(node, node->left);  // ���ʰ����� �ٲ�
        }
        else {                             // �Ѵ� �ƴϸ�
            Node* minRight = findMin(node->right);  // node���� ū �� �� �ּҰ��� �ּҸ� ã�Ƽ� minRight�� �̸� ����
            fixColor = minRight->color; //
            fixNode = minRight->right; // fixNode�� ������ ����Ž��Ʈ�������� ���������� �����.

            if (minRight->parent == node) // minRight�� �ٷ� �Ʒ��� �ڼ��̾��ٸ�
                fixNode->parent = minRight; //�ٷ� parent�� ��������
            else {
                transplant(minRight, minRight->right); //�ƴ� ��� minright�� �� ���������� ����
                minRight->right = node->right;         //�� �ڸ����� node�� �������� ���� ��
                minRight->right->parent = minRight; //minRight�� right�� ���� �� �θ� minRight�� �ٽ� ����.
            }

            transplant(node, minRight); //node�� minRightt�� �ٲ���
            minRight->left = node->left;        //node�� ���ʰ��� minRight�� ���ʰ����� ����
            minRight->left->parent = minRight;  //���ʰ��� �θ� minRight�� ����
            minRight->color = node->color;      //color�� node�� color�� ���󰡵��� ��.
        }

        if (fixColor == BLACK)          //���� �ٲ� ������ black�� ���
            fixRemove(fixNode);         //���� ����ȭ��Ű�� ���� ������ ��ħ

        delete node;
    }

    size_t size() const {
        return getSize(root);
    }

    bool empty() const {
        return root == nullptr;
    }

private:
    void insertNode(Node* newNode) { //insertNode ����Լ� 
        Node* current = root; // ���� current�� �ּҸ� root��
        Node* parent = nullptr; // parent�� �ּҸ� �����ϱ� ���� �ʱ�ȭ.

        while (current != nullptr) { // ���� ���� ���(root)�� �ִٸ�
            parent = current; // parent�� ���� ����� �ּҷ� ����.
            if (newNode->key < current->key) // key�� ���� ���� newNode�� �� ���� ���� ��� 
                current = current->left; // ���� ������ ��Ʈ�� �̵���Ŵ.
            else
                current = current->right; // �ݴ��� ��� ������ ������ �̵�
        } // while���̹Ƿ� ������ ��尡 ���� �� ���� ���� �������� �۾��� �ݺ�.

        newNode->parent = parent; // while���� �������Ƿ� ���� current�� ���� nullptr. parent�� �������� �ִ� ��.
        //���ο� ����� �θ� ������ parent ������ ����.

        if (parent == nullptr) // ����� Ʈ���� �ƿ� ����־��� ���.
            root = newNode; // �׷� ��쿡�� root�� �� ���� ����
        else if (newNode->key < parent->key)  // ���� �� ����� key���� �θ��� key������ �۴ٸ�
            parent->left = newNode; // �������� �̵�
        else
            parent->right = newNode; // �ݴ�� ������.
    }

    void fixInsert(Node* newNode) { //fixInsert ����Լ�
        while (newNode != root && newNode->parent->color == RED) { // ���ο� ��尡 ����� Ʈ���� ������ ��尡 �ƴϰ� parent�� ���� red�� ����
            if (newNode->parent == newNode->parent->parent->left) { // �� ����� �θ� �� ����� �ҸӴ��� ������ ��� ( �� 2�� ������ �����̿��� ���)
                Node* uncle = newNode->parent->parent->right; // ���� ����� �ּҸ� �ҸӴ��� ������ �ڽ����� ����

                if (uncle != nullptr && uncle->color == RED) { //������ �����ϸ� �� ������ red�� ����
                    newNode->parent->color = BLACK; //�θ� ���� black���� ����.
                    uncle->color = BLACK; // ���� ��嵵 black���� �ٲ�.
                    newNode->parent->parent->color = RED; // �ҸӴ� ���� red�� ����.
                    newNode = newNode->parent->parent; // �� ��带 �ҸӴ� ���� ����.
                }
                else {                                          // ������ �������� �ʰų� ������ black�� ��� or �Ѵ�.
                    if (newNode == newNode->parent->right) {    // �� ��尡 ���� �θ��� �����ʿ� �ִ� ���̶��?
                        newNode = newNode->parent;              // �� ��带 parent�� �ּҷ� ����.
                        rotateLeft(newNode);                    // �������� rotate.  line 160-178
                    }

                    newNode->parent->color = BLACK;             // ���ο� ����� �θ� ����� ���� black
                    newNode->parent->parent->color = RED;       // �ҸӴ� ����� ���� red
                    rotateRight(newNode->parent->parent);       // �ҸӴ� ��� �������� �����U rotate. line 180-198
                }
            }
            else {
                Node* uncle = newNode->parent->parent->left;       //�� ����� �θ� �� ����� �ҸӴ��� �������� ��� (2�� ������ ������ �� ������)
                                                       //���� ���� �ҸӴ��� ���� �ڽ�
                if (uncle != nullptr && uncle->color == RED) {     //������ �����ϸ� red�� ���
                    newNode->parent->color = BLACK;                //�θ� black����
                    uncle->color = BLACK;                          //���̵� black����
                    newNode->parent->parent->color = RED;          //�ҸӴ� red
                    newNode = newNode->parent->parent;             //�� ��带 �ҸӴ� �ּҷ�
                }
                else {                                             //������ �������� �ʰų� black�� ���///
                    if (newNode == newNode->parent->left) {        //�� ��尡 �θ��� ���� �ڽ��� ��쿡��
                        newNode = newNode->parent;                 //�� ��带 �θ�� ����
                        rotateRight(newNode);                      //������ rotate. line 180-198
                    }
                    /////////���ݺ��� ���� �߸� ĥ�ѰŰ���.
                    newNode->parent->color = BLACK;                //�� ����� �θ��� ���� black����
                    newNode->parent->parent->color = RED;          //�ҸӴ��� ���� red
                    rotateLeft(newNode->parent->parent);           //���� rotate. line 160-178
                }
            }
        }

        root->color = BLACK; // root�� ���� black���� ��.
    }

    void rotateLeft(Node* node) {
        Node* rightChild = node->right; //���� ����� �������� ����� �ּҸ� rightchild��� �̸����� ����
        node->right = rightChild->left; // ���� ����� �������� ������ �ּ��� left�� �ּҰ����� ����

        if (rightChild->left != nullptr) //���� rightChild�� ������ ��尡 �����Ѵٸ� 
            rightChild->left->parent = node;   //�� ���� �θ��� ��忡 ���Ե� ���� �־���.

        rightChild->parent = node->parent;  // rightChild�� �θ� ������ ���� �θ��� �ּҷ� ����.

        if (node->parent == nullptr) // ���� node�� ù ��忴�ٸ�
            root = rightChild; // root�� rightChild�� �Ǵ� ��
        else if (node == node->parent->left) // else if�� else�� �θ� �����ϰ� �����ִ� ����.
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node; //rightChild�� ���ʿ� ��� �ּҸ� ����
        node->parent = rightChild; //node�� �θ� rightchild�� ����
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->right)
            node->parent->right = leftChild;
        else
            node->parent->left = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    Node* findNode(Node* node, const KeyType& key) const { //ã�� key���� ���� ��尡 �ִ��� ã�� ����
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return findNode(node->left, key);
        }
        else {
            return findNode(node->right, key);
        }
    }

    Node* findMin(Node* node) const {  // key�� �ּҰ��� ã�� ����
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left == nullptr) {
            return node;
        }

        return findMin(node->left);
    }

    void transplant(Node* oldNode, Node* newNode) { // ���� ��带 �� ���� ��ü�ϴ� ��
        if (oldNode->parent == nullptr) // oldNode�� �θ� ��尡 ���ٸ�
            root = newNode;             // root�� �� ���� 
        else if (oldNode == oldNode->parent->left) // �θ� ��尡 �ְ� oldNode�� �� ������ ���
            oldNode->parent->left = newNode;       // �� ���� ����
        else
            oldNode->parent->right = newNode;

        if (newNode != nullptr)             // newNode�� nullptr�� �ƴϸ�
            newNode->parent = oldNode->parent; // �θ� ���� ���� ���� ��������.
    }

    void fixRemove(Node* fixNode) {
        while (fixNode != root && fixNode->color == BLACK) { //���� fixNode�� �Ѹ��� �ƴϰ� ���� ���̸� �ݺ���.
            if (fixNode == fixNode->parent->left) {          //���� fixNode�� �θ� ����� �����̸�
                Node* sibling = fixNode->parent->right;      //�������� ���� ���� ����.

                if (sibling->color == RED) {            //������ �÷��� ������
                    sibling->color = BLACK;             //������ ������ �ٲٰ�
                    fixNode->parent->color = RED;       //�θ� ��带 ����� �ٲٸ�
                    rotateLeft(fixNode->parent);        //�θ� �������� left������Ʈ->�θ� �ڽ��� ��
                    sibling = fixNode->parent->right;   //������ ������ �θ��� ������ �ڽ��� �� ��.
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) { //������ �ڽĵ��� ���� black
                    sibling->color = RED;   //������ ���� �����
                    fixNode = fixNode->parent; //���� �ö󰡸鼭 ���� �ٲ���
                }
                else { //������ �ڽ��� �ϳ��� ���� ���
                    if (sibling->right->color == BLACK) { //������ �������� ���̸� 
                        sibling->left->color = BLACK;   //���ʵ� ������ ������
                        sibling->color = RED;   //������ ���� �����
                        rotateRight(sibling);      //���� ���� rightRotate�� �ϸ� �ڽ� �� �ϳ��� ������ �ڸ��� ��.
                        sibling = fixNode->parent->right;   // ������ �θ��� ���� �÷���
                    }

                    sibling->color = fixNode->parent->color;    //������ �÷��� ��ģ ����� �θ��� �÷��� �ٲ���
                    fixNode->parent->color = BLACK;             //��ģ ����� �θ��� ���� black���� 
                    sibling->right->color = BLACK;              //������ ������ �ڼ��� ���� ������ 
                    rotateLeft(fixNode->parent);                // fixnode�� �θ� �ǰ� �θ�� �ڼ��� ������ �ڼ��� ��.
                    fixNode = root;     //�Ƚ���尡 ��Ʈ�� �ּҰ��� ��
                }
            }
            else {              //fixnode�� �θ��� �����U�� ���. ������ �������� �����ϴ� �� �ܿ� ���⵵ ���� �ݴ�� ����.
                Node* sibling = fixNode->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    fixNode->parent->color = RED;
                    rotateRight(fixNode->parent);
                    sibling = fixNode->parent->left;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    fixNode = fixNode->parent;
                }
                else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = fixNode->parent->left;
                    }

                    sibling->color = fixNode->parent->color;
                    fixNode->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rotateRight(fixNode->parent);
                    fixNode = root;
                }
            }
        }

        fixNode->color = BLACK;
    }

    void clear(Node* node) {   //��������� ����
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    size_t getSize(Node* node) const { //getSize�� ��������� left�� right�� �ڽ��� ���� ���� ��� return.
        if (node == nullptr) {
            return 0;
        }

        return 1 + getSize(node->left) + getSize(node->right);
    }
};
