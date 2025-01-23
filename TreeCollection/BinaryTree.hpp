#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "BinaryTreeIterator.hpp"
#include "BinaryTreeNode.hpp"
#include <exception>
#include <stdexcept>

struct Empty {};

template <typename T, typename AD> class BinarySearchTreeBase;

template <typename T, typename AD = Empty> class BinaryTree {
public:
  class BinaryTreeNodeWrapper;

  using BTN = BinaryTreeNode<T, AD>;
  using BTNW = BinaryTreeNodeWrapper;
  using iterator = BinaryTreeIterator<T, AD>;
  using inorder_iterator = InOrderIterator<T, AD>;
  using preorder_iterator = PreOrderIterator<T, AD>;
  using postorder_iterator = PostOrderIterator<T, AD>;

  class BinaryTreeNodeWrapper {
    friend class BinaryTree;

  protected:
    BTN *m_node;

  public:
    explicit BinaryTreeNodeWrapper(BTN *node = nullptr) : m_node(node) {}
    virtual ~BinaryTreeNodeWrapper() = default;

    bool valid() const { return m_node != nullptr; }
    AD additional_data() { return m_node->ad; }
    T data() const { return m_node->data; }
    bool has_left() { return m_node->left != nullptr; }
    BTNW left() { return BTNW(m_node->left); }
    bool has_right() { return m_node->right != nullptr; }
    BTNW right() { return BTNW(m_node->right); }

    bool operator==(const BTNW &other) const { return m_node == other.m_node; }
    bool operator!=(const BTNW &other) const { return m_node != other.m_node; }
  };

  BinaryTree() : m_size(0) {
    m_head = new BTN(T());
    m_head->right = new BTN(T());
    m_head->left = new BTN(T());
    m_head->right->right = new BTN(T());
  }

  virtual ~BinaryTree() { _delete_tree(m_head); }

  std::size_t size() const { return m_size; }

  bool empty() const { return m_size == 0; }

  BTNW root() { return BTNW(this->_root()); }

  size_t height() const { return this->_height_helper(m_head->right->left); }

  BTNW insert_root(const T &val) {
    if (!empty())
      throw std::runtime_error("Root already exists");

    this->_insert_root(val);
    return root();
  }

  BTNW insert_left(BTNW node, const T &val) {
    if (node.has_left())
      throw std::runtime_error("Node already has a left child");

    return BTNW(this->_insert_left(node.m_node, val));
  }

  BTNW insert_right(BTNW node, const T &val) {
    if (node.has_right())
      throw std::runtime_error("Node already has a right child");

    return BTNW(this->_insert_right(node.m_node, val));
  }

  void delete_node(BTNW parent, BTNW node) {
    if (!node.valid() || !parent.valid())
      throw std::runtime_error("Node/Parent is invalid");

    if (node.m_node->left && node.m_node->right)
      throw std::runtime_error("Node has two children");

    this->_delete_node(parent.m_node, node.m_node);
  }

  inorder_iterator inorder_begin() {
    if (empty())
      return inorder_end();
    inorder_iterator iter(nullptr);
    iter.push_left(this->_root_parent());
    return iter;
  }

  inorder_iterator inorder_end() {
    return inorder_iterator(this->_root_parent());
  }

  inorder_iterator rev_inorder_begin() {
    if (empty())
      return rev_inorder_end();
    inorder_iterator iter(nullptr);
    iter.m_stack.push(this->m_head);
    iter.push_right(this->_root());
    return iter;
  }

  inorder_iterator rev_inorder_end() { return inorder_iterator(m_head); }

  preorder_iterator preorder_begin() {
    if (empty())
      return preorder_end();
    preorder_iterator iter(this->_root());
    iter.m_stack.push(this->_root_parent());
    return iter;
  }

  preorder_iterator preorder_end() {
    return preorder_iterator(this->_root_parent()->right);
  }

  preorder_iterator rev_preorder_begin() {
    if (empty())
      return rev_preorder_end();
    preorder_iterator iter(nullptr);
    iter.m_stack.push(this->_root_parent());
    iter.push_right_left(this->_root());
    return iter;
  }

  preorder_iterator rev_preorder_end() {
    return preorder_iterator(this->_root_parent());
  }

  postorder_iterator postorder_begin() {
    if (empty())
      return postorder_end();
    postorder_iterator iter(nullptr);
    iter.push_left_right(this->_root_parent());
    return iter;
  }

  postorder_iterator postorder_end() {
    return postorder_iterator(this->_root_parent()->right);
  }

  postorder_iterator rev_postorder_begin() {
    if (empty())
      return rev_postorder_end();
    postorder_iterator iter(this->_root());
    iter.m_stack.push(this->m_head);
    iter.m_stack.push(this->_root_parent());
    return iter;
  }

  postorder_iterator rev_postorder_end() {
    return postorder_iterator(this->m_head->left);
  }

protected:
  virtual void _insert_root(const T &val) {
    m_head->right->left = new BTN(val);
    m_size++;
  }

  virtual BTN *_insert_left(BTN *parentNode, const T &val) {
    BTN *newNode = new BTN(val);
    parentNode->left = newNode;
    m_size++;
    return newNode;
  }

  virtual BTN *_insert_right(BTN *parentNode, const T &val) {
    BTN *newNode = new BTN(val);
    parentNode->right = newNode;
    m_size++;
    return newNode;
  }

  virtual void _delete_node(BTN *parentNode, BTN *nodeToDelete) {
    bool isLeft = nodeToDelete == parentNode->left;
    if (nodeToDelete->left || nodeToDelete->right) {
      if (isLeft)
        parentNode->left =
            nodeToDelete->left ? nodeToDelete->left : nodeToDelete->right;
      else
        parentNode->right =
            nodeToDelete->left ? nodeToDelete->left : nodeToDelete->right;
    } else {
      if (isLeft)
        parentNode->left = nullptr;
      else
        parentNode->right = nullptr;
    }
    m_size--;
    delete nodeToDelete;
  }

  BTN *_head() { return m_head; }
  BTN *_root() { return m_head->right->left; }
  BTN *_root_parent() { return m_head->right; }
  void _increase_size() { m_size++; }
  void _decrease_size() { m_size--; }

  friend class BinarySearchTreeBase<T, AD>;

private:
  BTN *m_head;
  std::size_t m_size;

  static void _delete_tree(BTN *node) {
    if (node) {
      _delete_tree(node->left);
      _delete_tree(node->right);
      delete node;
    }
  }

  size_t _height_helper(BTN *node) const {
    if (node) {
      size_t left = _height_helper(node->left);
      size_t right = _height_helper(node->right);
      return 1 + std::max(left, right);
    }
    return 0;
  }
};

