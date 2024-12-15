#pragma once

#include <queue>

#include "BinarySearchTreeNode.h"
#include "InorderIterator.h"
#include "PostorderIterator.h"
#include "PreorderIterator.h"

template <typename T>
class BinarySearchTree {
 public:
  using node = BinarySearchTreeNode<T>;
  using node_ptr = node*;
  using inorder_iterator = InorderIterator<T>;
  using preorder_iterator = PreorderIterator<T>;
  using postorder_iterator = PostorderIterator<T>;

  BinarySearchTree() : _size(0), root(nullptr), dummy_root(new node(T())) {
    dummy_root->right = new node(T());
  }

  ~BinarySearchTree() {
    std::queue<node_ptr> q;
    q.push(dummy_root);

    while (!q.empty()) {
      node_ptr node = q.front();
      q.pop();

      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);

      delete node;
    }
  }

  void insert(const T& val) {
    node_ptr newNode = new node(val);
    node_ptr curr = root;
    node_ptr prev = nullptr;

    while (curr) {
      prev = curr;
      curr = val > curr->value ? curr->right : curr->left;
    }

    if (prev == nullptr) {
      root = newNode;
      dummy_root->left = root;
    } else if (val > prev->value) {
      prev->right = newNode;
    } else {
      prev->left = newNode;
    }

    _size++;
  }

  bool search(const T& val) const {
    node_ptr node = root;
    while (node && node->value != val) {
      node = val > node->value ? node->right : node->left;
    }
    return node != nullptr;
  }

  void remove(const T& val) {
    node_ptr curr = root;
    node_ptr prev = nullptr;

    while (curr && curr->value != val) {
      prev = curr;
      curr = val > curr->value ? curr->right : curr->left;
    }

    if (curr == nullptr) return;

    if (curr->left == nullptr || curr->right == nullptr) {
      node_ptr newCurr;
      newCurr = curr->left ? curr->left : curr->right;

      if (!prev) {
        root = newCurr;
        dummy_root->left = root;
      } else {
        if (curr == prev->left)
          prev->left = newCurr;
        else
          prev->right = newCurr;
        delete curr;
      }
    } else {
      node_ptr p = nullptr;
      node_ptr temp = curr->right;
      while (temp->left) {
        p = temp;
        temp = temp->left;
      }

      if (p)
        p->left = temp->right;
      else
        curr->right = temp->right;

      curr->value = temp->value;

      delete temp;
    }
    _size--;
  }

  size_t size() const { return _size; }

  size_t height() const {
    if (root == nullptr) {
      return 0;
    }

    std::queue<node_ptr> q;
    q.push(root);
    int height = -1;

    while (!q.empty()) {
      size_t levelSize = q.size();
      height++;

      while (levelSize--) {
        node_ptr node = q.front();
        q.pop();

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
      }
    }

    return height;
  }

  inorder_iterator inorder_begin() {
    return inorder_iterator(dummy_root, true);
  }

  inorder_iterator inorder_end() { return inorder_iterator(dummy_root, false); }

  preorder_iterator preorder_begin() {
    return preorder_iterator(dummy_root, true);
  }

  preorder_iterator preorder_end() {
    return preorder_iterator(dummy_root->right, false);
  }

  postorder_iterator postorder_begin() {
    return postorder_iterator(dummy_root, true);
  }

  postorder_iterator postorder_end() {
    return postorder_iterator(dummy_root->right, false);
  }

 private:
  node_ptr dummy_root;
  node_ptr root;

  size_t _size;
};