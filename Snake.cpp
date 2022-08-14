#include <iostream>
#include <ctime>
#include <unistd.h>
#include <vector>
using namespace std;
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
unsigned const int SIZE = 10, TOTAL = 3;
struct Snake
{
public:
  int y, x, d, points;
  vector<int> h_x, h_y;
  Snake()
  {
    y = SIZE / 2, x = SIZE / 2,
    d = RIGHT, points = 0;
  }
};
