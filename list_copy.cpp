#include <iostream>
#include "PythonDataTypes/list.h"
#include <utility>
#include <chrono>

using std::cout;
using std::endl;

int main()
{

  List<char> list1 = {'a', 'e', 'i', 'o', 'i', 'u'};
  cout << list1.index('u') << endl;
}