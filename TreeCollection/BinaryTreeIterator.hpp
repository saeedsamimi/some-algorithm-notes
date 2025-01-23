#ifndef BIN_TREE_ITERATOR_HPP
#define BIN_TREE_ITERATOR_HPP

// #include "BinaryTree.hpp"
#include <stack>

template <typename T, typename AD> class BinaryTree;

template <typename T, typename AD> class BinaryTreeIterator {
public:
  using BTN = typename BinaryTree<T, AD>::BTN;

  BinaryTreeIterator(BTN *node) : m_current(node) {}

  T operator*() const { return m_current->data; }
  AD additional_data() { return m_current->ad; }

  virtual ~BinaryTreeIterator() = default;

  bool operator==(const BinaryTreeIterator &other) const {
    return m_current == other.m_current;
  }
  bool operator!=(const BinaryTreeIterator &other) const {
    return m_current != other.m_current;
  }

protected:
  friend class BinaryTree<T, AD>;

  std::stack<BTN *> m_stack;
  BTN *m_current;

  void pop_top() {
    this->m_current = this->m_stack.top();
    this->m_stack.pop();
  }

  void push_left(BTN *node) {
    while (node) {
      this->m_stack.push(node);
      node = node->left;
    }
    pop_top();
  }

  void push_right(BTN *node) {
    while (node) {
      this->m_stack.push(node);
      node = node->right;
    }
    pop_top();
  }

  void push_left_right(BTN *node) {
    while (node->left || node->right) {
      this->m_stack.push(node);
      node = node->left ? node->left : node->right;
    }
    this->m_current = node;
  }

  void push_right_left(BTN *node) {
    while (node->right || node->left) {
      this->m_stack.push(node);
      node = node->right ? node->right : node->left;
    }
    this->m_current = node;
  }
};

template <typename T, typename AD>
class InOrderIterator : public BinaryTreeIterator<T, AD> {
public:
  using BTN = typename BinaryTree<T, AD>::BTN;

  InOrderIterator(BTN *node) : BinaryTreeIterator<T, AD>(node) {}

  ~InOrderIterator() = default;

  InOrderIterator &operator++() {
    this->push_left(this->m_current->right);
    return *this;
  }

  InOrderIterator &operator--() {
    this->push_right(this->m_current->left);
    return *this;
  }
};

template <typename T, typename AD>
class PreOrderIterator : public BinaryTreeIterator<T, AD> {
public:
  using BTN = typename BinaryTree<T, AD>::BTN;
  PreOrderIterator(BTN *node) : BinaryTreeIterator<T, AD>(node) {}

  ~PreOrderIterator() = default;

  PreOrderIterator &operator++() {
    if (this->m_current->left) {
      this->m_stack.push(this->m_current);
      this->m_current = this->m_current->left;
    } else if (this->m_current->right) {
      this->m_stack.push(this->m_current);
      this->m_current = this->m_current->right;
    } else {
      while (this->m_current != this->m_stack.top()->left ||
             !this->m_stack.top()->right) {
        this->m_current = this->m_stack.top();
        this->m_stack.pop();
      }
      this->m_current = this->m_stack.top()->right;
    }
    return *this;
  }

  PreOrderIterator &operator--() {
    BTN *parent = this->m_stack.top();
    if (this->m_current == parent->right && parent->left)
      this->push_right_left(parent->left);
    else {
      this->m_current = parent;
      this->m_stack.pop();
    }
    return *this;
  }
};

template <typename T, typename AD>
class PostOrderIterator : public BinaryTreeIterator<T, AD> {
public:
  using BTN = typename BinaryTree<T, AD>::BTN;

  PostOrderIterator(BTN *node) : BinaryTreeIterator<T, AD>(node) {}

  ~PostOrderIterator() = default;

  PostOrderIterator &operator++() {
    BTN *parent = this->m_stack.top();
    if (this->m_current == parent->left && parent->right)
      this->push_left_right(parent->right);
    else {
      this->m_current = parent;
      this->m_stack.pop();
    }
    return *this;
  }

  PostOrderIterator &operator--() {
    if (this->m_current->right) {
      this->m_stack.push(this->m_current);
      this->m_current = this->m_current->right;
    } else if (this->m_current->left) {
      this->m_stack.push(this->m_current);
      this->m_current = this->m_current->left;
    } else {
      while (this->m_current != this->m_stack.top()->right ||
             !this->m_stack.top()->left) {
        this->m_current = this->m_stack.top();
        this->m_stack.pop();
      }
      this->m_current = this->m_stack.top()->left;
    }
    return *this;
  }
};

#endif // BIN_TREE_ITERATOR_HPP