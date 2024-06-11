#pragma once

#include "grid.hpp"

class Simulation{
    private:
    int columns=20,rows=20;
    Grid grid,nexGrid;
    
    int focusOffsetX=0,focusOffsetY=0;
    int width,height;

    int  overPopulationCondition=3;
    int  underPopulationCondition=3;

    void SetOverPopulationCondition  (int condition);
    void SetUnderPopulationCondition (int condition);
    void NextGeneration();

    public:
    Simulation(int rows, int columns, int cellSize=20);
    bool paused=false;
    int count=0;
    int ufps=10;

    ~Simulation(){

    };

    void Draw();
    void SetCell(int row, int column, int value);
    void Clear();

    // WIdth and height preferably constant and only cellSize changed
    void Set(int width, int height);
    void SetCellSize(int cellSize); 


    int  CountLiveNeighbors(int row, int col);


    // updating the simulation
    void Update();
    void SetFPS(int fps);
    void Next();
    void SkipGenerations(int generations);

    // changing rules of simulation
    void SetRules(int overPopulationCondition, int underPopulationCondition);    
    
    int SetFocus(int x, int y); 

    void TogglePause();

    void SetPaused(bool paused);





};
