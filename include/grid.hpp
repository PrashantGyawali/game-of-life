#pragma once
#include<vector>
#include "raylib.h"
#include <iostream>
#include <vector>


class Grid{
    private:
        int rows,columns,cellSize=20;
        int focusOffsetX=0,focusOffsetY=0;
        std::vector<std::vector<int>> cells;
        Color ALIVE = {255, 255, 255, 255};
        Color DEAD = {75, 75, 75, 255};
        Color HOVER={185,185,185,255};

    public:


        Grid(int r,int c);
        Grid();
        ~Grid();

        bool IsWIthinBounds(int row, int col)
        {
            if(row>=0 && row<this->rows && col>=0 && col<this->columns)
            {
                return true;
            }
            return false;
        };

        void Set(int r, int c);
        void SetCellSize(int cSize);
        int  GetCellSize();
        void UpdateFocus(int focusX, int focusY);
        
        void Clear();
        void FillRandom();

        void Draw();
        void SetCell(int x, int y, int value);
        void SetCell(std::vector<std::vector<int>> cells);
        int  GetCell(int row, int col);
        int  GetRows();
        int  GetColumns();
};

