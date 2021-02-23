# Review: ND_Cpp_Astar
>AUTHOR: SungwookLE (joker1251@naver.com)  
>DATE: '21.2/22  
>LANGUAGE: C++

### Build Script
Build: `g++ main.cpp a_star.cpp boardfile.cpp -o a_star`  
Run: `./a_star`

## 1. INTRODUCTION
You can adjust `maze.txt` file to test the a* algorithm functionality.

The structure of A_star is as below.  
![image](https://video.udacity-data.com/topher/2019/August/5d4b1057_addtoopen/addtoopen.png)
`Search()` function is implemented by using **A star** one of effcient algorithm when finding a route from Start to Goal.

This **A star** is well used in area of autonomous parking system when finding the proper route to get the goal point under complex ground.

## 2. MAIN
Except for `ReadBoardFile()` and `PrintSolution()`, I would explain the **A star** algorithm. As you can see the `main()` as below. Flow is same as above figure.
```c++
//main.cpp
#include "boardfile.h"
#include "a_star.h"
int main(){
    files maze("maze.txt");
    maze.ReadBoardFile();
    maze.PrintGrid();
    maze.set_solution(Search(maze.init, maze.goal, maze.grid));
    maze.PrintSolution();
    return 0;
}
```

For implementing the **A star**, there are some points that be remembered. First is `Heuristic(), h` that is the some of the cost value. Heuristic value can be calculated by various methods. In this project, Heuristic value is manhatan distance that is distance from `Goal` to `Target` as below.
```c++
//a_star.cpp
int manhatan_dist(std::vector<int> target, std::vector<int> goal){
    int res;
    res = std::abs(goal[0]-target[0]) + std::abs(goal[1]-target[1]);
    return res;
}
``` 
Second is `g` value. When moving one step, then `Step` is increased by one.  
Third is that overall total cost value in **A star** is `f=g+h`. This value is used when determining the next cell(place) by choosing the smallenst value among the proper open candidates.  

Those are all thing when implementing the **A star** algorithm.


```pseudo code
//pseudo code
def A_star_search( grid, start, goal):
 *1.Given ( grid, start, goal)
    closed = [0, 0, 0, 0, ...] 
    (0 means not visted yet, size is same as grid)

    <-`Heuristic`->
    heuristic = manhatan_distance(each cell, goal)
    
 *2.initial point:
    closed[start point] = 1 (1 means close)
    g = 0
    h = heuristic[start]
    f = g+h
    opens_candidate.append({f,x,y})

 *3.loop:
    while (found != true and resign != true):
        if len(opens_candidate )==0:
          resign = true;
          print("fail to find route")
        else:

          <-`CellSort`->
          sort(opens_candidate) as descending order
          next= opens_candidate.pop()
          x = next[1]
          y = next[2]

          if (x == goal[0] && y == goal[1]):
            found =true;
          else:

            <-`ExpandNeighbors`->
            for delta in range(up, down, left, right direction): 
              x2 = x + delta[0]
              y2 = y + delta[1]

              <-`CheckValidCell()`->
              if (x2 and y2 in grid area):
                g2 = g + 1
                f2 = g2 + heuristic[x2, y2]

                <-`AddToOpen()`->
                opens_candidate.append({f2, x2, y2}) 
```

Let's dive the code in detail.

```c++ 
//a_star.cpp
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

    closed[init[0]][init[1]]=1; // start closed

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
    return navi;
}
```

As I explain it in pseudo code, the A_star is consists of `CellSort()`, `ExpandNeighbors()`, `CheckValidCell()`, `Heuristic()`, `AddToOpen()`. It is the efficient way to get route from start to goal. Using Heuristic value, and sorting the opens list by heuristic. the best candidate is choosen.

## 3. CONCLUSION
You can modify the maze.txt in order to test under various map data.

```
MAZE is: 
  *    1    0    0    0    0    0    0
  0    1    0    1    1    1    1    0
  0    1    0    0    0    0    1    0
  0    1    1    0    1    0    1    0
  0    1    0    0    1    1    1    0
  0    0    0    1    1    0    0    *
** 1 is grid / 0 is aisle

COST is: 
  INIT-1   17   18   19   20   21   22
  1   -1   16   -1   -1   -1   -1   23
  2   -1   15   11   12   13   -1   24
  3   -1   -1   10   -1   14   -1   25
  4   -1    8    9   -1   -1   -1   26
  5    6    7   -1   -1   -1   -1   GOAL
** Number is cost value(how many step: 27)

NAVIGATOR is: 
  *    #    >    >    >    >    >    v
  v    #    ^    #    #    #    #    v
  v    #    ^    <              #    v
  v    #    #    ^    #         #    v
  v    #    >    ^    #    #    #    v
  >    >    ^    #    #              *
```

## DISCUSSION
Another approach is the dynamic programming to find route for dynamic object. It provide dynamic route in all given grid.
I will update this approach soon.
