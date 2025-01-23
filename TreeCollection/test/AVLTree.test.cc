#include "gmock/gmock-matchers.h"
#include <gtest/gtest.h>
#include "../AVLTree.hpp"
#include "../PureAVLSearchTree.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <ostream>
#include <tuple>
#include <vector>

template <typename T> void AVLTreeHeightCheck(const AVLTree<T> &tree) {
  size_t height = tree.height();
  ASSERT_LE(height, 1.45 * std::log2(tree.size()));
  ASSERT_GE(height, std::log2(tree.size()));
}

template <typename T>
void checkPreorderAVLTree(AVLTree<T> &tree, std::vector<T> expected_data,
                          std::vector<char> expected_bf) {
  std::vector<T> actual_data;
  std::vector<char> actual_bf;

  for (auto it = tree.preorder_begin(); it != tree.preorder_end(); ++it) {
    actual_data.push_back(*it);
    actual_bf.push_back(it.additional_data().balanceFactor());
  }

  EXPECT_THAT(actual_data, ::testing::ContainerEq(expected_data));
  EXPECT_THAT(actual_bf, ::testing::ContainerEq(expected_bf));
}

#define AVL_TREE_BASIC_INSERT_CHECK                                            \
  checkPreorderAVLTree(tree, {'b', 'a', 'c'}, {0, 0, 0})

TEST(AVLTreeBasicInsert, insertRR) {
  AVLTree<char> tree;
  auto root = tree.insert_root('a');
  auto right = tree.insert_right(root, 'b');
  tree.insert_right(right, 'c');

  AVL_TREE_BASIC_INSERT_CHECK;
}

TEST(AVLTreeBasicInsert, insertLL) {
  AVLTree<char> tree;
  auto root = tree.insert_root('c');
  auto right = tree.insert_left(root, 'b');
  tree.insert_left(right, 'a');

  AVL_TREE_BASIC_INSERT_CHECK;
}

TEST(AVLTreeBasicInsert, insertRL) {
  AVLTree<char> tree;
  auto root = tree.insert_root('a');
  auto right = tree.insert_right(root, 'c');
  tree.insert_left(right, 'b');

  AVL_TREE_BASIC_INSERT_CHECK;
}

TEST(AVLTreeBasicInsert, insertLR) {
  AVLTree<char> tree;
  auto root = tree.insert_root('c');
  auto right = tree.insert_left(root, 'a');
  tree.insert_right(right, 'b');

  AVL_TREE_BASIC_INSERT_CHECK;
}

TEST(AVLTreeBasicDelete, deleteLn1) {
  AVLTree<char> tree;
  auto root = tree.insert_root('b');
  auto left = tree.insert_left(root, 'a');
  auto right = tree.insert_right(root, 'c');
  tree.insert_right(right, 'd');

  tree.delete_node(root, left);

  checkPreorderAVLTree(tree, {'c', 'b', 'd'}, {0, 0, 0});
}

TEST(AVLTreeBasicDelete, deleteR1) {
  AVLTree<char> tree;
  auto root = tree.insert_root('c');
  auto left = tree.insert_left(root, 'b');
  auto right = tree.insert_right(root, 'd');
  tree.insert_left(left, 'a');

  tree.delete_node(root, right);

  checkPreorderAVLTree(tree, {'b', 'a', 'c'}, {0, 0, 0});
}

TEST(AVLTreeBasicDelete, deleteL1) {
  AVLTree<char> tree;
  auto root = tree.insert_root('b');
  auto left = tree.insert_left(root, 'a');
  auto right = tree.insert_right(root, 'd');
  tree.insert_left(right, 'c');

  tree.delete_node(root, left);

  checkPreorderAVLTree(tree, {'c', 'b', 'd'}, {0, 0, 0});
}

TEST(AVLTreeBasicDelete, deleteRMinus1) {
  AVLTree<char> tree;
  auto root = tree.insert_root('c');
  auto left = tree.insert_left(root, 'a');
  auto right = tree.insert_right(root, 'd');
  tree.insert_right(left, 'b');

  tree.delete_node(root, right);

  checkPreorderAVLTree(tree, {'b', 'a', 'c'}, {0, 0, 0});
}

TEST(AVLTreeComplexDelete, delete2LMinus1) {
  AVLTree<char> tree;
  auto c = tree.insert_root('c');
  auto b = tree.insert_left(c, 'b');
  auto e = tree.insert_right(c, 'e');
  auto a = tree.insert_left(b, 'a');
  tree.insert_left(e, 'd');
  auto f = tree.insert_right(e, 'f');
  tree.insert_right(f, 'g');

  tree.delete_node(b, a);

  checkPreorderAVLTree(tree, {'e', 'c', 'b', 'd', 'f', 'g'},
                       {0, 0, 0, 0, -1, 0});
}

