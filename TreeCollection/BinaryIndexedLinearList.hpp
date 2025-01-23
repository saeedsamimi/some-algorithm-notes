#ifndef BINARY_INDEXED_LINEAR_LIST
#define BINARY_INDEXED_LINEAR_LIST

#include "BinaryIndexedTree.hpp"
#include <stdexcept>

template <typename T>
class BinaryIndexedLinearList : public BinaryIndexedTree<T> {
public:
  using BTN = typename BinaryIndexedTree<T>::BTN;

  BinaryIndexedLinearList() : BinaryIndexedTree<T>() {}

  void insert(int idx, const T &val) {
    if (idx < 0 || idx > this->size())
      throw std::exception();

    BTN *node = get(this->_head(), idx - 1);
    if (node->right) {
      node = node->right;
      while (node->left)
        node = node->left;
      this->_insert_left(node, val);
    } else
      this->_insert_right(node, val);
  }

  T &get(int idx) {
    if (idx < 0 || idx >= this->size())
      throw std::out_of_range("The index is out of range");

    return get(this->_root(), idx).data;
  }

  void remove(int idx) {
    if (idx < 0 || idx >= this->size())
      throw std::out_of_range("The index is out of range");

    BTN *node = get(this->_root(), idx);
    if (node->left && node->right) {
      BTN *successor = node->right;
      while (successor->left)
        successor = successor->left;
      node->data = successor->data;
      node = successor;
    }

    this->_delete_node(node->ad.parent, node);
  }

private:
  BTN *get(BTN *node, int idx) {
    while (idx != node->ad.left_size()) {
      if (idx > node->ad.left_size()) {
        idx -= node->ad.left_size() + 1;
        node = node->right;
      } else
        node = node->left;
    }
    return node;
  }
};

#endif // BINARY_INDEXED_LINEAR_LIST
