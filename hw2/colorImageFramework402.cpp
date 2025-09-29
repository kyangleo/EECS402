#include <iostream>
using namespace std;

// Author: Kaiyang Luo, Date: Sep 25
/*
*/

// CONSTANT DEFINITION
const int MIN_COLOR_VALUE = 0;
const int MAX_COLOR_VALUE = 1000;
const int IDX_DEFAULT = -99999;
const int IMAGE_ROW_NUM = 10;
const int IMAGE_COL_NUM = 18;


// CLASS DEFINITION
class ColorClass
{
  private:
    // Member attributes
    // Must be in the range of [MIN_COLOR_VALUE, MAX_COLOR_VALUE]
    int redVal;
    int greenVal;
    int blueVal;

    // Private member function
    // Clip to valid range
    int colorClip(const int inVal);

  public:
    // Public member function
    
    // Ctor
    // The default ctor set full white
    ColorClass();
    // The value ctor set the initial values to the values provided.
    // Clip if need.
    ColorClass(
         const int inRed,
         const int inGreen,
         const int inBlue
         );

    // Set the indicated color in full
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    // Set color value to the provided and clip if need(return true)
    bool setTo(
         const int inRed,
         const int inGreen,
         const int inBlue
         );
    // Set color value to the same as "inColor" and clip if need(return true)
    bool setTo(
         const ColorClass &inColor
         );

    // Add "rhs" and clip if need(return true)
    bool addColor(
         const ColorClass &rhs
         );
    // Substract "rhs" and clip if need(return true)
    bool subtractColor(
         const ColorClass &rhs
         );
    // Multiply each RGB value by the "adjFactor" to adjust brightness.
    // Assign back to an int for the updated value, using cast.
    // Clip if need(return true).
    bool adjustBrightness(
         const double adjFactor
         );

    // Print color values using the format "R: <red> G: <green> B: <blue>"
    void printComponentValues() const;

};

// Stand alone. Know nothing about "ColorClass" and "ColorImageClass".
class RowColumnClass
{
  private:
    // Member Attributes
    int rowIdx;
    int colIdx;
  
  public:
    // Member Functions

    // Ctor
    // The default ctor sets both the attributes to "IDX_DEFAULT"
    RowColumnClass();
    // The value ctor sets values to the corresponding value passed in
    RowColumnClass(
         const int inRow,
         const int inCol
         );

    // These setter functions simply do what their names imply
    void setRowCol(
         const int inRow,
         const int inCol
         );
    void setRow(
         const int inRow
         );
    void setCol(
         const int inCol
         );

    // These getter functions simply return the appropriate value
    int getRow() const;
    int getCol() const;

    // Add the input value to the attributes of object
    void addRowColTo(
         const RowColumnClass &inRowCol
         );

    // Print attributes in the format "[<row>,<col>]"
    void printRowCol() const;
};

class ColorImageClass
{
  private:
    // Member Attributes
    int rowNum;
    int colNum;
    ColorClass pixelArrary[IMAGE_ROW_NUM][IMAGE_COL_NUM];

  public:
    // Member Functions
    
    // Ctor
    // Default ctor set all pixels to full black
    ColorImageClass();
    
    // Initial all pixels to the color provided 
    void initializeTo(
         const ColorClass &inColor
         );

    // Add image to object. Return true if require clipping
    bool addImageTo(
         const ColorImageClass &rhsImg
         );

    // Add images and assign object to the result.
    // Return true if require clipping.
    bool addImages(
         const int numImgsToAdd,
         const ColorImageClass imagesToAdd[]
         );

    // Set pixels at the "inRowCol" location to the "inColor".
    // If the location is valid, return true.
    // Else, image is not modified and return false.
    bool setColorAtLocation(
         const RowColumnClass &inRowCol,
         const ColorClass &inColor
         );

    // If "inRowCol" is valid for the image, return true and "outColor" is
    // assigned to the color of the image pixel at that position.
    // Else, return false and not modify "outColor".
    bool getColorAtLocation(
         const RowColumnClass &inRowCol,
         ColorClass &outColor
         ) const;

    // Print the contents of the image.
    void printImage() const;

};
// MAIN BODY
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}
#endif

// FUNCTION IMPLEMENT

// ===== RowColumnClass Member Function =====

