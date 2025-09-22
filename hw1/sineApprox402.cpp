#include <iostream>
using namespace std;

//Author: Kaiyang Luo
//Date: Sep 15, 2025
//Desc: To estimate the sine of an angle using Taylor series without relying
//on any other programs or libraries. The number of terms in this series 
//will be 5 or less. The values of angles in units of radians or degrees are
//both accepted.

const double PI_VALUE = 3.14159265359;

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
  char typeDegree;
  char typeRadian;
  bool isSuccess; //indicates whether the whole process goes successfully
  double angleRawVal;
  double angleStdVal;
  double approxSinVal;
  int numTerm;
  int minNumTerm;
  int maxNumTerm;

  typeDegree = 'd';
  typeRadian = 'r';
  isSuccess = true;
  minNumTerm = 1;
  maxNumTerm = 5;

  cout << "Would you like to enter angle in degrees (" << typeDegree 
       << ") or radians (" << typeRadian << ")? ";
  cin >> angleType;

  if (angleType != typeDegree && angleType != typeRadian)
  {
    cout << "ERROR: Invalid input - must respond with either " << typeDegree
         << " or " << typeRadian << "!";
    cout << endl;
    isSuccess = false;
  }
  else
  {
    cout << "Enter the angle: ";
    cin >> angleRawVal;

    cout << "How many terms to use in the series (" << minNumTerm
         << " to " << maxNumTerm << " inclusive): ";
    cin >> numTerm;

    if (angleType == typeDegree)
    {
      angleStdVal = degreesToRadians(angleRawVal);
    }
    else
    {
      angleStdVal = angleRawVal;
    }

    if (!approximateSine(angleStdVal, numTerm, approxSinVal))
    {
      isSuccess = false;
    }
    else
    {
      cout << "sin(angle) = " << approxSinVal << endl;
      cout << endl;
      cout << "Here are results for other numbers of terms:" << endl;
      for (int i = minNumTerm; i <= maxNumTerm; i++)
      {
        if (i != numTerm)
        {
          double otherResult;
          bool otherSuccess;

          otherSuccess = approximateSine(angleStdVal, i, otherResult);
          if (otherSuccess)
          {
            cout << "  # terms: " << i << " result: " << otherResult;
            cout << endl;
          }
        }
      }
    }
  }
  
  if (!isSuccess)
  {
    cout << "Unable to provide results due to invalid inputs!" << endl;
  }
  
  return 0;
}
#endif

double degreesToRadians(const double angleDeg)
{
  double angleReturn;
  int semiCircleDeg;

  semiCircleDeg = 180;
  angleReturn = angleDeg * PI_VALUE / semiCircleDeg;
  return angleReturn;
}

bool toThePower(const double baseVal, const int exponentVal, 
                double& outResult)
{
  int minVal;

  minVal = 0;
  if (exponentVal < minVal)
  {
    return false;
  }
  else
  {
    outResult = 1;
//Initial "i" = 1, since we have considered "i" = 0 for "outResult" = 1.
    for (int i = 1; i <= exponentVal; i++)
    {
      outResult *= baseVal;
    }
    return true;
  }
}

bool computeFactorial(const int inVal, int& outFactorial)
{
  int minNumFactorial;
  int maxNumFactorial;

  minNumFactorial = 0;
  maxNumFactorial = 12;

  if (inVal < minNumFactorial || inVal > maxNumFactorial)
  {
    return false;
  }
  else
  {
    outFactorial = 1;
    for (int i = 1; i <= inVal; i++)
    {
      outFactorial *= i;
    }
    return true;
  }
}
bool approximateSine(const double angleRad, const int numTerms,
                     double& outSineVal)
{
  double angleRadStd;
  int minNumTerm;
  int maxNumTerm;

  minNumTerm = 1;
  maxNumTerm = 5;

  // Input Validation
  if (numTerms < minNumTerm || numTerms > maxNumTerm)
  {
    cout << "ERROR: Invalid input - must respond with value between "
         << minNumTerm << " and " << maxNumTerm << "!" << endl;
    return false;
  }
  
  // Angle Normalization 
  angleRadStd = angleRad;
  while (angleRadStd > PI_VALUE)
  {
    angleRadStd -= 2 * PI_VALUE;
  }

  while (angleRadStd < -PI_VALUE)
  {
    angleRadStd += 2 * PI_VALUE;
  }

  // Calculation Sine Value
  outSineVal = 0.0;

  for (int i = 0; i < numTerms; i++)
  {
    double minusPow;
    double angleRadPow;
    double minusBaseVal;
    int coefFactorial;
    int angleExpVal;
    int endFactorialVal;
    bool doMinusPow;
    bool doAngleRadPow;
    bool doCoefFactorial;

    minusBaseVal = -1.0;
    angleExpVal = 2 * i + 1;
    endFactorialVal = 2 * i + 1;
    doMinusPow = toThePower(minusBaseVal, i, minusPow);
    doAngleRadPow = toThePower(angleRadStd, angleExpVal, angleRadPow);
    doCoefFactorial = computeFactorial(endFactorialVal, coefFactorial);
  
    if (doMinusPow && doAngleRadPow && doCoefFactorial)
    {
      outSineVal += minusPow * angleRadPow / coefFactorial;
    }
    else
    {
      return false;
    }
  }

  // If do successfully
  return true;
}
