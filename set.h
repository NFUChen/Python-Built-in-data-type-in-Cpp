#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <initializer_list>
#include "list.h"
template <class T>
class Set
{
private:
  std::set<T> m_set;

public:
  // ----------------constructor----------------------
  Set()
  {
  }
  Set(const std::initializer_list<T> &init)
      : m_set(init)
  {
  }
  template <typename Container>
  Set(const Container &container)
  {
    for (const auto &value : container)
    {
      m_set.insert(value);
    }
  }

  // -------------------------------------------------

  std::size_t size() const
  {
    return m_set.size();
  }

  std::size_t length() const
  {
    return m_set.size();
  }
  Set<T> copy() const
  {
    return Set<T>(m_set);
  }

  bool is_contains(const T &value) const
  {
    return (m_set.find(value) != m_set.end());
  }

  void add(const T &value)
  {
    m_set.insert(value);
  }

  void remove(const T &value)
  {
    if (!this->is_contains(value)) // not found
    {
      throw std::invalid_argument("value not in set");
    }

    m_set.erase(value);
  }

  void discard(const T &value)
  {
    m_set.erase(value);
  }

  void clear()
  {
    m_set.clear();
  }

  void update(const Set<T> &_other_set)
  // The update() method updates the current set, by adding items from another set (or any other iterable).
  // If an item is present in both sets,
  // only one appearance of this item will be present in the updated set.
  {
    for (const T &value : _other_set.values())
    {
      m_set.insert(value);
    }
  }

  Set<T> union_with(const Set<T> &_other_set) const
  {
    Set<T> union_set(m_set);
    for (const T &value : _other_set.values())
    {
      union_set.add(value);
    }
    return union_set;
  }

  Set<T> difference_with(const Set<T> &_other_set) const
  {
    Set<T> difference_set(m_set);
    for (const T &value : _other_set.values())
    {
      if (difference_set.is_contains(value)) // if find
      {
        difference_set.remove(value);
      }
    }

    return difference_set;
  }
  Set<T> intersection_with(const Set<T> &_other_set) const
  {
    Set<T> intersection_set;
    for (const T &self_value : m_set)
    {
      if (_other_set.is_contains(self_value))
      {
        intersection_set.add(self_value);
      }
    }

    return intersection_set;
  }

  std::set<T> &values() // for iteration
  {
    return m_set;
  }
  const std::set<T> &values() const // for const value iteration
  {
    return m_set;
  }
  bool operator==(const Set<T> &_other_set) const
  {
    if (m_set.size() != _other_set.m_set.size())
    {
      return false;
    }
    // std::set is sorted by default
    for (const T &value : m_set)
    {
      if (!_other_set.is_contains(value))
      {
        return false;
      }
    }
    return true;
  }

  // custom iterator
  typedef typename std::set<T>::iterator iterator;
  typedef typename std::set<T>::const_iterator const_iterator;

  iterator begin()
  {
    return m_set.begin();
  }

  iterator end()
  {
    return m_set.end();
  }
  const_iterator begin() const
  {
    return m_set.begin();
  }

  const_iterator end() const
  {
    return m_set.end();
  }
  const_iterator cbegin() const
  {
    return m_set.cbegin();
  }

  const_iterator cend() const
  {
    return m_set.cend();
  }

  friend std::ostream & operator<<(std::ostream &stream, const Set<T> &set)
  {
    if (set.size() == 0)
    {
      stream << "{ }";
      return stream;
    }
    stream << "{";

    std::size_t idx = 0;
    for (const T &value : set.m_set)
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

      if (idx == set.size() - 1)
      {
        continue;
      }
      stream << ",";
      idx += 1;
    }

    stream << "}";

    return stream;
  }
};

#endif
