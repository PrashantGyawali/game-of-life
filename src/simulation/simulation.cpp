#include "simulation.hpp"
#include<vector>
#include<utility>
#include<iostream>
#include "raylib.h"
void Simulation::Draw(Sidepanel &sPanel)
{
    grid.UpdateFocus(focusOffsetX,focusOffsetY);
    grid.Draw(sPanel, paused);
}




void Simulation::SetCell(int x, int y, int value)
{
    grid.SetCell(x, y, value);
}

long long int Simulation::GetCurrentGeneration()
{
    return currentGeneration;
}



void Simulation::Set(int width, int height)
{
    this->width=width;
    this->height=height;

    int cellWidth=(width/columns);
    int cellHeight=(height/rows);

    int cellSize=std::min(cellWidth, cellHeight);

    grid.Set(rows, columns);
    nexGrid.Set(rows, columns);

    nexGrid.height=height;
    grid.height=height;
    
    SetCellSize(cellSize);
    grid.FillRandom();
}

void Simulation::FillRandom()
{
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
    Color color = GRAY;

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
    currentGeneration++;
}



void Simulation::SetFPS(int fps) {
    ufps = fps;
    count=0;
}


void Simulation::zoomIn()
{
    //std::cout<<"CellSize: "<<grid.GetCellSize()<<" "<<grid.GetRows()*grid.GetCellSize()<<" "<<height<<std::endl;

    SetCellSize(grid.GetCellSize()+2*(grid.GetCellSize()/20+1));
}

void Simulation::zoomOut()
{
    //std::cout<<"CellSize: "<<grid.GetCellSize()<<" "<<grid.GetRows()*grid.GetCellSize()<<" "<<height<<std::endl;
    if(grid.GetColumns()*grid.GetCellSize()>width || grid.GetRows()*grid.GetCellSize()>height)
     {
        SetCellSize(grid.GetCellSize()-2*(grid.GetCellSize()/20+1));
    }
}

void Simulation::ControlPattern(int row, int column, int val, bool togglePattern)
{
    if(paused)
    {
        grid.ControlPattern(row, column, val, togglePattern);
    }
}


void Simulation::Update(Sidepanel &sPanel)
{
    int rows = grid.GetRows();
    int columns = grid.GetColumns();

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


        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {0, initialOffSetY*1.0f, width*1.0f, height*1.0f}) && paused)
        {  
            Vector2 mousePosition = GetMousePosition();
            int row = (mousePosition.y + focusOffsetY-initialOffSetY) / grid.GetCellSize();
            int column = (mousePosition.x + focusOffsetX) / grid.GetCellSize();

            if(row >= rows || column >= columns) {
                return;
            }
                int size = sPanel.pGrid[sPanel.currentPattern].first.size();

                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < sPanel.pGrid[sPanel.currentPattern].first[i].size(); j++) {
                        ControlPattern(row-(size/2)+i, column-(size/2)+j, sPanel.pGrid[sPanel.currentPattern].first[i][j], sPanel.togglePattern); 
                    }
                }
        };


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









Simulation::Simulation(int rows, int columns, int cellSize):grid(rows,columns,50),nexGrid(rows,columns,50)
    {
        this->rows=rows;
        this->columns=columns;

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