#pragma once

#include "raylib.h"
#include<vector>
#include<string>

class Sidepanel{

    private:
    int selection=0;
    int width,height;
    int patternType=1;
    std::vector<std::vector<int>> customCells;
    Color ALIVE = {255, 255, 255, 255};
    Color DEAD = {75, 75, 75, 255};
    Color HOVER={255,255,255,170};


    public:
    bool togglePattern=true;
    bool addCustomPattern = false;
    bool customPatternText = false;
    char CustomPatternName[20] = "Custom";
    int currentPattern = 0;
    int offsetX=1000, offsetY=0;

    Sidepanel(int width);
    ~Sidepanel();

    // Draw the sidepanel
    void Draw();
    void SetOffset(int x, int y);
    void SetHeight();

    // To change the pattern selection
    void SetSelection(int change);
    void customGridDraw();
    void customGridSet();
    void toggleCustomCell(int row, int column);

    //changes here saturday

    typedef std::pair<std::vector<std::vector<int>>, std::string> GridPattern;
    std::vector<GridPattern> readVectorFromFile(const std::string& filename);
    std::vector<GridPattern> pGrid;
    void appendPatternToFile(const GridPattern& pattern);

};