template <typename T, typename AD> class BinarySearchTreeBase {
public:
  using BTN = typename BinaryTree<T, AD>::BTN;
  using BTNW = typename BinaryTree<T, AD>::BTNW;

  BinarySearchTreeBase(BinaryTree<T, AD> *bt) : bt(bt) {}

  void insert(const T &data) {
    if (bt->empty())
      bt->_insert_root(data);
    else {
      BTN *current = bt->_root();
      while (true) {
        if (data < current->data) {
          if (current->left)
            current = current->left;
          else {
            bt->_insert_left(current, data);
            break;
          }
        } else {
          if (current->right)
            current = current->right;
          else {
            bt->_insert_right(current, data);
            break;
          }
        }
      }
    }
  }

  BTNW find(const T &i) {
    BTN *current = bt->_root();
    while (current) {
      if (i == current->data)
        return BTNW(current);
      else if (i < current->data)
        current = current->left;
      else
        current = current->right;
    }
    return BTNW();
  }

  bool remove(const T &data) {
    BTN *current = bt->_root();
    BTN *parent = bt->_root_parent();
    while (current) {
      if (data == current->data) {
        this->_remove_helper(parent, current);
        return true;
      } else {
        parent = current;
        current = data > current->data ? current->right : current->left;
      }
    }
    return false;
  }

private:
  void _remove_helper(BTN *the_parent, BTN *the_node) {
    if (the_node->left && the_node->right) {
      the_parent = the_node;
      BTN *successor = the_node->right;
      while (successor->left) {
        the_parent = successor;
        successor = successor->left;
      }
      the_node->data = successor->data;
      this->_remove_helper(the_parent, successor);
    } else
      bt->_delete_node(the_parent, the_node);
  }

  BinaryTree<T, AD> *bt;
};

#endif // BINARY_TREE_HPP