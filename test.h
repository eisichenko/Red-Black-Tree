#ifndef RB_TREE_H
#define RB_TREE_H
#endif

#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include "MyTimer.h"

using namespace std::chrono;

template<typename T>
void test_rb_tree()
{
    bool result = true;

    cout << "======================\n";

    auto start = high_resolution_clock::now();

    // LL test
    RBTree<T>* tree = new RBTree<T>();

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

    // 1000 random trees test
    tree = new RBTree<T>();
    
    result = insert_random_tests(tree);

    if (result)
        cout << "1000 random tests OK\n";
    else
    {
        cout << "1000 random tests FAIL\n";
        result = false;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "\nTests passed in " << duration.count() / 1e9 << " seconds\n";
    (result) ? cout << "Verdict: OK\n" : cout << "Verdict: FAIL\n";
    cout << "======================\n";
}

void test_finding(int n)
{
    cout << "======================\n";

    mt19937 generator(time(0));

    vector<int> a(n);

    cout << "Building a random tree of size: " << n << endl;

    MyTimer timer = MyTimer();

    timer.start();

    for (int i = 0; i < n; i++) a[i] = i;

    shuffle(a.begin(), a.end(), generator);

    RBTree<int>* tree = new RBTree<int>();

    for (int i = 0; i < n; i++) tree->insert(a[i]);

    timer.stop();

    cout << "Time: " << timer.get_time() << " seconds\n";

    cout << "Actual tree size: " << tree->size << endl;

    double max_time = -1;
    double min_time = 2e9;

    n = min(1000000, n);

    cout << "Finding " << n << " random elements\n";

    for (int i = 0; i < n; i++)
    {
        timer.start();

        if (!tree->find(a[i]))
        {
            cout << "Fail " << a[i] << endl;
            break;
        }

        timer.stop();

        double current_time = timer.get_time();

        if (current_time > max_time) max_time = current_time;
        if (current_time < min_time) min_time = current_time;
    }

    cout << "Max find time: " << max_time << " seconds" << endl;
    cout << "Min find time: " << min_time << " seconds" << endl;

    cout << "======================\n\n";

    delete tree;
}

void test_iterator(int n)
{
    cout << "======================\n";

    mt19937 generator(time(0));

    vector<int> a(n);

    cout << "Building a random tree of size: " << n << endl;

    MyTimer timer = MyTimer();

    timer.start();

    for (int i = 0; i < n; i++) a[i] = i;

    shuffle(a.begin(), a.end(), generator);

    RBTree<int>* tree = new RBTree<int>();

    for (int i = 0; i < n; i++) tree->insert(a[i]);

    timer.stop();

    cout << "Time: " << timer.get_time() << " seconds\n";

    cout << "Actual tree size: " << tree->size << endl;

    int prev = -1;

    bool result = true;
    bool cur_res = true;

    timer.start();

    for (auto it = tree->begin(); it != tree->end(); it = it + 1)
    {
        if (prev != -1 && *it - prev != 1)
        {
            result = false;
            cur_res = false;
            break;
        }
    }

    timer.stop();

    cout << "Acsending iteration time over " << n << " elements: " << timer.get_time() << " seconds";

    cur_res ? cout << " OK\n" : cout << " FAIL\n";
    cur_res = true;

    Node<int>* cur = tree->root;

    while (cur->right)
    {
        cur = cur->right;
    }

    timer.start();

    prev = n;

    for (auto it = tree->begin(cur); it != tree->end(); it--)
    {
        if (prev != n && *it - prev != -1)
        {
            result = false;
            cur_res = false;
            break;
        }
    }

    timer.stop();

    cout << "Descending iteration time over " << n << " elements: " << timer.get_time() << " seconds";

    cur_res ? cout << " OK\n" : cout << " FAIL\n";
    cur_res = true;

    prev = -1;

    timer.start();

    for (auto num : *tree)
    {
        if (prev != -1 && num - prev != 1)
        {
            result = false;
            cur_res = false;
            break;
        }
    }

    timer.stop();

    cout << "Foreach iteration time over " << n << " elements: " << timer.get_time() << " seconds";

    cur_res ? cout << " OK\n" : cout << " FAIL\n";

    result ? cout << "Verdict: OK\n" : cout << "Verdict: FAIL\n\n";

    cout << "======================\n\n";

    delete tree;
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

template<typename T>
bool insert_random_tests(RBTree<T>*& tree)
{
    if (tree) delete tree;

    mt19937 generator(time(0));

    int n = 1000;

    bool res = true;

    uniform_int_distribution<int> uid(1, n); 

    vector<int> a(n);

    for (int i = 0; i < n; i++) a[i] = i;

    for (int test = 0; test < 1000; test++)
    {
        int current_size = uid(generator);

        tree = new RBTree<int>();

        shuffle(a.begin(), a.end(), generator);

        for (int i = 0; i < current_size; i++)
        {
            tree->insert(a[i]);
        }

        res = is_rb_tree<int>(tree);

        delete tree;
    }

    return res;
}