TEST(AVLTreeComplexDelete, delete2R1) {
  AVLTree<char> tree;
  auto e = tree.insert_root('e');
  auto c = tree.insert_left(e, 'c');
  auto f = tree.insert_right(e, 'f');
  auto b = tree.insert_left(c, 'b');
  tree.insert_right(c, 'd');
  auto g = tree.insert_right(f, 'g');
  tree.insert_left(b, 'a');

  tree.delete_node(f, g);

  checkPreorderAVLTree(tree, {'c', 'b', 'a', 'e', 'd', 'f'},
                       {0, 1, 0, 0, 0, 0});
}

TEST(AVLTreeMoreComplexDelete, delete2L1) {
  AVLTree<char> tree;
  // root
  auto e = tree.insert_root('e');
  // level 2
  auto c = tree.insert_left(e, 'c');
  auto j = tree.insert_right(e, 'j');
  // level 3
  auto a = tree.insert_left(c, 'a');
  auto d = tree.insert_right(c, 'd');
  auto h = tree.insert_left(j, 'h');
  auto k = tree.insert_right(j, 'k');
  // level 4
  auto b = tree.insert_right(a, 'b');
  auto g = tree.insert_left(h, 'g');
  auto i = tree.insert_right(h, 'i');
  auto l = tree.insert_right(k, 'l');
  // level 5
  auto f = tree.insert_left(g, 'f');

  tree.delete_node(a, b);

  checkPreorderAVLTree(tree,
                       {'h', 'e', 'c', 'a', 'd', 'g', 'f', 'j', 'i', 'k', 'l'},
                       {0, 0, 0, 0, 0, 1, 0, -1, 0, -1, 0});
}

TEST(AVLTreeMoreComplexDelete, delete2RMinus1) {
  AVLTree<char> tree;
  // root
  auto h = tree.insert_root('h');
  // level 2
  auto c = tree.insert_left(h, 'c');
  auto k = tree.insert_right(h, 'k');
  // level 3
  auto b = tree.insert_left(c, 'b');
  auto e = tree.insert_right(c, 'e');
  auto i = tree.insert_left(k, 'i');
  auto l = tree.insert_right(k, 'l');
  // level 4
  auto a = tree.insert_left(b, 'a');
  auto d = tree.insert_left(e, 'd');
  auto f = tree.insert_right(e, 'f');
  auto j = tree.insert_right(i, 'j');
  // level 5
  auto g = tree.insert_right(f, 'g');

  tree.delete_node(i, j);

  checkPreorderAVLTree(tree,
                       {'e', 'c', 'b', 'a', 'd', 'h', 'f', 'g', 'k', 'i', 'l'},
                       {0, 1, 1, 0, 0, 0, -1, 0, 0, 0, 0});
}

TEST(AVLSearchTreeManyInsert, insertManyCheckHeight) {
  AVLSearchTree<int> tree;

  size_t count = 10000;
  int range = 100000;
  ::testing::internal::Random random(3209);

  for (int i = 0; i < count; i++) {
    tree.insert(random.Generate(range));
  }

  AVLTreeHeightCheck(tree);
}

TEST(AVLSaerchTreeManyInsert, insertManyMeasureTime) {
  AVLSearchTree<long> tree;

  size_t count = 10000;
  int range = 10000;
  ::testing::internal::Random random(3412);
  std::vector<long> data(count);
  for (int i = 0; i < count; ++i) {
    data[i] = random.Generate(range);
  }

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < count; ++i) {
    tree.insert(data[i]);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = std::chrono::duration<double, std::chrono::milliseconds::period>(
                 end - start)
                 .count();
  std::cout << "AVLSearchTree insert " << count << " elements: " << dur << " ms"
            << std::endl;
  ASSERT_LE(dur, 800);
  AVLTreeHeightCheck(tree);
}

