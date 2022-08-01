#include <iostream>
#include <map>
#include <unordered_map>
#include "PythonDataTypes/dictionary.h"
#include <vector>
#include "PythonDataTypes/list.h"
#include <set>
#include "PythonDataTypes/set.h"
#include <string>
#include "PythonDataTypes/string.h"
using std::cout;
using std::endl;



int main() {
    std::vector<int> std_vec = {1,2,3,4, 5, 1,2,3,4,5};

    // std::vector -> Python List
    List<int> py_list1 = std_vec; 
    cout << py_list1 << endl; // [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
    // std::vector -> Python Set
    Set<int> py_set1 = std_vec; 
    cout << py_set1 << endl; // {1, 2, 3, 4, 5}

    std::set<int> std_set = {1, 2, 3, 4, 5};

    // std::set -> Python List
    List<int> py_list2 = std_set; 
    cout << py_list2 << endl; // {1, 2, 3, 4, 5}
    // std::set -> Python Set
    Set<int> py_set2 = std_set;
    cout << py_set2 << endl; // {1, 2, 3, 4, 5}

    // std::unordered_map/std::map -> Python Dictionary
    std::unordered_map<int, char> unordered_map = {
        {0, 'a'}, {1,'b'}, {2,'c'}
    };
    std::map<int, char> map = {
        {0, 'a'}, {1, 'b'}, {2, 'c'}
    };
    // conversion works both from unordered_map and map to Dict, as shown below
    Dict<int, char> py_dict1 = unordered_map; // {0 : 0, 1 : 1, 2 : 2}
    py_dict1 = map;                           //{2 : 2, 1 : 1, 0 : 0}
    cout << py_dict1 << endl; 

    // const char* -> Python String
    const char* char_array = "abc";
    cout << String(char_array) << endl;
    // char -> Python String
    char a_char = 'a';
    cout << String(a_char) << endl;
    // std::string -> Python String
    std::string std_string = "abc";
    cout << String(std_string) << endl;
    // number type -> Python String -> use std::to_string under the hood
    cout << String(1) << endl;  // "1"
    // be careful while converting double into String, might not work as you expect
    cout << String(1.0) << endl; // "1.000000"

    return 0;
}