#include <iostream>

using namespace std;

enum Color
{
    RED,
    BLACK
};

template<typename T>
void print_white(T data)
{
    cout << ("\033[1;37m" + to_string(data) + "\033[0m");
}

template<typename T>
void print_red(T data)
{
    cout << ("\033[1;31m" + to_string(data) + "\033[0m");
}

template<typename T>
class Node
{
public:
    T data;
    Color color;
    
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = RED;
    }
};

template <typename T>
class RBTree
{
private:
    Node<T>* root;

    Node<T>* BST_insert(Node<T>*&, T, Node<T>*);
    void print_right_inorder(Node<T>*&, int);
    void balance(Node<T>*&);
public:
    RBTree()
    {
        root = NULL;
    }

    void insert(T);
    void print();
};

template<typename T>
void RBTree<T>::balance(Node<T>*& current_node)
{
    if (current_node == root)
    {
        current_node->color = BLACK;
        return;
    }

    if (current_node->parent->color == BLACK)
        return;

    Node<int>* father = current_node->parent;
    Node<int>* grandfather = father->parent;
    Node<int>* uncle = (father == grandfather->left) ? grandfather->right : grandfather->left;
}

template<typename T>
void RBTree<T>::insert(T data)
{
    Node<T>* current_node = BST_insert(root, data, NULL);

    if (current_node)
        balance(current_node);
}

template <typename T>
Node<T>* RBTree<T>::BST_insert(Node<T>*& current_node, T data, Node<T>* parent)
{
    if (!current_node)
    {
        current_node = new Node<T>(data);
        current_node->parent = parent;
        return current_node;
    }

    if (data > current_node->data)
        return BST_insert(current_node->right, data, current_node);
    else if (data < current_node->data)
        return BST_insert(current_node->left, data, current_node);

    return NULL;
}

template <typename T>
void RBTree<T>::print()
{
    print_right_inorder(root, 0);
}

template <typename T>
void RBTree<T>::print_right_inorder(Node<T>*& node, int indent)
{
    if (!node) return;

    print_right_inorder(node->right, indent + 1);

    for (int i = 0; i < indent; i++)
        cout << '\t';

    if (node->color == RED)
        print_red(node->data);
    else
        print_white(node->data);

    cout << "\n";

    print_right_inorder(node->left, indent + 1);
}
