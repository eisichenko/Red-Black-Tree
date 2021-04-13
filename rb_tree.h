#include <iostream>
#include "Node.h"

using namespace std;

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

template <typename T>
class RBTree
{
private:
    void print_right_inorder(Node<T>*&, int);
    void balance(Node<T>*&);
    void fix_double_black(Node<T>*&, bool);
    void ll_case(Node<T>*&, Node<T>*&);
    void rr_case(Node<T>*&, Node<T>*&);
    Node<T>* BST_find(Node<T>*&, T);
    Node<T>* BST_insert(Node<T>*&, T, Node<T>*);
    void remove(Node<T>*&);
    void right_rotate(Node<T>*&);
    void left_rotate(Node<T>*&);
public:
    Node<T>* root;
    int size;

    RBTree()
    {
        root = NULL;
        size = 0;
    }

    class NodeIterator
    {
    private:
        Node<T>* cur; 
    public:

        NodeIterator()
        {
            this->cur = NULL;
        }

        NodeIterator(Node<T>* cur)
        {
            this->cur = cur;
        }

        NodeIterator(NodeIterator* it)
        {
            this->cur = it->cur;
        }

        NodeIterator* operator++ ()
        {
            if (!cur) return NULL;

            if (cur->right)
            {
                cur = cur->right;
                
                while (cur->left)
                    cur = cur->left;
            }
            else if (cur)
            {
                Node<T>* parent = cur->parent;

                while (parent && cur == parent->right)
                {
                    cur = parent;
                    parent = parent->parent;
                }

                cur = parent;
            }
            
            return this;
        }

        NodeIterator* operator++ (int)
        {
            return operator++();
        }

        NodeIterator* operator-- ()
        {
            if (!cur) return NULL;

            if (cur->left)
            {
                cur = cur->left;
                
                while (cur->right)
                    cur = cur->right;
            }
            else if (cur)
            {
                Node<T>* parent = cur->parent;

                while (parent && cur == parent->left)
                {
                    cur = parent;
                    parent = parent->parent;
                }

                cur = parent;
            }

            return this;
        }

        NodeIterator* operator-- (int)
        {
            return operator--();
        }

        NodeIterator* operator+ (int n)
        {
            for (int i = 0; i < n && cur; i++)
                operator++();

            return this;
        }

        NodeIterator* operator- (int n)
        {
            for (int i = 0; i < n && cur; i++)
                operator--();

            return this;
        }

        NodeIterator* operator+= (int n)
        {
            return operator+(n);
        }

        NodeIterator* operator-= (int n)
        {
            return operator-(n);
        }

        bool operator== (const NodeIterator& it)
        {
            return it.cur == cur;
        }

        bool operator!= (const NodeIterator& it)
        {
            return it.cur != cur;
        }

        T operator* ()
        {
            if (cur) 
                return cur->data;
            else 
                throw runtime_error("access to null node");
        }
    };

    NodeIterator end_element = NodeIterator();

    void insert(T);
    void remove(T);
    bool find(T);
    void print();
    
    NodeIterator begin()
    {
        Node<T>* cur = root;

        while (cur->left)
            cur = cur->left;

        return NodeIterator(cur);
    }

    NodeIterator begin(Node<T>* node)
    {
        return NodeIterator(node);
    }

    NodeIterator& end()
    {
        return end_element;
    }
};

template<typename T>
void RBTree<T>::remove(T data)
{
    Node<T>* node_to_delete = BST_find(root, data);

    if (!node_to_delete) return;

    remove(node_to_delete);

    size--;
}

