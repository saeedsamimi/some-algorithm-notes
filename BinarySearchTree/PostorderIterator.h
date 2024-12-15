#pragma once

#include "BaseBinaryTreeIterator.h"

template <typename T>
class PostorderIterator : public BaseBinaryTreeIterator<T> {
 public:
  PostorderIterator(BinarySearchTreeNode<T>* dummyRoot, bool begin) {
    if (begin) {
      push_left(dummyRoot);
      advance();
    } else {
      this->curr = dummyRoot;
    }
  }

  PostorderIterator& operator++() {
    advance();
    return *this;
  }

 private:
  void push_left(BinarySearchTreeNode<T>* node) {
    while (node) {
      this->parents.push(node);
      node = node->left;
    }
  }

  void advance() {
    BinarySearchTreeNode<T>* parent = this->parents.top();

    if (parent->left == this->curr) {
      while (parent->right) {
        push_left(parent->right);
        parent = this->parents.top();
      }
    }

    this->curr = parent;
    this->parents.pop();
  }
};