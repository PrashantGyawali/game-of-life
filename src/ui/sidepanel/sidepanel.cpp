#include "sidepanel.hpp"
#include "raylib.h"
#include "raygui.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

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

void Sidepanel::appendPatternToFile(const GridPattern& pattern) {
    std::ofstream outputFile("patterns/custom_patterns.txt", std::ios_base::app);

    if (!outputFile) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    outputFile << pattern.second << std::endl;  // Write pattern name

    for (const auto& row : pattern.first) {
        for (int cell : row) {
            outputFile << cell << " ";
        }
        outputFile << std::endl;
    }
    outputFile << std::endl;  // Separate patterns with a blank line

    outputFile.close();
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
        currentPattern=0;
    }

    if(GuiButton({offsetX+100.0f, 40, 100, 48 }, "Custom")){
        patternType=2; 
        currentPattern=0;   
    }


    GuiSetIconScale(2); 
        if(GuiToggle({offsetX+0.0f, 90+130+50, 50, 40 }, togglePattern?"#112#":" ", &togglePattern)){
        }
        if(GuiButton({offsetX+50.0f, 90+130+50, 150, 40 }, "Toggle Pattern")){
            togglePattern=!togglePattern;
        }
    GuiSetIconScale(1);


    if(addCustomPattern==false)
     {
        if(GuiButton({offsetX+0.0f, 330, 200, 48 }, "+ Add Custom Pattern")){
            customGridSet();
            addCustomPattern = true;
     }
    }

    if(addCustomPattern)
    {
    //textbox for adding custom pattern name
     GuiSetStyle(TEXTBOX, TEXT_COLOR_NORMAL, ColorToInt(WHITE)); 
     
     DrawText("Pattern Name:", offsetX+10, offsetY+330, 20, WHITE);
     if(GuiTextBox({offsetX+0.0f, offsetY+355.0f,200 ,48}, CustomPatternName, 20, customPatternText)){
            customPatternText= !customPatternText;
     }

    // Draw the grid for adding custom pattern
      DrawText("Draw Pattern:", offsetX+10, offsetY+415, 20, WHITE);
      customGridDraw();

      if(GuiButton({offsetX+0.0f, 604, 100, 48 }, "+ Add")){
        addCustomPattern = false;

        // Create the temporary grid to store custom pattern
        std::vector<std::vector<int>> grid(10, std::vector<int>(10, 0));
    
        // Fill the grid with the specific pattern using nested loops
       for (int row = 0; row < 10; row++) {
        for (int column = 0; column < 10; column++) {
            if (customCells[row][column]) {
                grid[row][column] = 1;
            }
            else{
                grid[row][column] = 0;
            }
         }
        }

        GridPattern newPattern={grid, CustomPatternName};
       
        appendPatternToFile(newPattern);
        patternType=2;
        pGrid = readVectorFromFile(patternType==1?"patterns/default_patterns.txt":"patterns/custom_patterns.txt");
        currentPattern = pGrid.size()-1;
      }

      if(GuiButton({offsetX+100.0f, 604, 100, 48 }, "Cancel")){
        addCustomPattern = false;
      }


       
      if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {  
            Vector2 mousePosition = GetMousePosition();
            int row = (mousePosition.y-425)/15;
            int column = (mousePosition.x-1008)/15;
            if(row>=1 && row<=10 && column>=1 && column<=10)
            {
                toggleCustomCell(row-1,column-1);
            }
       }
    }
}

void Sidepanel::toggleCustomCell(int row,int column){
    customCells[row][column]= !customCells[row][column];
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

void Sidepanel::customGridDraw()
{
    Color color;

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        { 
            switch(customCells[row][col])
            {
                case 1:
                    color = ALIVE;
                    break;
                default:               
                    color = DEAD;
                    break;
            }

            int csize = 15;
            int cellX = offsetX + 24 + (col * csize);
            int cellY = offsetY + 440 + (row * csize); 

            DrawRectangle(cellX, cellY, csize-1, csize-1, color);
        }
    }

}

void Sidepanel::customGridSet(){
     customCells.resize(10);

    for (int i = 0; i < 10; i++)
    {
        customCells[i].resize(10);
    }

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            customCells[row][col] = 0;
        }
    }
}