#include "Snake.cpp"
using namespace std;

class Map
{
private:
  const char SNAKE = '@', FRUIT = 'F', EMPTY = ' ', TAIL = 'T';
  char cells[SIZE][SIZE];
  vector<int> ecx, ecy;
  
public:
  bool exists(int a, int b)
  {
    for (int i = 0; i < ecx.size(); i++)
      if (ecx[i] == a && ecy[i] == b)
	return true;
    return false;
  }

  void del_el(int a, int b)
  {
    for (int i = 0; i < ecx.size(); i++)
      if (ecx[i] == a && ecy[i] == b)
	ecx.erase(ecx.begin() + i), ecy.erase(ecy.begin() + i);
  }
  void add_el(int a, int b)
  {	
    cells[a][b] = EMPTY;
    ecx.push_back(a), ecy.push_back(b);
  }
  
  Map(Snake snake)
  {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
      {
	cells[j][i] = EMPTY;
	add_el(j, i);
      }
    cells[snake.x][snake.y] = SNAKE;
    del_el(snake.x, snake.y);
    for (int i = 0; i < TOTAL; i++)
      spawn();
  }
  
  void rendering()
  {
    for (int i = 1; i < SIZE+2; i++)
      cout << "##";
    cout << "\n";
    for (int i = 0; i < SIZE; i++)
    {
      cout << "#";
      for (int j = 0; j < SIZE; j++)
	cout << cells[j][i] << " ";
      cout << "#\n";
    }
    for (int i = 1; i < SIZE+2; i++)
      cout << "##";
    cout << "\n";
  }
    
  void spawn()
  {
    int t1 = rand() % (ecx.size() - 1), t2 = rand() % (ecx.size() - 1);
    cells[ecx[t1]][ecy[t2]] = FRUIT;
    del_el(t1, t2);
  }
  
  void snake_move(Snake& snake)
  {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
	if (cells[j][i] == TAIL)
	{
	  cells[j][i] = EMPTY;
	  add_el(j, i);
	}
    int last[] = {snake.x, snake.y};
    snake.h_x.push_back(snake.x), snake.h_y.push_back(snake.y);
    
    if (snake.d == LEFT && snake.x > 0)
    {
      snake.x--;
      del_el(snake.x, snake.y);
    }
    else if (snake.d == RIGHT && snake.x < SIZE-1)
    {
      snake.x++;
      del_el(snake.x, snake.y);
    }
    else if (snake.d == UP && snake.y > 0)
    {
      snake.y--;
      del_el(snake.x, snake.y);
    }
    else if (snake.d == DOWN && snake.y < SIZE-1)
    {
      snake.y++;
      del_el(snake.x, snake.y);
    }

    if (cells[snake.x][snake.y] == FRUIT)
    {
      snake.points++;
      spawn();
    }
    
    for (int i = 1; i <= snake.points; i++)
    {
      if (cells[snake.h_x[snake.h_x.size() - i]][snake.h_y[snake.h_y.size() - i]] == FRUIT)
	spawn();
      
      cells[snake.h_x[snake.h_x.size() - i]][snake.h_y[snake.h_y.size() - i]] = TAIL;
      del_el(snake.h_x[snake.h_x.size() - i], snake.h_y[snake.h_y.size() - i]);
    }
    
    if (cells[snake.x][snake.y] == SNAKE || cells[snake.x][snake.y] == TAIL)
    {
      cout << "GAME OVER!\npoints: " << snake.points << "\n";
      exit(EXIT_SUCCESS);
    }
    if (snake.points == 0) cells[last[0]][last[1]] = EMPTY;
    cells[snake.x][snake.y] = SNAKE;
  }
};
