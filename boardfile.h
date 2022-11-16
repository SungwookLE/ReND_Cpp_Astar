#ifndef _BOARD_FILE_H
#define _BOARD_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "a_star.h"

class files{
    public:
    files(std::string file): board_file(file){}

    void ReadBoardFile();

    void PrintSolution(){
        std::cout<< "Solution is: " << std::endl;
        for(int i =0 ; i < solution.size() ; ++i){
            for (int j=0; j < solution[0].size(); ++j)
                std::cout << std::setw(3) <<solution[i][j];
            std::cout << std::endl;
        }
    }
    void set_solution(std::vector<std::vector<std::string>> res){
        this->solution=res;
    }
    void PrintMap(){
        std::cout<< "Map is: " << std::endl;
        for(int row =0 ; row < this->map.size() ; ++row){
            for (int col=0; col < this->map[0].size(); ++col){
                if ((row == this->start[0]) && (col == this->start[1]))
                    std::cout <<  std::setw(3) << "S"; // start
                else if ((row == this->goal[0]) && (col == this->goal[1]))
                    std::cout << std::setw(3) << "G"; // goal
                else
                    std::cout << std::setw(3) <<this->map[row][col];
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> map;
    std::vector<int> start={0,0};
    std::vector<int> goal={0,0};

    void PrintCost(){
           /* if needed COST VALUE MONITORING, comment in)*/
        std::cout<< "COST is: " << std::endl;
        for(int i =0 ; i < count_traced.size() ; ++i){
            for (int j=0; j < count_traced[0].size(); ++j){
                if (j != (count_traced[0].size()-1))
                    std::cout << std::setw(3) <<count_traced[i][j];
                else
                    std::cout << std::setw(3) <<count_traced[i][j];
            }
            std::cout << std::endl;
    }
    }

    private:
    std::vector<std::vector<std::string>> solution;
    std::string board_file;
};




#endif