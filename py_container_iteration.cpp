#include <iostream>
#include "PythonDataTypes/dictionary.h"
#include "PythonDataTypes/list.h"
#include "PythonDataTypes/set.h"
#include "PythonDataTypes/string.h"
using std::cout;
using std::endl;

int main() {

 
    // Python List iteration
    // for loop with index
    cout << "--Python List--" << endl;
    List<int> py_list = {1,2,3};
    for (std::size_t idx =0; idx < py_list.length(); idx++) {
        cout << py_list[idx] << endl;
    }
    cout << "----" << endl;
    // for loop, iterator pointer
    for (auto it = py_list.begin(); it != py_list.end(); it++)
    {
        cout << *it << endl;
    }

    cout << "----" << endl;
    // range-based for loop
    for (const int& val: py_list) {
        cout << val << endl;
    }

    Set<int> py_set = {1,2,3};
    // Python Set iteration
    // for loop, iterator pointer
    cout << "--Python Set--" << endl;
    for (auto it = py_set.begin(); it != py_set.end(); it++) {
        cout << *it << endl;
    }
    cout << "----" << endl;
    // range-based for loop
    for (const int& val: py_set) {
        cout << val << endl;
    }
    cout << "--Python Dict--" << endl;
    Dict<int, char> py_dict = {
        {0, 'a'}, {1, 'b'}, {2, 'c'}
    };
    // Python Dict iteration
    // for loop, iterator pointer
    for (auto it = py_dict.begin(); it != py_dict.end(); it++)
    {
        cout << (*it).first << ": " << (*it).second << endl;
    }
    cout << "----" << endl;
    // range-based for loop
    for (const auto &[key, value] : py_dict.items()) // .items() is just make it more idiomatic, just py_dict will also work
//  for (const auto &[key, value] : py_dict)
    { 
        cout << key << ": " << value << endl;
    }
    // Python String iteration
    
    cout << "--Python String--" << endl;
    String py_string("ABCDEFG");
    // for loop, index approach
    for (std::size_t idx = 0; idx < py_string.size(); idx++) {
        cout << py_string[idx] << endl;
    }
    cout << "----" << endl;
    // for loop, iterator pointer
    for (auto it = py_string.begin(); it != py_string.end(); it++)
    {
        cout << *it << endl;
    }
    cout << "----" << endl;
    // range-based for loop
    for (const char & _char : py_string)
    {
        cout << _char << endl;
    }

    return 0;
}