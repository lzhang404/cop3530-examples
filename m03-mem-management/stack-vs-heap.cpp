#include <iostream>
using namespace std;

int main() {
    const size_t ROWS = 2;
    const size_t COLS = 5;

    cout << "=== 2D contiguous single block: new double[ROWS*COLS] ===\n";
    double* block = new double[ROWS * COLS];
    for (size_t i = 0; i < ROWS * COLS; ++i) block[i] = static_cast<double>(i + 1);

    cout << "sizeof(double) = " << sizeof(double) << " bytes\n";
    for (size_t r = 0; r < ROWS; ++r) {
        for (size_t c = 0; c < COLS; ++c) {
            size_t idx = r * COLS + c;
            cout << "  block[" << idx << "]=" << block[idx]
                 << "  &block[" << idx << "]=" << static_cast<const void*>(&block[idx]) << "\n";
        }
    }
    delete[] block;

    cout << "\n=== 2D pointer-to-pointer: double** + ROWS x new double[COLS] ===\n";
    double** dyn = new double*[ROWS];              // outer array of row pointers
    for (size_t r = 0; r < ROWS; ++r) {
        dyn[r] = new double[COLS];                 // each row allocated separately
        for (size_t c = 0; c < COLS; ++c) dyn[r][c] = static_cast<double>(r * COLS + c + 1);
    }

    cout << "outer pointer table base = " << static_cast<const void*>(dyn) << "\n";
    for (size_t r = 0; r < ROWS; ++r) {
        cout << "  &dyn[" << r << "] = " << static_cast<const void*>(&dyn[r])
             << "  dyn[" << r << "] -> " << static_cast<const void*>(dyn[r]) << "\n";
        for (size_t c = 0; c < COLS; ++c) {
            cout << "    &dyn[" << r << "][" << c << "]=" << static_cast<const void*>(&dyn[r][c])
                 << "  value=" << dyn[r][c] << "\n";
        }
    }

    for (size_t r = 0; r < ROWS; ++r) delete[] dyn[r];
    delete[] dyn;
}
