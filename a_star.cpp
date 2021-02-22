#include "a_star.h"

std::vector<std::vector<int>> Search(std::vector<int> init, std::vector<int>goal,  
                                    std::vector<std::vector<int>> grid)
                                    {


int cost= 1;
std::vector<int> temp_closed(grid[0].size(), 0);
std::vector<std::vector<int>> closed(grid.size(), temp_closed );

std::cout << closed.size() << ", " << closed[0].size() << std::endl;

// here it is (2/22)


return ;
                                    }

int manhatan_dist(std::vector<int> target, std::vector<int> goal){
    // X,Y from 'goal' to 'target', Getting manhatan_distance as INT
    int res;
    res = std::abs(goal[0]-target[0]) + std::abs(goal[1]-target[1]);
    return res;
}

std::vector<std::vector<int>> heauristic_grid(std::vector<std::vector<int>> grid, std::vector<int> goal){
    int dist;
    std::vector<std::vector<int>> heauristic;
    for(int row = 0 ; row < grid.size() ; ++row){
        std::vector<int> temp_dist;
        for (int col =0 ; col < grid[0].size() ; ++col){
            std::vector<int> target = { row, col};
            dist = manhatan_dist(target, goal);
            temp_dist.push_back(dist);
        }
        heauristic.push_back(temp_dist);
    }


    return heauristic;
}
