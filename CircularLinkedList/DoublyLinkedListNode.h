#pragma once

template <typename T>
struct DoublyLinkedListNode {
  DoublyLinkedListNode(const T& val)
      : value(val), next(nullptr), prev(nullptr) {}

  T value;
  DoublyLinkedListNode<T>* next;
  DoublyLinkedListNode<T>* prev;
};