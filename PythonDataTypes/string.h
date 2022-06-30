#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <regex>
#include "list.h"

class String
{
private:
    void __raise_out_of_range_error__(std::string_view string_v, const int &idx) const
    {
        assert(
            (
                "String index out of range", (idx <= string_v.size() - 1) || (idx < 0)
            )
        );
    }
    void __raise_substring_not_found_error__(std::string func_name) const
    {
        std::string msg = "substring not found";
        throw std::invalid_argument(func_name + msg);
    }

    void __raise_exceed_1_char_long_error(std::string func_name) const {
        std::string msg = "'fillchar' must be 1 character long";
        throw std::invalid_argument(func_name + msg);
    }
    
    const char &__getchar__(const int &idx) const
    {

        if (idx < 0)
        {
            std::size_t negate_idx = (idx * -1);
            __raise_out_of_range_error__(m_string_v, negate_idx - 1);
            return m_string.at(m_string.size() - negate_idx); // string[-1] -> m_string.back()
        }

        __raise_out_of_range_error__(m_string_v, idx);

        return m_string.at(idx);
    }

    std::size_t __find_substring__(std::string_view searched_string_v, std::size_t start = std::string::npos, std::size_t end = std::string::npos) const
    {
        if (start == std::string::npos)
            start = 0;
        if (end == std::string::npos)
            end = m_string.size() - searched_string_v.size();

        for (std::size_t idx = start; idx <= end; idx++)
        {
            std::string_view current_substr_v = m_string.substr(idx, searched_string_v.size());
            if (searched_string_v == current_substr_v)
            {
                return idx;
            }
        }
        return std::string::npos;
    }

public:
    std::string m_string;
    std::string_view m_string_v;
    String()
    {
    }
    String(const std::string &string)
        : m_string(string), m_string_v(m_string)
    {
    }
    String(std::string_view string_v)
        : m_string(string_v), m_string_v(string_v)
    {
    }
    String(const char &_char)
        : m_string(std::string(1, _char)), m_string_v(m_string)
    {
    }
    String(const char *string)
        : m_string(string), m_string_v(m_string)
    {
    }
    template <typename T>
    requires std::is_arithmetic_v<T>
    String(const T &number)
        : m_string(std::to_string(number)), m_string_v(m_string)
    {
    }

    bool is_contains(const String &searched_string) const
    {
        return m_string.find(searched_string.m_string_v) != std::string::npos;
    }
    bool is_in(const String &string) const
    {
        return string.is_contains(m_string_v);
    }

    long int find(const String &searched_string, std::size_t start = std::string::npos, std::size_t end = std::string::npos) const
    {
        std::size_t found_idx = __find_substring__(searched_string.m_string_v, start, end);
        if (found_idx == std::string::npos)
        {
            return -1;
        }
        return found_idx;
    }

    std::size_t index(const String &searched_string, std::size_t start=std::string::npos, std::size_t end=std::string::npos) const
    {
        std::size_t found_idx = __find_substring__(searched_string.m_string_v, start, end);
        if (found_idx == std::string::npos) {
            __raise_substring_not_found_error__(__PRETTY_FUNCTION__);
        }
        return found_idx;
        
    }

    std::size_t length() const
    {
        return m_string.size();
    }
    std::size_t size() const
    {
        return m_string.size();
    }

    String slice(const std::size_t &begin_idx = std::string::npos, std::size_t end_idx = std::string::npos) const
    {
        if (begin_idx == std::string::npos && end_idx == std::string::npos)
        {
            return String(m_string);
        }

        if (end_idx == std::string::npos)
        {
            end_idx = m_string.size();
        }
        std::size_t substr_len = end_idx - begin_idx;

        return String(m_string_v.substr(begin_idx, substr_len));
    }

    String substr(const std::size_t &begin_idx = 0, const std::size_t &substr_len = std::string::npos) const
    {
        return String(m_string_v.substr(begin_idx, substr_len));
    }

    String lower() const
    {
        std::string lowercase_string;
        for (const char &_char : m_string)
        {
            lowercase_string += std::tolower(_char);
        }

        return String(lowercase_string);
    }

    String upper() const
    {
        std::string uppercase_string;
        for (const char &_char : m_string)
        {
            uppercase_string += std::toupper(_char);
        }

        return String(uppercase_string);
    }

