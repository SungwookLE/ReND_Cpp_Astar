#include <vector>
#include <iostream>
#include <string>
#include "boardfile.h"
#include "a_star.h"



// void Search();

// void CellSort();

// void ExpandNeighbors();
// void CheckValidCell();
// void Heuristic();
// void AddToOpen();

int main(){


    files maze("test.txt");
    maze.ReadBoardFile();
    std::cout<< "MAZE is: " << std::endl;
    maze.PrintGrid();

    std::cout<< "ESCAPE is: " << std::endl;
    
    maze.set_solution(Search(maze.init, maze.goal, maze.grid));
    maze.PrintSolution();
    




    return 0;
}

