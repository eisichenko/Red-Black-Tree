#include <iostream>
#include "rb_tree.h"
#include "test.h"
#include "MyTimer.h"

using namespace std;

void test_finding(int n)
{
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

    delete tree;
}

void test_iterator(int n)
{
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

    timer.start();

    // for (auto num : *tree)
    // {
    //     if (prev != -1 && num - prev != 1)
    //     {
    //         result = false;
    //         break;
    //     }
    // }

    for (auto it = tree->begin(); it != tree->end(); it = it + 1)
    {
        if (prev != -1 && *it - prev != 1)
        {
            result = false;
            break;
        }
    }

    timer.stop();

    cout << "Iteration time over " << n << " elements: " << timer.get_time() << " seconds\n";

    result ? cout << "Verdict: OK\n" : cout << "Verdict: FAIL\n";

    delete tree;
}

int main()
{
    //test_finding(5000000);

    test_iterator(1000000);

    // RBTree<int>* tree = new RBTree<int>();

    // tree->insert(1);
    // tree->insert(2);
    // tree->insert(3);
    // tree->insert(4);
    // tree->insert(5);
    // tree->insert(6);
    // tree->insert(7);
    // tree->insert(8);
    // tree->insert(9);
    // tree->insert(10);
    // tree->insert(11);

    // //test_rb_tree(tree);

    // tree->print();

    // cout << endl;
    
    // Node<int>* cur = tree->root;

    // while (cur->right)
    // {
    //     cur = cur->right;
    // }

    // for (auto it = tree->begin(); it != tree->end(); it++)
    // {
    //     cout << *it << " ";
    // }

    // delete tree;

    cout << "\n\n";

    return 0;
}