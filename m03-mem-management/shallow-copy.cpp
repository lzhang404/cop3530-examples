#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Class that OWNS a raw heap buffer but DOES NOT define Rule-of-3/5.
// Copying is shallow → multiple objects hold the same pointer.
class List {
private:
    int* array;   // owned buffer (or nullptr)
    int  size;

public:
    List() : array(nullptr), size(0) {}

    List(int count, int value = 0) : array(new int[count]), size(count) {
        for (int i = 0; i < size; ++i) array[i] = value;
    }

    // NO copy ctor, NO copy assignment → compiler generates SHALLOW copy.
    ~List() {
        // This will double-free if multiple List objects share the same 'array'
        delete[] array;
    }

    int& at(int idx) { return array[idx]; }
    int* data() const { return array; }  // expose pointer for demo only
    int   length() const { return size; }

    void print(const char* tag) const {
        cout << tag << " values: ";
        for (int i = 0; i < size; ++i) cout << array[i] << (i + 1 < size ? ' ' : '\n');
    }

    void show_addresses(const char* tag) const {
        // Cast to const void* to print addresses portably
        cout << fixed << setbase(10);
        cout << tag
             << " this=" << (const void*)this
             << "  array(ptr)=" << (const void*)array;
        if (array && size > 0) {
            cout << "  &array[0]=" << (const void*)&array[0];
            if (size > 1) cout << "  &array[1]=" << (const void*)&array[1];
        }
        cout << "\n";
    }
};

int main() {
    cout << "=== Construct one real owner ===\n";
    List list(5, 10);
    list.show_addresses("list  ");
    list.print("list  ");

    cout << "\n=== Copy-construct (SHALLOW) → list2 shares the same buffer ===\n";
    List list2(list);       // shallow copy: array pointer value is copied
    list2.show_addresses("list2 ");
    list2.print("list2 ");

    cout << "\n=== Default-construct then copy-assign (SHALLOW) → list3 shares too ===\n";
    List list3;
    list3 = list;           // shallow copy again
    list3.show_addresses("list3 ");
    list3.print("list3 ");

    cout << "\n=== Mutate through one alias; all reflect it (shared storage) ===\n";
    list.at(4) = 1;
    list.print( "list  ");
    list2.print("list2 ");
    list3.print("list3 ");

    cout << "\nAddresses summary (all array(ptr) equal ⇒ one heap block shared):\n";
    list.show_addresses( "list  ");
    list2.show_addresses("list2 ");
    list3.show_addresses("list3 ");

  // Important: when main returns, destructors run for list3, list2, and list (in reverse construction order).
  // Each destructor calls delete[] on the SAME pointer → double/triple free (undefined behavior).
  // The extra newline helps flush output so you can read it before the crash occurs on many systems.
  // must add a \n or endl to flush the text to the screen before the crash
  cout << "Expect memory error after because of the double/triple free of the same data.\n";

  return EXIT_SUCCESS; // program likely crashes during object destruction due to shallow copies
}

