#include "expression_analyzer.h"

int main (int /*argc*/, char * /*argv*/[])
{
  std::string expression_arg("true and false xor false");
  expression_analyzer ea(expression_arg);
  ea.truths();
}
