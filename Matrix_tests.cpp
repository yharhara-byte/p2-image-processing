#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_init) {
  Matrix mat;
  Matrix_init(&mat, 3, 4);
  ASSERT_EQUAL(Matrix_width(&mat), 3);
  ASSERT_EQUAL(Matrix_height(&mat), 4);
  cout<<"INIT PASS";
}

TEST(test_read_write) {
  Matrix mat;
  Matrix_init(&mat, 2, 3);
  *Matrix_at(&mat,1,1) = 7;
  ASSERT_EQUAL(*Matrix_at(&mat,1,1),7);
  const Matrix* cmat = &mat;
  ASSERT_EQUAL(*Matrix_at(cmat,1,1),7);
  cout<<"READ WRITE PASS";
}

TEST(test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 4, 3);
  Matrix_fill(&mat, 0);
  Matrix_fill_border(&mat, 9);
  ASSERT_EQUAL(*Matrix_at(&mat,0,0),9);//the corners
  ASSERT_EQUAL(*Matrix_at(&mat,0,3),9);
  ASSERT_EQUAL(*Matrix_at(&mat,2,0),9);
  ASSERT_EQUAL(*Matrix_at(&mat,2,3),9);
  ASSERT_EQUAL(*Matrix_at(&mat,1,1),0); //for the inside
  ASSERT_EQUAL(*Matrix_at(&mat,1,2),0);
  cout<<"FILL BORDER PASS";
}

TEST(test_max) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat, 0);
  *Matrix_at(&mat,2,1) = 42;
  *Matrix_at(&mat,0,2) = 17;
  ASSERT_EQUAL(Matrix_max(&mat),42);
  cout<<"MAX PASS";
}

TEST(test_min_funcs) {
  Matrix mat;
  Matrix_init(&mat, 5, 2);
  *Matrix_at(&mat,0,0)=6;
  *Matrix_at(&mat,0,1)=7;
  *Matrix_at(&mat,0,2)=1;
  *Matrix_at(&mat,0,3)=1;
  *Matrix_at(&mat,0,4)=2;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,0,0,5),1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,0,0,5),2); 
  cout<<"MIN FUNCS PASS";
}

TEST(test_print) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat,0,0)=1; *Matrix_at(&mat,0,1)=2;
  *Matrix_at(&mat,1,0)=3; *Matrix_at(&mat,1,1)=4;
  ostringstream out;
  Matrix_print(&mat,out);
  ostringstream correct;
  correct<<"2 2\n";
  correct<<"1 2 \n";
  correct<<"3 4 \n";
  ASSERT_EQUAL(out.str(),correct.str());
  cout<<"PRINT PASS";
}
TEST_MAIN() // Do NOT put a semicolon here
