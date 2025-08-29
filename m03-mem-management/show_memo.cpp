#include <iostream>
#include <iomanip>

int g_static_global = 42;                // static storage (global)

void show_static_local() {
    static int s_static_local = 123;     // static storage (function-local static)
    std::cout << "static local  " << static_cast<const void*>(&s_static_local) << "\n";
}

int main() {
    std::cout << std::hex << std::showbase;

    static int s_static_in_main = 7;     // static storage (file image)
    int stack_var = 0;                    // stack
    int* heap_var = new int(0);           // heap

    std::cout << "global static " << static_cast<const void*>(&g_static_global) << "\n";
    std::cout << "static in main " << static_cast<const void*>(&s_static_in_main) << "\n";
    show_static_local();
    std::cout << "stack         " << static_cast<const void*>(&stack_var) << "\n";
    std::cout << "heap          " << static_cast<const void*>(heap_var) << "\n";

    delete heap_var;
    return 0;
}

