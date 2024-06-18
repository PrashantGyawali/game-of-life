#include "grid.hpp"
#include<raylib.h>
#include<iostream>
#include "utils.cpp"
#include<cmath>


Grid::Grid()
{
    Set(40, 50);
}
Grid::Grid(int r, int c, int initialOffSetY,int height)
{
    Set(r, c);
    this->initialOffSetY = initialOffSetY;
}



void Grid::UpdateFocus(int focusX, int focusY)
{
    focusOffsetX = focusX;
    focusOffsetY = focusY;
}


void Grid::Set(int r, int c)
{

    this->rows = r;
    this->columns = c;
    
    cells.resize(this->rows);

    for (int i = 0; i < this->rows; i++)
    {
        cells[i].resize(this->columns);
    }

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            cells[row][col] = 0;
        }
    }
}



void Grid::Clear()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            cells[row][col] = 0;
        }
    }
}


void Grid::FillRandom()
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            cells[row][col] = getRandomBoolean(40);
        }
    }
}


void Grid::Draw(Sidepanel &sPanel, bool paused)
{
    Color color;
    
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {

            // needed for rainbow colors
            float distance = std::sqrt(row * row + col * col);
            float maxDistance = std::sqrt(rows * rows + columns * columns);

            // Normalize the distance
            float normalizedDistance = distance /( maxDistance);

            switch(cells[row][col])
            {
                case 1:
                    color = ALIVE;

                    // For rainbow colors different options
                    color=ColorFromHSV((float)(row*columns+col)/((float)rows*columns)*360, 0.8, 0.8);
                    // color = ColorFromHSV(normalizedDistance * 360, 0.75, 0.8);
                    break;
                default:               
                    color = DEAD;
                    break;
            }
            // std::cout <<initialOffSetY<<std::endl;
            int x = col * cellSize-this->focusOffsetX;
            int y = row * cellSize-this->focusOffsetY+initialOffSetY;

            if(paused) {
                int size = sPanel.pGrid[sPanel.currentPattern].first.size();

                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < sPanel.pGrid[sPanel.currentPattern].first[i].size(); j++) {
                        if(IsMouseHoveringCell(row+(size/2)-i, col+(size/2)-j)) {       //+ adds coloured box to left or above
                            if(sPanel.pGrid[sPanel.currentPattern].first[i][j]) {
                                color = HOVER;
                            }
                        }
                    }
                }
            }

            DrawRectangle(x, y, cellSize-1, cellSize-1, color);
        }
    }

}

Grid::~Grid()
{
    cells.clear();
};




void Grid::SetCell(int row, int col, int value)
{
    if (IsWIthinBounds(row, col))
    {
        cells[row][col] = value;
    }
}

void Grid::SetCell(std::vector<std::vector<int>> cells)
{
    this->cells.clear();
    this->cells = cells;
}

int Grid::GetCell(int row, int col)
{
    if (IsWIthinBounds(row, col))
    {
        return cells[row][col];
    }
    return 0;
}

int Grid::GetRows()
{
    return rows;
}
int Grid::GetColumns()
{
    return columns;
}


void Grid::SetCellSize(int cSize)
{
    if(cSize>1 && cSize<80)
    {
        cellSize = cSize;
    }
    else if(cSize<=1)
    {
        cellSize = 2;
    }
    else
    {
        cellSize = 80;
    }
}

int Grid::GetCellSize()
{
    return cellSize;
}

void Grid::ControlPattern(int row, int column, int val, bool togglePattern)
{
    if(IsWIthinBounds(row, column))
    {
        if(val != 0) {
            if(togglePattern) {
                cells[row][column] = !cells[row][column];
            }
            if(!togglePattern) {
                cells[row][column] = val;
            }
        }
    }
}

bool Grid::IsMouseHoveringCell(int cellX, int cellY)
{
    Vector2 mousePos = GetMousePosition();
    if( !CheckCollisionPointRec(mousePos, {0, initialOffSetY*1.0f, cellSize*columns*1.0f, height*1.0f}))
    {
        return false;
    }
    return (mousePos.y >= (cellX * cellSize+initialOffSetY-focusOffsetY) && mousePos.y < ((cellX + 1) * cellSize+initialOffSetY-focusOffsetY) &&
            mousePos.x >= (cellY * cellSize-focusOffsetX) && mousePos.x < ((cellY + 1) * cellSize)-focusOffsetX);
}



bool Grid::IsWIthinBounds(int row, int col)
{
    if(row>=0 && row<this->rows && col>=0 && col<this->columns)
    {
        return true;
    }
    return false;

}