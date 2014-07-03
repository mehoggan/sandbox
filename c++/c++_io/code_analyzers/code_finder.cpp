#include "code_finder.h"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

struct file_error : public std::exception
{
  file_error(std::string error) {m_error = error;}
  virtual ~file_error() throw() {};
  std::string m_error;
};

code_finder::code_finder()
{
}

code_finder::code_finder(std::string dir, std::string key_word_file)
{
  m_top_most_dir = dir;
  m_code_found_map.set_file(key_word_file);
}

code_finder::~code_finder()
{
}

int code_finder::run()
{
  std::cout << "Finding occurences of key words in " 
            << "opengl_functions inside directory structure "
            << m_top_most_dir << std::endl;
  std::ifstream ifs;
  ifs >> m_code_found_map;
  try {
    code_finder::rec_dir_descent(m_top_most_dir);
    
    // Out put the map
    std::ofstream out_file;
    out_file.open("results_by_function.csv");    
    out_file << m_code_found_map;
    out_file.close();

  } catch (file_error fe) {
    std::cout << "ERROR: " << fe.m_error << std::endl;
  }
  return 0;
}


typedef boost::filesystem::directory_iterator dir_iter;

void code_finder::rec_dir_descent(std::string dir)
{
  boost::filesystem::path pwd(dir);
  
  if (!exists(pwd)) throw file_error("The directory " + dir + " does not exist\n");

  dir_iter end_itr;
  for (dir_iter start_itr(pwd); start_itr != end_itr; ++start_itr) {
    if (boost::filesystem::is_directory(start_itr->status())) {
      rec_dir_descent(start_itr->path().string());
    } else {
      read_file(start_itr->path().string());
    }     
  }

  print_results();
}

void code_finder::read_file(std::string file) 
{
  std::ifstream file_reader;
  file_reader.open(file.c_str(), std::ios::in);
  if (file_reader.fail() || file_reader.bad())
    file_reader.close();

    typedef std::istream_iterator<std::string> string_input;
    typedef std::map<std::string, std::set<std::string> >::const_iterator mapItr;
    size_t count = 1;
    size_t found = 0;
    std::string line;
    while (getline(file_reader, line, '\n')) {
      mapItr bmi = m_code_found_map.get_map().begin();
      mapItr emi = m_code_found_map.get_map().end();
      size_t index;
      while (bmi != emi) {
        std::string sub_string = bmi->first;
        index = line.find(sub_string);
        if (index != std::string::npos) {
          std::string insert = file + std::string(", line(") + boost::lexical_cast<std::string>(count)
                               + std::string("), ") + sub_string + std::string(",") + line;
          m_results.push_back(insert);
          m_code_found_map.insert_into_map(bmi->first, insert);
          ++found;
        }
        ++bmi;
      }
      ++count;
    }
    file_reader.close();
   
    if(found) {
      std::string insert = ",,,";
      m_results.push_back(insert);
      m_results.push_back(insert);
      m_results.push_back(insert);
    }
}

void code_finder::print_results() 
{
  std::ofstream out_file;
  out_file.open("results_by_file.csv", std::ios::out);
  std::copy(m_results.begin(), m_results.end(), std::ostream_iterator<std::string>(out_file, "\n"));
  out_file.close();

  //*/
  //*/
}
