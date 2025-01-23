#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "BinaryTree.hpp"

template <typename T, typename AD = Empty>
class BinarySearchTree : public BinaryTree<T, AD>,
                         public BinarySearchTreeBase<T, AD> {
public:
  using BTN = typename BinaryTree<T>::BTN;
  using BTNW = typename BinaryTree<T>::BTNW;

  BinarySearchTree() : BinaryTree<T, AD>(), BinarySearchTreeBase<T, AD>(this) {}
  ~BinarySearchTree() = default;

  BTNW insert_root(const T &val) = delete;
  BTNW insert_left(BTNW node, const T &val) = delete;
  BTNW insert_right(BTNW node, const T &val) = delete;
  void delete_node(BTNW node) = delete;
};

#endif // BINARY_SEARCH_TREE_HPP