template<typename T>
void RBTree<T>::remove(Node<T>*& node_to_delete) 
{
    if (!node_to_delete) return;

    if (node_to_delete == root && !node_to_delete->left && !node_to_delete->right)
    {
        delete root;
        root = NULL;
        return;
    }

    // node with 2 childs
    if (node_to_delete->left && node_to_delete->right)
    {
        Node<T>* min = node_to_delete->right;

        while (min->left) min = min->left;

        T t = min->data;
        min->data = node_to_delete->data;
        node_to_delete->data = t;

        remove(min);

        return;
    }

    int childs_num = 0;
    if (node_to_delete->left) childs_num++;
    if (node_to_delete->right) childs_num++;

    // black node with 1 child
    if (node_to_delete->color == BLACK && childs_num == 1)
    {
        if (node_to_delete->left)
        {
            node_to_delete->data = node_to_delete->left->data;
            delete node_to_delete->left;
            node_to_delete->left = NULL;
        }
        else
        {
            node_to_delete->data = node_to_delete->right->data;
            delete node_to_delete->right;
            node_to_delete->right = NULL;
        }

        return;
    }

    // red node without childs
    if (node_to_delete->color == RED && childs_num == 0)
    {
        Node<T>* parent = node_to_delete->parent;
        
        if (parent->left == node_to_delete)
        {
            delete node_to_delete;
            parent->left = NULL;
        }
        else
        {
            delete node_to_delete;
            parent->right = NULL;
        }

        return;
    }

    // black node without childs
    if (node_to_delete->color == BLACK && childs_num == 0)
    {
        Node<T>* parent = node_to_delete->parent;

        bool double_black_from_left = false;

        if (node_to_delete == parent->left)
        {
            parent->left = NULL;
            double_black_from_left = true;
        }
        else
        {
            parent->right = NULL;
        }

        delete node_to_delete;

        fix_double_black(parent, double_black_from_left);
    }
}

template<typename T>
void RBTree<T>::fix_double_black(Node<T>*& parent, bool double_black_from_left)
{
    if (!parent) return;

    Node<T>* sibling = double_black_from_left ? parent->right : parent->left;

    bool sibling_is_left_child = !double_black_from_left;

    // sibling is black
    if (sibling->color == BLACK)
    {
        // LL case, s - left child, r - left or both
        if (sibling_is_left_child
            && ((sibling->left && sibling->left->color == RED)
            || (sibling->left && sibling->right && sibling->left->color == RED
                && sibling->right->color == RED)))
        {
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            
            right_rotate(parent);
        }
        // RR case, s - rigth child, r - right or both
        else if (!sibling_is_left_child
            && ((sibling->right && sibling->right->color == RED)
            || (sibling->left && sibling->right && sibling->left->color == RED
                && sibling->right->color == RED)))
        {
            sibling->right->color = sibling->color;
            sibling->color = parent->color;

            left_rotate(parent);
        }
        // LR case, s - left, r - right
        else if (sibling_is_left_child
            && sibling->right && sibling->right->color == RED)
        {
            sibling->right->color = parent->color;

            left_rotate(sibling);
            right_rotate(parent);
        }
        // RL case, s - right, r - left
        else if (!sibling_is_left_child
            && sibling->left && sibling->left->color == RED)
        {
            sibling->left->color = parent->color;

            right_rotate(sibling);
            left_rotate(parent);
        }
        // sibling is black and its both children are black
        else if ((!sibling->left || sibling->left->color == BLACK)
            && (!sibling->right || sibling->right->color == BLACK))
        {
            sibling->color = RED;
            if (parent->color == RED)
                parent->color = BLACK;
            else
                fix_double_black(parent->parent, parent->parent ? parent->parent->left == parent : false);
            return;
        }

        parent->color = BLACK;
    }
    // sibling red
    else
    {
        parent->color = RED;
        sibling->color = BLACK;

        if (sibling_is_left_child)
            right_rotate(parent);
        else
            left_rotate(parent);

        fix_double_black(parent, double_black_from_left);
    }
}

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
    return BST_find(root, data) ? 1 : 0;
}

template<typename T>
Node<T>* RBTree<T>::BST_find(Node<T>*& current_node, T data)
{
    if (!current_node) return NULL;

    if (data > current_node->data)
        return BST_find(current_node->right, data);
    else if (data < current_node->data)
        return BST_find(current_node->left, data);

    return current_node;
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

template <typename T>
void RBTree<T>::left_rotate(Node<T>*& ptr)
{
    Node<T>* right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != NULL)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

template <typename T>
void RBTree<T>::right_rotate(Node<T>*&ptr)
{
    Node<T>* left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != NULL)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}
