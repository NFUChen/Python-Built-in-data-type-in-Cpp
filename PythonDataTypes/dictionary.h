#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <cassert>

#include "list.h"

template <class K, class V>
class Dict
{
private:
    std::unordered_map<K, V> m_map;

    void __raise_key_not_exist_error__(const K &key) const
    {
        assert(
            ("Key not in Dict", m_map.count(key)));
    }

public:
    // ----------------constructor----------------------
    Dict()
    {}
    Dict(const std::initializer_list<std::pair<const K, V>> &init)
        : m_map(init)
    {}
    Dict(const std::unordered_map<K, V> &map)
        : m_map(map)
    {}
    Dict(const std::map<K, V> &map)
    {
        for (const auto &[key, value] : map)
        {
            m_map[key] = value;
        }
    }
    // -------------------------------------------------

    bool is_contains(const K &key) const
    {
        return (m_map.count(key));
    }

    std::size_t size() const
    {
        return m_map.size();
    }
    std::size_t length() const 
    {
        return m_map.size();
    }

    void clear()
    {
        m_map.clear();
    }

    Dict<K, V> copy() const
    {
        return Dict<K, V>(m_map);
    }

    V pop(const K &key)
    {

        __raise_key_not_exist_error__(key);

        V popped_value = m_map[key];
        m_map.erase(key);

        return popped_value;
    }
    V pop(const K &key, const V &default_value)
    {

        if (!m_map.count(key))
        {
            return default_value;
        }
    }

    void update(const Dict<K, V> &_other_dict)
    {
        for (const auto &[key, value] : _other_dict.items())
        {
            m_map[key] = value;
        }
    }

    V setdefault(const K &key)
    {
        // The setdefault() method returns the value of the item with the specified key.
        // If the key does not exist, insert the key, with the specified value
        return m_map[key];
    }
    V setdefault(const K &key, const V &default_value)
    {
        // The setdefault() method returns the value of the item with the specified key.
        // If the key does not exist, insert the key, with the specified value
        if (!m_map.count(key))
        {
            m_map[key] = default_value;
            return default_value;
        }

        return default_value;
    }

    void set(const K &key, const V &value)
    {
        m_map[key] = value;
    }
    V &get(const K &key) // setter
    {
        __raise_key_not_exist_error__(key);
        return m_map[key];
    }
    const V &get(const K &key) const
    {
        __raise_key_not_exist_error__(key);
        return m_map[key];
    }

    const V &get(const K &key, const V &default_value)
    {
        if (!m_map.count(key))
        {
            return default_value;
        }
        return m_map[key];
    }

    V &operator[](const K &key)
    // setter and getter, only with key that is non-exist, may result in undefined behaviour e.g., dict[non_existent_key]
    {
        return m_map[key];
    }

    const V &operator[](const K &key) const
    // setter and getter, only with key that is non-exist, may result in undefined behaviour e.g., dict[non_existent_key]
    {
        return m_map.at(key);
    }

    bool operator==(const Dict<K, V> &_other_dict) const
    {
        if (m_map.size() != _other_dict.m_map.size())
        {
            return false;
        }

        for (const auto &[key, value] : _other_dict.items())
        {
            if (!(m_map[key] == value))
            {
                return false;
            }

            if (!(m_map.count(key)))
            {
                return false;
            }
        }
        return true;
    }
    

    // custom iterator
    typedef typename std::unordered_map<K, V>::iterator iterator;
    typedef typename std::unordered_map<K, V>::const_iterator const_iterator;

    iterator begin()
    {
        return m_map.begin();
    }

    iterator end()
    {
        return m_map.end();
    }
    const_iterator begin() const
    {
        return m_map.begin();
    }

    const_iterator end() const
    {
        return m_map.end();
    }

    const_iterator cbegin() const
    {
        return m_map.cbegin();
    }

    const_iterator cend() const
    {
        return m_map.cend();
    }
    List<V> values() const // for iteration
    {
        std::vector<V> value_vector;
        for (const auto &[_, value] : m_map)
        {
            value_vector.push_back(value);
        }

        return List<V>(value_vector);
    }

    List<K> keys() const // for iteration
    {
        std::vector<K> key_vector;
        for (const auto &[key, _] : m_map)
        {
            key_vector.push_back(key);
        }

        return List<K>(key_vector);
    }

    std::unordered_map<K, V> &items() const // for iteration
    {
        return m_map;
    }

    friend std::ostream & operator<<(std::ostream &stream, const Dict<K, V> &dict)
    {
        if (dict.size() == 0)
        {
            stream << "{ }";
            return stream;
        }
        stream << "{";
        std::size_t idx = 0;
        for (const auto &[key, value] : dict.m_map)
        {
            stream << key << " : " << value;
            if (idx == dict.size() - 1)
            {
                continue;
            }
            idx += 1;

            stream << ", ";
        }

        stream << "}";

        return stream;
    }
};

#endif
