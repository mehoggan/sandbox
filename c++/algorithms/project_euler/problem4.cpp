#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

bool is_palendrome(int N) 
{
  char buffer[16];
  memset(buffer, 0, 16);
  sprintf(buffer, "%d", N);
  int len = strlen(buffer);
  /*
   * Scan from left and right if you find unmatching
   * chars at left and right then return false
   */ 
  for (int x = 0, y = len - 1; x < y; ++x, --y) {
    if (buffer[x] != buffer[y]) {
      return false;
    }
  }
  return true;
}


int main(int argc, char *argv[]) 
{
 std::priority_queue<int, std::vector<int> > pri_que;
 for (int x = 999; x >= 100; --x) {
   for (int y = 999; y >= 100; --y) {
     int product = x * y;
     if(is_palendrome(product)) {
       pri_que.push(product);
     }
   }
 }
 fprintf(stdout, "%d", pri_que.top());
 return 0;
}
