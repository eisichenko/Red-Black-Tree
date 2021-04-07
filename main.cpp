#include <iostream>
#include "MyArray.h"
#include <random>
#include <algorithm>
#include <vector>
#include "rb_tree.h"
#include "test.h"

using namespace std;

int main()
{
    RBTree<int>* tree = new RBTree<int>();

    int n = 10000;

    vector<int> a(n);

    for (int i = 0; i < n; i++) a[i] = i;

    random_device rd;

    mt19937 prng(rd());

    for (int test = 0; test < 1000; test++)
    {
        RBTree<int>* tree = new RBTree<int>();

        shuffle(a.begin(), a.end(), prng);

        for (int i = 0; i < n; i++)
        {
            tree->insert(a[i]);
        }

        //tree->print();

        bool res = is_rb_tree<int>(tree);

        (res) ? cout << "OK!\n" : cout << "FAIL...\n";

        if (!res) 
        {
            tree->print();
            break;
        }

        delete tree;
    }
    

    //test_rb_tree(tree);

    cout << "\n\n";

    return 0;
}