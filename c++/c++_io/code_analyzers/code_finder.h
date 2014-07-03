#ifndef CODE_FINDER_H_
#define CODE_FINDER_H_

#include "file_to_map.h"
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>

class code_finder
{
public:
  code_finder();
  code_finder(std::string dir, std::string key_word_file);
  ~code_finder();
  int run();
protected:
  void rec_dir_descent(std::string dir);
  void read_file(std::string dir);
  void print_results();
private:
  file_to_map<std::string, std::set<std::string>, std::string >  m_code_found_map;
  std::string m_top_most_dir;
  std::vector<std::string> m_results;
};

#endif//CODE_FINDER_H_
