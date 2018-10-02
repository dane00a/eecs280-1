// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Image.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>
#include <string>
#include <iostream>

using std::string;
using namespace std;

// This is the public Image test for which the autograder gives feedback.
// It only tests VERY FEW of the expected behaviors of the Image module.
// It will only really tell you if your code compiles and you remembered to
// write the functions. It is not to be trusted. It tells the truth, but not
// the whole truth. It might put you in a blender. You get the point.
// You must write your own comprehensive unit tests in Image_tests.cpp!


TEST(test_image_basic) {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Image *img = new Image;
  Image_init(img, 3, 4);
  cout << "one" << endl;
  ASSERT_EQUAL(Image_width(img), 3);
  cout << "two" << endl;
  ASSERT_EQUAL(Image_height(img), 4);
  cout << "three" << endl;
  Image_fill(img, red);
  cout << "four" << endl;
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), red));
  cout << "five" << endl;
  Image_set_pixel(img, 0, 0, green);
  cout << "six" << endl;
  cout << "image: " << img->green_channel.data[0] << endl;
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), green));
  cout << "seven" << endl;
  delete img;
}

void dump(Image* img){
	int width = img->width;
	int height = img->height; 
	int total = width * height;
  for(int i = 0; i < total; ++i){
    cout << "dump: " << img->red_channel.data[i] << " " << img->green_channel.data[i] << " " << img->blue_channel.data[i];
  }

}

TEST(test_image_from_and_to_stream) {
  Image *img = new Image;

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  cout << "one" << endl;
  Image_init(img, ss_input);
  dump(img);
  cout << "two" << endl;
  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  dump(img);
  Image_print(img, ss_output);
  cout << "three" << endl;
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
  cout << "four" << endl;

  delete img;
}

TEST_MAIN()
