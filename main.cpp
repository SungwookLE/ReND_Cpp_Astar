#include <vector>
#include <iostream>
#include <string>
#include "boardfile.h"
#include "a_star.h"

int main(int argc, char** argv){
    files maze(argv[1]);
    maze.ReadBoardFile();
    
    maze.PrintMap();
    maze.set_solution(Search(maze.start, maze.goal, maze.map));
    maze.PrintSolution();

    try{
        if (std::string(argv[2]) == "-COST"){
            maze.PrintCost();
        }
    }
    catch(...){
        ;
    }       
        
    return 0;
}

