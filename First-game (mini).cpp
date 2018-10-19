#include "TXLib.h"
#include "Vector.h"

struct SBall
    {
    SVector pos;
    double size;
    SVector v;
    COLORREF color;
    };

void MoveBall ();
void DrawBall (SBall* ball);
void Physics (SBall* ball, int dt);
void BallAndMouseInteraction (SBall* ball);
double Distance (const SBall* ball1, const SBall* ball2);
void InteractionOfBalls (SBall* ball1, SBall* ball2);

//-----------------------------------------------------------------------------
int main ()
    {
    txCreateWindow (1000, 650);

    txBegin ();

    txSetFillColor (RGB (26, 140, 255));
    txRectangle (0, 0, 1000, 650);

    //POINT mouse = txMousePos ();

    //SVector A = txMousePos ();

    SVector B = {150, 300};

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        txSetFillColor (TX_BLACK);
        txCircle (A.x, A.y, 20);
        txCircle (B.x, B.y, 15);

        B = txMousePos ();

        txSleep (50);

        SVector d = A - B;
        double dist = Length (d);
        if (dist < 0.01) return;
        double F = 500/dist;
        SVector Fp = !d * F;

        DrawVector (A, B, TX_CYAN);
        DrawVector (A, A + Fp * 25, TX_LIGHTGREEN, 3);
        DrawVector (A, A + !d * 25, TX_LIGHTRED, 2);
        }

    }

int mmmain ()
    {
    txCreateWindow (1000, 650);

    txBegin ();

    txSetFillColor (RGB (26, 140, 255));
    txRectangle (0, 0, 1000, 650);

    SVector A = {200, 600};
    SVector B = {900, 100};

    bool followmouse = true;

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        txSetColor (TX_BLACK);
        txCircle (A.x, A.y, 5);
        txCircle (B.x, B.y, 5);

        DrawVector (A, B, (followmouse ? TX_WHITE : TX_BLACK), (followmouse ? 2 : 7));

        if (GetAsyncKeyState (VK_SPACE))
            followmouse = ! followmouse;

        if (GetAsyncKeyState (MK_LBUTTON) || followmouse == false)
            A = txMousePos ();

        if (GetAsyncKeyState (MK_RBUTTON) || followmouse)
            B = txMousePos ();

        txSleep (50);
        }
    }

int mmain ()
    {
    txCreateWindow (1000, 650);

    txSetFillColor (RGB (26, 140, 255));
    txRectangle (0, 0, 1000, 650);

    MoveBall();
    }

//-----------------------------------------------------------------------------

void MoveBall ()
    {
    SBall ball1 = {{100, 100}, 15, {1, 2}, TX_BLACK};
    SBall ball2 = {{700, 600}, 10, {0, 0}, TX_WHITE};

    int t = 0;
    int dt = 1;

    txBegin ();

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        DrawBall (&ball1);
        DrawBall (&ball2);

        Physics (&ball1, dt);

        BallAndMouseInteraction (&ball2);

        InteractionOfBalls (&ball1, &ball2);

        t++;
        txSleep (40);
        }

    txEnd ();
    }

void DrawBall (SBall* ball)
    {
    txSetColor (ball->color);
    txSetFillColor (ball->color);
    txCircle (ball->pos.x, ball->pos.y, ball->size);
    }

void Physics (SBall* ball, int dt)
    {
    ball->pos.x = ball->pos.x + dt * ball->v.x;

    ball->pos.y = ball->pos.y + dt * ball->v.y;

    if (ball->pos.x > 1000)
        {
        ball->v.x = - ball->v.x;
        ball->pos.x = 1000;
        }

    if (ball->pos.x < 0)
        {
        ball->v.x = - ball->v.x;
        ball->pos.x = 0;
        }

    if (ball->pos.y > 650)
        {
        ball->v.y = - ball->v.y;
        ball->pos.y = 650;
        }

    if (ball->pos.y < 0)
        {
        ball->v.y = - ball->v.y;
        ball->pos.y = 0;
        }
    }

void BallAndMouseInteraction (SBall* ball)
    {
    POINT mouse = txMousePos ();

    double Fx = mouse.x - ball->pos.x;
    double Fy = mouse.y - ball->pos.y;

    double m = 10;

    double ax = Fx/m;
    double ay = Fy/m;

    ball->pos.x = ball->pos.x + ax;
    ball->pos.y = ball->pos.y + ay;
    }

double Distance (const SBall* ball1, const SBall* ball2)
    {
    double dx = ball1->pos.x - ball2->pos.x;
    double dy = ball1->pos.y - ball2->pos.y;
    double d = sqrt (dx*dx + dy*dy);
    return d;
    }

void InteractionOfBalls (SBall* ball1, SBall* ball2)
    {
    SVector d = ball1->pos - ball2->pos;

    double dist = Length (d);

    if (dist < 0.01) return;

    double F = 500/dist;

    SVector Fp = !d * F;

    //txSetColor (TX_CYAN);
    //txLine (ball1->pos.x, ball1->pos.y, ball2->pos.x, ball2->pos.y);

    DrawVector (ball1->pos, ball2->pos, TX_CYAN);

    //txSetColor (TX_LIGHTGREEN, 3);
    //txLine (ball1->pos.x, ball1->pos.y, Fp.x*25 + ball1->pos.x, Fp.y*25 + ball1->pos.y);

    DrawVector (ball1->pos, ball1->pos + Fp * 25, TX_LIGHTGREEN, 3);

    //txSetColor (TX_LIGHTRED, 2);
    //txLine (ball1->pos.x, ball1->pos.y, !d.x*25 + ball1->pos.x, !d.y*25 + ball1->pos.y);

    DrawVector (ball1->pos, ball1->pos + !d * 25, TX_LIGHTRED, 2);

    }
