#pragma once

#include "BaseBinaryTreeIterator.h"

template <typename T>
class InorderIterator : public BaseBinaryTreeIterator<T> {
 public:
  InorderIterator(BinarySearchTreeNode<T>* dummyRoot, bool begin) {
    if (begin) {
      push_left(dummyRoot);
      this->curr = this->parents.top();
      this->parents.pop();
    } else {
      this->curr = dummyRoot;
    }
  }

  InorderIterator& operator++() {
    push_left(this->curr->right);
    this->curr = this->parents.top();
    this->parents.pop();
    return *this;
  }

 private:
  void push_left(BinarySearchTreeNode<T>* node) {
    while (node) {
      this->parents.push(node);
      node = node->left;
    }
  }
};