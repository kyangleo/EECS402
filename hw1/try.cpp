#include <iostream>
using namespace std;

int main()
{
  int i = 0;
  for (i = 1; i <= 2 && 0 > 3; i++)
  {
    cout << "done" << endl;
  }
  cout << "i: " << i << endl;
  return 0;
}
