// resize.cpp
// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include <fstream>
#include "Image.h"
#include "processing.h"
using namespace std;

// Checks whether or not the command line args are valid
// Checks that the inputted width is less than the image's width
// and same for height if a height was inputted
static int check_cmdln_args(int argc, char* argv[], Image *img) {
    if (atoi(argv[3]) <= 0 || atoi(argv[3]) > Image_width(img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    else if (argc == 5) {
        if (atoi(argv[4]) <= 0 || atoi(argv[4]) > Image_height(img)) {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
    }
    return 0;
}

// Checks whether the inputted files can be read from and written to
static int check_args_and_files(int argc, char* argv[]) {
    if (!(argc == 4 || argc == 5)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    
    string inName = argv[1];
    string outName = argv[2];

    ifstream fin(inName);
    ofstream fout(outName);
    if (!fin.is_open()) {
        cout << "Error opening file: " << inName << endl;
        return 1;
    }
    if (!fout.is_open()) {
        cout << "Error opening file: " << outName << endl;
        return 1;
    }

    fin.close();
    fout.close();

    return 0;
}

// Checks command line arguments and I/O validity, then initializes
// the necessary variables and calls processing functions to resize
// the picture
int main(int argc, char* argv[]) {
    
    if (check_args_and_files(argc, argv) == 1)
        return 1;

    string infile = argv[1];
    Image *img = new Image;
    ifstream fin;
    fin.open(infile.c_str());
    Image_init(img, fin);
    fin.close();
    
    if (check_cmdln_args(argc, argv, img) == 1)
        return 2;

    int width = atoi(argv[3]);
    if (argc == 5) {
        int height = atoi(argv[4]);
        seam_carve(img, width, height);
    }
    else
        seam_carve_width(img, width);

    string outfile = argv[2];
    ofstream fout;
    fout.open(outfile.c_str());
    Image_print(img, fout);
    fout.close();

    delete img;
    return 0;
}