#include "TXLib.h"

void MoveBall ();
//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 650);

    MoveBall ();
    }
//-----------------------------------------------------------------------------

void MoveBall ()
    {
    int x = 100, y = 500;
    int vx = 3, vy = 2;
    int dt = 1;

    while (true)
        {
        txSetColor (TX_BLACK);
        txCircle (x, y, 15);

        x = x + dt*vx;
        y = y + dt*vy;

        if (x > 1000)
            {
            vx = -vx;
            x = 1000;
            }

        if (x < 0)
            {
            vx = -vx;
            x = 0;
            }

        if (y > 650)
            {
            vy = -vy;
            y = 650;
            }

        if (y < 0)
            {
            vy = -vy;
            y = 0;
            }

        if (GetAsyncKeyState (VK_RIGHT))
            {
            vx = vx + 2;
            }

        if (GetAsyncKeyState (VK_SPACE))
            vx = 0;

        txSleep (10);
        }
    }
