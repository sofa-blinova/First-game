#include "TXLib.h"

struct SVector
    {
    double x, y;
    };

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
SVector Difference (SVector A, SVector B);
SVector operator - (SVector A, SVector B);
SVector operator / (SVector A, double val);
SVector operator * (SVector A, double val);
double Length (SVector A);
SVector Normalize (SVector A);
//-----------------------------------------------------------------------------

int main ()
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
        txSleep ();
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
    //if (d < 0.01) continue;

    //double dx = ball2->pos.x - ball1->pos.x;
    //double dy = ball2->pos.y - ball1->pos.y;

    SVector d = ball1->pos - ball2->pos;

    double dist = Length (d);

    double F = 500/dist;

    //double ix = dx/dist;
    //double iy = dy/dist;

    SVector i = Normalize (d);

    //double Fx = ix * F;
    //double Fy = iy * F;

    SVector Fp = i * F;

    txSetColor (TX_CYAN);
    txLine  (ball1->pos.x, ball1->pos.y, ball2->pos.x, ball2->pos.y);

    txSetColor (TX_LIGHTGREEN, 3);
    txLine (ball1->pos.x, ball1->pos.y, Fp.x*25 + ball1->pos.x, Fp.y*25 + ball1->pos.y);

    txSetColor (TX_LIGHTRED, 2);
    txLine (ball1->pos.x, ball1->pos.y, i.x*25 + ball1->pos.x, i.y*25 + ball1->pos.y);

    }

SVector Difference (SVector A, SVector B)
    {
    SVector result = { B.x - A.x, B.y - A.y };

    return result;
    }

SVector operator - (SVector A, SVector B)
    {
    SVector result = { B.x - A.x, B.y - A.y };

    return result;
    }

SVector operator / (SVector A, double val)
    {
    SVector result = { A.x / val, A.y / val };

    return result;
    }

double Length (SVector A)
    {
    double leng = sqrt (A.x*A.x + A.y*A.y);

    return leng;
    }

SVector Normalize (SVector A)
    {
    double leng = sqrt (A.x*A.x + A.y*A.y);

    SVector norm = A / leng;

    return norm;
    }

SVector operator * (SVector A, double val)
    {
    SVector result = {A.x * val, A.y * val};

    return result;
    }
