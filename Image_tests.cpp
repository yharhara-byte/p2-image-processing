#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.
TEST(test_image_init) {
  Image img;
  Image_init(&img,3,2);
  ASSERT_EQUAL(Image_width(&img),3);
  ASSERT_EQUAL(Image_height(&img),2);
  cout<<"INIT PASS";
}

TEST(test_image_setter_getter) {
  Image img;
  Image_init(&img,2,2);
  Pixel p={7,8,9};
  Image_set_pixel(&img,1,0,p);
  Pixel q=Image_get_pixel(&img,1,0);
  ASSERT_EQUAL(q.r,7);
  ASSERT_EQUAL(q.g,8);
  ASSERT_EQUAL(q.b,9);
  cout<<"SETTER AND GETTER PASS";
}

TEST(test_fill) {
  Image img;
  Image_init(&img,3,2);
  Pixel c={10,20,30};
  Image_fill(&img,c);
  for(int r=0;r<Image_height(&img);r++){
    for(int ccol=0;ccol<Image_width(&img);ccol++){
      Pixel q=Image_get_pixel(&img,r,ccol);
      ASSERT_EQUAL(q.r,10);
      ASSERT_EQUAL(q.g,20);
      ASSERT_EQUAL(q.b,30);
    }
  }
    cout<<"FILL PASS";
}

TEST(test_image_print) {
  Image img;
  Image_init(&img,2,1);
  Pixel a={0,0,0};
  Pixel b={255,128,64};
  Image_set_pixel(&img,0,0,a);
  Image_set_pixel(&img,0,1,b);
  ostringstream out;
  Image_print(&img,out);
  ostringstream correct;
  correct<<"P3\n2 1\n255\n";
  correct<<"0 0 0 255 128 64 \n";
  ASSERT_EQUAL(out.str(),correct.str());
  cout<<"PRINT PASS";
}

TEST_MAIN() // Do NOT put a semicolon here
