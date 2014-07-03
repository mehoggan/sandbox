#include "filereader.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string &path, 
  unsigned char data[], long long bytes_to_read)
{
  _m_InFile.open(path.c_str());
  if (!_m_InFile) {
    throw std::runtime_error("Failure to open " + path);
  }
  
  try {
    _m_InFile.read(reinterpret_cast<char *>(data), bytes_to_read);
  } catch (std::ios_base::failure e) {
    throw std::runtime_error("Failure while reading first N bytes");
  }
}
 
FileReader::~FileReader()
{
  _m_InFile.close();
}
