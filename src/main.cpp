#include "Tree.cpp"

int main(int argc, char* argv[])
{
    BST tree;
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
    tree.print();
    tree.save("muj_strom1.dot");
    std::cout << tree.contains(11) << std::endl;
    std::cout << tree.contains(7) << std::endl;
    std::cout << tree.contains(100) << std::endl;
    std::cout << tree.contains(888) << std::endl;
    tree.remove(9);
    tree.remove(3);
    tree.remove(5);
    tree.remove(2);
    std::cout << tree.contains(3) << std::endl;
    std::cout << tree.contains(5) << std::endl;
    tree.print();
    tree.save("muj_strom2.dot");

    BST tree2 = tree;
    return 0;
}