#ifndef PURE_AVL_SEARCH_TREE_HPP
#define PURE_AVL_SEARCH_TREE_HPP

#include <algorithm>
#include <ostream>

template <typename T> class PureAVLSearchTree;
template <typename T> class PureAVLSearchTreeTest;

template <typename T> class PureAVLSearchTreeNode {
protected:
  PureAVLSearchTreeNode(const T &data, PureAVLSearchTreeNode<T> *nil)
      : data(data), right(nil), left(nil), bf(0) {}

  friend class PureAVLSearchTree<T>;
  friend class PureAVLSearchTreeTest<T>;

  char bf;
  PureAVLSearchTreeNode<T> *right;
  PureAVLSearchTreeNode<T> *left;
  T data;
};

template <typename T> class PureAVLSearchTree {
public:
  using PAVSTN = PureAVLSearchTreeNode<T>;
  PureAVLSearchTree() : m_size(0), m_nil_sentinel(new PAVSTN(T(), nullptr)) {
    m_nil_sentinel->left = m_nil_sentinel->right = m_nil_sentinel;
  }

  ~PureAVLSearchTree() { 
		delete_sub_tree(m_nil_sentinel->left);
		delete m_nil_sentinel;
	}

  size_t size() const { return m_size; }

  bool empty() const { return m_size == 0; }

  bool insert(const T &data) {
    if (empty()) {
      insert_root(data);
      return true;
    }
    if (insert_helper(&m_nil_sentinel->left, data)) {
      m_size++;
      return true;
    }
    return false;
  }

private:
  size_t m_size;
  PAVSTN *m_nil_sentinel;

  constexpr bool exists(const PAVSTN *n) const { return n != m_nil_sentinel; }

  constexpr PAVSTN *root() const { return m_nil_sentinel->left; }

  void insert_root(const T &data) {
    m_nil_sentinel->left = new PAVSTN(data, m_nil_sentinel);
    m_size = 1;
  }

  PAVSTN *insert_helper(PAVSTN **node, const T &data) {
    PAVSTN *cn = m_nil_sentinel;

    if (data > (*node)->data) {
      if (exists((*node)->right)) {
        cn = insert_helper(&(*node)->right, data);
      } else {
        (*node)->right = cn = new PAVSTN(data, m_nil_sentinel);
      }

      if (exists(cn)) {
        (*node)->bf--;
        if ((*node)->bf == -2) {
          if ((*node)->right->bf <= 0) {
            *node = rotate_left(*node);
          } else {
            (*node)->right = rotate_right((*node)->right);
            *node = rotate_left(*node);
          }
        }
        if ((*node)->bf == 0)
          cn = m_nil_sentinel;
      }
    } else if (data < (*node)->data) {
      if (exists((*node)->left)) {
        cn = insert_helper(&(*node)->left, data);
      } else {
        (*node)->left = cn = new PAVSTN(data, m_nil_sentinel);
      }

      if (exists(cn)) {
        (*node)->bf++;
        if ((*node)->bf == 2) {
          if ((*node)->left->bf >= 0) {
            *node = rotate_right(*node);
          } else {
            (*node)->left = rotate_left((*node)->left);
            *node = rotate_right(*node);
          }
        }
        if ((*node)->bf == 0)
          cn = m_nil_sentinel;
      }
    }

    return cn;
  }

  PAVSTN *rebalance(PAVSTN *node) {
    if (node->bf == 2) {
      if (node->left->bf >= 0) {
        node = rotate_right(node);
      } else {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
      }
    } else if (node->bf == -2) {
      if (node->right->bf <= 0) {
        node = rotate_left(node);
      } else {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
      }
    }
    return node;
  }

  PAVSTN *rotate_left(PAVSTN *node) {
    PAVSTN *right = node->right;
    node->right = right->left;
    right->left = node;

    node->bf = node->bf + 1 - std::min<char>(right->bf, 0);
    right->bf = right->bf + 1 + std::max<char>(node->bf, 0);
    return right;
  }

  PAVSTN *rotate_right(PAVSTN *node) {
    PAVSTN *left = node->left;
    node->left = left->right;
    left->right = node;

    node->bf = node->bf - 1 - std::max<char>(left->bf, 0);
    left->bf = left->bf - 1 + std::min<char>(node->bf, 0);
    return left;
  }

  void delete_sub_tree(PureAVLSearchTreeNode<T> *node) {
    if (exists(node)) {
      delete_sub_tree(node->left);
      delete_sub_tree(node->right);
      delete node;
    }
  }

  friend class PureAVLSearchTreeTest<T>;
};

template <typename T> struct PureAVLSearchTreeTestNode {
  T data;
  char bf;

  bool operator==(const PureAVLSearchTreeTestNode<T> &node) const {
    return node.data == data && node.bf == bf;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const PureAVLSearchTreeTestNode<T> &node) {
    return os << '{' << node.data << ',' << static_cast<int>(node.bf) << '}';
  }
};

template <typename T> class PureAVLSearchTreeTest {
public:
  PureAVLSearchTreeTest(PureAVLSearchTree<T> *tree) : tree(tree) {}

  void perorder_iteration(std::vector<PureAVLSearchTreeTestNode<T>> &out) {
    out.clear();
    preorder_iteration_helper(tree->root(), out);
  }

  std::pair<size_t, bool> height() {
    bool isValid = true;
    size_t h = _height(tree->root(), isValid);
    return std::make_pair(h, isValid);
  }

  void set_tree(PureAVLSearchTree<T> *new_tree) { tree = new_tree; }

  PureAVLSearchTree<T> *get_tree() { return tree; }

  void delete_tree() {
    delete tree;
    tree = nullptr;
  }

private:
  PureAVLSearchTree<T> *tree;

  void
  preorder_iteration_helper(PureAVLSearchTreeNode<T> *node,
                            std::vector<PureAVLSearchTreeTestNode<T>> &out) {
    if (tree->exists(node)) {
      out.push_back({node->data, node->bf});
      preorder_iteration_helper(node->left, out);
      preorder_iteration_helper(node->right, out);
    }
  }

  size_t _height(const PureAVLSearchTreeNode<T> *node, bool &valid) {
    if (tree->exists(node)) {
      size_t hl = _height(node->left, valid);
      size_t hr = _height(node->right, valid);
      if (hl - hr != node->bf)
        valid = false;
      return std::max(hr, hl) + 1;
    }
    return 0;
  }
};

#endif // PURE_AVL_SEARCH_TREE_HPP