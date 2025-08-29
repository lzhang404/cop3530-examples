#include <iostream>

using namespace std;

// This example demonstrates a class that OWNS dynamic memory (raw int*).
// It defines a destructor but does NOT define a copy constructor or copy assignment.
// Consequence: the compiler generates default (shallow) copy behavior.
// Shallow copies mean multiple List objects end up pointing to the SAME heap array.
// When each destructor later runs, each will delete[] the same pointer → double/triple free crash.

// List class
//   Only has a destructor
//   Missing copy constructor and copy assignment operator overloading
class List {
 private:
  int *array;  // pointer to a heap-allocated int array (or nullptr)
  int size;    // number of elements stored
 public:
  List();                          // default constructor: empty list
  List(int count, int value = 0);  // construct with 'count' elements, each initialized to 'value'
  ~List();                         // destructor: releases the owned heap memory (if any)
  int &at(int index);              // returns reference to element (NO bounds checking)
  void print();                    // prints all elements followed by newline
};

List::List() {
  // Start as an empty list with no allocated storage.
  array = nullptr;
  size = 0;
}

List::List(int count, int value) {
  // Allocate 'count' ints on the heap and fill them with 'value'.
  size = count;
  array = new int[size];
  for (int i = 0; i < count; ++i)
    array[i] = value;
}

List::~List() {
  // Release the owned array. If shallow copies exist, multiple objects will
  // try to delete[] the same pointer → undefined behavior (typically a crash).
  delete [] array;
}

int &List::at(int index) {
  // Return a reference to the element at 'index'.
  // Note: there is NO bounds checking; invalid indices cause undefined behavior.
  return array[index];
}

void List::print() {
  // Print elements separated by spaces, then newline.
  for (int i = 0; i < size; ++i)
    cout << array[i] << " ";
  cout << endl;
}

int main() {
  // Construct a list of 5 elements, all initialized to 10.
  // Internally allocates a heap array of size 5 and stores its pointer in 'list.array'.
  List list(5, 10);  // the constructor taking two int values is triggered

  // Copy construction with NO user-defined copy constructor:
  // The compiler-generated copy constructor performs a SHALLOW copy:
  //   - copies 'size'
  //   - copies the 'array' pointer VALUE (both objects point to the same heap block)
  List list2(list);  // copy constructor is triggered

  // Default construction produces an empty list (array == nullptr, size == 0)
  List list3;  // the default constructor will be triggered

  // Copy assignment with NO user-defined operator=:
  // The compiler-generated assignment does a SHALLOW copy too.
  // After this line, 'list3.array' points to the SAME memory as 'list.array' and 'list2.array'.
  // Note: since list3 previously had nullptr, there is no leak here—but now three objects share one buffer.
  list3 = list;  // default assignment operator is triggered

  // All three lists currently share the exact same underlying array.
  list.print();  // 10 10 10 10 10
  list2.print(); // 10 10 10 10 10
  list3.print(); // 10 10 10 10 10

  // Modify the 5th value through 'list'. Because of shallow copy, the change is visible in list2 and list3 as well.
  list.at(4) = 1; // modify the 5th value

  // All three outputs will be the same with the 5th value modified (evidence of shared storage).
  list.print();  // 10 10 10 10 1
  list2.print(); // 10 10 10 10 1
  list3.print(); // 10 10 10 10 1

  // Important: when main returns, destructors run for list3, list2, and list (in reverse construction order).
  // Each destructor calls delete[] on the SAME pointer → double/triple free (undefined behavior).
  // The extra newline helps flush output so you can read it before the crash occurs on many systems.
  // must add a \n or endl to flush the text to the screen before the crash
  cout << "Expect memory error after because of the double/triple free of the same data.\n";

  return EXIT_SUCCESS; // program likely crashes during object destruction due to shallow copies
}

