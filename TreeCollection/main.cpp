#include "AVLTree.hpp"
#include "BinaryIndexedLinearList.hpp"
#include "BinaryIndexedTree.hpp"
#include "BinarySearchTree.hpp"
#include "PureAVLSearchTree.hpp"
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <string_view>

using namespace std;

template <typename T, typename K>
void orders(const std::string &name, BinaryTree<T, K> &tree) {
  cout << "[START]------------- " << name << " -------------[START]" << endl;
  auto iit = tree.inorder_begin();
  cout << "Inorder: ";
  while (iit != tree.inorder_end()) {
    cout << *iit << " ";
    ++iit;
  }
  cout << endl;

  auto riit = tree.rev_inorder_begin();
  cout << "Reverse Inorder: ";
  while (riit != tree.rev_inorder_end()) {
    cout << *riit << " ";
    --riit;
  }
  cout << endl;

  auto pit = tree.preorder_begin();
  cout << "Preorder: ";
  while (pit != tree.preorder_end()) {
    cout << *pit << " ";
    ++pit;
  }
  cout << endl;

  auto rpit = tree.rev_preorder_begin();
  cout << "Reverse Preorder: ";
  while (rpit != tree.rev_preorder_end()) {
    cout << *rpit << " ";
    --rpit;
  }
  cout << endl;

  auto poit = tree.postorder_begin();
  cout << "Postorder: ";
  while (poit != tree.postorder_end()) {
    cout << *poit << " ";
    ++poit;
  }
  cout << endl;

  auto rpoit = tree.rev_postorder_begin();
  cout << "Reverse Postorder: ";
  while (rpoit != tree.rev_postorder_end()) {
    cout << *rpoit << " ";
    --rpoit;
  }
  cout << endl;
  cout << "[END]------------- " << name << " -------------[END]" << endl;
}

void indexedTreeTests();

