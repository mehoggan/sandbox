/*
 * You have an ordered array X of n integers. Find the array M containing
 * elements where Mi is the product of all integers in X except for Xi.
 * You may not use division. You can use extra memeory
 */

#include <iostream>
#include <stack>
#include <queue>
#include <vector>

/*!
 * Class used to generate sequences with helper function
 */
template <class T>
class sequence : public std::iterator<std::forward_iterator_tag, T>
{
    T val;
public:
    sequence(T init) : val(init) {}
    T operator *() { return val; }
    sequence &operator++() { ++val; return *this; }
    bool operator!=(sequence const &other) { return val != other.val; }
};

template <class T>
sequence<T> gen_seq(T const &val) {
    return sequence<T>(val);
}



static const int N = 3;
std::stack<int> stk;
std::queue<int> que;
int main(int argc, char *argv[]) {
  std::vector<int> seq(gen_seq(1), gen_seq(N + 1));
  for (int x = 0, y = N - 1; x < N && y >= 0; ++x, --y) {
    if (x == 0 && y == N - 1) {
      stk.push(1);
      que.push(1);
    } else {
      stk.push(stk.top() * seq[x - 1]);
      que.push(que.back() * seq[y + 1]);
    }
  }
  for (int x = 0; x < N; ++x) {
    std::cout << (stk.top() * que.front()) << std::endl;
    stk.pop();
    que.pop();
  }
}
