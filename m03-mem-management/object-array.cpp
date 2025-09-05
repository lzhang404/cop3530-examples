#include <iostream>
#include <string>
using namespace std;

class State {
private:
    string name;
public:
    State() : name("") {}
    State(const string& n) : name(n) {}
    string getName() const { return name; }
};

int main() {
    const size_t N = 6;

    cout << "=== 1D contiguous: new State[N] (one allocation) ===\n";
    State* states1 = new State[N];                 // contiguous block of N objects
    for (size_t i = 0; i < N; ++i) states1[i] = State("Alabama");

    cout << "sizeof(State) = " << sizeof(State) << " bytes\n";
    for (size_t i = 0; i < N; ++i) {
        cout << "  &states1[" << i << "] = " << static_cast<const void*>(&states1[i])
             << "  name=" << states1[i].getName() << "\n";
    }
    delete[] states1;

    cout << "\n=== 1D pointer table: new State*[N] + N x new State ===\n";
    State** states2 = new State*[N]();             // pointer table (contiguous pointers)
    for (size_t i = 0; i < N; ++i) states2[i] = new State("Alabama");

    cout << "pointer table base  = " << static_cast<const void*>(states2) << "\n";
    for (size_t i = 0; i < N; ++i) {
        cout << " address of &states2[" << i << "] = " << static_cast<const void*>(&states2[i])
             << "; the value of states2[" << i << "] = " << static_cast<const void*>(states2[i])
             << " -> name=" << states2[i]->getName() << "\n";
    }
    for (size_t i = 0; i < N; ++i) delete states2[i];
    delete[] states2;
}