    String capitalize() const
    {
        std::string capitalized_string;
        for (std::size_t idx = 0; idx <= m_string.size() - 1; idx++)
        {
            if (idx == 0)
            {
                capitalized_string += std::toupper(m_string.at(idx));
            }
            else
            {
                capitalized_string += std::tolower(m_string.at(idx));
            }
        }
        return String(capitalized_string);
    }
    String title(const char& trailing_char = ' ') const 
    {  
        std::string titled_string;

        std::size_t start_idx = 0;
        while (m_string.at(start_idx) == trailing_char)
        {
            start_idx += 1;
        }

        std::size_t end_idx = m_string.size() - 1;
        while (m_string.at(end_idx) == trailing_char)
        {
            end_idx -= 1;
        }

        for (std::size_t idx = start_idx; idx <= end_idx; idx++)
        {
            if (idx == 0)
            {
                titled_string += std::toupper(m_string.at(idx));
            }
            else if (m_string.at(idx - 1) == trailing_char)
            {
                titled_string += std::toupper(m_string.at(idx));
            }
            else
            {
                titled_string += std::tolower(m_string.at(idx));
            }
        }
        String front_blank = String(trailing_char) * start_idx;
        String back_blank = String(trailing_char) * (m_string.size() - 1 - end_idx);

        return String(front_blank.m_string + 
                      titled_string + 
                      back_blank.m_string);
    }
    String strip(const char& stripped = ' ') const
    {
        std::size_t left = 0;
        std::size_t right = m_string.length() - 1;
        while (m_string.at(left) == stripped)
        {
            left += 1;
        }
        while (m_string.at(right) == stripped)
        {
            right -= 1;
        }     
        std::size_t substr_len = (right - left + 1);

        return String( m_string_v.substr(left, substr_len) );
    }
    String pad_left(const std::size_t &width, const String &fillchar = " ") const
    {
        if (fillchar.size() != 1) {
            __raise_exceed_1_char_long_error(__PRETTY_FUNCTION__);
        }
        
        std::string pad_string;
        std::string pad;
        while (pad.size() < (width - m_string.size()))
        {
            pad += fillchar.m_string;
        }
        pad_string = (pad + m_string);

        return String(pad_string);
    }
    String pad_right(const std::size_t &width, const String &fillchar = " ") const
    {
        if (fillchar.size() != 1)
        {
            __raise_exceed_1_char_long_error(__PRETTY_FUNCTION__);
        }

        std::string pad_string;
        std::string pad;
        while (pad.size() < (width - m_string.size()))
        {
            pad += fillchar.m_string;
        }
        pad_string = (m_string + pad);

        return String(pad_string);
    }

    String center(const std::size_t &width, const String &fillchar = " ") const
    {
        std::string pad_string = m_string;
        while (pad_string.size() < width)
        {
            pad_string = (pad_string + fillchar.m_string); // "A" -> "A-"
            pad_string = (fillchar.m_string + pad_string); // "A-" -> "-A-"
        }

        return String(pad_string);
    }
    template <typename Container>
    String join(const Container &container) const
    {
        String joined;
        String delimiter = m_string;
        bool is_first_value = true;

        for (const auto &value : container)
        {
            if (is_first_value)
            {
                joined += value;
                is_first_value = false;
            }
            else
            {
                joined += (delimiter + value);
            }
        }

        return joined;
    }
    String replace(const String &replaced, const String &replace_with) const
    {

        std::string string_after_replacing = std::regex_replace(
            m_string,
            std::regex(replaced.m_string),
            replace_with.m_string);

        return String(string_after_replacing);
    }

    bool endswith(const String &end) const
    {
        std::size_t check_idx = m_string.size() - end.m_string.size();
        std::size_t end_string_idx = 0;

        while (end_string_idx <= end.m_string.size() - 1)
        {
            if (m_string_v.at(check_idx) != end.m_string_v.at(end_string_idx))
            {
                return false;
            }
            check_idx += 1;
            end_string_idx += 1;
        }

        return true;
    }

    bool startswith(const String &start) const
    {
        std::size_t start_idx = 0;
        for (std::size_t idx = 0; idx <= start.size() - 1; idx++)
        {
            if (m_string_v.at(idx) != start.m_string_v.at(idx))
            {
                return false;
            }
        }
        return true;
    }

    List<String> split(const String &delimeter = " ") const
    {
        std::size_t pos = 0;
        std::vector<String> words;

        std::string m_string_copy = m_string;
        std::string token;
        while ((pos = m_string_copy.find(delimeter.m_string)) != std::string::npos) // while delimeter in m_string_copy
        {
            token = m_string_copy.substr(0, pos); // hello World -> .substr(0, pos=5) -> hello
            words.push_back(token);
            m_string_copy.erase(0, pos + delimeter.length()); // hello World -> .erase(0, 5+1) -> World
        }
        words.push_back(m_string_copy);

        return List<String>(words);
    }

