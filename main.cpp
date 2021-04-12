#include <iostream>
#include "rb_tree.h"
#include "test.h"

using namespace std;

int main()
{
    //test_finding(100000);

    // test_iterator(1000000);

    // test_rb_tree<int>();

    RBTree<int>* tree = new RBTree<int>();

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
    // tree->insert(12);
    // tree->insert(13);
    // tree->insert(14);
    // tree->insert(15);

    // tree->insert(8);
    // tree->insert(5);
    // tree->insert(2);
    // tree->insert(10);
    // tree->insert(7);
    // tree->insert(6);


    tree->insert(5);
    tree->insert(10);
    tree->insert(0);
    tree->insert(2);
    tree->insert(3);
    tree->insert(4);

    // tree->insert(80);
    // tree->insert(100);
    // tree->insert(110);
    // tree->insert(50);
    // tree->insert(20);
    // tree->insert(25);
    // tree->insert(10);
    // tree->insert(105);
    // tree->insert(70);
    // tree->insert(75);
    // tree->insert(80);
    // tree->insert(104);
    // tree->insert(5);
    // tree->insert(15);
    // tree->insert(12);
    // tree->insert(17);
    // tree->insert(130);
    // tree->insert(18);

    tree->print();

    tree->remove(10);

    cout << "========\n";

    tree->print();

    cout << endl;

    if (is_rb_tree(tree)) cout << "OK\n";

    //return 0;

///////////////////////////////////////////////////

    if (tree->root)
    {
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
    }
    
    delete tree;

    cout << "\n\n";

    return 0;
}