TEST(AVLSearchTreeManyInsert, insertSequentialData) {
  AVLSearchTree<int> tree;

  size_t count = 10000;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < count; ++i) {
    tree.insert(i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto dur = std::chrono::duration<double, std::chrono::milliseconds::period>(
                 end - start)
                 .count();
  std::cout << "AVLSearchTree insert " << count
            << " squential elements: " << dur << " ms" << std::endl;
  ASSERT_LE(dur, 800);
  AVLTreeHeightCheck(tree);
}

TEST(AVLSaerchTreeManyInsertAndDelete, deleteRandomAllNodes) {
  AVLSearchTree<int> tree;

  size_t count = 10000;
  int range = 10000;
  ::testing::internal::Random random(3412);
  std::vector<long> data(count);
  for (int i = 0; i < count; ++i) {
    data[i] = random.Generate(range);
  }

  for (int i = 0; i < count; ++i) {
    tree.insert(data[i]);
  }

  AVLTreeHeightCheck(tree);

  std::random_shuffle(data.begin(), data.end());

  int i;
  for (i = 0; i < count / 2; ++i) {
    tree.remove(data[i]);
  }

  AVLTreeHeightCheck(tree);

  for (; i < count; ++i)
    tree.remove(data[i]);

  ASSERT_EQ(tree.size(), 0);
}

TEST(AVLSaerchTreeManyDelete, deleteNotExistenceNumbers) {
  AVLSearchTree<int> tree;

  size_t count = 1000;
  int range = 10000;
  ::testing::internal::Random random(3412);
  std::vector<long> data(count);
  for (int i = 0; i < count; ++i) {
    data[i] = random.Generate(range);
  }

  for (int i = 0; i < count; ++i) {
    tree.insert(data[i]);
  }

  AVLTreeHeightCheck(tree);

  for (int i = 0; i < count; ++i) {
    tree.remove(range + random.Generate(range));
  }

  AVLTreeHeightCheck(tree);
  ASSERT_EQ(tree.size(), count);
}

class BasePureAVLSearchTreeTest : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    tree_tester = new PureAVLSearchTreeTest<int>(nullptr);
  }

  static void TearDownTestSuite() {
    delete tree_tester;
    tree_tester = nullptr;
  }

  void SetUp() override {
    auto *tree = new PureAVLSearchTree<int>;
    tree_tester->set_tree(tree);
  }

  void TearDown() override { tree_tester->delete_tree(); }

  void
  test_insert(const std::vector<int> &input,
              const std::vector<PureAVLSearchTreeTestNode<int>> &expected) {
    for (int i : input)
      tree_tester->get_tree()->insert(i);
    std::vector<PureAVLSearchTreeTestNode<int>> out;
    tree_tester->perorder_iteration(out);

    EXPECT_THAT(out, ::testing::ContainerEq(expected));
  }

  bool insert_into_tree(const int &value) {
    return tree_tester->get_tree()->insert(value);
  }

  void test_height() {
    auto [height,isValid] = tree_tester->height();

		EXPECT_TRUE(isValid) << "The AVL Tree is not valid!";
    ASSERT_GE(height, std::log2(tree_tester->get_tree()->size()));
    ASSERT_LE(height, 1.5f * std::log2(tree_tester->get_tree()->size()));
  }

private:
  static PureAVLSearchTreeTest<int> *tree_tester;
};

PureAVLSearchTreeTest<int> *BasePureAVLSearchTreeTest::tree_tester = nullptr;

class PureAVLSearchTreeBasicInsertTest
    : public BasePureAVLSearchTreeTest,
      public ::testing::WithParamInterface<std::vector<int>> {
protected:
  static std::vector<PureAVLSearchTreeTestNode<int>> expected_out;
};

std::vector<PureAVLSearchTreeTestNode<int>>
    PureAVLSearchTreeBasicInsertTest::expected_out{{6, 0}, {5, 0}, {7, 0}};

TEST_P(PureAVLSearchTreeBasicInsertTest, TreeTestBasicInsert) {
  test_insert(GetParam(), expected_out);
}

TEST_F(BasePureAVLSearchTreeTest, TreeTestComplexInsert1) {
  test_insert({7, 6, 8, 4, 9, 5},
              {{7, 0}, {5, 0}, {4, 0}, {6, 0}, {8, -1}, {9, 0}});
}

TEST_F(BasePureAVLSearchTreeTest, TreeTestComplexInsert2) {
  test_insert({4, 2, 5, 1, 3, 0},
              {{2, 0}, {1, 1}, {0, 0}, {4, 0}, {3, 0}, {5, 0}});
}

TEST_F(BasePureAVLSearchTreeTest, TreeTestComplexInsert3) {
  test_insert(
      {6, 4, 8, 2, 5, 7, 1, 3, 0},
      {{6, 1}, {2, 0}, {1, 1}, {0, 0}, {4, 0}, {3, 0}, {5, 0}, {8, 1}, {7, 0}});
}

TEST_F(BasePureAVLSearchTreeTest, TreeTestManyInsertion1) {
  const int maxn = 1e5;
  for (int i = 0; i < maxn; ++i) {
    ASSERT_TRUE(insert_into_tree(i));
  }
  test_height();
}

TEST_F(BasePureAVLSearchTreeTest, TreeTestManyInsertion2) {
  const int maxn = 1e6;
  for (int i = 0; i < maxn; ++i) {
    insert_into_tree(random());
  }
  test_height();
}

INSTANTIATE_TEST_SUITE_P(TreeBasicInsert, PureAVLSearchTreeBasicInsertTest,
                         ::testing::Values(std::vector{5, 6, 7},
                                           std::vector{5, 7, 6},
                                           std::vector{7, 6, 5},
                                           std::vector{7, 5, 6}));