    unsigned int count(const String &searched, std::size_t start = std::string::npos, std::size_t end = std::string::npos) const
    {
        if (start == std::string::npos)
            start = 0;
        if (end == std::string::npos)
            end = m_string.size() - searched.m_string.size();

        unsigned int current_count = 0;
        for (std::size_t idx = start; idx < end; idx++)
        {
            std::string_view current_substr_v = m_string_v.substr(idx, searched.m_string.size());
            if (current_substr_v == searched.m_string_v)
            {
                current_count += 1;
                idx += searched.m_string_v.size() - 1;
            }
        }
        return current_count;
    }

    template <typename T>
    T to_number() const
    {
        if (typeid(T) == typeid(int))
            return static_cast<T>(std::stoi(m_string));
        if (typeid(T) == typeid(long))
            return static_cast<T>(std::stol(m_string));
        if (typeid(T) == typeid(long long))
            return static_cast<T>(std::stoll(m_string));
        if (typeid(T) == typeid(unsigned))
            return static_cast<T>(std::stoul(m_string));
        if (typeid(T) == typeid(unsigned long))
            return static_cast<T>(std::stoul(m_string));
        if (typeid(T) == typeid(unsigned long long))
            return static_cast<T>(std::stoull(m_string));
        if (typeid(T) == typeid(float))
            return static_cast<T>(std::stof(m_string));
        if (typeid(T) == typeid(double))
            return static_cast<T>(std::stod(m_string));
        if (typeid(T) == typeid(long double))
            return static_cast<T>(std::stold(m_string));
    }
    // checker
    bool isnumeric() const
    {
        for (const char &_char : m_string_v)
        {
            if (!(_char >= '0' && _char <= '9'))
            {
                return false;
            }
        }
        return true;
    }
    bool isalpha() const
    {
        for (const char &_char : m_string_v)
        {
            bool is_lower_letter = (_char >= 'a' && _char <= 'z');
            if (is_lower_letter)
            {
                continue;
            }

            bool is_upper_letter = (_char >= 'A' && _char <= 'Z');
            if (is_upper_letter)
            {
                continue;
            }
            return false;
        }
        return true;
    }
    bool islower() const
    {
        for (const char &_char : m_string_v)
        {
            bool is_lower_letter = (_char >= 'a' && _char <= 'z');
            if (!is_lower_letter)
            {
                return false;
            }
        }
        return true;
    }
    bool isupper() const
    {
        for (const char &_char : m_string_v)
        {
            bool is_upper_letter = (_char >= 'A' && _char <= 'Z');
            if (!is_upper_letter)
            {
                return false;
            }
        }
        return true;
    }

    bool isspace() const
    {
        char BLANK_SPACE = ' ';

        for (const char &_char : m_string_v)
        {
            bool is_space = _char == BLANK_SPACE;
            if (!is_space)
            {
                return false;
            }
        }
        return true;
    }

    const char &operator[](const int &idx) const
    {
        return __getchar__(idx);
    }

    String operator+(const String &_other_string) const
    {
        return String(m_string + _other_string.m_string);
    }
    String operator*(const std::size_t &times) const
    {
        std::string string;
        for (std::size_t idx = 0; idx < times; idx++)
        {
            string += m_string;
        }
        return String(string);
    }

    void operator+=(const String &_other_string)
    {
        m_string += _other_string.m_string;
    }

    bool operator==(const String &_other_string) const
    {
        return m_string_v == _other_string.m_string_v;
    }
    bool operator>(const String &_other_string) const
    {
        return m_string_v > _other_string.m_string_v;
    }
    bool operator<(const String &_other_string) const
    {
        return m_string_v < _other_string.m_string_v;
    }
    // custom iterator
    typedef typename std::string::iterator iterator;
    typedef typename std::string::const_iterator const_iterator;

    iterator begin()
    {
        return m_string.begin();
    }

    iterator end()
    {
        return m_string.end();
    }
    const_iterator begin() const
    {
        return m_string.begin();
    }

    const_iterator end() const
    {
        return m_string.end();
    }

    const_iterator cbegin() const
    {
        return m_string.cbegin();
    }

    const_iterator cend() const
    {
        return m_string.cend();
    }
    std::string values() const
    {
        return m_string;
    }

    friend std::ostream &operator<<(std::ostream &stream, const String &string)
    {
        stream << '"' << string.m_string << '"';

        return stream;
    }
};

#endif