#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include "CircularDoublyLinkedList.h"
#include "CircularSinglyLinkedList.h"

using namespace std;

template <typename T>
class CircularDoublyLinkedListTestWrapper {
 public:
  CircularDoublyLinkedListTestWrapper()
      : l(new CircularDoublyLinkedList<T>()) {}
  ~CircularDoublyLinkedListTestWrapper() { delete l; }

  void push_back(const T& v) {
    l->push_back(v);
    cout << "after push_back (" << v << "): ";
    print();
  }

  void insert(size_t i, const T& v) {
    try {
      l->insert(i, v);
      cout << "after insert (" << i << ',' << v << "): ";
      print();
    } catch (std::out_of_range& oor) {
      cout << "Out of range exception throwed in insertion: " << oor.what()
           << endl;
    }
  }

  void remove(size_t i) {
    try {
      l->remove(i);
      cout << "after remove (" << i << "): ";
      print();
    } catch (std::out_of_range& oor) {
      cout << "Out of range exception throwed in remove: " << oor.what()
           << endl;
    }
  }

  void print() {
    for (auto it = l->begin(); it != l->end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }

  CircularDoublyLinkedList<T>* operator->() { return l; }

 private:
  CircularDoublyLinkedList<T>* l;
};

int main(int argc, char* argv[]) {
  CircularDoublyLinkedListTestWrapper<int> list1;

  cout << "Mission Started Here by assuming an empty linked list: " << endl;

  list1.push_back(10);
  list1.push_back(30);
  list1.push_back(20);
  list1.push_back(10);
  list1.push_back(900);
  list1.insert(3, 3);
  list1.insert(2, 50);
  list1.remove(3);
  list1.remove(4);
  list1.remove(5);
  list1.remove(2);
  list1.remove(2);

  cout << "Successfull!" << endl;

  {
    const int maxn = 1e5;
    std::vector<double> randoms(maxn);

    std::mt19937 random_machine;
    std::uniform_real_distribution<double> dist;

    for (double& i : randoms) {
      i = dist(random_machine);
    }

    CircularDoublyLinkedList<double> list2;

    cout << "Measuring the heavy operation elapsed time: " << endl;
    auto startTime = chrono::high_resolution_clock::now();
    for (double& i : randoms) {
      list2.push_back(i);
    }
    auto endTime = chrono::high_resolution_clock::now();
    cout << "Elapsed time for " << maxn << " Push backs is: "
         << chrono::duration<double, chrono::milliseconds::period>(endTime -
                                                                   startTime)
                .count()
         << endl;
  }

  {
    cout << "Running loop iteration over list1 by 20 iterations: " << endl;
    int loop_size = 20;
    for (auto lit = list1->loop_begin(); loop_size > 0; loop_size--, ++lit) {
      cout << *lit << " ";
    }
    cout << endl;
  }

  {
    CircularSinglyLinkedList<int> list2;
    list2.push_back(3);
    list2.push_back(5);
    list2.push_back(7);
    list2.push_back(8);

    cout << "\nCircular Singly List: after 4 insertions: {3,5,7,8}\n";

    for (auto it = list2.begin(); it != list2.end(); ++it) {
      cout << *it << " ";
    }

    list2.pop_front();
    list2.pop_front();
    list2.pop_front();
    cout << "\nCircular Singly List: after 3 pop_fronts: \n";

    for (auto it = list2.begin(); it != list2.end(); ++it) {
      cout << *it << " ";
    }

    list2.push_front(1);
    list2.push_front(3);

    cout << "\nCircular Singly List: after 2 push_fronts: {1,3} \n";

    for (auto it = list2.begin(); it != list2.end(); ++it) {
      cout << *it << " ";
    }

    cout << endl;

    list2.push_back(3);
    list2.push_back(5);
    list2.push_back(1);
    list2.push_back(8);

    cout << "\nCircular Singly List: after 4 push_backs: {3,5,1,8} , iteration "
            "using loop iterator: \n";

    int i = 0;
    for (auto it = list2.loop_begin(); i < 10; i++, ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }

  return 0;
}