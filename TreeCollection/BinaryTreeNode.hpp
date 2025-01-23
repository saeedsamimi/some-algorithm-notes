#ifndef BINARY_TREE_NODE_HPP
#define BINARY_TREE_NODE_HPP

template <typename T, typename AD> class BinaryTree;

template <typename T, typename AD> struct BinaryTreeNode {
  using BTN = BinaryTreeNode<T, AD>;

  BinaryTreeNode(const T &data)
      : data(data), ad(), left(nullptr), right(nullptr) {}

  T data;
  AD ad;
  BTN *left;
  BTN *right;
};

#endif // BINARY_TREE_NODE_HPP