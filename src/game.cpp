#define RAYGUI_IMPLEMENTATION

#include "raylib.h"
#include "raygui.h"
#include <string>
#include "simulation.hpp"
#include <iostream>

class Game
{
    int screenWidth=1000;
    int screenHeight=800;
    int targetFPS = 10;
    int cellSize =20;

    // rows and columns of simulation must be in 600:1000 ratio for best results
    Simulation simulation{35, 50, cellSize};


    Color BackgroundColor={35, 35, 35, 255};
    Color CellColor={255, 255, 255, 255};


    const char *colorText = "Color";
    const char *skipGenText = "#208# Skip Gen";
    const char *zoomInText = "#107# +";
    const char *zoomOutText = "#107# -";
    const char *playButton = "#131#";
    const char *ClearText = "#93#Clear";
    const char *NextText = "#134# Next";
    const char *panLeftSymbol = "#118#";
    const char *panRightText = "#119#";
    
    bool skipGenEditMode = false;
    int skipGenValue = 10;
    bool Button006Pressed = false;
    bool Button007Pressed = false;

    float uiYOffset=700;


public:
    Game(int screenW=1000, int screenH=800)
    {
        this->screenWidth = screenW;
        this->screenHeight = screenH;
        // Initialize simulation height and width
    }

    void Init()
    {
        InitWindow(screenWidth, screenHeight, "Game of Life Editor");
        SetTargetFPS(targetFPS);
        simulation.Set(screenWidth, screenHeight-200, cellSize);

    }


    void Update()
    {

        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(BackgroundColor);
            simulation.Update();
            simulation.Draw();






            // GUI STUFF
            {
            GuiSetStyle(DEFAULT, TEXT_SIZE, 18);


            DrawRectangle(0, uiYOffset-2, 1000, 52, { 150, 150, 150, 255 });


            GuiColorPicker({ 830, uiYOffset+2, 46, 46 }, "", &BackgroundColor); 
            GuiColorPicker({ 750, uiYOffset+2, 46, 46 }, "", &CellColor);  

            if (GuiSpinner({ 576, uiYOffset, 88, 48 }, "", &skipGenValue, 0, 100, skipGenEditMode))
                skipGenEditMode = !skipGenEditMode;
            if(GuiButton({ 444, uiYOffset, 120, 48 }, skipGenText))
            {
                simulation.SkipGenerations(skipGenValue);
            };

            // If button clicked, enable the gradient mode for cool visual effects
            Button006Pressed = GuiButton({ 664, uiYOffset, 80, 48 }, colorText);

            GuiButton({ 20, uiYOffset, 48, 48 }, zoomInText);
            GuiButton({ 68, uiYOffset, 48, 48 }, zoomOutText);

            GuiSetIconScale(2); // Increase icon size
            GuiToggle({ 372, uiYOffset, 72, 48 }, playButton, &simulation.paused);
            GuiSetIconScale(1); // Reset icon size so that it doesn't affect other icons

            // Arrange space for this button
            if(GuiButton({ 900, uiYOffset, 96, 48 }, "Randomize")) 
            {
                // fill random
            };

            if(GuiButton({ 212, uiYOffset, 96, 48 }, ClearText)) 
            {
                simulation.paused ? simulation.Clear() : void();
            };

            if(GuiButton({ 308, uiYOffset, 64, 48 }, NextText))
            {
                simulation.Next();
            };

            GuiButton({ 116, uiYOffset, 48, 48 }, panLeftSymbol); 
            GuiButton({ 164, uiYOffset, 48, 48 }, panRightText); 


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