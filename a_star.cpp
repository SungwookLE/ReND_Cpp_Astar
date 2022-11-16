#include "a_star.h"

std::vector<std::vector<int>> count_traced;

std::vector<std::vector<std::string>> Search(std::vector<int> start, std::vector<int> goal,
                                             std::vector<std::vector<int>> map)
{
    std::vector<std::vector<int>> closed(map.size(), std::vector<int>(map[0].size(), 0));
    count_traced.assign(map.size(), std::vector<int>(map[0].size(), -1));
    std::vector<std::vector<int>> delta_traced(map.size(), std::vector<int>(map[0].size(), -1));
    std::vector<std::vector<std::string>> navigation(map.size(), std::vector<std::string>(map[0].size(), ""));

    std::vector<std::string> delta_emoji = {">", "<", "v", "^"};
    std::vector<std::vector<int>> delta = {
        {0, 1},  // go right
        {0, -1}, // go left
        {1, 0},  // go down
        {-1, 0}, // go up
    };

    closed[start[0]][start[1]] = 1; // closed, visited

    for (int row = 0; row < navigation.size(); ++row)
    {
        for (int col = 0; col < navigation[0].size(); ++col)
        {
            if (map[row][col] == 1)
                navigation[row][col] = "#";
        }
    }

    std::vector<std::vector<int>> heuristic_map;
    heauristic_map(map, goal, heuristic_map);

    int cost = 1;
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = heuristic_map[x][y];
    int f = g + h;

    std::vector<std::vector<int>> opens;
    opens = {{f, g, x, y}};
    std::vector<int> next;

    bool found = false;
    bool resign = false;
    int count = 0;

    while (found != true && resign != true)
    {
        if (opens.size() == 0)
        {
            resign = true;
            navigation[start[0]][start[1]] = "S";
            navigation[goal[0]][goal[1]] = "G";
            std::cout << "Fail to find the exit!" << std::endl;
            break;
        }
        else
        {
            // CellSort()
            std::sort(opens.begin(), opens.end(), [](auto a, auto b)
                      {
                        if (a[0] > b[0]) 
                            return true;
                        else
                            return false; });

            next = opens.back();
            opens.pop_back();

            f = next[0];
            g = next[1];
            x = next[2], y = next[3];

            count_traced[x][y] = count;
            count += 1;

            if ((x == goal[0]) && (y == goal[1]))
            {
                found = true;
                // SAVE NAVIGATION
                navigation[x][y] = "*G";
                while ((x != start[0]) || (y != start[1]))
                {
                    int x_ex = x - delta[delta_traced[x][y]][0];
                    int y_ex = y - delta[delta_traced[x][y]][1];
                    navigation[x_ex][y_ex] = delta_emoji[delta_traced[x][y]];
                    x = x_ex;
                    y = y_ex;
                }
                navigation[x][y] = "*S";
            }
            else
            {
                // ExpandNeighbors()
                for (int i = 0; i < delta.size(); ++i)
                {
                    int x2 = x + delta[i][0];
                    int y2 = y + delta[i][1];
                    // CheckValidCell()
                    if ((x2 >= 0) && (x2 < map.size()) && (y2 >= 0) && (y2 < map[0].size()))
                    {
                        if ((closed[x2][y2] == 0) && (map[x2][y2] == 0))
                        {
                            int g2 = g + cost;
                            int h2 = heuristic_map[x2][y2];
                            int f2 = g2 + h2;
                            // AddToOpen()
                            opens.push_back({f2, g2, x2, y2});
                            closed[x2][y2] = 1;
                            delta_traced[x2][y2] = i;
                        }
                    }
                }
            }
        }
    }
 
    return navigation;
}

int manhatan_dist(std::vector<int> target, std::vector<int> goal)
{
    // X,Y from 'goal' to 'target', Getting manhatan_distance as INT
    int res;
    res = std::abs(goal[0] - target[0]) + std::abs(goal[1] - target[1]);
    return res;
}

void heauristic_map(std::vector<std::vector<int>> map, std::vector<int> goal, std::vector<std::vector<int>> &heauristic_map)
{
    int dist;
    // std::vector<std::vector<int>> heauristic;
    for (int row = 0; row < map.size(); ++row)
    {
        std::vector<int> row_heuristic;
        for (int col = 0; col < map[0].size(); ++col)
        {
            std::vector<int> target = {row, col};
            dist = manhatan_dist(target, goal);
            row_heuristic.push_back(dist);
        }
        heauristic_map.push_back(row_heuristic);
    }
    return;
}
