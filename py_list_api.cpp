#include <iostream>
#include "PythonDataTypes/list.h"
using std::cout;
using std::endl;

int main()
{
    // initialized a empty list;
    List<int> list = {};
    // append a element
    list.append(1);
    // access element with bracket (operator[])
    cout << "list[0]: " << list[0] << endl; // 1
    // negative indexing is also supported
    cout << "list[-1]: " << list[-1] << endl; // last element -> 1
    // get the length of list
    cout << "list.length(): " << list.length() << endl; // similar to len(list)

    // modify element with bracket
    list[0] = 20;
    cout << list << endl;
    // extend multiple elements
    list.extend({5, 4, 3, 2}); // extended with initializer_list
    // extend accepts 'iterables' (container having .begin() and .end() methods implemented),
    // below only takes another List as example, but containers (e.g. std::vector, std::set, Python Set) are all accepted
    List<int> another_list = {1, 4, 2, 3, 4};
    list.extend(another_list);
    cout << list << endl;

    // list can be sorted, just like in python
    // if element is user-defined type (i.e. custom class), make sure you implement 'operator<' to make it comparable
    list.sort(); // an inplace operation, return void (std::sort under the hood)
    cout << "After sorting: " << list << endl;

    // list can be reversed
    list.reverse(); // an inplace operation, return void (std::reverse under the hood)
    cout << "After reversing: " << list << endl;

    // count occurances of certain element in the list (
    // if element is user-defined type (i.e. custom class), make sure you implement 'operator==' to make it comparable
    cout << "4 occurs " << list.count(4) << " times." << endl; // [ 5, 4, 4, 4, 3, 3, 2, 2, 1, 1] -> 3

    // .index() returns the index of the specified element in the list.
    // if element is user-defined type (i.e. custom class), make sure you implement 'operator==' to make it comparable
    cout << "First 1 appers at index " << list.index(1) << endl; // [ 5, 4, 4, 4, 3, 3, 2, 2, 1, 1] -> 8

    // .copy()  returns a copy of the list.
    List<int> copy_list = list.copy();
    copy_list[0] = 1000;
    cout << "Copy List: " << copy_list << endl;
    // modifing copy of list won't affect original list
    cout << "Original List: " << list << endl;

    // .slice(inclusive idx, exclusive idx) for list slicing
    cout << "list[0:5]: " << list.slice(0, 5) << endl; // [20, 5, 4, 4,4]
    // .slice also supports step
    cout << "list[0:5:2]" << list.slice(0, 5, 2) << endl; // [20, 4, ,4]

    cout << "Is 1 in list: " << list.is_contains(1) << endl;   // check if 1 is in the list, true
    cout << "Is 10 in list: " << list.is_contains(10) << endl; // check if 10 is in the list, false

    // .insert() inserts an element to the list at the specified index
    list.insert(3, 100); // insert value 100 at index 3
    cout << "After insertion: " << list << endl;

    // .is_all() check if all element is specified value
    // method chaining is also possible
    //  list([1,1,1])
    cout << "[1,1,1].is_all(1): " << List<int>({1, 1, 1}).is_all(1) << endl; // [1,1,1] -> true
    cout << "[1,2,3].is_all(1): " << List<int>({1, 2, 3}).is_all(1) << endl; // [1,2,3] -> false

    // .remove() removes the first matching element (which is passed as an argument) from the list.
    // If the element doesn't exist, it throws value not in list error
    // if element is user-defined type (i.e. custom class), make sure you implement 'operator==' to make it comparable
    cout << "list before removing 1: " << list << endl;
    list.remove(1); // first one will be removed
    cout << "list after removing 1: " << list << endl;

    // .pop removes the item at the given index from the list and returns the removed item.
    int last_element = list.pop();   // [1, 2, 3] -> remove 3 and return it.
    int first_element = list.pop(0); // [1, 2, 3] -> remove 1 and return it.
    // .clear() removes all items from the list.
    list.clear();
    cout << "After clearing: " << list << endl;

    // other custom methdo (.map, .for_each, )
    List<int> list2 = {1, 2, 3, 4, 5};
    // .map() creates a new array populated with the results of calling a provided function on every element in the calling array.
    // since map method doesn't know if an given array will change its type in the callback (e.g., bool callback will return bool, although lits type is int)
    // passing template callback resulting type is required (e.g., list.map<bool>(callback) if callback reutrns bool)
    auto plus_3 = [](const int &num)
    {
        return num + 3;
    };

    cout << "Map with plus_3 callback: " << list2.map<int>(plus_3) << endl;

    auto is_greater_than_3 = [](const int &num)
    {
        return num > 3;
    };
    cout << "list calling .map() with is_greater_than_3 callback: " << list2.map<bool>(is_greater_than_3) << endl;

    // empty list calling map will returns empty list with speified type
    cout << "empty list calling .map() with is_greater_than_3 callback: " << list.map<bool>(is_greater_than_3) << endl;

    // .for_each() executes a provided function once for each array element, thus it is an inplace operation
    // it is encouraged to not return anything from callback passing into .for_each()
    // Note: calling list.for_each will return void
    auto plus_3_inplace = [](int &num)
    {
        num += 3;
    };

    cout << "list2 before for_each(plus_3_inplace) is called: " << list2 << endl;
    list2.for_each(plus_3_inplace);
    cout << "list2 after for_each(plus_3_inplace) is called: " << list2 << endl; //  [1, 2, 3, 4, 5] -> [4, 5, 6, 7, 8]

    // other arithmetic function
    cout << "----Other Arithmetic Functions----" << endl;
    cout << "list2.min(): " << list2.min() << endl;
    cout << "list2.max(): " << list2.max() << endl;
    cout << "list2.mean(): " << list2.mean() << endl;
    cout << "list2.sum(): " << list2.sum() << endl;
    return 0;
}