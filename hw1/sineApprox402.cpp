#include <iostream>
using namespace std;

// Project: Sine Approximation
// Author: Kaiyang Luo
// Date: Sep 22, 2025
// Desc: To estimate the sine of an angle using Taylor series without relying
// on any other programs or libraries. The number of terms in this series 
// will be 5 or less. The values of angles in units of radians or degrees are
// both accepted.

// --- Constant ---
const double PI_VALUE = 3.14159265359;
const int MIN_NUM_TERM = 1;
const int MAX_NUM_TERM = 5;
const int MIN_VAL_FCTRL = 0;
const int MAX_VAL_FCTRL = 12;
const char TYPE_DEGREE = 'd';
const char TYPE_RADIAN = 'r';

// --- Function ---

//This function converts the value of "angleDeg" (which will be an angle,
//specified in degrees) to radians and return the result.
double degreesToRadians(const double angleDeg);

//This function raises "baseVal" to the power "exponentVal" and stores the 
//result in the reference parameter "outResult". No input or output is done.
//Only support non-negative exponents. Return true on success.
bool toThePower(const double baseVal, const int exponentVal, 
                double& outResult);

//This function computes the factorial of "inVal" and assigns the result to
//the reference parameter "outFactorial". Only support input values from
//0 to 12 (inclusive). Return true on success.
bool computeFactorial(const int inVal, int& outFactorial);

//This function approximates the value of the sine of "angleRad", using the
//number of terms specified via "numTerms". The result is stored in the 
//output reference parameter "outSineVal". Support input angles of any
//value, but will set it in the range -π to +π. Fail when either 
//"numTerms" is not in the range(1 to 5 inclusive), or functions
//(toThePower and computeFactorial) fail. Return true on success.
bool approximateSine(const double angleRad, const int numTerms, 
                     double& outSineVal);

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
  char angleType;
  bool isSuccess; // indicates whether the whole process goes successfully
  double angleInputVal;
  double angleStdVal; // standard angle value for approximation
  double approxResult;
  int numTerm;

  isSuccess = true;

  // input angle type
  cout << "Would you like to enter angle in degrees (" << TYPE_DEGREE 
       << ") or radians (" << TYPE_RADIAN << ")? ";
  cin >> angleType;

  // check angle type
  if (angleType != TYPE_DEGREE && angleType != TYPE_RADIAN)
  {
    cout << "ERROR: Invalid input - must respond with either " << TYPE_DEGREE
         << " or " << TYPE_RADIAN << "!";
    cout << endl;
    isSuccess = false;
  }
  else
  {
    cout << "Enter the angle: ";
    cin >> angleInputVal;

    cout << "How many terms to use in the series (" << MIN_NUM_TERM
         << " to " << MAX_NUM_TERM << " inclusive): ";
    cin >> numTerm;

    
    // standardize the type of angle
    if (angleType == TYPE_DEGREE)
    {
      angleStdVal = degreesToRadians(angleInputVal);
    }
    else
    {
      angleStdVal = angleInputVal;
    }

    // check approximation function
    if (!approximateSine(angleStdVal, numTerm, approxResult))
    {
      isSuccess = false;
    }
    else
    {
      // print result
      cout << "sin(angle) = " << approxResult << endl;
      cout << endl;
      cout << "Here are results for other numbers of terms:" << endl;
      //print other result
      for (int i = MIN_NUM_TERM; i <= MAX_NUM_TERM; i++)
      {
        if (i != numTerm)
        {
          double otherResult;
          if(approximateSine(angleStdVal, i, otherResult))
          {
            cout << "  # terms: " << i << " result: " << otherResult;
            cout << endl;
          }
        }
      }
    }
  }
  // if fail in approximating, print warning
  if (!isSuccess)
  {
    cout << "Unable to provide results due to invalid inputs!" << endl;
  }
  
  return 0;
}

#endif

// --- Function complement ---

double degreesToRadians(const double angleDeg)
{
  double angleReturn;
  int semiCircleDeg;

  semiCircleDeg = 180;
  
  // formula of transforming degrees to radians
  angleReturn = angleDeg * PI_VALUE / semiCircleDeg;

  return angleReturn;
}

bool toThePower(const double baseVal, const int exponentVal, 
                double& outResult)
{
  int minVal;
  bool doSuccess;

  minVal = 0;
  doSuccess = true;

  if (exponentVal < minVal)// invalid "exponentVal"
  {
    doSuccess = false;    
  }
  else if (exponentVal == minVal)
  {
    outResult = 1.0;
  }
  else
  {
    outResult = 1.0;
    for (int i = 0; i < exponentVal; i++)
    {
      outResult *= baseVal;
    }
  }
  
  return doSuccess;
}

bool computeFactorial(const int inVal, int& outFactorial)
{
  bool doSuccess;

  doSuccess = true;

  if (inVal < MIN_VAL_FCTRL || inVal > MAX_VAL_FCTRL)// invalid "inVal"
  {
    doSuccess = false;
  }
  else
  {
    outFactorial = 1;// By default, 0! = 1
    for (int i = 1; i <= inVal; i++)
    {
      outFactorial *= i;
    }
  }
  
  return doSuccess;
}

bool approximateSine(const double angleRad, const int numTerms,
                     double& outSineVal)
{
  double angleStdRad;
  int coefFctrl;
  int inValFctrl;
  double coefNegPow;
  double negBaseVal;
  int negExpVal; 
  double coefAnglePow;
  int angleExpVal;
  double sumTermVal;
  bool doSuccess;
  bool doNegPow;
  bool doAnglePow;
  bool doFctrl;
  
  doSuccess = true;
  // standardize the range of angle
  if (angleRad >= -PI_VALUE && angleRad <= PI_VALUE)
  {
    angleStdRad = angleRad;
  }
  else
  {
    angleStdRad = angleRad;
    while (angleStdRad < -PI_VALUE)
    {
      angleStdRad += 2 * PI_VALUE;
    }
    while (angleStdRad > PI_VALUE)
    {
      angleStdRad -= 2* PI_VALUE;
    }
  }
  
  // approximate the sine value
  sumTermVal = 0.0;
  negBaseVal = -1.0;
  
  if (numTerms < MIN_NUM_TERM || numTerms > MAX_NUM_TERM)
  {
    cout << "ERROR: Invalid input - must respond with value between "
         << MIN_NUM_TERM << " and " << MAX_NUM_TERM << "!" << endl;
    doSuccess = false;
  }
  else
  {
    for (int i = 0; i < numTerms; i++)
    {
      negExpVal = i;
      angleExpVal = 2 * i + 1;
      inValFctrl = 2 * i + 1;

      doNegPow = toThePower(negBaseVal, negExpVal, coefNegPow);
      doAnglePow = toThePower(angleStdRad, angleExpVal, coefAnglePow);
      doFctrl = computeFactorial(inValFctrl, coefFctrl);
      
      if (doNegPow && doAnglePow && doFctrl)
      {
        sumTermVal += coefNegPow * coefAnglePow / coefFctrl;
      }
      else
      {
        doSuccess = false;
        i = numTerms; // terminate the loop early when "doSuccess" = false
      }
    }
  }
  // assign approximation to "outSineVal"
  if (doSuccess)
  {
    outSineVal = sumTermVal;
  }
  
  return doSuccess;
}
