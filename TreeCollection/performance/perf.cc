#include <PureAVLSearchTree.hpp>
#include <chrono>
#include <set>
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  PureAVLSearchTree<long> tree;
  ifstream file("perf_test.txt");
  int x;
  vector<long> v;
  while (file >> x) {
    v.push_back(x);
  }
  cout << "Read: " << v.size() << " Numbers." << endl;
  auto start = chrono::high_resolution_clock::now();
  for (auto i : v) {
    tree.insert(i);
  }
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, chrono::milliseconds::period> diff1(end - start);
	cout << "Time for PureAVLSearchTree: " << diff1.count() << "ms" << endl;

	std::set<long> s;
	start = chrono::high_resolution_clock::now();
	for (auto i : v) {
		s.insert(i);
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double, chrono::milliseconds::period> diff2(end - start);
	cout << "Time for std::set: " << diff2.count() << "ms" << endl;

	PureAVLSearchTreeTest<long> tester(&tree);
	auto [height,isValid] = tester.height();
	cout << "Size: " << tree.size() << endl;
	cout << "Height: " << height << endl;
	cout << "Height is valid: " << (height >= std::log2(tree.size()) && height <= 1.45 * std::log2(tree.size())) << endl;
	cout << "Is Valid: " << isValid << endl;
  return 0;
}