#pragma once
#include <stack>

#include "BinarySearchTreeNode.h"

template <typename T>
class BaseBinaryTreeIterator {
 public:
  const T* operator->() const { return curr->value; }

  T operator*() const { return curr->value; }

  bool operator==(const BaseBinaryTreeIterator& other) const {
    return other.curr == curr;
  }

  bool operator!=(const BaseBinaryTreeIterator& other) const {
    return other.curr != curr;
  }

 protected:
  BinarySearchTreeNode<T>* curr;
  std::stack<BinarySearchTreeNode<T>*> parents;
};