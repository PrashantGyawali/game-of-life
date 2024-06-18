#pragma once
#include<vector>
#include "raylib.h"
#include <iostream>
#include <vector>
#include "sidepanel.hpp"


class Grid{
    private:
        int rows,columns,cellSize=20;
        int focusOffsetX=0,focusOffsetY=0;
        int initialOffSetY=50;
        std::vector<std::vector<int>> cells;
        Color ALIVE = {255, 255, 255, 255};
        Color DEAD = {75, 75, 75, 255};
        Color HOVER={255,255,255,170};

    public:
        int height=700;


        Grid(int r,int c, int initialOffSetY=50, int height=700);
        Grid();
        ~Grid();

        bool IsWIthinBounds(int row, int col);


        void Set(int r, int c);
        void SetCellSize(int cSize);
        int  GetCellSize();
        void UpdateFocus(int focusX, int focusY);
        void ControlPattern(int row, int column, int val, bool togglePattern);
        
        void Clear();
        void FillRandom();

        void Draw(Sidepanel &sPanel, bool paused);
        void SetCell(int x, int y, int value);
        void SetCell(std::vector<std::vector<int>> cells);
        int  GetCell(int row, int col);
        int  GetRows();
        int  GetColumns();
        bool IsMouseHoveringCell(int cellX, int cellY);
};

