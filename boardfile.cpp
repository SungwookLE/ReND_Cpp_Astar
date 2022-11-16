#include "boardfile.h"

void files::ReadBoardFile()
{
    std::ifstream readFile(board_file); //읽을 목적의 파일 선언
    std::string line;
    std::string value;

    int row = 0, col;
    if (readFile.is_open())
    { //파일이 열렸는지 확인
        while (!readFile.eof())
        { //파일 끝까지 읽었는지 확인
            col = 0;
            std::getline(readFile, line);
            std::istringstream linestream(line);

            std::vector<int> row_map;
            while (std::getline(linestream, value, ' '))
            {
                if (value == "S")
                {
                    this->start = {row, col};
                    row_map.push_back(0);
                }
                else if (value == "G")
                {
                    this->goal = {row, col};
                    row_map.push_back(0);
                }
                else
                {
                    row_map.push_back(std::stoi(value));
                }
                col++;
            }
            this->map.push_back(row_map);
            row++;
        }
    }
    readFile.close();
}