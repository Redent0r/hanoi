#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

void play(const int & n);
void printStacks(std::vector <std::stack<int>> & stacks);
void move(std::stack<int> & from, std::stack<int> & to, int & ru);

int main()
{
  const int DISKS = 5;
  play(DISKS);
}

void play(const int & n)
{
  if(n < 1)
    {
      std::cout << "Please choose a positive number of disks\n";
      return;
    }
  
  std::vector <std::stack<int>> stacks (3); // always 3 possible positions
  std::unordered_map <int, int> moves; // maps disk to it's last position
  int lrud = -1; // keeps track of least recently used disk
  
  for(int i = n - 1; i >= 0; i--) // the disks are zero-based
    {
      stacks[0].push(i); // all discs start on the left(stacks[0])
    }
  
  std::cout << "initial position:\n";
  printStacks(stacks);
  
}

void move(std::vector<std::stack<int>> & stacks, std::stack<int> & from, std::stack<int> & to, int & ru)
{
  
}

void printStacks(std::vector <std::stack<int>> & stacks)
{
  int i = 0;
  for(const auto & stack : stacks)
    {
      std::cout << i++ << " : ";
      for(auto dump = stack; !dump.empty(); dump.pop())
	std::cout << dump.top() << " - ";
      std::cout << '\n';
    }
  std::cout << '\n';
}
