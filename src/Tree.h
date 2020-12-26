#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <tuple>

template<typename T>
struct Node {
  Node(T data);
  T data_;
  std::unique_ptr<Node> left_;
  std::unique_ptr<Node> right_;
  ~Node();
};

template<typename T>
class BST {
public:
  BST();
  ~BST();
  BST(const BST& other);
  void insert(const T data);
  void remove(const T data);
  bool contains(const T data) const;
  void save(const std::string& filename) const;
  void printBFS() const;
  void printDFS() const;
  std::tuple<Node<T>*, Node<T>*, char, char> find(const int data) const;
private:
  Node<T>* root_;
};