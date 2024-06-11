#pragma once


class Sidepanel{

    private:
    int selection=0;
    int width,height;
    int currentPattern = 0;


    public:
    int offsetX=1000, offsetY=0;

    Sidepanel(int width);
    ~Sidepanel();

    // Draw the sidepanel
    void Draw();
    void SetOffset(int x, int y);
    void SetHeight();

    // To change the pattern selection
    void SetSelection(int change);

};