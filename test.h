#ifndef RB_TREE_H
#define RB_TREE_H
#endif

#include <chrono>

using namespace std::chrono;

template<typename T>
void test_rb_tree(RBTree<T>*& tree)
{
    bool result = true;

    cout << "======================\n";

    auto start = high_resolution_clock::now();

    if (tree) delete tree;

    // LL test
    tree = new RBTree<T>();

    insert_LL_test(tree);

    if (is_rb_tree(tree))
        cout << "LL test OK\n";
    else
    {
        cout << "LL test FAIL\n";
        result = false;
    }

    delete tree;

    // LR test
    tree = new RBTree<T>();

    insert_LR_test(tree);

    if (is_rb_tree(tree))
        cout << "LR test OK\n";
    else
    {
        cout << "LR test FAIL\n";
        result = false;
    }

    delete tree;

    // RR test
    tree = new RBTree<T>();
    
    insert_RR_test(tree);

    if (is_rb_tree(tree))
        cout << "RR test OK\n";
    else
    {
        cout << "RR test FAIL\n";
        result = false;
    }

    delete tree;

    // RL test
    tree = new RBTree<T>();
    
    insert_RL_test(tree);

    if (is_rb_tree(tree))
        cout << "RL test OK\n";
    else
    {
        cout << "RL test FAIL\n";
        result = false;
    }

    delete tree;

    // combined methods test
    tree = new RBTree<T>();
    
    insert_combined_test(tree);

    if (is_rb_tree(tree))
        cout << "combined methods test OK\n";
    else
    {
        cout << "combined methods test FAIL\n";
        result = false;
    }

    delete tree;

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\nTests passed in " << duration.count() / 1e6 << " seconds\n";
    (result) ? cout << "Verdict: OK\n" : cout << "Verdict: FAIL\n";
    cout << "======================\n";
}

template<typename T>
bool is_rb_tree(RBTree<T>*& tree)
{
    bool result = true;
    bool cur_result = true;

    if (tree->root->color != BLACK)
    {
        cout << "Red root!\n";
        result = false;
    }   

    cur_result = true;

    adjacent_red_nodes(tree->root, cur_result);

    if (!cur_result)
    {
        cout << "Adjacent red nodes!\n";
        result = false;
    }

    cur_result = true;
    int black_length = get_black_length(tree->root);
    black_path(tree->root, black_length, 0, cur_result);

    if (!cur_result)
    {
        cout << "Black path error\n";
        result = false;
    }

    cur_result = true;
    parent_nodes(tree->root, tree->root, cur_result);

    if (!cur_result)
    {
        cout << "Invalid parent nodes\n";
        result = false;
    }

    return result;
}

template<typename T>
void black_path(Node<T>*& current_node, int black_length, int current_len, bool& result)
{
    if (!current_node)
    {
        if (black_length != current_len)
        {
            result = false;
        }

        return;
    }

    black_path(current_node->left, black_length, (current_node->color == BLACK) ? current_len + 1 : current_len, result);
    black_path(current_node->right, black_length, (current_node->color == BLACK) ? current_len + 1 : current_len, result);
}

template<typename T>
int get_black_length(Node<T>*& current_node)
{
    if (!current_node) return 0;

    if (current_node->color == BLACK) 
        return 1 + get_black_length(current_node->left);
    
    return get_black_length(current_node->left);
}

template<typename T>
void adjacent_red_nodes(Node<T>*& current_node, bool& result)
{
    if (!current_node)
    {
        return;
    }

    if (current_node->parent && current_node->color == RED && current_node->parent->color == RED)
    {
        result = false;
        return;
    }

    adjacent_red_nodes(current_node->left, result);
    adjacent_red_nodes(current_node->right, result);
}

template<typename T>
void parent_nodes(Node<T>*& current_node, Node<T>* parent, bool& result)
{
    if (!current_node)
    {
        return;
    }

    if (current_node->parent && current_node->parent != parent)
    {
        result = false;
        return;
    }

    parent_nodes(current_node->left, current_node, result);
    parent_nodes(current_node->right, current_node, result);
}

// tests here

template<typename T>
void insert_LL_test(RBTree<T>*& tree)
{
    for (int i = 100; i >= 0; i--)
    {
        tree->insert(i);
    }
}

template<typename T>
void insert_LR_test(RBTree<T>*& tree)
{
    tree->insert(10);
    tree->insert(2);
    tree->insert(3);
}

template<typename T>
void insert_RR_test(RBTree<T>*& tree)
{
    for (int i = 0; i < 100; i++)
    {
        tree->insert(i);
    }
}

template<typename T>
void insert_RL_test(RBTree<T>*& tree)
{
    tree->insert(1);
    tree->insert(4);
    tree->insert(3);
}

template<typename T>
void insert_combined_test(RBTree<T>*& tree)
{
    tree->insert(10);
    tree->insert(5);
    tree->insert(1);
    tree->insert(3);
    tree->insert(4);
    tree->insert(6);
    tree->insert(0);
    tree->insert(12);
    tree->insert(7);
    tree->insert(8);
    tree->insert(9);
}