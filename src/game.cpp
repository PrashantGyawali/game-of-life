#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"
#include <string>
#include "simulation.hpp"
#include "grid.hpp"
#include <iostream>
#include "sidepanel.hpp"

class Game
{
    int screenWidth;
    int screenHeight;
    int targetFPS = 100;
    int cellSize = 20;

    // rows and columns of simulation must be in 600:1000 ratio for best results
    Simulation simulation{35, 50, cellSize};

    Sidepanel sidePanel=Sidepanel(200);

    Color BackgroundColor={35, 35, 35, 255};
    Color CellColor={255, 255, 255, 255};

    const char *colorText = "Color";
    const char *skipGenText = "#208# Skip Gen";
    const char *zoomInText ="#106#" ;
    const char *zoomOutText = "#103#";
    const char *playButton = "#131#";
    const char *ClearText = "#93#Clear";
    const char *NextText = "#134# Next";
    const char *panLeftSymbol = "#118#";
    const char *panRightText = "#119#";

    bool skipGenEditMode = false;
    int skipGenValue = 10;
    int userFPS=10;
    bool userFPSEdit = false;
    bool Button006Pressed = false;
    bool Button007Pressed = false;

    float uiYOffset;


public:
    Game(int screenW=1200, int screenH=600)
    {
        this->screenWidth = screenW;
        this->screenHeight = screenH;
        // Initialize simulation height and width
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
        simulation.Set(screenWidth-200,monitorHeight-50);
        uiYOffset=monitorHeight-48;
    }


    void Update()
    {

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BackgroundColor);
            simulation.Update(sidePanel);
            simulation.Draw();

            

            // GUI STUFF

            // yo gui stuff ko lagi chai BottomPanel class ma rakhne ani tyo class lai yaha bata call garne

            {
                GuiSetStyle(DEFAULT, TEXT_SIZE, 18);


                DrawRectangle(0, uiYOffset-2, 1000, 52, { 150, 150, 150, 255 });

                GuiSetIconScale(2); // Increase icon size
                if(GuiButton({5, uiYOffset, 48, 48 }, zoomInText)){
                    simulation.zoomIn();
                };

                if(GuiButton({53, uiYOffset, 48, 48 }, zoomOutText)){
                    simulation.zoomOut();
                };

                GuiSetIconScale(1); // Increase icon size

                GuiButton({ 101, uiYOffset, 48, 48 }, panLeftSymbol); 
                GuiButton({ 149, uiYOffset, 48, 48 }, panRightText); 

                if(GuiButton({197, uiYOffset, 85, 48 }, ClearText)) 
                {
                    simulation.paused ? simulation.Clear() : void();
                };

                if(GuiButton({282, uiYOffset, 75, 48 }, NextText))
                {
                    simulation.Next();
                };

                

                GuiSetIconScale(2); // Increase icon size
                GuiToggle({357, uiYOffset, 48, 48 }, playButton, &simulation.paused);
                GuiSetIconScale(1); // Reset icon size so that it doesn't affect other icons

                if(GuiButton({405, uiYOffset, 115, 48 }, skipGenText))
                {
                    simulation.SkipGenerations(skipGenValue);
                };
                if (GuiSpinner({520, uiYOffset, 100, 48 }, "", &skipGenValue, 0, 100, skipGenEditMode)) {
                    skipGenEditMode = !skipGenEditMode;
                };

                //boxed for user set FPS value
                if(GuiButton({620, uiYOffset, 50, 48 }, "FPS"))
                {
                    simulation.SetFPS(userFPS);
                };

                if (GuiSpinner({670, uiYOffset, 100, 48 }, "", &userFPS, 1, 20, userFPSEdit)) {
                    userFPSEdit = !userFPSEdit;
                };
                
                // If button clicked, enable the gradient mode for cool visual effects
                //Button006Pressed = GuiButton({695, uiYOffset, 50, 48 }, colorText);
                //people have eyes to see color picker, no need to place "color" text, we already have less space for buttons

                GuiColorPicker({780, uiYOffset+2, 46, 46 }, "", &BackgroundColor); 
                GuiColorPicker({830, uiYOffset+2, 46, 46 }, "", &CellColor); 

                // Arrange space for this button
                if(GuiButton({ 900, uiYOffset, 96, 48 }, "Random")) 
                {
                    // fill random
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