// Ctor
// Default ctor
RowColumnClass::RowColumnClass()
{
  rowIdx = IDX_DEFAULT;
  colIdx = IDX_DEFAULT;
}

// Value ctor
RowColumnClass::RowColumnClass(
     const int inRow,
     const int inCol
    )
{
  rowIdx = inRow;
  colIdx = inCol;
}

// These setter functions simply do what their names imply
void RowColumnClass::setRowCol(
     const int inRow,
     const int inCol
     )
{
  rowIdx = inRow;
  colIdx = inCol;
}    

void RowColumnClass::setRow(
     const int inRow
     )
{
  rowIdx = inRow;
}

void RowColumnClass::setCol(
     const int inCol
     )
{
  colIdx = inCol;
}

// These getter functions simply return the appropriate value
int RowColumnClass::getRow() const
{
  return rowIdx;
}

int RowColumnClass::getCol() const
{
  return colIdx;
}

// Add the input value to the attributes of object
void RowColumnClass::addRowColTo(
     const RowColumnClass &inRowCol
     )
{
  rowIdx += inRowCol.getRow();
  colIdx += inRowCol.getCol();
}

// Print attributes in the format "[<row>,<col>]"
void RowColumnClass::printRowCol() const
{
  cout << "[" << rowIdx << "," << colIdx << "]";
}

// ===== ColorClass Member Function =====

// Clip to valid range
int ColorClass::colorClip(const int inVal)
{
  int outVal;
  if (inVal < MIN_COLOR_VALUE)
    outVal = MIN_COLOR_VALUE;
  else if (inVal > MAX_COLOR_VALUE)
    outVal = MAX_COLOR_VALUE;
  else
    outVal = inVal;
  
  return outVal;
}

// Ctor
// The default ctor set full white
ColorClass::ColorClass()
{
  redVal = 1000;
  greenVal = 1000;
  blueVal = 1000;
}
// The value ctor set the initial values to the values provided
ColorClass::ColorClass(
     const int inRed,
     const int inGreen,
     const int inBlue
     )
{
  redVal = colorClip(inRed);
  greenVal = colorClip(inGreen);
  blueVal = colorClip(inBlue);
}

// Set the indicated color in full
void ColorClass::setToBlack()
{
  redVal = 0;
  greenVal = 0;
  blueVal = 0;
}
void ColorClass::setToRed()
{
  redVal = 1000;
  greenVal = 0;
  blueVal = 0;
}
void ColorClass::setToGreen()
{
  redVal = 0;
  greenVal = 1000;
  blueVal = 0;
}
void ColorClass::setToBlue()
{
  redVal = 0;
  greenVal = 0;
  blueVal = 1000;
}
void ColorClass::setToWhite()
{
  redVal = 1000;
  greenVal = 1000;
  blueVal = 1000;
}

// Set color value to the provided and clip if need(return true)
bool ColorClass::setTo(
     const int inRed,
     const int inGreen,
     const int inBlue
     )
{
  redVal = colorClip(inRed);
  greenVal = colorClip(inGreen);
  blueVal = colorClip(inBlue);
  
  if (redVal == inRed && greenVal == inGreen && blueVal == inBlue)
    return false;
  else
    return true;
}
// Set color value to the same as "inColor". Since "inColor" is the object
// of ColorClass, we don't need to clip.
bool ColorClass::setTo(
     const ColorClass &inColor
     )
{
  redVal = inColor.redVal;
  greenVal = inColor.greenVal;
  blueVal = inColor.blueVal;
  
  return false;
}

