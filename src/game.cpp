#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"
#include <string>
#include "simulation.hpp"
#include "grid.hpp"
#include <iostream>
#include "sidepanel.hpp"
#include "toppanel.hpp"

class Game
{
    int screenWidth;
    int screenHeight;
    int targetFPS = 100;
    int cellSize = 20;

    // rows and columns of simulation must be in 600:1000 ratio for best results
    Simulation simulation{35, 50, cellSize};

    Sidepanel sidePanel=Sidepanel(200);
    TopPanel topPanel;

    Color BackgroundColor={35, 35, 35, 255};
    Color CellColor={255, 255, 255, 255};


    const char *colorText = "Colors";
    const char *skipGenText = "#208# Skip Gen";
    const char *zoomInText ="#106#" ;
    const char *zoomOutText = "#103#";
    const char *playButton = "#131#";
    const char *ClearText = "#93#Clear";
    const char *NextText = "#134# Next";
    
    bool skipGenEditMode = false;
    int skipGenValue = 10;
    int userFPS=10;
    bool userFPSEdit = false;
    bool rainbowMode = false;
    float uiYOffset;


public:
    Game(int screenW=1200, int screenH=600)
    {
        this->screenWidth = screenW;
        this->screenHeight = screenH;
    }

    void Init()
    {



        // Temporary window that will get the monitor height and width and close itself
        // yeslai chuttai class banauna paryo pachi, ani mainmenu dekhaunu bhanda aghi run garnu paryo
        InitWindow(100, 50, "Loading...");
        ClearBackground(RAYWHITE);
        DrawText("Loading...", 10, 10, 20, BLACK);
        EndDrawing();
        SetTargetFPS(1);
        int monitorHeight = GetMonitorHeight(GetCurrentMonitor())*85/100;
        WaitTime(1);
        CloseWindow();




        InitWindow(screenWidth, monitorHeight, "Game of Life");
        SetTargetFPS(targetFPS);
        SetWindowState(FLAG_WINDOW_ALWAYS_RUN);


        // 200 bhaneko sidepanel ko width ho
        // 50 bhaneko bottom panel ko height ho
        simulation.Set(screenWidth-200,monitorHeight-100);
        topPanel=TopPanel{screenWidth-200,50};
        uiYOffset=monitorHeight-48;
    }


    void Update()
    {

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BackgroundColor);
            simulation.Update(sidePanel);
            simulation.Draw(sidePanel);


            topPanel.Update();

            

            // GUI STUFF

            // yo gui stuff ko lagi chai BottomPanel class ma rakhne ani tyo class lai yaha bata call garne

            {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);


                DrawRectangle(0, uiYOffset-2, 1000, 52, { 150, 150, 150, 255 });




                GuiSetIconScale(2);
                if(GuiButton({5, uiYOffset, 48, 48 }, zoomInText)){
                    simulation.zoomIn();
                };

                if(GuiButton({53, uiYOffset, 48, 48 }, zoomOutText)){
                    simulation.zoomOut();
                };
                GuiSetIconScale(1);





                if(GuiButton({101, uiYOffset, 85, 48 }, ClearText)) 
                {
                    simulation.paused ? simulation.Clear() : void();
                };
                //boxed for user set FPS value
                if(GuiButton({186, uiYOffset, 50, 48 }, "FPS"))
                {
                    simulation.SetFPS(userFPS);
                };

                if (GuiSpinner({236, uiYOffset, 100, 48 }, "", &userFPS, 1, 20, userFPSEdit)) {
                    userFPSEdit = !userFPSEdit;
                };

                if(GuiButton({336, uiYOffset, 75, 48 }, NextText))
                {
                    simulation.Next();
                };

                

                GuiSetIconScale(2);
                GuiToggle({411, uiYOffset, 48, 48 }, playButton, &simulation.paused);
                GuiSetIconScale(1);



                if(GuiButton({459, uiYOffset, 115, 48 }, skipGenText))
                {
                    simulation.SkipGenerations(skipGenValue);
                };
                if (GuiSpinner({574, uiYOffset, 100, 48 }, "", &skipGenValue, 0, 100, skipGenEditMode)) {
                    skipGenEditMode = !skipGenEditMode;
                };





                
                if(GuiButton({676, uiYOffset, 70, 48 }, colorText)){
                    rainbowMode = !rainbowMode;
                };

                GuiColorPicker({750, uiYOffset+2, 46, 46 }, "", &BackgroundColor); 
                GuiColorPicker({830, uiYOffset+2, 46, 46 }, "", &CellColor); 




                if(GuiButton({ 900, uiYOffset, 96, 48 }, "Random")&& simulation.paused) 
                {
                    simulation.FillRandom();
                }; 

                sidePanel.SetHeight();
                sidePanel.Draw();


            }
            EndDrawing();
        }
        close();
    }

    
    void close()
    {
        CloseWindow();
    }
};




int main(void)
{
    Game game;
    game.Init();
    game.Update();


    return 0;
}