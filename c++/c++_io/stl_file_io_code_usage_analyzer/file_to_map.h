#ifndef FILE_TO_MAP_H_
#define FILE_TO_MAP_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

template <class T> 
struct print
{
  print(std::ostream &out) : os(out) {}
  void operator() (T x) { os << x << ' ' << std::endl; }
  std::ostream & os;
};

template <class key, class container, class container_type>
class file_to_map
{
public:
  file_to_map() 
  {
    m_file = "";
  }

  file_to_map(std::string file)
  {
    m_file = file;
  }

  ~file_to_map() 
  {
  }

  std::map<key, container>& get_map() 
  {
    return m_map;
  }
 
  void set_file(const std::string file)
  {
    m_file = file;
  }

  void insert_into_map(key insert, container_type value)
  {
    m_map[insert].insert(value);
  }

  friend std::ostream& operator<< (std::ostream &out, file_to_map<key, container, container_type> &obj)
  {
    typedef typename std::map<key, container>::const_iterator mapItr;
    mapItr mbi = obj.m_map.begin();
    mapItr emi = obj.m_map.end();
    while (mbi != emi) {
      out << " -- " << mbi->first << " -- " << std::endl;
      typename container::const_iterator cbi = mbi->second.begin();
      typename container::const_iterator cei = mbi->second.end();
      std::copy(cbi, cei, std::ostream_iterator<container_type>(out, "\t\n"));
      out << std::endl;
      out << std::endl;
      out << std::endl;
      ++mbi;
    }
    return out;
  }

  friend std::istream& operator>> (std::ifstream &in, file_to_map<key, container, container_type> &obj)
  {
    if (in.is_open()) 
        in.close();
    
    if (obj.m_file == "")
      return in;

    in.open(obj.m_file.c_str(), std::ios::in);

    if (in.fail() || in.bad()) {
      in.close();
      return in;
    }

    std::vector<key> tmp;
    typedef std::istream_iterator<key> string_input;
    copy(string_input(in), string_input(), back_inserter(tmp));
    typename std::vector<key>::iterator bvi = tmp.begin();
    typename std::vector<key>::iterator evi = tmp.end();
    while (bvi != evi) {
        obj.m_map[*(bvi)] = container();
        ++bvi;
    }
    
    in.close();
    return in;
  }
private:
  std::map<key, container> m_map;
  std::string m_file;
};

#endif//FILE_TO_MAP_H_
