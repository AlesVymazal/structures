#include <iostream>
#include <fstream>
#include <vector>

struct Node {
    Node(const int data)
    {
        this->data = data;
    }

    int data;
    Node* right = nullptr;
    Node* left = nullptr;
};

class BST {
public:
    ~BST()
    {
        if (root_) {
            for (auto node : currentNodes_) {
                delete node;
            }
            for (auto node : removedNodes_) {
                delete node;
            }
        }
    }
    void insert(const int data)
    {
        if (!root_) {
            root_ = new Node(data);
            return;
        }
        if (root_) {
            tree_ = root_;
            while (true) {
                if (tree_->data < data) {
                    if (tree_->right) {
                        tree_ = tree_->right;
                        continue;
                    }
                    tree_->right = new Node(data);
                    return;
                }
                else {
                    if (tree_->left) {
                        tree_ = tree_->left;
                        continue;
                    }
                    tree_->left = new Node(data);
                    return;
                }
            }
        }
    }
    void print()
    {
        tree_ = root_;
        currentNodes_ = { tree_ };
        int size = 1;
        for (int i = 0; i < size; ++i) {
            if (currentNodes_[i]->right && currentNodes_[i]->left) {
                currentNodes_.push_back(currentNodes_[i]->right);
                currentNodes_.push_back(currentNodes_[i]->left);
                edges_.push_back(std::make_pair(i, size++));
                edges_.push_back(std::make_pair(i, size++));
                std::cout << i << ". Node, Value - " << currentNodes_[i]->data << ". Points to right " << currentNodes_[i]->right->data << " and left " << currentNodes_[i]->left->data << std::endl;
                continue;
            }

            if (currentNodes_[i]->right) {
                currentNodes_.push_back(currentNodes_[i]->right);
                edges_.push_back(std::make_pair(i, size++));
                std::cout << i << ". Node, Value - " << currentNodes_[i]->data << ". Points to right " << currentNodes_[i]->right->data << std::endl;
                continue;
            }
            if (currentNodes_[i]->left) {
                currentNodes_.push_back(currentNodes_[i]->left);
                edges_.push_back(std::make_pair(i, size++));
                std::cout << i << ". Node, Value - " << currentNodes_[i]->data << ". Points to left " << currentNodes_[i]->left->data << std::endl;
                continue;
            }
            if (!currentNodes_[i]->left || !currentNodes_[i]->right) {
                std::cout << i << ". Node, Value - " << currentNodes_[i]->data << ". Leaf Node " << std::endl;
                continue;
            }
        }
    }
    void remove(const int data)
    {

        if (!root_) {
            std::cout << "No value in tree_" << std::endl;
            return;
        }
        if (root_) {
            bool firstTime = true;
            tree_ = root_;
            while (true) {
                if (tree_->data == data) {
                    if (firstTime) {
                        if (root_->left && root_->right) {
                            parentOfSmallest(root_);
                            if (root_->data == parent_->data) {
                                //removedNodes_.push_back(root_);
                                root_->data = parent_->right->data;
                                parent_->right = nullptr;
                                return;
                            }
                            else {
                                root_->data = parent_->left->data;
                                removedNodes_.push_back(parent_->left);
                                parent_->left = nullptr;
                                return;
                            }
                        }
                        if (root_->left || root_->right) {
                            if (root_->left) {
                                root_ = root_->left;
                                return;
                            }
                            if (root_->right) {
                                root_ = root_->right;
                                return;
                            }
                        }
                        else {
                            root_ = nullptr;
                        }
                    }
                    else {
                        if (tree_->left && tree_->right) {
                            parentOfSmallest(tree_);
                            if (tree_->data == parent_->data) {
                                removedNodes_.push_back(parent_->right);
                                tree_->data = parent_->right->data;
                                parent_->right = nullptr;
                                return;
                            }
                            else {
                                removedNodes_.push_back(parent_->left);
                                tree_->data = parent_->left->data;
                                parent_->left = nullptr;
                                return;
                            }
                        }
                        if (tree_->left || tree_->right) {
                            if (tree_->left) {
                                removedNodes_.push_back(parent_->left);
                                parent_->left = tree_->left;
                                return;
                            }
                            if (tree_->right) {
                                removedNodes_.push_back(parent_->right);
                                parent_->right = tree_->right;
                                return;
                            }
                        }
                        else {
                            if (parent_->left) {
                                removedNodes_.push_back(parent_->left);
                                parent_->left = nullptr;
                                return;
                            }
                            if (parent_->right) {
                                removedNodes_.push_back(parent_->right);
                                parent_->right = nullptr;
                                return;
                            }
                        }
                    }
                }
                firstTime = false;
                if (tree_->data < data) {
                    if (tree_->right) {
                        parent_ = tree_;
                        tree_ = tree_->right;
                        continue;
                    }
                }
                if (tree_->data > data) {
                    if (tree_->left) {
                        parent_ = tree_;
                        tree_ = tree_->left;
                        continue;
                    }
                }
            }
        }
    }
    bool contains(const int data)
    {
        tree_ = root_;
        currentNodes_ = { tree_ };
        int size = 1;
        for (int i = 0; i < size; ++i) {
            if (currentNodes_[i]->right && currentNodes_[i]->left) {
                currentNodes_.push_back(currentNodes_[i]->right);
                currentNodes_.push_back(currentNodes_[i]->left);
                ++size;
                ++size;
                continue;
            }
            if (currentNodes_[i]->right) {
                currentNodes_.push_back(currentNodes_[i]->right);
                ++size;

                continue;
            }
            if (currentNodes_[i]->left) {
                currentNodes_.push_back(currentNodes_[i]->left);
                ++size;
                continue;
            }
        }
        for (auto N : currentNodes_) {
            if (N->data == data) {
                return true;
            };
        }
        return false;
    }

    void parentOfSmallest(Node* start)
    {
        Node* subtree = start->right;
        parent_ = start->right;
        if (subtree->left) {
            while (subtree->left) {
                if (subtree->left->data < parent_->data) {
                    parent_ = subtree;
                }
                subtree = subtree->left;
            }
        }
        else {
            parent_ = start;
        }
    }
    void save(std::string filename)
    {
        std::ofstream file;
        file.open(filename);
        file << "digraph D {\n";
        file << "\tlabel = \"Binary tree_\";\n";
        file << "\tlabelloc = \"t\";\n";
        for (int i = 0; i < currentNodes_.size(); ++i) {
            file << "\tnode" << i << " [shape=circle, label=" << currentNodes_[i]->data << "]\n";
        }
        for (auto edge : edges_) {
            file << "\tnode" << edge.first << " -> "
                 << "node" << edge.second << "\n";
        }
        file << "}\n";
        file.close();
        edges_.clear();
    }

    Node* root_ = nullptr;
    Node* tree_ = nullptr;
    Node* parent_ = nullptr;
    std::vector<Node*> currentNodes_;
    std::vector<Node*> removedNodes_;
    std::vector<std::pair<int, int> > edges_;
};

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
    return 0;
}
