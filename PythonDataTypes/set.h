#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <initializer_list>

template <class T>
class Set
{
private:
  std::set<T> m_set;
  void __raise_value_not_found_error__(std::string func_name) const
  {
    std::string msg = "value not in set";
    throw std::invalid_argument(func_name + msg);
  }

public:
  Set()
  {}
  Set(const std::initializer_list<T> &init)
      : m_set(init)
  {}
  template <typename Container>
  Set(const Container &container)
  {
    for (const T &value : container)
    {
      m_set.insert(value);
    }
  }

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
    return m_set.count(value);
  }

  void add(const T &value)
  {
    m_set.insert(value);
  }

  void remove(const T &value)
  {
    if (!this->is_contains(value)) // not found
    {
      __raise_value_not_found_error__(__PRETTY_FUNCTION__);
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

  template <typename Container>
  void update(const Container &container)
  // The update() method updates the current set, by adding items from another set (or any other iterable).
  // If an item is present in both sets,
  // only one appearance of this item will be present in the updated set.
  {
    for (const T& value : container)
    {
      m_set.insert(value);
    }
  }
  template <typename Container>
  Set<T> union_with(const Container &container) const
  {
    Set<T> union_set(m_set);
    for (const T& value : container)
    {
      union_set.add(value);
    }
    return union_set;
  }

  template <typename Container>
  Set<T> difference_with(const Container &container) const
  {
    Set<T> difference_set(m_set);
    for (const T& value : container)
    {
      if (difference_set.is_contains(value)) // if find
      {
        difference_set.remove(value);
      }
    }

    return difference_set;
  }
  template <typename Container>
  Set<T> intersection_with(const Container &container) const
  {
    Set<T> intersection_set;
    for (const T& value : container)
    {
      if (this->is_contains(value)) {
        intersection_set.add(value);
      }
    }
    return intersection_set;
  }
  bool operator==(const Set<T> &_other_set) const
  {
    if (m_set.size() != _other_set.m_set.size())
    {
      return false;
    }
    // std::set is sorted by default
    for (const T& value : m_set)
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
  std::set<T> values() const
  {
    return m_set;
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
    for (const T& value : set.m_set)
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
