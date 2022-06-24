#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <initializer_list>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <cassert>

#include "dictionary.h"
#include "set.h"

template <class T>
class List
{
private:
    std::vector<T> m_vector;

    void __raise_out_of_range_error__(const std::vector<T> &vector, const int &idx) const
    {
        assert(
            ("List index out of range", (idx <= vector.size() - 1) || (idx < 0)));
    }

    T &__setitem__(const int &idx)
    {

        if (idx < 0)
        {
            std::size_t negate_idx = (idx * -1);
            __raise_out_of_range_error__(m_vector, negate_idx - 1);
            return m_vector.at(m_vector.size() - negate_idx); // list[-1] -> m_vector.back()
        }

        __raise_out_of_range_error__(m_vector, idx);

        return m_vector.at(idx);
    }
    const T &__getitem__(const int &idx) const
    {

        if (idx < 0)
        {
            std::size_t negate_idx = (idx * -1);
            __raise_out_of_range_error__(m_vector, negate_idx - 1);
            return m_vector.at(m_vector.size() - negate_idx); // list[-1] -> m_vector.back()
        }

        __raise_out_of_range_error__(m_vector, idx);

        return m_vector.at(idx);
    }

public:
    List()
    {
    }
    List(const std::initializer_list<T> &init)
        : m_vector(init)
    {
    }
    template <typename Container>
    List(const Container &container)
    {
        for (const auto &value : container)
        {
            m_vector.push_back(value);
        }
    }
    List<T> copy() const
    {
        return List<T>(m_vector);
    }
    void clear()
    {
        m_vector.clear();
    }

    void append(const T &value)
    {

        m_vector.push_back(value);
    }

    void extend(const List<T> &_other_list)
    {

        for (const T &value : _other_list.values())
        {
            m_vector.push_back(value);
        }
    }
    void extend(const std::initializer_list<T> &init)
    {
        for (const T &value : init)
        {
            m_vector.push_back(value);
        }
    }

    void insert(const int &index, const T &value)
    {
        m_vector.insert(m_vector.begin() + index, value);
    }

    void remove_value_along_with_duplicates(const T &value)
    {
        bool is_value_exist = false;
        int value_count = this->count(value);

        while (value_count != 0)
        {
            for (std::size_t idx = 0; idx <= m_vector.size() - 1; idx++)
            {
                if (m_vector.at(idx) == value)
                {
                    is_value_exist = true;
                    m_vector.erase(m_vector.begin() + idx);
                    value_count -= 1;
                    break;
                }
            }
        }

        if (!is_value_exist)
        {
            throw std::invalid_argument("value not in list");
        }
    }

    void remove(const T &value)
    {
        bool is_value_exist = false;

        for (std::size_t idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            if (m_vector.at(idx) == value)
            {
                is_value_exist = true;
                m_vector.erase(m_vector.begin() + idx);
                return; // only removes the first matching value.
            }
        }

        if (!is_value_exist)
        {
            throw std::invalid_argument("value not in list");
        }
    }

    std::size_t index(const T &searched_value, int start = -1, int end = -1) const
    {

        if (start == -1)
        {
            start = 0;
        }
        if (end == -1)
        {
            end = m_vector.size() - 1;
        }
        __raise_out_of_range_error__(m_vector, start);
        __raise_out_of_range_error__(m_vector, end);

        for (std::size_t idx = start; idx <= end; idx++)
        {
            if (m_vector.at(idx) == searched_value)
            {
                return idx;
            }
        }

        throw std::invalid_argument("value not found");
    }

    T pop()
    {
        T popped_value = m_vector.at(m_vector.size() - 1);
        m_vector.pop_back();

        return popped_value;
    }
    T pop(std::size_t idx)
    {
        T popped_value = m_vector.at(idx);
        m_vector.erase(m_vector.begin() + idx);
        return popped_value;
    }

    List<T> slice(const int &begin_idx = -1, int end_idx = -1) const
    {
        // e.g. [1,2,3,4,5].slice() -> [1,2,3,4,5]
        // e.g. [1,2,3,4,5].slice(1, 4) -> [2,3,4]
        if (begin_idx == -1 && end_idx == -1)
        {
            return this->copy();
        }

        if (end_idx == -1)
        {
            end_idx = m_vector.size();
        }

        __raise_out_of_range_error__(m_vector, begin_idx);
        __raise_out_of_range_error__(m_vector, end_idx);

        std::vector<T> sliced_vector;
        for (std::size_t idx = begin_idx; idx < end_idx; idx++)
        {
            sliced_vector.push_back(m_vector.at(idx));
        }

        List<T> sliced_list(sliced_vector);

        return sliced_list;
    }
    List<std::string> map_to_string()
    {
        assert(("Integral or floating types required", std::is_arithmetic_v<T>));
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");

        List<std::string> string_list;
        for (const auto &value : m_vector)
        {

            string_list.append(std::to_string(value));
        }

        return string_list;
    }

