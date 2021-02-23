#ifndef __A_STAR_H_
#define __A_STAR_H_

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

std::vector<std::vector<std::string>> Search(std::vector<int> init, std::vector<int>goal, std::vector<std::vector<int>> grid);
int manhatan_dist(std::vector<int> target, std::vector<int> goal);
void heauristic_grid(std::vector<std::vector<int>> grid, std::vector<int> goal,std::vector<std::vector<int>> &heauristic);

#endif