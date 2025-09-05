#include <iostream>
using namespace std;

int main() {
    cout << "=== References ===\n";
    int x = 10;

    // ref is another name (alias) for x
    int& ref = x;      

    cout << "Address of x   = " << &x << "\n";
    cout << "Address of ref = " << &ref << " (same as x)\n";

    ref = 20;          // changes x too (ref is not reseated)
    cout << "x = " << x << ", ref = " << ref << "\n\n";

    cout << "=== Pointers ===\n";
    int a = 10;

    // ptr stores the address of a
    int* ptr = &a;     

    cout << "Address of a   = " << &a << "\n";
    cout << "ptr (points to)= " << ptr << "\n";

    *ptr = 20;         // changes a through dereference
    cout << "a = " << a << " (changed via *ptr)\n";

    // reseating: make ptr point to x instead of a
    ptr = &x;          
    cout << "ptr now points to address " << ptr 
         << " (x's address)\n";
    cout << "x = " << x << " (accessed via *ptr = " << *ptr << ")\n";

    return 0;
}