// Add "rhs" and clip if need(return true)
bool ColorClass::addColor(
     const ColorClass &rhs
     )
{
  int sumRed = redVal + rhs.redVal;
  int sumGreen = greenVal + rhs.greenVal;
  int sumBlue = blueVal + rhs.blueVal;
  
  redVal = colorClip(sumRed);
  greenVal = colorClip(sumGreen);
  blueVal = colorClip(sumBlue);

  if (redVal == sumRed && greenVal == sumGreen && blueVal == sumBlue)
    return false;
  else
    return true;
}     
// Substract "rhs" and clip if need(return true)
bool ColorClass::subtractColor(
     const ColorClass &rhs
     )
{
  int subRed = redVal - rhs.redVal;
  int subGreen = greenVal - rhs.greenVal;
  int subBlue = blueVal - rhs.blueVal;
  
  redVal = colorClip(subRed);
  greenVal = colorClip(subGreen);
  blueVal = colorClip(subBlue);

  if (redVal == subRed && greenVal == subGreen && blueVal == subBlue)
    return false;
  else
    return true;
}
// Multiply each RGB value by the "adjFactor" to adjust brightness.
// Assign back to an int for the updated value, using cast.
// Clip if need(return true).
bool ColorClass::adjustBrightness(
     const double adjFactor
     )
{
  int mulRed = static_cast<int>(redVal * adjFactor);
  int mulGreen = static_cast<int>(greenVal * adjFactor);
  int mulBlue = static_cast<int>(blueVal * adjFactor);

  redVal = colorClip(mulRed);
  greenVal = colorClip(mulGreen);
  blueVal = colorClip(mulBlue);

  if (redVal == mulRed && greenVal == mulGreen && blueVal == mulBlue)
    return false;
  else
    return true;
}   

// Print color values using the format "R: <red> G: <green> B: <blue>"
void ColorClass::printComponentValues() const
{
  cout << "R: " << redVal << " G: " << greenVal << " B: " << blueVal;
}

// ===== ColorImageClass Member Function =====
   
// Ctor
// Default ctor set all pixels to full black
ColorImageClass::ColorImageClass()
{
  rowNum = IMAGE_ROW_NUM;
  colNum = IMAGE_COL_NUM;
  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      pixelArrary[i][j].setToBlack();
    }
  }
}

// Initial all pixels to the color provided 
void ColorImageClass::initializeTo(
     const ColorClass &inColor
     )
{
  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      pixelArrary[i][j].setTo(inColor);
    }
  }
}    

// Add image to object. Return true if require clipping
bool ColorImageClass::addImageTo(
     const ColorImageClass &rhsImg
     )
{
  bool flagClip = false;

  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      flagClip = pixelArrary[i][j].addColor(rhsImg.pixelArrary[i][j]) ||
                 flagClip;
    }
  }

  return flagClip;
}     

// Add images and assign object to the result.
// Return true if require clipping.
bool ColorImageClass::addImages(
     const int numImgsToAdd,
     const ColorImageClass imagesToAdd[]
     )
{
  ColorImageClass sumImg;
  bool flagClip = false;

  for (int i = 0; i < numImgsToAdd; i++)
  {
    flagClip = sumImg.addImageTo(imagesToAdd[i]) || flagClip;
  }
  
  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < colNum; j++)
    {
      pixelArrary[i][j].setTo(sumImg.pixelArrary[i][j]);
    }
  }

  return flagClip;
}     

// Set pixels at the "inRowCol" location to the "inColor".
// If the location is valid, return true.
// Else, image is not modified and return false.
bool ColorImageClass::setColorAtLocation(
     const RowColumnClass &inRowCol,
     const ColorClass &inColor
     )
{
  int lowerBound = 0;
  int rowLoc = inRowCol.getRow();
  int colLoc = inRowCol.getCol();

  if (rowLoc >= lowerBound && rowLoc < rowNum &&
      colLoc >= lowerBound && colLoc < colNum)
  {
    pixelArrary[rowLoc][colLoc].setTo(inColor); 
    return true;
  }
  else
  {
    return false;
  }
  
}    

// If "inRowCol" is valid for the image, return true and "outColor" is
// assigned to the color of the image pixel at that position.
// Else, return false and not modify "outColor".
bool ColorImageClass::getColorAtLocation(
     const RowColumnClass &inRowCol,
     ColorClass &outColor
     ) const
{
  int lowerBound = 0;
  int rowLoc = inRowCol.getRow();
  int colLoc = inRowCol.getCol();

  if (rowLoc >= lowerBound && rowLoc < rowNum &&
      colLoc >= lowerBound && colLoc < colNum)
  {
    outColor.setTo(pixelArrary[rowLoc][colLoc]);
    return true;
  }    
  else
  {
    return false;
  }
}     

// Print the contents of the image.
void ColorImageClass::printImage() const
{
  int stopDashCol = colNum - 1;
  
  for (int i = 0; i < rowNum; i++)
  {
    for (int j = 0; j < stopDashCol; j++)
    {
      pixelArrary[i][j].printComponentValues();
      cout << "--";
    }
    pixelArrary[i][stopDashCol].printComponentValues();
    cout << endl;
  }
}


