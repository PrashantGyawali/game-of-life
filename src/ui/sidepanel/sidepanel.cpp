#include "sidepanel.hpp"
#include "raylib.h"
#include "raygui.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

Sidepanel::Sidepanel(int width=200)
{
    this->width=width;
    this->height=700;
}

Sidepanel::~Sidepanel()
{
}

typedef std::pair<std::vector<std::vector<int>>, std::string> GridPattern;

std::vector<GridPattern> Sidepanel::readVectorFromFile(const std::string& filename)
{
    std::ifstream inputFile(filename);
    std::vector<GridPattern> patterns;

    if (!inputFile) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return patterns;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue; // Skip empty lines

        std::string patternName = line;
        std::vector<std::vector<int>> grid;
        
        // Read the grid rows until a blank line or end of file is encountered
        while (std::getline(inputFile, line) && !line.empty()) {
            std::istringstream ss(line);
            std::vector<int> row;
            int value;
            while (ss >> value) {
                row.push_back(value);
            }
            grid.push_back(row);
        }

        patterns.push_back({grid, patternName});
    }

    inputFile.close();
    return patterns;
}


void Sidepanel::Draw()
{
    DrawRectangle(offsetX, offsetY, width, height, {100, 100, 100, 255});
    DrawRectangleLines(offsetX, offsetY, width, height, {100, 100, 100, 255});
    DrawText("Patterns", offsetX+10, offsetY+10, 20, WHITE);

    pGrid = readVectorFromFile(patternType==1?"patterns/default_patterns.txt":"patterns/custom_patterns.txt");

    // Draw the grid
    for (int i = 0; i < pGrid[currentPattern].first.size(); i++) {
        for (int j = 0; j < pGrid[currentPattern].first[i].size(); j++) {
            int csize = 130 / std::max(pGrid[currentPattern].first[i].size(), pGrid[currentPattern].first.size());
            int cellX = offsetX + 35 + (j * csize);
            int cellY = offsetY + 130 + (i * csize);  // Incremented by 30
            DrawRectangle(cellX+1, cellY+1, csize-1, csize-1, pGrid[currentPattern].first[i][j] == 0 ? GRAY : WHITE);
            DrawText(pGrid[currentPattern].second.c_str(), offsetX+30, offsetY+105, 20, WHITE);
        }
    }


    // Draw the increment and decrement buttons
    float buttonWidth = 30;
    float buttonHeight = 110;
    int buttonSpacing = 60;


    if (GuiButton({offsetX+5.0f, 140, buttonWidth, buttonHeight}, "<")) {
        currentPattern=(currentPattern-1+pGrid.size())%pGrid.size();
    }

    if (GuiButton({offsetX+15.0f+150, 140, buttonWidth, buttonHeight}, ">")) {
        currentPattern=(currentPattern+1)%pGrid.size();
    }

    if(GuiButton({offsetX+0.0f, 40, 100, 48 }, "Default")){
        patternType=1;  
    }

    if(GuiButton({offsetX+100.0f, 40, 100, 48 }, "Custom")){
        patternType=2;    
    }


    GuiSetIconScale(2); 
        if(GuiToggle({offsetX+0.0f, 90+130+50, 50, 40 }, togglePattern?"#112#":" ", &togglePattern)){
        }
        if(GuiButton({offsetX+50.0f, 90+130+50, 150, 40 }, "Toggle Pattern")){
            togglePattern=!togglePattern;
        }
    GuiSetIconScale(1);


}


void Sidepanel::SetOffset(int x, int y)
{
    offsetX=x;
    offsetY=y;
}

void Sidepanel::SetHeight()
{
    height=GetScreenHeight();
}
