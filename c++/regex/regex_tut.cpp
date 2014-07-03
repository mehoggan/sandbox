/* All captures from a regular expression */
#include <boost/regex.hpp>
#include <iostream>

void print_captures(const std::string& regx, const std::string& text)
{
   boost::regex e(regx);
   boost::smatch what;
   std::cout << "Expression:  \"" << regx << "\"\n";
   std::cout << "Text:        \"" << text << "\"\n";
   if(boost::regex_match(text, what, e, boost::match_extra))
   {
      unsigned i;
      std::cout << "** Match found **\n   Sub-Expressions:\n";
      for(i = 0; i < what.size(); ++i) {
         std::cout << "      $" << i << " = \"" << what[i] << "\"\n";
      }
   }
   else
   {
      std::cout << "** No Match found **\n";
   }
}

int main(int argc, char* argv[ ])
{
   print_captures("^\\w+\\s*-->?\\s*\\w+\\s*(\\(\\d+\\))?", "AB --> CD (12)" );
   return 0;
}
