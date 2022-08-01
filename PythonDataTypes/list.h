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

template <class T>
class List
{
private:
    std::vector<T> m_vector;

    void __raise_out_of_range_error__(const std::vector<T> &vector, const int &idx) const
    {
        assert(("List index out of range", (idx <= vector.size() - 1) || (idx < 0)));
    }
    void __raise_value_not_found_error__(std::string func_name) const
    {
        std::string msg = "value not in list";
        throw std::invalid_argument(func_name + msg);
    }

    void __assert_is_arithmetic_type__()
    {
        assert(("Integral or floating types required", std::is_arithmetic_v<T>));
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");
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
        for (const T &value : container)
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
    template <typename Container>
    void extend(const Container &container)
    {
        for (const T &value : container)
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

    void insert(const std::size_t &index, const T &value)
    {
        m_vector.insert(m_vector.begin() + index, value);
    }

    void remove_value_along_with_duplicates(const T &value)
    {

        bool is_value_exist = false;
        for (std::size_t idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            if (m_vector.at(idx) == value)
            {
                if (!is_value_exist)
                    is_value_exist = true;
                m_vector.erase(m_vector.begin() + idx);
                idx -= 1;
            }
        }
        if (!is_value_exist)
        {
            __raise_value_not_found_error__(__PRETTY_FUNCTION__);
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
            __raise_value_not_found_error__(__PRETTY_FUNCTION__);
        }
    }

    std::size_t index(const T &searched_value, std::size_t start = std::string::npos, std::size_t end = std::string::npos) const
    {

        if (start == std::string::npos)
            start = 0;
        if (end == std::string::npos)
            end = m_vector.size();

        __raise_out_of_range_error__(m_vector, start);

        for (std::size_t idx = start; idx < end; idx++) // not including end index
        {
            if (m_vector.at(idx) == searched_value)
            {
                return idx;
            }
        }

        __raise_value_not_found_error__(__PRETTY_FUNCTION__);
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

    List<T> slice(const std::size_t &begin_idx = std::string::npos, std::size_t end_idx = std::string::npos, std::size_t step = 1) const
    {
        // e.g. [1,2,3,4,5].slice() -> [1,2,3,4,5]
        // e.g. [1,2,3,4,5].slice(1, 4) -> [2,3,4]
        if (begin_idx == std::string::npos && end_idx == std::string::npos)
        {
            return this->copy();
        }

        if (end_idx == std::string::npos)
        {
            end_idx = m_vector.size();
        }

        __raise_out_of_range_error__(m_vector, begin_idx);
        __raise_out_of_range_error__(m_vector, end_idx);

        std::vector<T> sliced_vector;
        for (std::size_t idx = begin_idx; idx < end_idx; idx += step)
        {
            sliced_vector.push_back(m_vector.at(idx));
        }

        return List<T>(sliced_vector);
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
    template <typename ReturnedType>
    List<ReturnedType> map(const std::function<ReturnedType(const T &)> &map_callback) const
    {
        if (m_vector.empty())
        {
            return List<ReturnedType>();
        }

        std::vector<ReturnedType> copy_vector;
        for (std::size_t idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            copy_vector.push_back(
                map_callback(m_vector.at(idx)));
        }
        return List<ReturnedType>(copy_vector);
    }
    void for_each(const std::function<void(T &)> &transform_callback)
    {

        for (T &value : m_vector)
        {
            transform_callback(value);
        }
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
        for (const T &value : m_vector)
        {
            if (value != checked_value)
            {
                return false;
            }
        }

        return true;
    }

    T &operator[](const int &idx) // setter
    {

        return this->__setitem__(idx);
    }
    const T &operator[](const int &idx) const
    {

        return this->__getitem__(idx);
    }
    template <typename Container>
    List<T> operator+(const Container &container) const
    {
        List<T> copy_list = this->copy();
        copy_list.extend(container);

        return copy_list;
    }
    List<T> operator*(const std::size_t &times) const
    {
        List<T> copy_list;
        for (std::size_t idx = 0; idx < times; idx++)
        {
            copy_list.extend(m_vector);
        }

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

    std::vector<T> values() const
    {
        return m_vector;
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
            if (typeid(T) == typeid(char))
            {
                stream << " "
                       << "'" << value << "'";
            }
            else
            {
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
            if (!(value < temp_max))
            {
                temp_max = value;
            }
        }

        return temp_max;
    }
    T sum()
    {
        __assert_is_arithmetic_type__();
        T sum = 0;
        for (const T &value : m_vector)
        {
            sum += value;
        }

        return sum;
    }
    long double mean()
    {
        __assert_is_arithmetic_type__();
        long double avg = (this->sum() / static_cast<double>(m_vector.size()));

        return avg;
    }
};

#endif
