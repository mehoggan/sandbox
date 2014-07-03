#ifndef EXPRESSION_CPP
#define EXPRESSION_CPP
#include "expression.h"

expression::expression(ExpressionPart left, ExpressionPart op, ExpressionPart right) :
  _left(left),
  _operator(op),
  _right(right)
{
  ExpressionPart parts[3];
  parts[0] = left;
  parts[1] = op;
  parts[2] = right;

  std::string expression_str = "(";
  for (int i = 0; i < 3; ++i) {
    if (i != 0) expression_str += " ";
    switch(parts[i])
    {
    case (True):
      expression_str += "true";
      break;
    case (False):
      expression_str += "false";
      break;
    case (And):
      expression_str += "and";
      _evaluation = _left && _right;
      break;
    case (Or):
      expression_str += "or";
      _evaluation = _left || _right;
      break;
    case (Xor):
      expression_str += "xor";
      _evaluation = (_left || _right) && !(_left && _right);
      break;
    default:
      throw std::runtime_error("Invalid string to expression");
    };
  }
  expression_str += ")";
  _expression_str += expression_str;
}

expression::expression(ExpressionPart left, ExpressionPart op, ExpressionPart right,
  std::string left_expression_str, std::string right_expression_str) :
  _left(left),
  _operator(op),
  _right(right)
{
  ExpressionPart parts[3];
  parts[0] = left;
  parts[1] = op;
  parts[2] = right;
  _expression_str += "(";
  for (int i = 0; i < 3; ++i) {
    switch(parts[i])
    {
    case (True):
      break;
    case (False):
      break;
    case (And):
      _expression_str += left_expression_str + " and " + right_expression_str;
      _evaluation = _left && _right;
      break;
    case (Or):
      _expression_str += left_expression_str + " or " + right_expression_str;
      _evaluation = _left || _right;
      break;
    case (Xor):
      _expression_str += left_expression_str + " xor " + right_expression_str;
      _evaluation += (_left || _right) && !(_left && _right);
      break;
    default:
      throw std::runtime_error("Invalid string to expression");
    };
  }
  _expression_str += ")";
}

simple_expression::simple_expression(ExpressionPart left)
{
  std::string tmp = _expression_str;
  expression(left, And, True);
  _expression_str = "";
  std::string expression_str = "";
  switch(left)
  {
  case (True):
    expression_str += "true";
    _evaluation = true;
    break;
  case (False):
    expression_str += "false";
    _evaluation = false;
    break;
  case (And):
    expression_str += "and";
    break;
  case (Or):
    expression_str += "or";
    break;
  case (Xor):
    expression_str += "xor";
    break;
  default:
    throw std::runtime_error("Invalid string to expression");
  };
  _expression_str = tmp + expression_str;
}

ExpressionPart expression::evaluation_to_expression_part()
{
  if (_evaluation) {
    return True;
  } else if (!_evaluation) {
    return False;
  }
  throw std::runtime_error("Unknown -- you are either true or false but not none");
  return False;
}
#endif // EXPRESSION_CPP
