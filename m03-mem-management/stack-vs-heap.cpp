#include <iostream>
using namespace std;

const size_t ROWS = 2;
const size_t COLS = 5;

// stack 2D: contiguous, needs COLS known at compile time
void scale(double m[][COLS], size_t rows, size_t cols, double factor) {
  for (size_t r = 0; r < rows; ++r)
    for (size_t c = 0; c < cols; ++c)
      m[r][c] *= factor;
}

// heap pattern 1: pointer-to-pointer (row blocks, not contiguous overall)
void scale(double** m, size_t rows, size_t cols, double factor) {
  for (size_t r = 0; r < rows; ++r)
    for (size_t c = 0; c < cols; ++c)
      m[r][c] *= factor;
}

// heap pattern 2: single contiguous block (row-major indexing)
void scale(double* m, size_t rows, size_t cols, double factor) {
  for (size_t i = 0; i < rows * cols; ++i) m[i] *= factor;
}

void print(const double m[][COLS], size_t rows, size_t cols) {
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c)
      cout << m[r][c] << (c + 1 < cols ? " " : "");
    cout << '\n';
  }
}
void print(double** m, size_t rows, size_t cols) {
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c)
      cout << m[r][c] << (c + 1 < cols ? " " : "");
    cout << '\n';
  }
}
void print(const double* m, size_t rows, size_t cols) {
  for (size_t r = 0; r < rows; ++r) {
    for (size_t c = 0; c < cols; ++c)
      cout << m[r * cols + c] << (c + 1 < cols ? " " : "");
    cout << '\n';
  }
}

int main() {
  // stack matrix (contiguous)
  double mat[ROWS][COLS] = {1,2,3,4,5,6,7,8,9,10};
  cout << "Stack 2D (contiguous)\n";
  scale(mat, ROWS, COLS, 2.0);
  print(mat, ROWS, COLS);

  // heap matrix via row pointers (not contiguous)
  cout << "Heap 2D via double** (row pointers)\n";
  double** dyn = new double*[ROWS];
  for (size_t r = 0; r < ROWS; ++r) {
    dyn[r] = new double[COLS];
    for (size_t c = 0; c < COLS; ++c) dyn[r][c] = r * COLS + c + 1;
  }
  scale(dyn, ROWS, COLS, 2.0);
  print(dyn, ROWS, COLS);
  for (size_t r = 0; r < ROWS; ++r) delete[] dyn[r];
  delete[] dyn;

  // heap matrix as a single block (contiguous)
  cout << "Heap 2D single block (contiguous)\n";
  double* block = new double[ROWS * COLS];
  for (size_t i = 0; i < ROWS * COLS; ++i) block[i] = i + 1;
  scale(block, ROWS, COLS, 2.0);
  print(block, ROWS, COLS);
  delete[] block;
}

