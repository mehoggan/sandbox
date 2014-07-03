#include <iostream>
#include <vector>
#include <cassert>
#include <stdint.h>
#include <iterator>
#include <queue>

/*
 * Shuttle Puzzle:
 * A Shuttle Puzzle of size 4 consists of 4 white marbles, 4 black marbles, and a strip of
 * wood with 9 holes (as shown below). The marbles of the same color are placed in the
 * holes at the opposite ends of the strip leaving the center hole empty. The object of the
 * puzzle is to completely reverse the marbles on the strip. In general, a shuttle puzzle of
 * size N consists of N white marbles, N black marbles and 2N+1 holes. There are only
 * two permissible types of moves. You may slide 1 marble 1 space (into an empty hole)
 * or jump 1 marble over 1 mar
 *
 * W W W W O B B B B
 */
//-------------------------------------------------------------------------------//
//Definition
class shuttle_puzzle
{
private :
  /* Private member variables and typedefs */
  typedef std::vector<char> board;
  board _game_board;
  uint32_t _N;
  enum SwapCase { LeftSkip = -2, ImmediateLeft = -1, Invalid = 0, ImmediateRight = 1, RightSkip = 2 };
  bool _problem_solved;
  std::queue<board> _solutions;

  /* Private Methods */
  void has_left_swap_move(uint32_t open_loc, SwapCase* cases, board &check_board);
  void has_right_swap_move(uint32_t open_loc, SwapCase* cases, board &check_board);
  bool solved(uint32_t open_loc, board &check_board);
  board swap_marbles(uint32_t open_location, SwapCase curr_case, board modify_board);

public :
  /* ctor */
  shuttle_puzzle(uint32_t N);

  /* Method that solves the problem above */
  void solve(uint32_t empty_location, board curr_game_board);

  /* getter */
  const board &get_game_board() const { return _game_board; }
  uint32_t get_start_open_loc() const { return _N; }
  const std::queue<board> &get_solutions() const { return _solutions; }
}; //shuttle_puzzle

//-------------------------------------------------------------------------------//
//Implmentation

/*
 * ctor
 * Build the table with N Ws on the left and N Bs on the
 * right, and a O representing the empty location in the middle.
 * N Specifies the number of white marbles or black marbles.
 */
shuttle_puzzle::shuttle_puzzle(uint32_t N) :
  _N(N),
  _problem_solved(false)
{
  try {
    _game_board.resize(2*N + 1);
  } catch (std::bad_alloc ba) {
    throw ba;
  }

  uint32_t left = 0;
  uint32_t right = _game_board.size() - 1;
  for (; left != right; ++left, --right) {
    _game_board[left] = 'W';
    _game_board[right] = 'B';
  }
  _game_board[left] = 'O';
  assert(left == right && _game_board[left] == 'O' && _game_board[right] == 'O');
}

/*
 * The approach to this problem uses the fact that one step towards the solution
 * is a binary choice of swapping to the left or to the right. As in the tree below
 *
 *                         W O B
 *                         /   \
 *                    O W B     W B O
 *
 * Using back tracking if a path down the tree will not lead to a solution
 */
void shuttle_puzzle::solve(uint32_t empty_location, board curr_game_board)
{
  /*
   * Once we have found a solution mark problem as solved for this object
   */
  if (solved(empty_location, curr_game_board)) {
    _solutions.push(curr_game_board);
    _problem_solved = true;
    return;
  }

  SwapCase left_cases[2] = {Invalid, Invalid};
  SwapCase right_cases[2] = {Invalid, Invalid};
  has_left_swap_move(empty_location, left_cases, curr_game_board);
  has_right_swap_move(empty_location, right_cases, curr_game_board);

  /*
   * If you can swap a white marble into the empty location (left_cases[0]) or if you can
   * hop a black with a white into an empty location (left_cases[1])
   */
  if (left_cases[0] || left_cases[1]) {
    SwapCase left_swap_case = ((left_cases[0]) ? left_cases[0] : left_cases[1]); // -1 or -2 will be results
    // swap marble at -1 or -2 from empty location with the empty location
    board game_board_swap_left = swap_marbles(empty_location, left_swap_case, curr_game_board);
    _solutions.push(curr_game_board);
    if (!_problem_solved) {
      solve(empty_location + left_swap_case, game_board_swap_left);
    }
    if (!_problem_solved) {
      _solutions.pop();
    }
  }

  /*
   * If you can swap a black marble into the empty location (right_cases[0]) or if you can
   * hop a white with a black into an empty location (right_cases[1])
   */
  if (right_cases[0] || right_cases[1]) {
    SwapCase right_swap_case = ((right_cases[0]) ? right_cases[0] : right_cases[1]); // 1 or 2 will be results
    // swap marble at 1 or 2 from empty location with the empty location
    board game_board_swap_right = swap_marbles(empty_location, right_swap_case, curr_game_board);
    _solutions.push(curr_game_board);
    if (!_problem_solved) {
      solve(empty_location + right_swap_case, game_board_swap_right);
    }
    if (!_problem_solved) {
      _solutions.pop();
    }
  }
}

