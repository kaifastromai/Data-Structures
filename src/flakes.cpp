//Bennett Bartel
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <Windows.h>
#undef MOUSE_MOVED
#include "C:\Users\cepha\Downloads\windows\windows\curses.h"
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;
//Type Flake, used to create a flake
struct Flake
{
    Flake()
    {
    }

    Flake(int c, int r)
    {
        col = c;
        row = r;
        foreground = (rand() % 2) == 0;
    }

    void Render()
    {
        //Creates a snowflake in the background with the shape of a .
        mvaddch(row, col, '.');
    }
    //Update frame
    void Update()
    {
        col += FBM();
        row++;
        if (col < 0 || col >= COLS || row >= LINES)
        {
            col = rand() % COLS;
            row = 0;
        }
    }
    bool IsForeGround()
    {
        return foreground;
    }
    //how far the snowflakes move left and right
private:
    int FBM() //how far the snowflakes move left and right
    {
        int pos;
        float dist = rand() % 100;
        if (dist < 80.0f)
        {
            if (rand() % 2 == 0)
            {
                pos = 1;
            }
            else
            {
                pos = -1;
            }
        }
        else
        {
            pos = 0;
        }
        return pos;
    }
    int col;
    int row;
    bool foreground;
};

struct Storm //the whole storm
{
    Storm(int n)
    {
        flakes.resize(n);
        for (auto &f : flakes)
        {
            f = Flake(rand() % COLS, -(rand() % LINES));
        }
    };

    void Render()
    {
        for (auto &f : flakes)
            f.Render();
    }
    void Update()
    {
        for (auto &f : flakes)
            f.Update();
    }

private:
    vector<Flake> flakes;
};

int main(int argc, char *argv[])
{

    srand((unsigned int)time(nullptr));
    initscr();
    curs_set(0);
    Storm s(COLS * 2);

    while (true)
    {
        erase();
        s.Update();
        s.Render();
        box(stdscr, 0, 0);
        refresh();
        this_thread::sleep_for(chrono::milliseconds(50)); //speed
    }
    curs_set(1);
    endwin();
    {
        char c;
        cout << "Hit any key to exit:";
        cin.get(c);
    }
    return 0;
}
