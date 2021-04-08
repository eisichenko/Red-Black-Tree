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
    Node<T>* BST_insert(Node<T>*&, T, Node<T>*);
    void print_right_inorder(Node<T>*&, int);
    void balance(Node<T>*&);
    void ll_case(Node<T>*&, Node<T>*&);
    void rr_case(Node<T>*&, Node<T>*&);
    bool BST_find(Node<T>*&, T);
public:
    Node<T>* root;
    int size;

    RBTree()
    {
        root = NULL;
        size = 0;
    }

    void insert(T);
    bool find(T);
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

    if (uncle && uncle->color == RED)
    {
        grandfather->color = RED;
        uncle->color = BLACK;
        father->color = BLACK;

        balance(grandfather);
    }
    else
    {
        // LL case
        if (father->left == current_node && grandfather->left == father)
        {
            ll_case(father, grandfather);
        }
        // LR case
        else if (father->right == current_node && grandfather->left == father)
        {
            grandfather->left = current_node;

            father->right = current_node->left;
            
            current_node->left = father;

            if (father->right) father->right->parent = father;
            current_node->parent = grandfather;
            father->parent = current_node;

            ll_case(current_node, grandfather);
        }
        // RR case
        else if (father->right == current_node && grandfather->right == father)
        {
            rr_case(father, grandfather);
        }
        // RL case
        else
        {
            grandfather->right = current_node;

            father->left = current_node->right;
            
            current_node->right = father;

            if (father->left) father->left->parent = father;
            current_node->parent = grandfather;
            father->parent = current_node;

            rr_case(current_node, grandfather);
        }
    }
}

template<typename T>
void RBTree<T>::ll_case(Node<T>*& father, Node<T>*& grandfather)
{
    grandfather->left = father->right;

    father->right = grandfather;

    father->color = BLACK;

    grandfather->color = RED;

    if (!grandfather->parent)
    {
        root = father;
        father->parent = NULL;
    }
    else
    {
        (grandfather->parent->left == grandfather) ? grandfather->parent->left = father : grandfather->parent->right = father;
        father->parent = grandfather->parent;
    }

    grandfather->parent = father;

    if (grandfather->left) grandfather->left->parent = grandfather;
}

template<typename T>
void RBTree<T>::rr_case(Node<T>*& father, Node<T>*& grandfather)
{
    grandfather->right = father->left;

    father->left = grandfather;

    father->color = BLACK;
    grandfather->color = RED;

    if (!grandfather->parent)
    {
        root = father;
        father->parent = NULL;
    }
    else
    {
        (grandfather->parent->left == grandfather) ? grandfather->parent->left = father : grandfather->parent->right = father;
        father->parent = grandfather->parent;
    }

    grandfather->parent = father;

    if (grandfather->right) grandfather->right->parent = grandfather;

}

template<typename T>
bool RBTree<T>::find(T data)
{
    return BST_find(root, data);
}

template<typename T>
bool RBTree<T>::BST_find(Node<T>*& current_node, T data)
{
    if (!current_node) return false;

    if (data > current_node->data)
        return BST_find(current_node->right, data);
    else if (data < current_node->data)
        return BST_find(current_node->left, data);

    return true;
}

template<typename T>
void RBTree<T>::insert(T data)
{
    Node<T>* current_node = BST_insert(root, data, NULL);

    if (current_node)
    {
        balance(current_node);
        size++;
    }
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
