#include "a_star.h"

std::vector<std::vector<std::string>> Search(std::vector<int> init, std::vector<int>goal,  
                                    std::vector<std::vector<int>> grid)
{
    int cost= 1;
    std::vector<int> temp_closed(grid[0].size(), 0);
    std::vector<std::vector<int>> closed(grid.size(), temp_closed );

    std::vector<int> temp_expand(grid[0].size(), -1);
    std::vector<std::vector<int>> expand(grid.size(), temp_expand );

    std::vector<std::string> temp_navi(grid[0].size(), " ");
    std::vector<std::vector<std::string>> navi(grid.size(), temp_navi );

    for(int row = 0; row < navi.size(); ++row){
        for(int col=0; col < navi[0].size(); ++col){
            if (grid[row][col] != 0 )
                navi[row][col] = "#";
        }
    }

    std::vector<int> temp_info(grid[0].size(), -1);
    std::vector<std::vector<int>> info(grid.size(), temp_info );

    closed[init[0]][init[1]]=1; // closed

    // Heuristic()
    std::vector<std::vector<int>> heuristic_map;
    heauristic_grid(grid,goal, heuristic_map); 

    int x = init[0];
    int y = init[1];

    int g = 0;
    int h = heuristic_map[x][y];
    int f = g+h;

    std::vector<std::vector<int>> opens;
    opens.push_back({f,g,x,y});

    std::vector<int> next;

    bool found = false;
    bool resign = false;
    int count =0;

    std::vector<std::vector<int>> delta =
         {{-1, 0 }, // go up
          { 0, -1}, // go left
          { 1, 0 }, // go down
          { 0, 1 }}; // go right

    std::vector<std::string> delta_name = { "^", "<", "v", ">"};

    while ( found != true and resign !=true)
    {
        if (opens.size() == 0){
            resign = true;
            std::cout << "Fail to find the exit!" << std::endl;
            break;
        }
        else{
            // CellSort()
            std::sort(opens.begin(), opens.end(), [](std::vector<int> a,std::vector<int> b)
            {   if (a[0] > b[0]) 
                    return true;
                else if ( a[0] == b[0]){
                    if (a[1] > b[1])
                        return true;
                    else if ( a[1] ==b[1]){
                        if (a[2] > b[2])
                            return true;
                        else if (a[2] == b[2]){
                            if (a[3] >= b[3])
                                return true;
                        }
                    }
                }
                    return false;}
            );
            next=opens.back();
            opens.pop_back();

            x = next[2];
            y = next[3];
            f = next[0];
            g = next[1];
            expand[x][y] = count;
            count+=1;
            if (( x == goal[0]) && ( y == goal[1])){
                found = true;
                // SAVE NAVIGATION
                navi[x][y] = "*";
                while ( (x != init[0]) || (y!=init[1]) ){
                    int x_ex = x - delta[info[x][y]][0];
                    int y_ex = y - delta[info[x][y]][1];
                    navi[x_ex][y_ex] = delta_name[info[x][y]];
                    x= x_ex;
                    y= y_ex;
                }
                navi[x][y]="*";
            }
            else{
                // ExpandNeighbors()
                for(int i =0 ; i < delta.size() ; ++i){
                    int x2 = x + delta[i][0];
                    int y2 = y + delta[i][1];
                    // CheckValidCell()
                    if ((x2 >= 0) && (x2 < grid.size()) && (y2>=0) && (y2 < grid[0].size()) ){
                        if ((closed[x2][y2] == 0) && (grid[x2][y2] ==0)){
                            int g2 = g +cost;
                            int h2 = heuristic_map[x2][y2];
                            int f2 = g2 + h2;
                            // AddToOpen()
                            opens.push_back({f2,g2,x2,y2});
                            closed[x2][y2] = 1;
                            info[x2][y2] = i;
                        }
                    }
                }
            }
        }
    }
    /* if needed COST VALUE MONITORING, comment in)
    std::cout<< "COST is: " << std::endl;
    for(int i =0 ; i < expand.size() ; ++i){
            for (int j=0; j < expand[0].size(); ++j){
                if (j != (expand[0].size()-1))
                    std::cout << std::setw(3) <<expand[i][j] << "  ";
                else
                    std::cout << std::setw(3) <<expand[i][j];
            }
            std::cout << std::endl;
    }
    */

    return navi;
}



int manhatan_dist(std::vector<int> target, std::vector<int> goal){
    // X,Y from 'goal' to 'target', Getting manhatan_distance as INT
    int res;
    res = std::abs(goal[0]-target[0]) + std::abs(goal[1]-target[1]);
    return res;
}

void heauristic_grid(std::vector<std::vector<int>> grid, std::vector<int> goal,std::vector<std::vector<int>> &heauristic){
    int dist;
    //std::vector<std::vector<int>> heauristic;
    for(int row = 0 ; row < grid.size() ; ++row){
        std::vector<int> temp_dist;
        for (int col =0 ; col < grid[0].size() ; ++col){
            std::vector<int> target = { row, col};
            dist = manhatan_dist(target, goal);
            temp_dist.push_back(dist);
        }
        heauristic.push_back(temp_dist);
    }


    return;
}
