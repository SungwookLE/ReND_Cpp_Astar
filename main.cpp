#include <vector>
#include <iostream>
#include <string>
#include "boardfile.h"
#include "a_star.h"

int main(){
    files maze("maze.txt");


    maze.ReadBoardFile();

    A_star solver(maze.init, maze.goal, maze.grid);
    maze.PrintGrid();
    maze.set_solution(solver.Search());
    maze.PrintSolution();
    
    return 0;
}

