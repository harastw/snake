#include "Map.cpp"
#include <thread>
#include <chrono>
using namespace std;
#include <unistd.h>
#include <termios.h>
char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
int main()
{
  srand(time(NULL));
  char ch;
  Snake snake = Snake();
  Map m = Map(snake);
  thread t([&]()
  {
    while (true)
    {
      ch = getch();
      if (ch == 'a') snake.d = LEFT;
      else if (ch == 'd') snake.d = RIGHT;
      else if (ch == 'w') snake.d = UP;
      else if (ch == 's') snake.d = DOWN;
    }
  });
  while (true)
  {
    m.rendering();
    this_thread::sleep_for(chrono::milliseconds(500));
    system("clear");
    m.snake_move(snake);
  }
  t.detach();
  return 0;
}
