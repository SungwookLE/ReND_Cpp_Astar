#ifndef __A_STAR_H_
#define __A_STAR_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

// 

class A_star{

public:
    /**
    * @brief Construct a new a star object
    * 
    * @param _start 
    * @param _goal 
    * @param _grid 
    */
    A_star(std::vector<int> _start, std::vector<int> _goal, std::vector<std::vector<int>> _grid){
        start = _start;
        goal = _goal;
        grid = _grid;

        std::vector<int> temp_closed(grid[0].size(), 0);
        std::vector<std::vector<int>> _closed(grid.size(),temp_closed);
        closed = _closed;

        std::vector<int> temp_info(grid[0].size(), -1);
        std::vector<std::vector<int>> _info(grid.size(), temp_info );
        info = _info;

        std::vector<int> temp_expand(grid[0].size(), -1);
        std::vector<std::vector<int>> _expand(grid.size(), temp_expand );
        expand = _expand;

        std::vector<std::string> temp_navi(grid[0].size(), " ");
        std::vector<std::vector<std::string>> _navi(grid.size(), temp_navi );
        navi = _navi;

        for(int row = 0 ; row < navi.size() ; ++row){
            for(int col = 0 ; col < navi[0].size(); ++col){
                if (grid[row][col] != 0)
                    navi[row][col] = "#";
            }
        } //Set maze for printing at last phase

        std::vector<int> temp_heuristic(grid[0].size(), (grid[0].size() + grid.size()));
        std::vector<std::vector<int>> _heuristic(grid.size(), temp_heuristic);
        heuristic=_heuristic;
    }


    std::vector<std::vector<std::string>> Search();


private:
    std::vector<int> start, goal;
    std::vector<std::vector<int>> grid;


    std::vector<std::vector<int>> closed, info, expand, heuristic;
    std::vector<std::vector<std::string>> navi;
    std::vector<std::vector<int>> opens;
    std::vector<int> next;

    int x, y, g, h, f;


    std::vector<std::vector<int>> delta =
         {{-1, 0 }, // go up
          { 0, -1}, // go left
          { 1, 0 }, // go down
          { 0, 1 }}; // go right
    std::vector<std::string> delta_name = { "^", "<", "v", ">"};

    bool found;
    bool resign;
    int count;
    int cost=1;

    void initialize(){
        closed[start[0]][start[1]] = 1; // closed
        heauristic_calculate();
        
        x = start[0];
        y = start[1];

        g = 0;
        h = heuristic[x][y];
        f = g+h;
        opens.push_back({f,h,x,y});

        found = false;
        resign = false;
        count = 0;
    }
    
    int manhatan_dist(std::vector<int> target, std::vector<int> _goal){
        int dist =0;
        dist = std::abs(target[0] - _goal[0]) + abs(target[1] - _goal[1]);
        return dist;
    }
    void heauristic_calculate(){
        for(int row = 0 ; row<grid.size() ; ++row){
            for(int col =0 ; col<grid[0].size(); ++col){
                int temp_heuristic = manhatan_dist({row, col}, goal);
                heuristic[row][col] = temp_heuristic;
            }
        }
    }

};






#endif