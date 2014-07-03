#ifndef EXPRESSION_ANALYZER_H
#define EXPRESSION_ANALYZER_H

#include "expression.h"
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>

class expression_analyzer
{
public:
    /*!
     * \brief ctor
     *
     * \param [in] std::string -- Expresion passed in by user
     * representing their boolean expression
     *
     * Initialized member variables, and calls parse on the
     * expression.
     */  
    expression_analyzer(std::string &expres_str);
    /*! 
     * \brief returns the parenthesizations that evaluate to true
     * for the expression provided to the constructor 
     *
     * Method only works on a scucceful parse from the constructor.
     * Calls helper method truth_evaluation() for evaluation of 
     * all parenthesizations.
     *
     * \sa truth_evaluation()
     */
    void truths();
private:
    /*!
     * \brief used by parser to keep track of current
     * position in string
     */  
    std::string::iterator tok_pos;

    /*!
     * \brief Copy of the string passed to the constructor
     */ 
    std::string _expression;

     /*!
      * \brief Used to hold the results of a parse for evaluation
      * by truths()
      *
      * \sa truths()
      */ 
    std::vector<ExpressionPart> truth_table;

    /*!
     * \brief Called by constructor to parse users expression
     * and produce intermediate data structures. Uses recursive
     * descent.
     */ 
    void parse();

    /*!
     * \brief First stage in recursive descent
     *
     * EBNF Rules:
     *   Expression := Constant Operator Expression | Constant
     *   Constant := False | True
     *   Operator:= And | Or | Xor
     */ 
    void get_constant(bool get_next);

    /*!
     * \brief Second stage in recursive descent parser 
     */
    void get_operator();

    /*!
     * \brief Third stage in recursive descent parser
     */
    void get_expression();

    /*!
     * \brief Helper method for evaluating an expression be left and right indices
     * stored within truth_table
     */
    std::list<expression> truth_evaluation(int left, int right);

    /*! 
     * \brief Used to strip leading and trailing spaces
     * from user input
     *
     * \sa left_trim_expression right_trim_expression
     */ 
    void trim_expression() {
      left_trim_expression();
      right_trim_expression();
    }
    void left_trim_expression () {
      _expression.erase(_expression.begin(), std::find_if(_expression.begin(), _expression.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    }
    void right_trim_expression () {
      _expression.erase(std::find_if(_expression.rbegin(), _expression.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), _expression.end());
    }
};

#endif // EXPRESSION_ANALYZER_H
