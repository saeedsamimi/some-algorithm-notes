#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <array>

#include "BinarySearchTree.h"

using namespace std;

static int testCounter = 1;

#define TEST_START cout << "---- TEST #" << testCounter << " START --" << endl
#define TEST_END cout << "---- TEST #" << testCounter++ << " END ----" << endl

void test_by_random_numbers(int n) {
  std::vector<int> numbers(n);

  std::random_device rdev;
  std::seed_seq seeds{rdev(), rdev(), rdev(), rdev()};
  std::mt19937 gen;
  std::uniform_int_distribution<int> dist;

  for (int &i : numbers) {
    i = dist(gen);
  }

  cout << n << " Numbers generated." << endl;

  BinarySearchTree<int> bst;

  auto startTime = chrono::high_resolution_clock::now();
  for (int &i : numbers) {
    bst.insert(i);
  }
  auto endTime = chrono::high_resolution_clock::now();
  auto dur = chrono::duration<double, chrono::milliseconds::period>(endTime -
                                                                    startTime);
  cout << "Elapsed time for insert " << n << " numbers: " << dur.count() << "ms"
       << endl;
}

void test_by_randoms() {
  array<size_t, 4> counts{1000, 40000, 400000, 1000000};
  for (size_t i : counts) {
    TEST_START;
    test_by_random_numbers(i);
    TEST_END;
  }
}

void test_orders_iterators() {
  std::array<int, 20> items{91, 25, 11, 100, 6,  5,  60, 15, 21, 9,
                            55, 53, 19, 97,  32, 86, 75, 30, 94, 36};

  TEST_START;
  BinarySearchTree<int> bst;
  for (int i : items) bst.insert(i);

  cout << "\nInorder Output: ";
  for (auto init = bst.inorder_begin(); init != bst.inorder_end(); ++init) {
    cout << *init << " ";
  }
  cout << endl;

  cout << "\nPreorder Output: ";
  for (auto preit = bst.preorder_begin(); preit != bst.preorder_end();
       ++preit) {
    cout << *preit << " ";
  }
  cout << endl;

  cout << "\nPostorder Output: ";
  for (auto posit = bst.postorder_begin(); posit != bst.postorder_end();
       ++posit) {
    cout << *posit << " ";
  }
  cout << endl;

  cout << "\nHeight of Tree: " << bst.height() << endl;
  TEST_END;
}

void test_remove() {
  TEST_START;
  BinarySearchTree<double> bst;

  bst.insert(34.0f);
  bst.insert(13.0f);

  assert(bst.size() == 2);

  bst.remove(13.0f);

  assert(bst.size() == 1);

  bst.insert(37.0f);
  bst.insert(-98.0f);
  bst.insert(3.545f);
  bst.insert(8.90f);

  assert(bst.size() == 5);

  cout << "\nInorder Output: ";
  for (auto init = bst.inorder_begin(); init != bst.inorder_end(); ++init) {
    cout << *init << " ";
  }
  cout << endl;

  cout << "\nPreorder Output: ";
  for (auto preit = bst.preorder_begin(); preit != bst.preorder_end();
       ++preit) {
    cout << *preit << " ";
  }
  cout << endl;

  TEST_END;
}

int main() {
  test_by_randoms();
  test_orders_iterators();
  test_remove();
  return 0;
}
