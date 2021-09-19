#include "a_star.h"

std::vector<std::vector<std::string>> A_star::Search(){

    initialize();

    while ( found != true && resign != true){

        if (opens.size() == 0){
            resign =true;
            std::cout << "Fail to find the route!" << std::endl;
            break;
        }
        else{
            // CellSort() as Descending order
            std::sort(opens.begin(), opens.end(), [](std::vector<int> a , std::vector<int> b){
                if (a[0] > b[0])
                    return true;
                else if (a[0] == b[0]){
                    if (a[1] > b[1])
                        return true;
                    else if (a[1] == b[1]){
                        if (a[2]<b[2])
                            return true;
                        else if (a[2] ==b[2]){
                            if (a[3]<b[3])
                                return true;
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            });

            next = opens.back();
            opens.pop_back();

            x = next[2];
            y = next[3];
            f = next[0];
            h = next[1];

            expand[x][y] = count;
            count+=1;

            if(( x==goal[0]) && (y==goal[1])){
                found = true;
                // SAVE NAVIGATION
                navi[x][y] = "E";
                while (( x!=start[0]) || (y!=start[0])){
                    int x_ex = x - delta[info[x][y]][0];
                    int y_ex = y - delta[info[x][y]][1];

                    navi[x_ex][y_ex] = delta_name[info[x][y]];
                    x = x_ex;
                    y = y_ex;
                }
                navi[x][y] = "S";
            }
            else{
                // ExpandNegihbors()
                for (int i =0 ; i < delta.size() ; ++i){
                    int x2 = x + delta[i][0];
                    int y2 = y + delta[i][1];

                    // CheckValidCell()
                    if ((x2>=0) && (y2>=0) && (x2<grid.size()) && (y2<grid[0].size())){
                        if ((closed[x2][y2] == 0) && (grid[x2][y2] == 0)){
                            int g2 = g+ cost;
                            int h2 = heuristic[x2][y2];
                            int f2 = g2 + h2;
                            
                            // AddToOpen()
                            opens.push_back({f2,h2,x2,y2});
                            closed[x2][y2]=1;
                            info[x2][y2]=i;
                        }
                    }
                }
            }
        }
    }
    /* if needed COST VALUE MONITORING, comment in)
    std::cout << "COST is: " << std::endl;
    for(int row = 0 ; row< expand.size() ; ++row){
        for (int col =0 ; col < expand[0].size(); ++col){
            if ( col != (expand[0].size()-1))
                std::cout << std::setw(3) << expand[row][col] << " ";
            else
                std::cout << std::setw(3) << expand[row][col] ;
        }
        std::cout << std::endl;
    }
    */

    return navi;
}
