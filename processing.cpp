#include <cassert>
#include <vector>
#include "processing.hpp"

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
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
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
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
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
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {


const int IMG_WIDTH = Image_width(img);
const int IMG_HEIGHT = Image_height(img);

Matrix_init(energy, IMG_WIDTH, IMG_HEIGHT);

int max_energy = 0;
  if (IMG_WIDTH >2 && IMG_HEIGHT >2){
    for (int r=1; r<(Image_height(img)-2); r++){
      for (int c=1; c<(Image_width(img)-2); c++){
        Pixel n = Image_get_pixel(img, r-1, c);
        Pixel e = Image_get_pixel(img, r, c+1);
        Pixel s = Image_get_pixel(img, r+1, c);
        Pixel w = Image_get_pixel(img, r, c-1);

        int energy_value =squared_difference(w, e) + squared_difference(n, s);
        *Matrix_at(energy, r, c);
        if(energy_value > max_energy)
          max_energy = energy_value;
      }
    }
  }

  Matrix_fill_border(energy, max_energy);
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
const int matwidth = Matrix_width(energy);
const int matheight = Matrix_height(energy);
Matrix_init(cost, matwidth, matheight);

  for (int c=0; c<matwidth; c++){
    *Matrix_at(cost, 0, c) = *Matrix_at(energy, 0, c);
  }

  for(int r=1; r<matheight; r++){
    for(int c=0; c<matwidth; c++){
      int lowest_energy = *Matrix_at(cost, r-1, c);
      
      if(c>0){ //up left
        if (lowest_energy > *Matrix_at(cost, r-1, c-1))
         lowest_energy = *Matrix_at(cost, r-1, c-1);
      }

      if (c+1<matwidth){ //up right
        if (lowest_energy > *Matrix_at(cost, r-1, c+1))
         lowest_energy = *Matrix_at(cost, r-1, c+1);
      }

      *Matrix_at(cost, r, c) = *Matrix_at(energy, r, c) + lowest_energy;
    }
  }

}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  const int matwidth = Matrix_width(cost);
  const int matheight = Matrix_height(cost);

  vector<int> seam(matheight);

  int min_cost_column = Matrix_column_of_min_value_in_row(cost, matheight-1, 0, matwidth);
  seam[matheight-1]= min_cost_column;
  int starting, ending;



  for (int row = matheight - 2; row >= 0; --row) {
    starting = (min_cost_column > 0) ? min_cost_column - 1 : 0;
    ending = (min_cost_column + 2 < matwidth) ? min_cost_column + 2 : matwidth;
    
    min_cost_column = Matrix_column_of_min_value_in_row(cost, row, starting, ending);
    seam[row] = min_cost_column;
  }

  return seam;

}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  const int IMG_WIDTH = Image_width(img);
  const int IMG_HEIGHT = Image_height(img);

  Image processed_image;
  Image_init(&processed_image, IMG_WIDTH-1, IMG_HEIGHT);

  for (int r = 0; r<IMG_HEIGHT; r++)
  {
    int remove = seam[r];

    for (int c=0; c<remove; c++){
      Image_set_pixel(&processed_image, r, c, Image_get_pixel(img, r ,c));
    }

    for (int c=remove+1; c<IMG_WIDTH; c++){
      Image_set_pixel(&processed_image,r, c-1, Image_get_pixel(img, r ,c));
    }
  }

  *img = processed_image;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {

  for (int x = Image_width(img); x > newWidth; x--) {
    Matrix energy, cost;
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);
    const std::vector<int> seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img, seam);
  }

}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
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
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
