// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>
#include <iostream>

using std::ostringstream;
using namespace std;


// This is the public Matrix test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Matrix module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Matrix_tests.cpp!


TEST(test_matrix_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);

  ASSERT_EQUAL(Matrix_width(mat), 5);
  cout << "one" << endl;
  ASSERT_EQUAL(Matrix_height(mat), 5);
  cout << "two" << endl;
  Matrix_fill(mat, 0);
  cout << "tres" << endl;
  int *ptr = Matrix_at(mat, 2, 3);
  cout << ptr << endl;
  cout << *ptr << endl;
  cout << "four" << endl;
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  cout << "five" << endl;
  ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
  cout << "six" << endl;
  ASSERT_EQUAL(*ptr, 0);
  cout << "seven" << endl;
  *ptr = 42;

  const int *cptr = Matrix_at(mat, 2, 3);
  cout << "eight" << endl;
  ASSERT_EQUAL(*cptr, 42);
  cout << "nine" << endl;

  Matrix_fill_border(mat, 2);
  cout << "ten" << endl;
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 2);
  cout << "eleven" << endl;
  ASSERT_EQUAL(Matrix_max(mat), 42);
  cout << "twelve" << endl;
  delete mat;
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST_MAIN()
