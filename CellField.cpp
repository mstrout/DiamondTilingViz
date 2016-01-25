#include "CellField.hpp"

#include <fstream>
using namespace std;

int CellField::sSpacing = 10;
int CellField::sRadius = 5;

CellField::CellField(int x_start, int y_start, int width, int height) {
    mXStart = x_start;
    mYStart = y_start;
    mWidth = width;
    mHeight = height;

    mLabel = new string*[mHeight];
    mStroke = new string*[mHeight];
    mFill = new string*[mHeight];

    for(int i = 0; i < mHeight; i++) {
        mLabel[i] = new string[mWidth];
        mStroke[i] = new string[mWidth];
        mFill[i] = new string[mWidth];

        for(int j = 0; j < mWidth; j++) {
            mStroke[i][j] = "black";
            mFill[i][j] = "white";
            mLabel[i][j]="";
        }
    }

    mBoxX1 = NO_BOX;
    mBoxY1 = NO_BOX;
    mBoxX2 = NO_BOX;
    mBoxY2 = NO_BOX;
}

void CellField::printToSVG(SVGPrinter& svg_printer) {

    // place a box behind cells if specified
    if(mBoxX1 != NO_BOX) {
        int x = (mBoxX1) * sSpacing + sSpacing/2;
        int y = (mHeight - mBoxY2) * sSpacing - sSpacing/2;
        int w = (mBoxX2 - mBoxX1 + 1) * sSpacing;
        int h = (mBoxY2 - mBoxY1 + 1) * sSpacing;

        svg_printer.printRectangle(mXStart+x, mYStart+y, 
                                   w, h, "darkgrey", "lightgrey");
    }
 
    // output the field of cells
    for(int i = 0; i < mHeight; i++) {
        for(int j = 0; j < mWidth; j++) {
            int x = (j+1) * sSpacing;
            int y = (mHeight - i) * sSpacing;
            
            svg_printer.printCircle(
                mXStart+x, mYStart+y, sRadius, mStroke[j][i], mFill[j][i]);
                
            svg_printer.printCenteredText(
                mXStart+x, mYStart+y, mLabel[j][i]);
        }
    }
}

void CellField::setLabel(int x, int y, string label) {
    mLabel[x][y] = label;
}

void CellField::setStroke(int x, int y, string stroke) {
    mStroke[x][y] = stroke;
}

void CellField::setFill(int x, int y, string fill) {
    mFill[x][y] = fill;
}

void CellField::setBox(int x1, int y1, int x2, int y2) {
    mBoxX1 = x1; mBoxY1 = y1; mBoxX2 = x2; mBoxY2 = y2;
}

string CellField::getLabel(int x, int y) {
   return(mLabel[x][y]);
}

string CellField::getStroke(int x, int y) {
   return(mStroke[x][y]);
}

string CellField::getFill(int x, int y) {
   return(mFill[x][y]);
}

