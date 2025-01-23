#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "BinaryTree.hpp"

template <typename T> class AVLTree;

template <typename T> class AVLAdditionalData {
public:
  AVLAdditionalData() : parent(nullptr), balance_factor(0) {}

  int balanceFactor() const { return static_cast<int>(this->balance_factor); }

protected:
  friend class AVLTree<T>;

  BinaryTreeNode<T, AVLAdditionalData<T>> *parent;
  char balance_factor;
};

template <typename T>
class AVLTree : public BinaryTree<T, AVLAdditionalData<T>> {
public:
  using BTN = typename BinaryTree<T, AVLAdditionalData<T>>::BTN;

  AVLTree() : BinaryTree<T, AVLAdditionalData<T>>() {
    this->_head()->left->ad.parent = this->_head();
    this->_root_parent()->ad.parent = this->_head();
    this->_root_parent()->right->ad.parent = this->_root_parent();
  }

  virtual ~AVLTree() = default;

protected:
  void _insert_root(const T &val) override {
    BinaryTree<T, AVLAdditionalData<T>>::_insert_root(val);
    this->_root()->ad.parent = this->_root_parent();
  }

  BTN *_insert_left(BTN *parentNode, const T &val) override {
    BTN *newNode =
        BinaryTree<T, AVLAdditionalData<T>>::_insert_left(parentNode, val);
    newNode->ad.parent = parentNode;
    _insert_fixup(newNode);
    return newNode;
  }

  BTN *_insert_right(BTN *parentNode, const T &val) override {
    BTN *newNode =
        BinaryTree<T, AVLAdditionalData<T>>::_insert_right(parentNode, val);
    newNode->ad.parent = parentNode;
    _insert_fixup(newNode);
    return newNode;
  }

  void _delete_node(BTN *parentNode, BTN *nodeToDelete) override {
    bool isLeftChild = parentNode->left == nodeToDelete;
    BinaryTree<T, AVLAdditionalData<T>>::_delete_node(parentNode, nodeToDelete);

    _delete_fixup(parentNode, isLeftChild);
  }

private:
  BTN *rotate_left(BTN *n) {
    BTN *x = n->right;
    x->ad.parent = n->ad.parent;
    if (n->ad.parent->right == n)
      n->ad.parent->right = x;
    else
      n->ad.parent->left = x;
    n->right = x->left;
    if (x->left)
      x->left->ad.parent = n;
    x->left = n;
    n->ad.parent = x;

    n->ad.balance_factor =
        n->ad.balance_factor + 1 - std::min<char>(x->ad.balance_factor, 0);
    x->ad.balance_factor =
        x->ad.balance_factor + 1 + std::max<char>(n->ad.balance_factor, 0);
    return x;
  }

  BTN *rotate_right(BTN *n) {
    BTN *x = n->left;
    x->ad.parent = n->ad.parent;
    if (n->ad.parent->right == n)
      n->ad.parent->right = x;
    else
      n->ad.parent->left = x;
    n->left = x->right;
    if (x->right)
      x->right->ad.parent = n;
    x->right = n;
    n->ad.parent = x;

    n->ad.balance_factor =
        n->ad.balance_factor - 1 - std::max<char>(x->ad.balance_factor, 0);
    x->ad.balance_factor =
        x->ad.balance_factor - 1 + std::min<char>(n->ad.balance_factor, 0);
    return x;
  }

  void _insert_fixup(BTN *node) {
    const BTN *end = this->_root_parent();
    BTN *parent;
    while (node != end) {
      parent = node->ad.parent;

      if (parent != end) {
        parent->ad.balance_factor += (node == parent->left ? 1 : -1);

        if (std::abs(parent->ad.balance_factor) == 2) {
          _rebalance(parent);
          return;
        }

        if (parent->ad.balance_factor == 0)
          return;
      }

      node = parent;
    }
  }

  void _delete_fixup(BTN *node, bool isLeft) {
    const BTN *end = this->_root_parent();
    BTN *parent = node;
    while (parent != end) {
      parent->ad.balance_factor += isLeft ? -1 : 1;

      if (parent->ad.balance_factor == 2) {
        char bBalanceFactor = parent->left->ad.balance_factor;
        parent = _rebalance(parent);
        if (bBalanceFactor == 0)
          return;
      } else if (parent->ad.balance_factor == -2) {
        char bBalanceFactor = parent->right->ad.balance_factor;
        parent = _rebalance(parent);
        if (bBalanceFactor == 0)
          break;
      } else if (parent->ad.balance_factor != 0)
        break;

      node = parent;
      parent = node->ad.parent;
      isLeft = parent->left == node;
    }
  }

  BTN *_rebalance(BTN *node) {
    if (node->ad.balance_factor == 2) {
      if (node->left->ad.balance_factor >= 0) {
        return this->rotate_right(node);
      } else {
        this->rotate_left(node->left);
        return this->rotate_right(node);
      }
    } else if (node->ad.balance_factor == -2) {
      if (node->right->ad.balance_factor <= 0) {
        return this->rotate_left(node);
      } else {
        this->rotate_right(node->right);
        return this->rotate_left(node);
      }
    }
    return node;
  }
};

template <typename T>
class AVLSearchTree : public AVLTree<T>,
                      public BinarySearchTreeBase<T, AVLAdditionalData<T>> {
public:
  using BTN = typename AVLTree<T>::BTN;
  using BTNW = typename AVLTree<T>::BTNW;

  AVLSearchTree()
      : AVLTree<T>(), BinarySearchTreeBase<T, AVLAdditionalData<T>>(this) {}

  virtual ~AVLSearchTree() = default;

  BTNW insert_root(const T &val) = delete;
  BTNW insert_left(BTNW node, const T &val) = delete;
  BTNW insert_right(BTNW node, const T &val) = delete;
  void delete_node(BTNW node) = delete;
};

#endif // AVL_TREE_HPPtemplate <typename T>