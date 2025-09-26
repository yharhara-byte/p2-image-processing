#include <cassert>
#include "Matrix.hpp"

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
mat->height = height;
mat->width = width;
mat->data.assign(width*height, 0);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os<<mat->width<<" "<<mat->height<<std::endl;
  for (int h = 0; h < mat->height; h++)
  {
    for (int w = 0; w < mat->width; w++)
    {
      os<<mat->data[h * mat->width + w] << " ";    
    }
    os<<std::endl;
  }
  
 
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  return &mat->data.at((row)*mat->width + column);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  return &mat->data.at((row)*mat->width + column);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
for (int w = 0; w < mat->width; w++)
  {
    for (int h = 0; h < mat->height; h++)
    {
      mat->data[h * mat->width + w] = value;    
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {

  for (int w = 0; w < mat->width; w++)
  {
    for (int h = 0; h < mat->height; h++)
    {
      if (w == 0 || h == 0 || w == (mat->width-1) || h == (mat->height-1))
      mat->data[h * mat->width + w] = value;    
    }
  }
}


// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int max;
for (int w = 0; w < mat->width; w++)
  { 
    if (w==0)
      max = mat->data[0];
    for (int h = 0; h < mat->height; h++)
    {
      if (max < mat->data[h * mat->width + w])
      max = mat->data[h * mat->width + w] ;    
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {

  int min = mat->data[row * mat->width + column_start]; 
  int mincol = column_start; 
  
  for (int w = column_start; w < column_end; w++) { 
    if (min > mat->data[row * mat->width + w])
    { 
      min = mat->data[row * mat->width + w];
      mincol = w; 
    } 
  } 
  return mincol;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
int min = mat->data[row * mat->width + column_start]; 
  
  for (int w = column_start; w < column_end; w++) { 
    if (min > mat->data[row * mat->width + w])
    { 
      min = mat->data[row * mat->width + w];
    } 
  } 
  return min;
}
