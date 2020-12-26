#include "Tree.cpp"

int main(int argc, char* argv[])
{
    BST<int> tree;
    tree.insert(9);
    tree.insert(11);
    tree.insert(6);
    tree.insert(10);
    tree.insert(5);
    tree.insert(14);
    tree.insert(3);
    tree.insert(4);
    tree.insert(2);
    tree.insert(888);
    tree.insert(1);
    tree.insert(12);
    tree.insert(13);
    tree.insert(8);
    tree.insert(7);
    tree.contains(888);
    tree.remove(11);
    tree.remove(7);
    tree.printBFS();
    tree.save("muj_strom1.dot");

    BST<int> tree2 = tree;
    tree2.insert(0);
    tree2.insert(999);
    tree2.printBFS();
    tree2.save("muj_strom2.dot");

    return 0;
}

