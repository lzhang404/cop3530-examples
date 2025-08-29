// Purpose: contrast (1) one contiguous heap block of objects vs (2) an array of pointers
//          each pointing to separately allocated objects.

#include <iostream>
#include <string>

using namespace std;

class State {
 private:
  string name;
 public:
  State();
  State(const string &name);
  string getName() const;
};

State::State(): name("") {}

State::State(const string &name): name(name) {}

string State::getName() const {
  return name;
}

int main() {
    constexpr size_t N = 100;

    cout << "=== 1) Raw 1D array of objects (one allocation) ===\n";
    // One contiguous heap block that contains N State objects
    State* states1 = new State[N];

    // Assign into each element (safe: State uses string)
    for (size_t i = 0; i < N; ++i){
       states1[i] = State("Alabama");
    }

    cout << states1[0].getName() << "\n";

    // Cleanup must match the allocation form (new[] ↔ delete[])
    delete[] states1;

    cout << "\n=== 2) Array of pointers to objects (N allocations) ===\n";

    // First allocate a table of N pointers; value-initialize to nullptr
    State** states2 = new State*[N]();

    // Each element now gets its own independent allocation
    for (size_t i = 0; i < N; ++i) 
    {
      states2[i] = new State("Alabama");
    }
    cout << states2[0]->getName() << "\n";
    
    // Cleanup order: delete each pointed-to object, then delete the pointer table
    for (size_t i = 0; i < N; ++i) 
    {
      delete states2[i];
    }  
    delete[] states2;

    return 0;
}

