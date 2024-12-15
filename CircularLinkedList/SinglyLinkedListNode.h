#pragma once

template <typename T>
struct SinglyLinkedListNode {
  SinglyLinkedListNode(const T& val) : value(val), next(nullptr) {}

  T value;
  SinglyLinkedListNode<T>* next;
};