#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <string>
#include <fstream>
#include <iostream>

class FileReader
{
public:
  FileReader(const std::string &path, unsigned char data[], 
    long long bytes_to_read);
  ~FileReader();
private:
  std::ifstream _m_InFile;
};

#endif
