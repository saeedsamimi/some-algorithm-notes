#pragma once

#include <cstddef>
#include <stdexcept>

#include "DoublyLinkedListNode.h"

template <typename T>
class CircularDoublyLinkedList {
 public:
  CircularDoublyLinkedList() : head(nullptr) {}

  ~CircularDoublyLinkedList() {
    if (head == nullptr) return;

    DoublyLinkedListNode<T>* curr = head;
    do {
      DoublyLinkedListNode<T>* temp = curr;
      curr = curr->next;
      delete temp;
    } while (curr != head);

    head = nullptr;
  }

  void insert(size_t i, const T& value) {
    if (i == 0) return push_front(value);
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(value);
    DoublyLinkedListNode<T>* current = head;

    do {
      current = current->next;
      i--;
    } while (current != head && i > 1);

    if (current == head) {
      delete newNode;
      throw std::out_of_range("Index out of bound.");
    }

    DoublyLinkedListNode<T>* nextNode = current->next;
    current->next = newNode;
    newNode->prev = current;
    newNode->next = nextNode;
    nextNode->prev = newNode;
  }

  void remove(size_t i) {
    if (head == nullptr) throw std::out_of_range("The List is empty.");

    if (i == 0) return pop_front();

    DoublyLinkedListNode<T>* current = head;
    do {
      current = current->next;
      i--;
    } while (current != head && i > 0);

    if (current == head) {
      throw std::out_of_range("Index out of bound.");
    }

    DoublyLinkedListNode<T>* prevNode = current->prev;
    DoublyLinkedListNode<T>* nextNode = current->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    delete current;
  }

  void push_front(const T& value) {
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(value);

    if (head == nullptr) {
      head = newNode;
      head->next = head;
      head->prev = head;
    } else {
      DoublyLinkedListNode<T>* tail = head->prev;
      newNode->next = head;
      newNode->prev = tail;
      head->prev = newNode;
      tail->next = newNode;
      head = newNode;
    }
  }

  void push_back(const T& value) {
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(value);

    if (head == nullptr) {
      head = newNode;
      head->next = head;
      head->prev = head;
    } else {
      DoublyLinkedListNode<T>* tail = head->prev;
      newNode->next = head;
      newNode->prev = tail;
      tail->next = newNode;
      head->prev = newNode;
    }
  }

  void pop_front() {
    if (head == nullptr) return;

    if (head->next == head) {
      delete head;
      head = nullptr;
    } else {
      DoublyLinkedListNode<T>* tail = head->prev;
      DoublyLinkedListNode<T>* temp = head;
      head = head->next;
      head->prev = tail;
      tail->next = head;
      delete temp;
    }
  }

  void pop_back() {
    if (head == nullptr) return;

    if (head->next == head) {
      delete head;
      head = nullptr;
    } else {
      DoublyLinkedListNode<T>* tail = head->prev;
      DoublyLinkedListNode<T>* newTail = tail->prev;
      newTail->next = head;
      head->prev = newTail;
      delete tail;
    }
  }

  class Iterator {
   public:
    Iterator(DoublyLinkedListNode<T>* node, DoublyLinkedListNode<T>* head)
        : head(head), current(node) {}

    T& operator*() { return current->value; }

    T* operator->() { return &current->value; }

    Iterator& operator++() {
      current = current->next;
      if (current == head) current = nullptr;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      *this->operator++();
      return temp;
    }

    bool operator==(const Iterator& other) const {
      return other.current == current;
    }

    bool operator!=(const Iterator& other) const {
      return other.current != current;
    }

   private:
    DoublyLinkedListNode<T>* head;
    DoublyLinkedListNode<T>* current;
  };

  Iterator begin() { return Iterator(head, head); }

  Iterator end() { return Iterator(nullptr, head); }

  class ReverseIterator {
   public:
    ReverseIterator(DoublyLinkedListNode<T>* node,
                    DoublyLinkedListNode<T>* tail)
        : current(node), tail(tail) {}

    T& operator*() { return current->value; }

    T* operator->() { return &current->value; }

    ReverseIterator& operator++() {
      current = current->prev;
      if (current == tail) current = nullptr;
      return *this;
    }

    ReverseIterator operator++(int) {
      Iterator temp = *this;
      *this->operator++();
      return temp;
    }

    bool operator==(const ReverseIterator& other) const {
      return other.current == current;
    }

    bool operator!=(const ReverseIterator& other) const {
      return other.current != current;
    }

   private:
    DoublyLinkedListNode<T>* tail;
    DoublyLinkedListNode<T>* current;
  };

  ReverseIterator rbegin() { return ReverseIterator(head->prev, head->prev); }

  ReverseIterator rend() { return ReverseIterator(nullptr, head->prev); }

  class LoopIterator {
   public:
    LoopIterator(DoublyLinkedListNode<T>* node) : node(node) {
      if (node == nullptr) {
        throw std::invalid_argument(
            "the node must be a valid pointer, or the list should contain some "
            "items");
      }
    }

    T& operator*() { return node->value; }

    T* operator->() { return &node->value; }

    LoopIterator& operator++() {
      node = node->next;
      return *this;
    }

    LoopIterator& operator--() {
      node = node->prev;
      return *this;
    }

    LoopIterator operator++(int) {
      Iterator temp = *this;
      *this->operator++();
      return temp;
    }

    LoopIterator operator--(int) {
      Iterator temp = *this;
      *this->operator--();
      return temp;
    }

    bool operator==(const ReverseIterator& other) const {
      return other.node == node;
    }

    bool operator!=(const ReverseIterator& other) const {
      return other.node != node;
    }

   private:
    DoublyLinkedListNode<T>* node;
  };

  LoopIterator loop_begin() { return LoopIterator(head); }

 private:
  DoublyLinkedListNode<T>* head;
};