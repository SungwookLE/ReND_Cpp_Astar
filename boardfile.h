#ifndef _BOARD_FILE_H
#define _BOARD_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

class files{
    public:
    files(std::string file): board_file(file){}

    void ReadBoardFile();
    void PrintSolution(){
        std::cout<< "NAVI is: " << std::endl;
        for(int i =0 ; i < solution.size() ; ++i){
            for (int j=0; j < solution[0].size(); ++j){
                if (j != (solution[0].size()-1))
                    std::cout << std::setw(3) <<solution[i][j] << "  ";
                else
                    std::cout << std::setw(3) <<solution[i][j];
            }
            std::cout << std::endl;
        }
    }
    void set_solution(std::vector<std::vector<std::string>> res){
        solution=res;
    }
    void PrintGrid(){
        std::cout<< "MAZE is: " << std::endl;
        for(int i =0 ; i < grid.size() ; ++i){
            for (int j=0; j < grid[0].size(); ++j){
                if ( (j == init[0]) && (i == init[1]) )
                    std::cout <<  std::setw(3) <<"*" << "  ";
                else if (j != (grid[0].size()-1))
                    std::cout << std::setw(3) << grid[i][j] << "  ";
                else if ( (j == goal[1]) && (i == goal[0]) )
                    std::cout << std::setw(3) << "*" ; // goal
                else
                    std::cout << std::setw(3) <<grid[i][j];
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> grid;
    std::vector<int> init={0,0};
    std::vector<int> goal;

    private:
    std::vector<std::vector<std::string>> solution;
    std::string board_file;
    

};




#endif