#include <iostream>
#include "rb_tree.h"
#include "test.h"

using namespace std;

int main()
{
    // test_finding(100000);

    // test_iterator(100000);

    // test_rb_tree<int>();

    RBTree<int>* tree = new RBTree<int>();

    tree->insert(1);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);
    tree->insert(8);

    tree->print();

    Node<int>* cur = tree->root;

    while (cur->right)
    {
        cur = cur->right;
    }

    for (auto it = tree->begin(cur); it != tree->end(); it--)
    {
        cout << *it << " ";
    }

    cout << endl;

    for (auto num : *tree)
    {
        cout << num << " ";
    }
    cout << endl;

    tree->clear();
    
    delete tree;

    cout << "\n\n";

    return 0;
}