    std::string join(const std::string &delimeter) const
    {
        assert(("Integral or floating types required", std::is_arithmetic_v<T>));
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");

        std::string repr_ = "";
        std::string joined_string;
        std::size_t idx = 0;
        for (const auto &value : m_vector)
        {
            if (idx == m_vector.size() - 1)
            {
                continue;
            }
            idx += 1;

            joined_string = std::to_string(value) + delimeter;

            repr_ += joined_string;
        }

        return repr_;
    }
    std::size_t size() const
    {
        return m_vector.size();
    }

    std::size_t length() const
    {
        return m_vector.size();
    }

    bool is_contains(const T &value) const
    {
        return (std::find(m_vector.begin(), m_vector.end(), value) != m_vector.end());
    }

    void sort()
    {
        std::sort(m_vector.begin(), m_vector.end());
    }
    void sort(const std::function<bool(const T &x, const T &y)> &compare_func)
    {
        std::sort(m_vector.begin(), m_vector.end(), compare_func);
    }

    void reverse()
    {
        std::reverse(m_vector.begin(), m_vector.end());
    }

    int count(const T &value) const
    {
        long int count = 0;
        for (const T &val : m_vector)
        {
            if (val == value)
            {
                count += 1;
            }
        }

        return count;
    }
    bool is_all(const T &checked_value)
    {
        int count = 0;
        for (const T &value : m_vector)
        {
            if (value == checked_value)
            {
                count += 1;
            }
        }

        return (count == m_vector.size());
    }

    T &operator[](const int &idx) // setter
    {

        return this->__setitem__(idx);
    }
    const T &operator[](const int &idx) const
    {

        return this->__getitem__(idx);
    }
    List<T> operator+(const List<T> &_other_list) const
    {
        List<T> copy_list = this->copy();
        copy_list.extend(_other_list);

        return copy_list;
    }

    bool operator==(const List<T> &_other_list) const
    {
        if (m_vector.size() != _other_list.m_vector.size())
        {
            return false;
        }

        for (std::size_t idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            if (m_vector.at(idx) != _other_list.m_vector.at(idx))
            {
                return false;
            }
        }
        return true;
    }

    std::vector<T> &values() // for iteration
    {
        return m_vector;
    }
    const std::vector<T> &values() const // for const value iteration
    {
        return m_vector;
    }

    // custom iterator
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    iterator begin()
    {
        return m_vector.begin();
    }

    iterator end()
    {
        return m_vector.end();
    }

    const_iterator begin() const
    {
        return m_vector.begin();
    }

    const_iterator end() const
    {
        return m_vector.end();
    }

    const_iterator cbegin() const
    {
        return m_vector.cbegin();
    }

    const_iterator cend() const
    {
        return m_vector.cend();
    }
    friend std::ostream &operator<<(std::ostream &stream, const List<T> &list)
    {
        if (list.length() == 0)
        {
            stream << "[ ]";
            return stream;
        }

        stream << "[";

        std::size_t idx = 0;
        for (const T &value : list.m_vector)
        {
            if (typeid(T) == typeid(char)) {
                stream << " " << "'" << value << "'";
            } else {
                stream << " " << value;
            }
            
            if (idx == list.length() - 1)
            {
                continue;
            }
            stream << ",";
            idx += 1;
        }

        stream << "]";
        return stream;
    }
    

    // arithimetic functions
    T min()
    {
        T temp_min = m_vector.at(0);
        for (const T &value : m_vector)
        {
            if (value < temp_min)
            {
                temp_min = value;
            }
        }

        return temp_min;
    }
    T max()
    {
        T temp_max = m_vector.at(0);
        for (const T &value : m_vector)
        {
            if (value > temp_max)
            {
                temp_max = value;
            }
        }

        return temp_max;
    }

    T sum()
    {
        assert(("Integral or floating types required", std::is_arithmetic_v<T>));
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");
        T sum = 0;
        for (const T &value : m_vector)
        {
            sum += value;
        }

        return sum;
    }

    long double mean()
    {
        assert(("Integral or floating types required", std::is_arithmetic_v<T>));
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");

        long double avg = (this->sum() / static_cast<double>(m_vector.size()));

        return avg;
    }
};

#endif
