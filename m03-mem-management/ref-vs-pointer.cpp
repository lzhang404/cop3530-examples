/**
 * Demonstration: pointer vs reference parameters.
 * Shows two overloads of swap (pointer-based and reference-based),
 * plus pointer/ref examples with std::string.
 *
 * Notes for teaching:
 *  - Overload chosen depends on call site: swap(&a,&b) picks pointer version; swap(a,b) picks reference version.
 *  - Using `using namespace std;` brings std::swap into scope too; our non-template swap(int&,int&) masks it here.
 *    In production, prefer `std::swap` explicitly and avoid `using namespace std;`.
 */

#include <iostream>
using namespace std;

// swap pointer version
// Caller passes ADDRESSES of ints. Function dereferences to mutate the originals.
// Pros: can pass nullptr to mean "no object" (but then you MUST check for null).
// Cons: noisier call syntax, nullability hazards.
void swap(int * ptr1, int * ptr2) {
  //assume ptr1 and ptr2 are not null
  int tmp = *ptr1; //read value at address ptr
  *ptr1 = *ptr2; //write value at atreess ptr1
  *ptr2 = tmp; //write value at address ptr2
}

// swap (reference version)
// Caller passes VARIABLES directly. References cannot be reseated and are never null.
// Pros: clean call syntax, no null checks needed.
// Cons: cannot express "no object" with a reference.
void swap(int & ref1, int & ref2) {
  int tmp = ref1; //read referred value
  ref1 = ref2; //write through reference
  ref2 = tmp;
}

// pointer to objects
// Demonstrates member access via pointer (->) vs dereference + dot ( (*p).member ).
// WARNING: assumes ptr1 is non-null; dereferencing a null pointer is undefined behavior.
void printLength(string * ptr1) {
  // ptr1->length() is a shorthand for (*ptr1).length()
  cout << "Length of the string: " << ptr1->length() << endl;
}

// ref to objects
// references cannot be null, so no check is required
void printLength(string & ref1) {
  cout << "Length of the string: " << ref1.length() << endl;
}

int main(int argc, char const *argv[])
{
  int a = 1;
  int b = 2;

  cout << "a = " << a << "; b = " << b <<endl;
  cout << "swap as pointer\n";
  swap(&a, &b);  // call pointer version, ptr1 = &a
  cout << "a = " << a << "; b = " << b <<endl;
  cout << "swap as reference\n";
  swap(a, b);  // call ref version, ref1 = a
  cout << "a = " << a << "; b = " << b <<endl;

  string str1 = "abc";
  string *ptr1 = &str1;

  printLength(ptr1);  // pointer, string * ptr1 = ptr1;
  printLength(&str1);  // pointer, string * ptr1 = &str1;
  printLength(str1);  // reference, string & ref1 = str1;

  return 0;
}
