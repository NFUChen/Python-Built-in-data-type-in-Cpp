#include <iostream>
#include "PythonDataTypes/string.h"
using std::cout;
using std::endl;

int main()
{
  // String contains some useful mehtod that python str offers
  String str = " HeLlo, wOrLd ";
  cout << "str.length(): " << str.length() << endl; // = str.size() 
  cout << "str.upper(): " << str.upper() << endl;
  cout << "str.lower(): " << str.lower() << endl;
  cout << "str.capitalize(): " << str.capitalize() << endl;
  cout << "str.title(): " << str.title() << endl;
  cout << "str.strip(): "  << str.strip() << endl;
  // strip offers to strip specified character
  String trailing_string = "--------Hello World--------";
  cout << String(trailing_string).strip('-') << endl;
  // method chaining is also possible 
  cout << String(trailing_string).strip('-').upper() << endl;
  cout << String(trailing_string).strip('-').lower() << endl;

  // string padding
  cout << String("ABC").pad_left(5, '-') << endl;  // "--ABC"
  cout << String("ABC").pad_right(5, '-') << endl; //"ABC--"
  cout << String("ABC").center(5, '-') << endl;    // -ABC-"

  cout << String("ABC").endswith("C") << endl; // 1
  cout << String("ABC").startswith("A") << endl; // 1
  cout << String("ABC").is_contains("AB") << endl; // 1
  cout << String("AB").is_in("ABC") << endl; // 1

  cout << String("ABC").replace("AB", "Z") << endl; // "ZC"
  
  // number conversion
  // String -> Number type
  cout << String("123").to_number<int>() << endl; // 123
  cout << String("123.123").to_number<double>() << endl; // 123.0
  // Number Type to String
  cout << String(123) << endl; // "123"
  cout << String(123.123) << endl; // "123.123000" be careful with this behaviour while converting double into string
  cout << String("123").isnumeric() << endl; // 1
  cout << String("123.0").isnumeric() << endl; // 0, since . is not a number
  cout << String("ABC").isalpha() << endl; // 1
  cout << String("ABC.").isalpha() << endl; // 0, since . is not an alphabet
  cout << String(" ").isspace() << endl; // 1

  // .count() returns the number of occurrences of a substring in the given string.
  cout << String("C++ is popular programming language").count("p") << endl; // 3

  
  // count after first 'i' and before the last 'i'
  cout << String("Python is awesome, isn't it?").count("i", 8, 25) << endl; // 1

  // .index() returns the index of a substring inside the string (if found). 
  // If the substring is not found, it raises an exception.
  String text = "Python is fun";
  cout << text.index("is") << endl; // 7
  // cout << text.index("C++") << endl; // substring not found error

  // .index() returns the index of a substring inside the string (if found).
  // If the substring is not found, returns -1.
  cout << text.find("is") << endl; // 7
  cout << text.find("C++") << endl;  // -1

  // .slice(inclusive_index, exclusive_index) returns specified range of substring
  cout << String("ABCDE").slice() << endl;     // "ABCDE" = str[::]
  cout << String("ABCDE").slice(1, 3) << endl; // "BC" = str[1:3]
  

  // .substr(start_index, substring_length)
  cout << String("ABCDE").substr(1, 2) << endl; // returns a substring from index 1, character length of 2 = "BC"
  // if substring_length is greater than substring, as many characters as possible are included
  cout << String("ABCDE").substr(1, 100) << endl; // "BCDE"

  // .join(iterable) takes all items in an iterable and joins them into one string.
  cout << String("-").join("ABCDE") << endl; // "A-B-C-D-E-"

  // .split(delimiter = " ") splits a string into a list based on specified delimiter.
  // split method returns a Python List 
  cout << String("welcome to the jungle").split() << endl; // [ "welcome", "to", "the", "jungle"]
  cout << String("hello my name is Peter").split(" ") << endl; // [ "hello", "my", "name", "is", "Peter"]

  auto to_upper = [](const String &str) -> String
  {
    return str.upper();
  };
  // bonus, combining String with List
  cout << String("hello my name is Peter").split(" ").map<String>(to_upper) << endl; // get uppercase of each word, [ 5, 2, 4, 2, 5]
}