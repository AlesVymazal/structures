#pragma once
#include <iostream>
#include <fstream>
#include <vector>
struct Node {
    Node(const int data);
    int data_;
    Node* right_;
    Node* left_;
};
class BST {
public:
    BST();
    BST(const BST& other);
    ~BST();
    void insert(const int data);
    void print();
    void remove(const int data);
    bool contains(const int data);
    void parentOfSmallest(Node* start);
    void save(const std::string& filename);

private:
    Node* root_ = nullptr;
    Node* tree_ = nullptr;
    Node* parent_ = nullptr;
    std::vector<Node*> currentNodes_;
    std::vector<Node*> removedNodes_;
    std::vector<std::pair<int, int> > edges_;
};