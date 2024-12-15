#pragma once

#include <stdexcept>

#include "SinglyLinkedListNode.h"

template <typename T>
class CircularSinglyLinkedList {
 public:
  CircularSinglyLinkedList() : tail(nullptr) {}

  ~CircularSinglyLinkedList() {
    if (tail == nullptr) return;

    SinglyLinkedListNode<T>* temp = tail;
    SinglyLinkedListNode<T>* curr = tail;
    curr = curr->next;
    while (curr != tail) {
      delete temp;
      temp = curr;
      curr = curr->next;
    }
    delete temp;
  }

  void push_back(const T& value) {
    push_front(value);
    tail = tail->next;
  }

  void push_front(const T& value) {
    if (tail == nullptr) {
      tail = new SinglyLinkedListNode<T>(value);
      tail->next = tail;
    } else {
      SinglyLinkedListNode<T>* newNode = new SinglyLinkedListNode<T>(value);
      newNode->next = tail->next;
      tail->next = newNode;
    }
  }

  void pop_front() {
    if (tail == nullptr) {
      throw std::out_of_range("The array is under empty.");
    }

    if (tail->next == tail) {
      delete tail;
      tail = nullptr;
    }

    SinglyLinkedListNode<T>* temp = tail->next;
    tail->next = tail->next->next;
    delete temp;
  }

  class Iterator {
   public:
    Iterator(SinglyLinkedListNode<T>* node, SinglyLinkedListNode<T>* tail)
        : node(node), tail(tail) {}

    T& operator*() { return node->value; }

    T* operator->() { return &node->value; }

    Iterator& operator++() {
      node = node->next;
      if (node == tail) node = nullptr;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      *this->operator++();
      return temp;
    }

    bool operator==(const Iterator& other) const { return other.node == node; }
    bool operator!=(const Iterator& other) const { return other.node != node; }

   private:
    SinglyLinkedListNode<T>* tail;
    SinglyLinkedListNode<T>* node;
  };

  Iterator begin() const { return Iterator(tail->next, tail->next); }

  Iterator end() const { return Iterator(nullptr, tail->next); }

  class LoopIterator {
   public:
    LoopIterator(SinglyLinkedListNode<T>* node) : node(node) {}

    T& operator*() { return node->value; }

    T* operator->() { return &node->value; }

    LoopIterator& operator++() {
      node = node->next;
      return *this;
    }

    LoopIterator operator++(int) {
      LoopIterator temp = *this;
      *this->operator++();
      return temp;
    }

    bool operator==(const LoopIterator& other) const {
      return other.node == node;
    }
    bool operator!=(const LoopIterator& other) const {
      return other.node != node;
    }

   private:
    SinglyLinkedListNode<T>* node;
  };

  LoopIterator loop_begin() { return LoopIterator(tail->next); }

 private:
  SinglyLinkedListNode<T>* tail;
};