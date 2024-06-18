#include "toppanel.hpp"
#include "raylib.h"
#include "raygui.h"
#include <iostream>

TopPanel::TopPanel()
{
    this->width = 0;
    this->height = 0;
}

TopPanel::TopPanel(int w, int h)
{
width=w;
height=h;
}

void TopPanel::Update()
{
    DrawRectangle(0, 0, width,height-5, GRAY);
    DrawText(TextFormat("Generation: %lld", 0), 10, 10, 20, BLACK);
    DrawText("Conway's Game of Life", 200, 10, 20, BLACK);
}