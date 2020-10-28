#include "Tree.h"

Node::Node(const int data)
    : data_(data)
    , right_(nullptr)
    , left_(nullptr)
{
}

BST::BST()
    : root_(nullptr)
    , tree_(nullptr)
    , parent_(nullptr)
{
}
BST::BST(const BST& other)
{
    Node* root_ = other.root_;
    Node* tree_ = other.tree_;
}
BST::~BST()
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
void BST::insert(const int data)
{
    if (!root_) {
        root_ = new Node(data);
        return;
    }
    if (root_) {
        tree_ = root_;
        while (true) {
            if (tree_->data_ < data) {
                if (tree_->right_) {
                    tree_ = tree_->right_;
                    continue;
                }
                tree_->right_ = new Node(data);
                return;
            }
            else {
                if (tree_->left_) {
                    tree_ = tree_->left_;
                    continue;
                }
                tree_->left_ = new Node(data);
                return;
            }
        }
    }
}
void BST::print()
{
	edges_.clear();
    tree_ = root_;
    currentNodes_ = { tree_ };
    int size = 1;
    for (int i = 0; i < size; ++i) {
        if (currentNodes_[i]->right_ && currentNodes_[i]->left_) {
            currentNodes_.push_back(currentNodes_[i]->right_);
            currentNodes_.push_back(currentNodes_[i]->left_);
            edges_.push_back(std::make_pair(i, size++));
            edges_.push_back(std::make_pair(i, size++));
            std::cout << i << ". Node, Value - " << currentNodes_[i]->data_ << ". Points to right " << currentNodes_[i]->right_->data_ << " and left " << currentNodes_[i]->left_->data_ << std::endl;
            continue;
        }

        if (currentNodes_[i]->right_) {
            currentNodes_.push_back(currentNodes_[i]->right_);
            edges_.push_back(std::make_pair(i, size++));
            std::cout << i << ". Node, Value - " << currentNodes_[i]->data_ << ". Points to right " << currentNodes_[i]->right_->data_ << std::endl;
            continue;
        }
        if (currentNodes_[i]->left_) {
            currentNodes_.push_back(currentNodes_[i]->left_);
            edges_.push_back(std::make_pair(i, size++));
            std::cout << i << ". Node, Value - " << currentNodes_[i]->data_ << ". Points to left " << currentNodes_[i]->left_->data_ << std::endl;
            continue;
        }
        if (!currentNodes_[i]->left_ || !currentNodes_[i]->right_) {
            std::cout << i << ". Node, Value - " << currentNodes_[i]->data_ << ". Leaf Node " << std::endl;
            continue;
        }
    }
}
void BST::remove(const int data)
{

    if (!root_) {
        std::cout << "No value in tree_" << std::endl;
        return;
    }
    if (root_) {
        bool firstTime = true;
        tree_ = root_;
        while (true) {
            if (tree_->data_ == data) {
                if (firstTime) {
                    if (root_->left_ && root_->right_) {
                        parentOfSmallest(root_);
                        if (root_->data_ == parent_->data_) {
                            //removedNodes_.push_back(root_);
                            root_->data_ = parent_->right_->data_;
                            parent_->right_ = nullptr;
                            return;
                        }
                        else {
                            root_->data_ = parent_->left_->data_;
                            removedNodes_.push_back(parent_->left_);
                            parent_->left_ = nullptr;
                            return;
                        }
                    }
                    if (root_->left_ || root_->right_) {
                        if (root_->left_) {
                            root_ = root_->left_;
                            return;
                        }
                        if (root_->right_) {
                            root_ = root_->right_;
                            return;
                        }
                    }
                    else {
                        root_ = nullptr;
                    }
                }
                else {
                    if (tree_->left_ && tree_->right_) {
                        parentOfSmallest(tree_);
                        if (tree_->data_ == parent_->data_) {
                            removedNodes_.push_back(parent_->right_);
                            tree_->data_ = parent_->right_->data_;
                            parent_->right_ = nullptr;
                            return;
                        }
                        else {
                            removedNodes_.push_back(parent_->left_);
                            tree_->data_ = parent_->left_->data_;
                            parent_->left_ = nullptr;
                            return;
                        }
                    }
                    if (tree_->left_ || tree_->right_) {
                        if (tree_->left_) {
                            removedNodes_.push_back(parent_->left_);
                            parent_->left_ = tree_->left_;
                            return;
                        }
                        if (tree_->right_) {
                            removedNodes_.push_back(parent_->right_);
                            parent_->right_ = tree_->right_;
                            return;
                        }
                    }
                    else {
                        if (parent_->left_) {
                            removedNodes_.push_back(parent_->left_);
                            parent_->left_ = nullptr;
                            return;
                        }
                        if (parent_->right_) {
                            removedNodes_.push_back(parent_->right_);
                            parent_->right_ = nullptr;
                            return;
                        }
                    }
                }
            }
            firstTime = false;
            if (tree_->data_ < data) {
                if (tree_->right_) {
                    parent_ = tree_;
                    tree_ = tree_->right_;
                    continue;
                }
            }
            if (tree_->data_ > data) {
                if (tree_->left_) {
                    parent_ = tree_;
                    tree_ = tree_->left_;
                    continue;
                }
            }
        }
    }
}
bool BST::contains(const int data)
{
    tree_ = root_;
    currentNodes_ = { tree_ };
    int size = 1;
    for (int i = 0; i < size; ++i) {
        if (currentNodes_[i]->right_ && currentNodes_[i]->left_) {
            currentNodes_.push_back(currentNodes_[i]->right_);
            currentNodes_.push_back(currentNodes_[i]->left_);
            ++size;
            ++size;
            continue;
        }
        if (currentNodes_[i]->right_) {
            currentNodes_.push_back(currentNodes_[i]->right_);
            ++size;

            continue;
        }
        if (currentNodes_[i]->left_) {
            currentNodes_.push_back(currentNodes_[i]->left_);
            ++size;
            continue;
        }
    }
    for (auto N : currentNodes_) {
        if (N->data_ == data) {
            return true;
        };
    }
    return false;
}

void BST::parentOfSmallest(Node* start)
{
    Node* subtree = start->right_;
    parent_ = start->right_;
    if (subtree->left_) {
        while (subtree->left_) {
            if (subtree->left_->data_ < parent_->data_) {
                parent_ = subtree;
            }
            subtree = subtree->left_;
        }
    }
    else {
        parent_ = start;
    }
}
void BST::save(const std::string& filename)
{
    std::ofstream file;
    file.open(filename);
    file << "digraph D {\n";
    file << "\tlabel = \"Binary tree\";\n";
    file << "\tlabelloc = \"t\";\n";
    for (int i = 0; i < currentNodes_.size(); ++i) {
        file << "\tnode" << i << " [shape=circle, label=" << currentNodes_[i]->data_ << "]\n";
    }
    for (auto edge : edges_) {
        file << "\tnode" << edge.first << " -> "
             << "node" << edge.second << "\n";
    }
    file << "}\n";
    file.close();
    edges_.clear();
}
