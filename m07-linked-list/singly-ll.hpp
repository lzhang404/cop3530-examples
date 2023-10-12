#ifndef SINGLY_LL_HPP
#define SINGLY_LL_HPP

#include <iostream>

template <class T>
class Node {
  T value;
  Node<T> *next;

 public:
  Node<T>();
  Node<T>(T value) : value(value), next(nullptr) {};
  void setNext(Node<T> *next) { this->next = next; }
  Node<T> *getNext() { return next; }
  T getValue() { return value; }
  void setValue(T value) { this->value = value; }
};

// A singly-linked list implementing List ADT
// a head pointer, a tail pointer
// a next pointer in node class
template <class T>
class SinglyLinkedList {
 private:
  Node<T> *head;
  Node<T> *tail;

 public:
  // out-of-line methods
  void insertAfter(Node<T> *node, Node<T> *newNode);
  void prepend(Node<T> *node);
  void append(Node<T> *node);
  void remove(Node<T> *node);
  Node<T> *search(T value);

  // inline methods
  SinglyLinkedList() : head(nullptr), tail(nullptr) {}

  bool isEmpty() { return head == nullptr; }

  int size() {
    int count = 0;
    Node<T> *node = head;
    while (node != nullptr) {
      ++count;
      node = node->getNext();
    }
    return count;
  }

  void print() {
    Node<T> *node = head;
    while (node != nullptr) {
      std::cout << node->getValue() << " ";
      node = node->getNext();
    }
    std::cout << std::endl;
  }

  ~SinglyLinkedList() {
    Node<T> *node = head;
    Node<T> *next;
    while (node != nullptr) {
      next = node->getNext();
      delete node;
      node = next;
    }
  }
};

// Append is a special case of insertAfter except for the case when the
// list is empty
template <class T>
void SinglyLinkedList<T>::append(Node<T> *node) {
  if (head == nullptr) {
    head = node;
    tail = node;
  } else
    insertAfter(tail, node);
}

template <class T>
void SinglyLinkedList<T>::prepend(Node<T> *node) {
  if (head == nullptr) {  // empty list
    head = node;
    tail = node;
  } else {
    node->setNext(head);
    head = node;
  }
}

template <class T>
void SinglyLinkedList<T>::insertAfter(Node<T> *node, Node<T> *newNode) {
  newNode->setNext(node->getNext());
  node->setNext(newNode);
  if (node == tail) // insert after the last node
    tail = newNode;
}

template <class T>
void SinglyLinkedList<T>::remove(Node<T> *node) {
  // Assuming that the node exist in the list
  Node<T> *prevNode;
  if (node == head) {  // remove first node
    head = head->getNext();
  } else {
    prevNode = head;
    // find the previous node,
    // should always able to find a match
    while (true) {
      if (prevNode->getNext() == node) break;
      prevNode = prevNode->getNext();
    }
    prevNode->setNext(node->getNext());
  }
  if (node == tail) {  // update the tail if the last node is removed
    tail = prevNode;
  }
  delete node;
}

template <class T>
Node<T> *SinglyLinkedList<T>::search(T value) {
  Node<T> *node = head;
  while (node != nullptr) {
    if (node->getValue() == value) return node;  // find a match
    node = node->getNext();
  }
  return nullptr;
}

#endif // SINGLY_LL_HPP
