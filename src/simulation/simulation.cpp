#include "simulation.hpp"
#include<vector>
#include<utility>
#include<iostream>
#include "raylib.h"
void Simulation::Draw()
{
    grid.UpdateFocus(focusOffsetX,focusOffsetY);
    grid.Draw();
}




void Simulation::SetCell(int x, int y, int value)
{
    grid.SetCell(x, y, value);
}



void Simulation::Set(int width, int height)
{
    this->width=width;
    this->height=height;

    int cellWidth=(width/columns);
    int cellHeight=(height/rows);

    int cellSize=std::min(cellWidth, cellHeight);
    std::cout<<columns<<" hi "<<rows<<std::endl;

    grid.Set(rows, columns);
    
    SetCellSize(cellSize);
    grid.FillRandom();
}



int Simulation::CountLiveNeighbors(int row, int col)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> offsets = {
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };
    int rows = grid.GetRows();
    int columns = grid.GetColumns();
    for(const auto& offset: offsets)
    {
        int testRow = (row + offset.first+ rows)%rows;
        int testCol = (col + offset.second + columns)%columns;

        liveNeighbors += grid.GetCell(testRow, testCol);
    }

    return liveNeighbors;
}


void Simulation::NextGeneration()
{
    int rows = grid.GetRows();
    int columns = grid.GetColumns();
    for(int r=0;r<rows;r++)
    {
        for(int c=0;c<columns;c++)
        {
            int liveNeighbors = CountLiveNeighbors(r, c);
            int cell = grid.GetCell(r, c);
            if(cell)
            {
                if(liveNeighbors<2 || liveNeighbors>3)
                {
                    nexGrid.SetCell(r, c, 0);
                }
                else{
                    nexGrid.SetCell(r, c, 1);
                }

            }
            else
            {
                if(liveNeighbors==3)
                {
                    nexGrid.SetCell(r, c, 1);
                }
                else{
                    nexGrid.SetCell(r, c, 0);
                }
            }
        }
    }
    grid=nexGrid;
}



void Simulation::SetFPS(int fps) {
    ufps = fps;
    count=0;
}






void Simulation::Update()
{
    int rows = grid.GetRows();
    int columns = grid.GetColumns();
    
        if(CheckCollisionPointRec(GetMousePosition(), {0, 0,float(width), float(height)}))
        {
            if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                SetCellSize(grid.GetCellSize()+2*(grid.GetCellSize()/20+1));
            }
            if(IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
            {
                std::cout<<"CellSize: "<<grid.GetCellSize()<<" "<<grid.GetRows()*grid.GetCellSize()<<" "<<height<<std::endl;
                if(grid.GetColumns()*grid.GetCellSize()>width || grid.GetRows()*grid.GetCellSize()>height)
                {
                    SetCellSize(grid.GetCellSize()-2*(grid.GetCellSize()/20+1));
                }
            }
        }

        if(IsKeyReleased(KEY_LEFT))
        {
            if(focusOffsetX>0)
            {
            focusOffsetX-=(grid.GetColumns()/10)* grid.GetCellSize();
            }
            else{
                focusOffsetX=0;
            }
        }
        if(IsKeyReleased(KEY_RIGHT))
        {
            if(focusOffsetX<(grid.GetColumns()*grid.GetCellSize()-1000))
            {
            focusOffsetX+=(grid.GetColumns()/10)* grid.GetCellSize();
            }
            else{
                focusOffsetX=(grid.GetColumns()*grid.GetCellSize()-1000);
            }
        }
        if(IsKeyReleased(KEY_UP))
        {
            if(focusOffsetY>=0.1*grid.GetRows()*grid.GetCellSize())
            {
            focusOffsetY-=(grid.GetRows()/10)* grid.GetCellSize();
            }
            else{
                focusOffsetY=0;
            }
        }
        if(IsKeyReleased(KEY_DOWN))
        {
            if(focusOffsetY+800<grid.GetRows()*grid.GetCellSize())
            {
            focusOffsetY+=(grid.GetRows()/10)* grid.GetCellSize();
            }
            else{
                focusOffsetY=grid.GetRows()*grid.GetCellSize()-800;
            }
        }

        if(IsKeyPressed(KEY_SPACE))
        {
            TogglePause();
        }



        if(paused)
        {
            return;
        }
        
        count++;
        if(count >= 60/ufps) {
            NextGeneration();
            count=0;
        }       
}












void Simulation::Next()
{
    if(!paused)
    {
        return;
    }
    NextGeneration();
}











// skipping generations
void Simulation::SkipGenerations(int generations)
{
    for(int i=0;i<generations;i++)
    {
        NextGeneration();
    }
}








void Simulation::SetOverPopulationCondition(int condition)
{
    overPopulationCondition = condition;
}
void Simulation::SetUnderPopulationCondition(int condition)
{
    underPopulationCondition = condition;
}

void Simulation::SetRules(int op, int up)
{
    if(up>-1 && up<9)
    {
        if(up<op)
        {
            SetUnderPopulationCondition(underPopulationCondition);
        }
    }
    if(op>-1 && op<9)
    {
        if(op>up)
        {
            SetOverPopulationCondition(overPopulationCondition);
        }
    }
}









Simulation::Simulation(int rows, int columns, int cellSize)
    {
        this->rows=rows;
        this->columns=columns;


        grid.Set(rows,columns);
        nexGrid.Set(rows,columns);

        grid.SetCellSize(cellSize);
        nexGrid.SetCellSize(cellSize);
    };










int Simulation::SetFocus(int x, int y)
{
    int cellSize=grid.GetCellSize();
    if(rows*cellSize<height || columns*cellSize<width)
    {
        return -1;
    }
    focusOffsetX=x;
    focusOffsetY=y;
    return 0;
}





void Simulation::SetCellSize(int cSize)
{
    grid.SetCellSize(cSize);
    nexGrid.SetCellSize(cSize);
}




void Simulation::TogglePause()
{
    paused=!paused;
}



void Simulation::SetPaused(bool pause)
{
    paused=pause;
}

void Simulation::Clear()
{
    grid.Clear();
    nexGrid.Clear();
}