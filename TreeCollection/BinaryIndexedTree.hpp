#ifndef BINARY_INDEXED_TREE_HPP
#define BINARY_INDEXED_TREE_HPP

#include "BinaryTreeNode.hpp"
#include "BinaryTree.hpp"

template<typename T>
class BinaryIndexedTree;

template <typename T> class BinaryIndexedTreeAdditionalData {
public:
  BinaryIndexedTreeAdditionalData() : leftSize(0), parent(nullptr) {}

  long left_size() const { return leftSize; }

private:
  long leftSize;
  BinaryTreeNode<T, BinaryIndexedTreeAdditionalData<T>> *parent;

	friend class BinaryIndexedTree<T>;
};

template <typename T>
class BinaryIndexedTree : public BinaryTree<T, BinaryIndexedTreeAdditionalData<T>> {
public:
  using BTN = typename BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>::BTN;

  BinaryIndexedTree() : BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>() {
    this->_head()->ad.leftSize = -1;
    this->_head()->left->ad.parent = this->_head();
    this->_root_parent()->ad.parent = this->_head();
    this->_root_parent()->right->ad.parent = this->_root_parent();
  }

  virtual ~BinaryIndexedTree() = default;

protected:
  void _insert_root(const T &val) override {
    BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>::_insert_root(val);
    this->_root()->ad.parent = this->_root_parent();
    increase_left_size(this->_root());
  }

  BTN *_insert_left(BTN *parentNode, const T &val) override {
    BTN *newNode =
        BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>::_insert_left(
            parentNode, val);
    newNode->ad.parent = parentNode;
    parentNode->ad.leftSize++;
    increase_left_size(parentNode);
    return newNode;
  }

  BTN *_insert_right(BTN *parentNode, const T &val) override {
    BTN *newNode =
        BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>::_insert_right(
            parentNode, val);
    newNode->ad.parent = parentNode;
    increase_left_size(parentNode);
    return newNode;
  }

  void _delete_node(BTN *parentNode, BTN *nodeToDelete) override {
    bool isLeftChild = parentNode->left == nodeToDelete;
    BinaryTree<T, BinaryIndexedTreeAdditionalData<T>>::_delete_node(
        parentNode, nodeToDelete);

    if (parentNode->left)
      parentNode->left->ad.parent = parentNode;
    if (parentNode->right)
      parentNode->right->ad.parent = parentNode;

    if (isLeftChild)
      parentNode->ad.leftSize--;

    decrease_left_size(parentNode);
  }

private:
  void increase_left_size(BTN *node) {
    while (node->ad.parent) {
      if (node->ad.parent->left == node)
        node->ad.parent->ad.leftSize++;
      node = node->ad.parent;
    }
  }

  void decrease_left_size(BTN *node) {
    while (node->ad.parent) {
      if (node->ad.parent->right == node)
        node->ad.parent->ad.leftSize--;
      node = node->ad.parent;
    }
  }

  void _insert_fixup(BTN *node) {
    const BTN *end = this->_root();
    BTN *parent;
    while (node != end) {
      parent = node->ad.parent;
      if (node == parent->left) {
        increase_left_size(node);
      }
      node = parent;
    }
  }
};

#endif // BINARY_INDEXED_TREE_HPP
