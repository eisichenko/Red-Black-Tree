#include <iostream>
#include "rb_tree.h"
#include "test.h"

using namespace std;

int main()
{
    // test_finding(1000000);

    // test_iterator(1000000);

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
    tree->insert(9);
    tree->insert(10);
    tree->insert(11);

    tree->print();

    cout << endl;
    
    Node<int>* cur = tree->root;

    while (cur->right)
    {
        cur = cur->right;
    }

    for (auto it = tree->begin(); it != tree->end(); it++)
    {
        cout << *it << " ";
    }

    delete tree;

    cout << "\n\n";

    return 0;
}