/*
 * This method will tell you which swap is valid to the left of the open
 * spot on the board. The cases are depeicted below
 *
 * W O B  -- Immediate Left Move
 * W B O  -- Left Skip
 * O W W B B -- Invalid
 */
void shuttle_puzzle::has_left_swap_move(uint32_t open_loc, SwapCase *cases, board &check_board)
{
  /*
   * If piece to left is black or piece to left
   * is white and the piece to the left of that is
   * black. Make sure to check that you are within
   * bounds
   */
    if (static_cast<int>(open_loc) - 1 < 0) {
      cases[0] = Invalid;
      cases[1] = Invalid;
    } else if (static_cast<int>(open_loc) - 2 >= 0) {
      if (check_board[open_loc - 1] == 'W') {
        cases[0] = ImmediateLeft;
        cases[1] = Invalid;
      } else if (check_board[open_loc - 1] == 'B' && check_board[open_loc - 2] == 'W') {
        cases[0] = Invalid;
        cases[1] = LeftSkip;
      }
    } else if (static_cast<int>(open_loc) - 1 >= 0 && check_board[open_loc - 1] == 'W') {
      cases[0] = ImmediateLeft;
      cases[1] = Invalid;
    } else {
      cases[0] = Invalid;
      cases[1] = Invalid;
    }
}

/*
 * This method will tell you which swap is valid to the right of the open
 * spot on the board. The cases are depeicted below
 *
 * W O B  -- Immediate Right Move
 * O W B  -- Right Skip
 * W W B B O -- Invalid
 */
void shuttle_puzzle::has_right_swap_move(uint32_t open_loc, SwapCase *cases, board &check_board)
{
  /*
   * If piece to right is white or piece to right
   * is black and the piece to the right of that is
   * white. Make sure to check that you are within
   * bounds
   */
  if (open_loc + 1 >= check_board.size()) {
    cases[0] = Invalid;
    cases[1] = Invalid;
  } else if (open_loc + 2 < check_board.size()) {
    if (check_board[open_loc + 1] == 'B') {
      cases[0] = ImmediateRight;
      cases[1] = Invalid;
    } else if (check_board[open_loc + 1] == 'W' && check_board[open_loc + 2] == 'B') {
      cases[0] = Invalid;
      cases[1] = RightSkip;
    }
  } else if (open_loc + 1 < check_board.size() && check_board[open_loc + 1] == 'B') {
    cases[0] = ImmediateRight;
    cases[1] = Invalid;
  } else {
    cases[0] = Invalid;
    cases[1] = Invalid;
  }
}

/*
 * A puzzle is solved if the open location is in the middle
 * of the board and if all the white marbles are on the right
 * and all the black marbles are on the left
 */
bool shuttle_puzzle::solved(uint32_t open_loc, board &check_board)
{
  uint32_t middle = (check_board.size()/2);
  if (open_loc != middle) {
    return false;
  }
  for (int i = 0, j = check_board.size() - 1; i != j; ++i, --j) {
    if (check_board[i] == 'W' || check_board[j] == 'B') {
      return false;
    }
  }
  return true;
}

/*
 * We cannot modify the original board, so we must return a copy
 * of the modified board. So we obtain a copy of the board. Modify
 * the copy, and return it to the caller for further processing
 */
shuttle_puzzle::board shuttle_puzzle::swap_marbles(uint32_t open_location, SwapCase curr_case, board modify_board)
{
  board ret = modify_board;
  char tmp = ret[open_location];
  ret[open_location] = ret[open_location + curr_case];
  ret[open_location + curr_case] = tmp;

  return ret;
}

int main(int argc, char *argv[])
{
  shuttle_puzzle sp(1);
  sp.solve(sp.get_start_open_loc(), sp.get_game_board());

  std::queue<std::vector<char> > sol = sp.get_solutions();
  for (;!sol.empty();) {
    std::copy(sol.front().begin(), sol.front().end(), std::ostreambuf_iterator<char>(std::cout));
    std::cout << std::endl;
    sol.pop();
  }

  return 0;
}
