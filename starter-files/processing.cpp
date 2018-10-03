
// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched
  
  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched
  
  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           size as the given Image, and then the energy matrix for that
//           The Matrix pointed to by energy is initialized to be the same
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  int energyVal;
  if(energy->width == img -> width && energy->height == img->height){
  int maxEnergy = 0;
    for(int i = img->width; i < img->width*img->height - img->width; ++i){
      if((i % img->width != 0 && (i-1)%img->width !=0)){
        energyVal = squared_difference(Image_get_pixel(img,i-img->width-1),Image_get_pixel(i+img->width+1)) + //take this line and typecast a *ptr value for this crap instead of doing tons of nested function calls
        squared_difference(Image_get_pixel(i+1),Image_get_pixel(i-1));
        energy->data[i] = energyVal;
        if(energyVal > maxEnergy){
          maxEnergy = energyVal;
        }
      }
    }
    for(int j = 0; j < img->width*img->height; ++j){
      energy->data[j] = maxEnergy;
      if((j+1) == img->width){
        for(int row = 2; row < img->height; ++row){ // math needs to be checked
          energy->data[row*j] = maxEnergy;
          energy->data[row*j-1] = maxEnergy;
        }
        j = img->width * img->height - img->width -1;
      }                    
    }
  }
  //assert(false); // TODO Replace with your implementation!
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  //assert(false); // TODO Replace with your implementation!

	// initializes cost to be the same size as the energy matrix
	cost->width = energy->width;
	cost->height = energy->height; 

	// fill in first row with energy values
	int row_length = energy->height / (sizeof(energy->data) / sizeof(int));
	for (int i = 0; i < row_length; i++) {
		cost->data[i] = energy->data[i];
	}

	// Loop through each pixel and compute the cost
	for (int i = 1; i < energy->height; i++) {
		int data_size = sizeof(*energy->data) / sizeof(int);
		int row_length = data_size / energy->height;
		for (int j = 0; j < row_length; j++) {
			int index = (i * row_length) + j;
			int min_col;
			if (j == 0) { // first column
				min_col = Matrix_column_of_min_value_in_row(cost, i - 1, 0, 1);
				}
			else if(j == row_length - 1){ // last column
				min_col = Matrix_column_of_min_value_in_row(cost, i - 1, row_length - 2, row_length - 1);
			}
			else { // every other column
				min_col = Matrix_column_of_min_value_in_row(cost, i - 1, j - 1, j + 1);
			}
			cost->data[index] = energy->data[index] + cost->data[((i - 1) * row_length) + min_col + 1];
		}
	}
}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {
  //assert(false); // TODO Replace with your implementation!
	
	// Bottom row
	int min_col = Matrix_column_of_min_value_in_row(cost, (cost->height) - 1, 0, (cost->width) - 1);
	seam[cost->height - 1] = min_col;
 	
	// The rest
	for (int i = 0; i < cost->height; i++) {
		int prev_col = seam[i];

		if (prev_col == 0) {
			min_col = Matrix_column_of_min_value_in_row(cost, (cost->height) - 1, 0, 1);
		}
		else if (prev_col == cost->width - 1) {
			min_col = Matrix_column_of_min_value_in_row(cost, (cost->height) - 1, cost->width - 2, cost->width - 1);
		}
		else {
			min_col = Matrix_column_of_min_value_in_row(cost, (cost->height) - 1, prev_col - 1, prev_col + 1);
		}
		seam[cost->height - 2 - i] = min_col;
	}
}


// REQUIRES: img points to a valid Image
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
  //assert(false); // TODO Replace with your implementation!

}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(false); // TODO Replace with your implementation!
}

