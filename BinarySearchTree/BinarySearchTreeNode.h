#pragma once

template <typename T>
struct BinarySearchTreeNode {
  BinarySearchTreeNode(const T& value)
      : value(value), left(nullptr), right(nullptr) {}

  T value;
  BinarySearchTreeNode<T>* left;
  BinarySearchTreeNode<T>* right;
};