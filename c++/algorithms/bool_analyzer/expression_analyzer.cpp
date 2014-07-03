#include "expression_analyzer.h"

expression combine_expressions(expression &left, ExpressionPart op, expression &right)
{
  ExpressionPart left_expr = left.evaluation_to_expression_part();
  ExpressionPart right_expr = right.evaluation_to_expression_part();
  expression ret_expr(left_expr, op, right_expr, left.expression_string(), right.expression_string());
  return ret_expr;
}

expression_analyzer::expression_analyzer(std::string &expres_str) :
  _expression(expres_str)
{
  parse();
}

void expression_analyzer::parse()
{
  tok_pos = _expression.begin();
  trim_expression();

  get_constant(true);
}

void expression_analyzer::truths()
{
  std::list<expression> truth = truth_evaluation(0, truth_table.size());
  for (std::list<expression>::iterator truth_it = truth.begin(); truth_it != truth.end(); ++truth_it) {
    expression tmp = (*truth_it);
    if (tmp.evaluation()) {
      std::cout << tmp.expression_string() << std::endl;
    }
  }
}

std::list<expression> expression_analyzer::truth_evaluation(int left, int right)
{
  if (right - left == 1) { // Simple Expression
    std::list<expression> simple;
    ExpressionPart insert = truth_table[left];
    simple_expression insert_expr(insert);
    simple.push_back(insert_expr);
    return simple;
  }
  if (right - left == 3) {
      std::list<expression> expr;
      ExpressionPart insert_left = truth_table[left];
      ExpressionPart insert_op = truth_table[left + 1];
      ExpressionPart insert_right = truth_table[left + 2];
      expression insert_expr(insert_left, insert_op, insert_right);
      expr.push_back(insert_expr);
      return expr;
  }

  std::list<expression> solution_list;
  for (int i = left + 1; i < right; i+=2) {
    std::list<expression> left_expr = truth_evaluation(left, i);
    std::list<expression> right_expr = truth_evaluation(i + 1, right);

    for (std::list<expression>::iterator left_it = left_expr.begin(); left_it != left_expr.end(); ++left_it) {
      for (std::list<expression>::iterator right_it = right_expr.begin(); right_it != right_expr.end(); ++right_it) {
        expression combined_exp = combine_expressions((*left_it), truth_table[i], (*right_it));
        solution_list.push_back(combined_exp);
      }
    }
  }
  return solution_list;
}

void expression_analyzer::get_constant(bool get_next)
{
  if (get_next == false) {
    throw std::runtime_error("Expression must terminate in a constant");
  }

  if (tok_pos >= _expression.end()) {
    return;
  }

  std::string constant;
  while (tok_pos != _expression.end() && (*tok_pos) != ' ') {
    constant.append(1, (*tok_pos));
    ++tok_pos;
  }

  std::transform(constant.begin(), constant.end(), constant.begin(), ::tolower);

  if (constant == "true") {
    truth_table.push_back(True);
  } else if (constant == "false") {
    truth_table.push_back(False);
  } else {
    throw std::runtime_error("Invalid constant");
  }

  ++tok_pos;

  if (tok_pos >= _expression.end()) {
    return;
  }
  get_operator();
}

void expression_analyzer::get_operator()
{
  if (tok_pos >= _expression.end()) {
    throw std::runtime_error("You must terminate with a constant");
  }

  std::string op;
  while (tok_pos != _expression.end() && (*tok_pos) != ' ')  {
    op.append(1, (*tok_pos));
    ++tok_pos;
  }

  std::transform(op.begin(), op.end(), op.begin(), ::tolower);

  if (op == "and") {
    truth_table.push_back(And);
  } else if (op == "or") {
    truth_table.push_back(Or);
  } else if (op == "xor") {
    truth_table.push_back(Xor);
  } else {
    throw std::runtime_error("Invalid operator specified");
  }

  ++tok_pos;
  get_expression();
}

void expression_analyzer::get_expression()
{
  if (tok_pos == _expression.end()) {
    get_constant(false);
  }

  get_constant(true);
}
