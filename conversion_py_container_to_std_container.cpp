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

int main()
{
    
    List<int> py_list = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5}; 
    // Python List -> std::vector
    std::vector<int> std_vec1 = py_list.values(); // use .values method to get underlying container (i.e. vector) to copy data from List to std::vector
    std::vector<int> std_vec2(py_list.begin(), py_list.end()); // or use iterator to copy data

    // Python Set -> std::vector
    Set<int> py_set = {1,2,3,4,5};
    std::set<int> std_vec1 = py_set.values();               // same way goes for conveting fomr Python Set to std::vector
    std::set<int> std_vec2(py_set.begin(), py_set.end());   // or use iterator to copy data
    

    // Python List -> std::set
    std::set<int> std_set1(py_list.begin(), py_list.end()); // since std::set is a different container from Python List, only iterator approach will work.
    // Python Set -> std::set
    std::set<int> std_set3(py_set.values()); // Python Set to std::set works well with two appraoches.
    std::set<int> std_set2(py_set.begin(), py_set.end()); 
    

    // Python Dictionary -> std::unordered_map/std::map
    Dict<int, char> py_dict = {
        {0, 'a'}, {1, 'b'}, {2, 'c'}
    };
    // both std::unordered_map/std::map words for iterator appraoch
    std::unordered_map<int, char> unordered_map(py_dict.begin(), py_dict.end());
    std::map<int, char> map(py_dict.begin(), py_dict.end()); 
    // since Python Dict (in our implementation) under the hook is constructed with std::unordered_map, 
    // so calling .items() from Python Dict works well with converting into std::unordered_map, as shown below
    unordered_map = py_dict.items(); // it works.

    // Python String -> std::string
    String py_string = "abc";
    std::string std_string(py_string.begin(), py_string.end());
    // or just calling .values() and assign to a std::string variable
    std_string = py_string.values(); // .values() returns a std::string


    return 0;
}