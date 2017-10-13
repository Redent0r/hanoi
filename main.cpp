#include<hanoi.h>

int main()
{
  const unsigned int DISKS = 3;
  Hanoi hanoi(DISKS);
  hanoi.play();
}
