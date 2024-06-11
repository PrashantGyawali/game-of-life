#include "sidepanel.hpp"
#include "raylib.h"
#include "raygui.h"
#include <iostream>
#include <vector>

Sidepanel::Sidepanel(int width=200)
{
    this->width=width;
    this->height=700;
}

Sidepanel::~Sidepanel()
{
}


void Sidepanel::Draw()
{
    DrawRectangle(offsetX, offsetY, width, height, {100, 100, 100, 255});
    DrawRectangleLines(offsetX, offsetY, width, height, {100, 100, 100, 255});
    DrawText("Patterns", offsetX+10, offsetY+10, 20, WHITE);

    std::vector<std::vector<std::vector<int>>> grid = {{
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    },    
    {{0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}},
    {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0}
    },
    {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
    }

    };



    // Draw the grid
    DrawText("Glider", offsetX+30, offsetY+60, 20, WHITE);
    for (int i = 0; i < grid[currentPattern].size(); i++) {
        for (int j = 0; j < grid[currentPattern][i].size(); j++) {
            int csize = 130 / std::max(grid[currentPattern][i].size(), grid[currentPattern].size());
            int cellX = offsetX + 40 + (j * csize);
            int cellY = offsetY + 80 + (i * csize);  // Incremented by 30
            DrawRectangle(cellX+1, cellY+1, csize-1, csize-1, grid[currentPattern][i][j] == 0 ? GRAY : WHITE);
        }
    }


    // Draw the increment and decrement buttons
    float buttonWidth = 30;
    float buttonHeight = 75;
    int buttonSpacing = 60;


    if (GuiButton({offsetX+10.0f, 90, buttonWidth, buttonHeight}, "<")) {
        currentPattern=(currentPattern-1+grid.size())%grid.size();
    }

    if (GuiButton({offsetX+20.0f+150, 90, buttonWidth, buttonHeight}, ">")) {
        currentPattern=(currentPattern+1)%grid.size();
    }


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
