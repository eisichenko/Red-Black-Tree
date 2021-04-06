#include <iostream>
#include "MyArray.h"
#include "rb_tree.h"

using namespace std;

int main()
{
    RBTree<int> tree = RBTree<int>();

    tree.insert(123);
    tree.insert(55);
    tree.insert(1222);
    tree.insert(1213);
    tree.insert(13);
    tree.insert(99);

    tree.print();

    return 0;
}