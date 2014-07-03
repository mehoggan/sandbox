#ifndef EXPRESSION_H
#define EXPRESSION_H

/*!
 * \enum ExpressionPart
 * \brief Used by the expression_analyzer and expressions
 * to convert string input over to integral based values
 */
enum ExpressionPart { False, True, And, Or, Xor };

#include <string>
#include <stdexcept>

/*!
 * \class expression
 * \brief Used in the expression_analyzer to store the 
 * state of an expression.
 *
 * Takes the form Constant Operator Constant
 *
 * \sa class simple_expression
 */
class expression
{
public:
  /*!
   * \brief default ctor
   */ 
  expression() {}

  /*!
   * \brief used to construct a basic Expression
   */  
  expression(ExpressionPart left, ExpressionPart op, ExpressionPart right);

  /*!
   * \brief used to put together two know expressions into one expression
   */ 
  expression(ExpressionPart left, ExpressionPart op, ExpressionPart right,
    std::string left_expression_str, std::string right_expression_str);

  /*!
   * \brief returns the left most element in expression which is a 
   * Constant (true | false)
   */ 
  virtual ExpressionPart left() const { return _left; }

  /*!
   * \brief returns the operator of expression
   * Operator(And | Or | Xor)
   */
  virtual ExpressionPart op() const { return _operator; }

  /*!
   * \brief returns right most element of expression which is a 
   * Constant (true | false)
   */ 
  virtual ExpressionPart right() const { return _right; }

  /*!
   * \brief returns a string representation of the expression appearing as
   * Constant Operator Constant where Constant = (true | false) and Operator = 
   * (and | or | xor)
   */
  virtual const std::string &expression_string() const { return _expression_str; }

  /*!
   * \brief boolean value of the expression which is computed in the constructor of the 
   * object
   */ 
  virtual bool evaluation() const { return _evaluation; }

  /*!
   * \brief Values for an expression are encoded in enum ExpressionPart
   * and must be decoded back to a string representation when print information
   * to screen
   */ 
  virtual ExpressionPart evaluation_to_expression_part();

protected:
  ExpressionPart _left;
  ExpressionPart _operator;
  ExpressionPart _right;
  std::string _expression_str;
  bool _evaluation;
};

/*!
 * \class simple_expression
 * \brief Not all expressions consist of a Constant Operator Constant 
 * form. For example, the singletons true and false are also expressions
 * and must be treated seperatly
 */
class simple_expression : public expression
{
public:
  simple_expression(ExpressionPart left);
private:
};
#endif // EXPRESSION_H
