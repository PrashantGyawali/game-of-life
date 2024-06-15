#pragma once

#include<vector>
#include<string>

class Sidepanel{

    private:
    int selection=0;
    int width,height;
    int patternType=1;

    public:
    bool togglePattern=true;
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

    //changes here saturday

    typedef std::pair<std::vector<std::vector<int>>, std::string> GridPattern;

    std::vector<GridPattern> readVectorFromFile(const std::string& filename);

    std::vector<GridPattern> pGrid;

};