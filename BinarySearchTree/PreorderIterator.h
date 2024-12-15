#pragma once

#include "BaseBinaryTreeIterator.h"

template <typename T>
class PreorderIterator : public BaseBinaryTreeIterator<T> {
 public:
  PreorderIterator(BinarySearchTreeNode<T>* dummyRoot, bool begin) {
    this->parents.push(dummyRoot);
    advance();
    if (begin) {
      advance();
    }
  }

  PreorderIterator& operator++() {
    advance();
    return *this;
  }

 private:
  void advance() {
    this->curr = this->parents.top();
    this->parents.pop();

    if (this->curr->right) this->parents.push(this->curr->right);
    if (this->curr->left) this->parents.push(this->curr->left);
  }
};