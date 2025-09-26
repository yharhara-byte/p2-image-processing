#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char* argv[]) {

  if(argc != 4 && argc != 5) 
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string fin = argv[1];
  string fout = argv[2];
  int new_w = stoi(argv[3]);
  int new_h = -1;

  if(argc == 5) 
  {
    new_h = stoi(argv[4]);
  }

  ifstream in(fin);
  if(!in) 
  {
    cout << "Error opening file: " << fin << endl;
    return 1;
  }

  Image pic;
  Image_init(&pic, in);
  in.close();

  int old_w = Image_width(&pic);
  int old_h = Image_height(&pic);

  if(new_h == -1) 
  {
    new_h = old_h;
  }

  if(new_w <= 0 || new_w > old_w || new_h <= 0 || new_h > old_h) 
  {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  seam_carve(&pic, new_w, new_h);

  ofstream out(fout);
  if(!out) 
  {
    cout << "Error opening file: " << fout << endl;
    return 1;
  }

  Image_print(&pic, out);
  out.close();

  return 0;
}
