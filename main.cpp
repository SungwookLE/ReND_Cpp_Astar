#include <vector>
#include <iostream>
#include <string>
#include "boardfile.h"
#include "a_star.h"

int main(){


    files maze("maze.txt");
    maze.ReadBoardFile();
    std::cout<< "MAZE is: " << std::endl;
    maze.PrintGrid();

    std::cout<< "ESCAPE is: " << std::endl;
    
    maze.set_solution(Search(maze.init, maze.goal, maze.grid));
    maze.PrintSolution();
    

    return 0;
}

