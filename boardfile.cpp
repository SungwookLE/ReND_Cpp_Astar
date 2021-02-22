#include "boardfile.h"



void files::ReadBoardFile(){
    //std::vector<std::vector<int>> grid;

    std::ifstream readFile(board_file);       //읽을 목적의 파일 선언
    std::string line;
    std::string value;
    

    if(readFile.is_open()){       //파일이 열렸는지 확인
        
        while(!readFile.eof()){   //파일 끝까지 읽었는지 확인
            std::getline(readFile, line);
            std::replace(line.begin(), line.end(), ' ', ',');
            std::istringstream linestream(line);
            std::vector<int> temp_vector;
            
            while (std::getline(linestream, value, ',')){
                temp_vector.push_back(std::stoi(value));
            }
            grid.push_back(temp_vector);
        }    
    }

    goal = { int(grid.size()-1), int(grid[0].size()-1)};
    readFile.close();
}