int main() {
  BinarySearchTree<long> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(1);
  tree.insert(9);
  tree.insert(10);
  tree.insert(0);
  tree.insert(8);
  tree.insert(6);

  orders("Tree", tree);

  tree.remove(3);
  orders("Tree(remove 3)", tree);

  tree.remove(5);
  orders("Tree(remove 5)", tree);

  tree.remove(7);
  orders("Tree(remove 7)", tree);

  AVLSearchTree<long> avlTree;

  avlTree.insert(100);
  avlTree.insert(10);
  avlTree.insert(1);
  avlTree.insert(2);
  avlTree.insert(20);
  avlTree.insert(0);
  avlTree.insert(8);

  orders("AVL Search Tree", avlTree);

  avlTree.remove(20);
  orders("AVL Search Tree(After remove 20)", avlTree);

  AVLSearchTree<std::string> avlTree2;

  avlTree2.insert("abcd");
  avlTree2.insert("ancd");
  avlTree2.insert("ncda");
  avlTree2.insert("nnc1");
  avlTree2.insert("11cn");
  avlTree2.insert("aamd");
  avlTree2.insert("aabb");
  avlTree2.insert("aabc");

  orders("String AVL Search Tree", avlTree2);

  AVLTree<std::string> avlTree3;

  auto root = avlTree3.insert_root("Saeed");
  auto left = avlTree3.insert_left(root, "Ali");
  auto right = avlTree3.insert_left(left, "Hassan");

  orders("String AVL Tree", avlTree3);

  AVLSearchTree<long> avlTree4;

  for (int i = 0; i <= 20; i++) {
    avlTree4.insert(i);
  }

  {
    auto node = avlTree4.find(7);
    assert(node == avlTree4.root());
    assert(node.left().data() == 3);
    assert(node.right().data() == 15);

    auto node2 = avlTree4.find(19);
    assert(node2 == avlTree4.root().right().right().right());
    assert(node2.left().data() == 18);
    assert(node2.right().data() == 20);

    auto node3 = avlTree4.find(0);
    assert(!node3.left().valid() && !node3.right().valid());
  }

  orders("AVL Search tree with 20 items", avlTree4);

  {
    avlTree4.remove(16);

    auto node = avlTree4.find(19);
    assert(node.left().data() == 17);
    assert(node.right().data() == 20);
    assert(node.left().right().data() == 18);
  }

  orders("AVL Search tree with 20 items after remove 16", avlTree4);
  AVLSearchTree<int> bigTree;
  const int benchInt = 1000000;

  {
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= benchInt; ++i) {
      bigTree.insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration<double, std::chrono::microseconds::period>(
        end - now);
    cout << "Time elapsed for insert: " << std::fixed << dur.count() << "us"
         << endl;
    cout << "Average time elapsed for each insert: " << std::fixed
         << dur.count() / benchInt << "us" << endl;
  }

  {
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= benchInt; ++i) {
      bigTree.find(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration<double, std::chrono::microseconds::period>(
        end - now);
    cout << "Time elapsed for find: " << std::fixed << dur.count() << "us"
         << endl;
    cout << "Average time elapsed for each find: " << std::fixed
         << dur.count() / benchInt << "us" << endl;
  }

  {
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= benchInt; ++i) {
      bigTree.remove(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration<double, std::chrono::microseconds::period>(
        end - now);
    cout << "Time elapsed for delete: " << std::fixed << dur.count() << "us"
         << endl;
    cout << "Average time elapsed for each delete: " << std::fixed
         << dur.count() / benchInt << "us" << endl;
  }

  indexedTreeTests();

  if (0) {
    AVLSearchTree<int> tree;

    const int maxn = 1e7;
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < maxn; ++i) {
      tree.insert(rand());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration<double, std::chrono::milliseconds::period>(
        end - now);
    cout << "Tree with " << maxn << " Numbers and height: " << tree.height()
         << endl;
    cout << "Time elapsed for: " << std::fixed << dur.count() << "ms" << endl;
  }

  {
    PureAVLSearchTree<int> tree;

    tree.insert(5);
    tree.insert(60);
    tree.insert(10);

		cout << "PureAVL tree End!" << endl;
  }

  return 0;
}

void beginTest(const std::string_view &&view) {
  static int counter = 1;
  cout << "[BEGIN] TEST" << counter++ << ": " << view << " -----[BEGIN]"
       << endl;
}

void endTest(const std::string_view &&view) {
  static int counter = 1;
  cout << "[END] TEST" << counter++ << ": " << view << " -----[END]" << endl;
}

void indexedTreeTests() {
  {
    beginTest("BinaryIndexedTree1[insert]");
    BinaryIndexedTree<int> tree;
    auto root = tree.insert_root(23);
    auto right = tree.insert_right(root, 45);
    auto left = tree.insert_left(root, 12);
    auto right2 = tree.insert_right(right, 56);

    assert(root.additional_data().left_size() == 1);
    assert(right.additional_data().left_size() == 0);
    assert(left.additional_data().left_size() == 0);
    assert(right2.additional_data().left_size() == 0);
    endTest("BinaryIndexedTree1[insert]");

    beginTest("BinaryIndexedTree1[delete]");

    tree.delete_node(root, right);

    assert(root.additional_data().left_size() == 1);
    assert(right2.additional_data().left_size() == 0);
    assert(left.additional_data().left_size() == 0);

    endTest("BinaryIndexedTree1[delete]");
  }

  {
    beginTest("BinaryIndedLinearList[insert]");
    int benchInt = 50;
    BinaryIndexedLinearList<long> list;
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < benchInt; ++i) {
      list.insert(i, rand());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration<double, std::chrono::microseconds::period>(
                   end - now)
                   .count();
    cout << "Time elapsed for " << benchInt << " insertion: " << dur << "us"
         << endl;
    cout << "Average time for each insert: " << dur / benchInt << "us" << endl;
    endTest("BinaryIndedLinearList[insert]");
  }
}
