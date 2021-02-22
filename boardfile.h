#ifndef _BOARD_FILE_H
#define _BOARD_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class files{
    public:
    files(std::string file): board_file(file){}

    void ReadBoardFile();
    void PrintSolution(){
        for(int i =0 ; i < solution.size() ; ++i){
            for (int j=0; j < solution[0].size(); ++j){
                if (j != (solution[0].size()-1))
                    std::cout << solution[i][j] << ", ";
                else
                    std::cout << solution[i][j];
            }
            std::cout << std::endl;
        }
    }
    void set_solution(std::vector<std::vector<int>> res){
        std::copy( res.begin(), res.end(), solution.begin() );
    }
    void PrintGrid(){
        for(int i =0 ; i < grid.size() ; ++i){
            for (int j=0; j < grid[0].size(); ++j){
                if ( (j == init[0]) && (i == init[1]) )
                    std::cout << "*" << "  ";
                else if (j != (grid[0].size()-1))
                    std::cout << grid[i][j] << "  ";
                else if ( (j == goal[1]) && (i == goal[0]) )
                    std::cout << "*" ; // goal
                else
                    std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> grid;
    std::vector<int> init={0,0};
    std::vector<int> goal;

    private:
    std::vector<std::vector<int>> solution;
    std::string board_file;
    

};




#endif