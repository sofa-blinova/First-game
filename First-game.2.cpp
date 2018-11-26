#include "\\Mac\Home\Desktop\TX\TXLib.h"
#include "Vector.h"

const int NBalls = 5;

struct SColors
    {
    COLORREF first, second, third, fourth, fifth;
    };

struct SKeys
    {
    int KeySpace, KeyRight, KeyLeft, KeyUp, KeyDown;
    };

struct SBall
    {
    SVector p;
    SVector v;

    double m;

    int exist;

    COLORREF color;
    SColors colors;

    SKeys keys;
    };

void MoveBall ();
void Colors   (SBall* ball);
void Physics (SBall* ball, int dt);
void Control (SBall* ball);
void DrawBall (int x, int y, double size, COLORREF ballcolor);
/*void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF ballColor);
*/
void DrawBallHelper (SBall ball, int t);
void FillBallArray      (SBall balls [], int nBalls);
void AddColorsForBalls  (SBall balls [], int nBalls);
void ProcessBalls       (SBall balls [], int nBalls, int t, int dt);
void DrawBallsFromArray (SBall balls [], int nBalls, int t);
void AddPhysicsForBalls (SBall balls [], int nBalls, int dt);
void AddControlForBalls (SBall balls [], int nBalls);
void BallAndMouseInteraction (SBall* ball);
void BallsAndMouseInteraction (SBall balls [], int nBalls);
void InteractionOfBalls (SBall balls [], int nBalls);
//-----------------------------------------------------------------------------

int main ()
    {
    txCreateWindow (1000, 650);

    txSetFillColor (RGB (26, 140, 255));
    txRectangle (0, 0, 1000, 650);

    MoveBall ();
    }
//-----------------------------------------------------------------------------

void MoveBall ()
    {
    SColors colors1 = {RGB (  2, 96,   2), RGB (100, 142,  62), RGB (  0, 187,   0), RGB ( 44, 244,  28), RGB (189, 255, 189)};
    SColors colors2 = {RGB (  4, 22, 187), RGB (100, 128, 255), RGB ( 90, 154, 241), RGB ( 17, 255, 255), RGB (  1, 186, 158)};
    SColors colors3 = {RGB (128,  0, 255), RGB (128,   0, 128), RGB (253,   2, 234), RGB (254, 141, 242), RGB (255,   0, 128)};
    SColors colors4 = {RGB (255,  0,   0), RGB (255, 140, 140), RGB (255, 128,   0), RGB (243, 191,  12), RGB (255, 255,   0)};
    SColors colors5 = {RGB (234,  0,   1), RGB (212, 440, 140), RGB (255, 198,  57), RGB (543, 391, 642), RGB (265, 585,  37)};

    SBall balls [NBalls] = {{{ 500, 325}, { 0,  0}, 50  , 1, RGB (255, 0, 0), colors1, {VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN}},
                            {{   0, 325}, { 4,  2.6}, 9   , 1, RGB (255, 0, 0), colors2, {'1',      'C',      'Z',     'S',   'X'    }},
                            {{1000, 325}, {-4, -2.6}, 9   , 1, RGB (255, 0, 0), colors3, {'2',      'N',      'V',     'H',   'B'    }},
                            {{ 500,   0}, {-4,  2.6}, 9   , 1, RGB (255, 0, 0), colors4, {'3',      'G',      'D',     'R',   'F'    }},
                            {{ 500, 650}, { 4, -2.6}, 9   , 1, RGB (255, 0, 0), colors5, {'4',      'K',      'H',     'U',   'J'    }}};

    FillBallArray (balls, NBalls);

    int t = 0;
    int dt = 1;

    //if (ball.exist == 0) return;

    txBegin ();

    while (true)
        {
        txSetFillColor (RGB (26, 140, 255));
        txClear ();

        AddColorsForBalls (balls, NBalls);

        ProcessBalls (balls, NBalls, t, dt);

        //InteractionOfBalls (balls, NBalls);

        //BallAndMouseInteraction (&balls [0]);

        //BallsAndMouseInteraction (balls, NBalls);

        txGetFPS ();

        t++;
        txSleep (0);
        }

    txEnd ();
    }

void Physics (SBall* ball, int dt)
    {
    if (ball->exist == 1)
        {
        //if (ball->m > 0.5) ball->m = ball->m - 0.005;
        //ball->v = ball->v * 0.9;
        ball->p = ball->p + dt * ball->v;

        if (ball->p.x > 1000)
            {
            ball->v.x = - ball->v.x;
            ball->p.x = 1000;
            }

        if (ball->p.x < 0)
            {
            ball->v.x = - ball->v.x;
            ball->p.x = 0;
            }

        if (ball->p.y > 650)
            {
            ball->v.y = - ball->v.y;
            ball->p.y = 650;
            }

        if (ball->p.y < 0)
            {
            ball->v.y = - ball->v.y;
            ball->p.y = 0;
            }
        }
    }

void Control (SBall* ball)
    {
    if (ball->exist == 1)
        {
        if (GetAsyncKeyState (ball->keys.KeySpace))
            {
            ball->v.x = 0;
            ball->v.y = 0;
            }

        if (GetAsyncKeyState (ball->keys.KeyRight))
            ball->v.x = ball->v.x + 1;

        if (GetAsyncKeyState (ball->keys.KeyLeft))
            ball->v.x = ball->v.x - 1;

        if (GetAsyncKeyState (ball->keys.KeyUp))
            ball->v.y = ball->v.y - 1;

        if (GetAsyncKeyState (ball->keys.KeyDown))
            ball->v.y = ball->v.y + 1;
        }
    }

void Colors (SBall* ball)
    {
    if (ball->exist == 1)
        {
        if ( -1 < ball->p.x && ball->p.x <= 200)
            {
            ball->color = ball->colors.first;
            //printf ("A");
            }

        if (200 < ball->p.x && ball->p.x <= 400)
            {
            ball->color = ball->colors.second;
            //printf ("B");
            }

        if (400 < ball->p.x && ball->p.x <= 600)
            {
            ball->color = ball->colors.third;
            //printf ("C");
            }

        if (600 < ball->p.x && ball->p.x <= 800)
            {
            ball->color = ball->colors.fourth;
            //printf ("D");
            }

        if (800 < ball->p.x && ball->p.x <= 1000)
            {
            ball->color = ball->colors.fifth;
            //printf ("E");
            }
        }
    }

void DrawBall (int x, int y, double size, COLORREF ballcolor)
    {
    txSetColor (TX_BLACK);
    txSetFillColor (ballcolor);
    txCircle (x, y, size);
    }

/*void DrawBird (int x, int y,
               double sizeX, double sizeY,
               double leg, double step, double wing,
               double tail, double wind,
               COLORREF ballColor)
    {

    txSetColor (TX_BLACK);
    txSetFillColor (ballColor);
    txEllipse (x- 9*sizeX, y- 5*sizeY, x+9*sizeX, y+5*sizeY);                                  // 782; 366
    txEllipse (x-16*sizeX, y-12*sizeY, x-5*sizeX, y-2*sizeY);
    txSetFillColor (RGB (255, 255, 255));
    txEllipse (x-14*sizeX, y-9*sizeY, x-11*sizeX, y-6*sizeY);
    txLine (x-1*sizeX, y+4*sizeY, x-(1+leg)*sizeX, y+(9-step)*sizeY);
    txLine (x+2*sizeX, y+4*sizeY, x+(2+leg)*sizeX, y+(9+step)*sizeY);
    txLine (x, y-2*sizeY, x, y+(3-wing)*sizeY);
    txLine (x-6*sizeX, y, x, y+(3-wing)*sizeY);
    txLine (x+9*sizeX, y, x+(16+tail)*sizeX, y-(7+wind)*sizeY);
    txLine (x+9*sizeX, y, x+(16+tail)*sizeX, y+(7-wind)*sizeY);
    txLine (x+9*sizeX, y, x+(19+tail)*sizeX, y-(3+wind)*sizeY);
    txLine (x+9*sizeX, y, x+(19+tail)*sizeX, y+(5-wind)*sizeY);
    txSetColor (RGB (255, 255, 0));
    txLine (x-17*sizeX, y-8*sizeY, x-18*sizeX, y-5*sizeY);
    txLine (x-19*sizeX, y-5*sizeY, x-15*sizeX, y-5*sizeY);
    }
*/

void DrawBallHelper (SBall ball, int t)
    {
    if (ball.exist == 1) DrawBall (ball.p.x, ball.p.y, ball.m, ball.color);
    }

void FillBallArray (SBall balls [], int nBalls)
    {
    int i = 4;
    while (i < nBalls)
        {
        SVector rp = {rand () % 500, rand () % 400};
        balls[i].p = rp;

        //balls[i].v.x   = rand () %   5 + 1;
        //balls[i].v.y   = rand () %   5 + 1;
        SVector rv = {rand () % 5 + 1, rand () % 5 + 1};
        balls[i].v = rv;

        balls[i].m = rand () %   13 + 1;
        balls[i].exist = 1;
        balls[i].color = RGB (rand () % 255, rand () % 255, rand () % 255);
        balls[i].colors.first  = RGB (rand () % 255, rand () % 255, rand () % 255);
        balls[i].colors.second = RGB (rand () % 255, rand () % 255, rand () % 255);
        balls[i].colors.third  = RGB (rand () % 255, rand () % 255, rand () % 255);
        balls[i].colors.fourth = RGB (rand () % 255, rand () % 255, rand () % 255);
        balls[i].colors.fifth  = RGB (rand () % 255, rand () % 255, rand () % 255);

        i++;
        }
    }

void AddColorsForBalls (SBall balls [], int nBalls)
    {
    int i = 0;
    while (i < nBalls)
        {
        Colors (&balls [i]);
        i++;
        }
    }

void ProcessBalls (SBall balls [], int nBalls, int t, int dt)
    {
    DrawBallsFromArray       (balls, nBalls, t);
    //BallsAndMouseInteraction (balls, nBalls);
    AddPhysicsForBalls       (balls, nBalls, dt);
    AddControlForBalls       (balls, nBalls);
    }

void DrawBallsFromArray (SBall balls [], int nBalls, int t)
    {
    for (int i = 0; i < nBalls; i++) DrawBallHelper (balls [i], t);
    }

void AddPhysicsForBalls(SBall balls [], int nBalls, int dt)
    {
    for (int i = 0; i < nBalls; i++) Physics (&balls [i], dt);
    }

void AddControlForBalls(SBall balls [], int nBalls)
    {
    for (int i = 0; i < nBalls; i++) Control (&balls [i]);
    }

void BallAndMouseInteraction (SBall* ball)
    {
    if (ball->exist == 1)
        {
        SVector M = txMousePos ();

        SVector d = M - ball->p;

        double dist = Length (d);

        if (dist < 0.01) return;

        double F = (350/dist);
        SVector Fp =  !d * F;

        SVector a = Fp/ball->m;

        ball->v = ball->v + a;

        if (dist < 5) ball->m = ball->m + 1;
        }
    }

void BallsAndMouseInteraction (SBall balls [], int nBalls)
    {
    for (int i = 0; i < nBalls; i++) BallAndMouseInteraction (&balls [i]);
    }

double Distance (const SBall* ball1, const SBall* ball2)
    {
    SVector d = ball1->p - ball2->p;

    double D = Length (d);
    return D;
    }

void InteractionOfBalls (SBall balls [], int nBalls)
    {
    for (int i = 0; i < nBalls; i++)                                    //   0 1 2 3    i++
        {                                                               // 0 -
        //printf ("DrawballHelper (balls [%d], %d): \n", i, i);         // 1 - -        i2 = i + 1; i2++
                                                                        // 2 - - -
        for (int i2 = i + 1; i2 < nBalls; i2++)                         // 3 - - - -
            {
            SBall* ball1 = &balls [i];
            SBall* ball2 = &balls [i2];

            if (ball1->exist == 1 && ball2->exist == 1)
                {
                SVector D = ball1->p - ball2->p;
                double dist = Length (D);

                double F = (40/dist);
                SVector f1 = !D * F;
                SVector f2 = - (!D * F);

                SVector a1 = f1/ball1->m;
                SVector a2 = f2/ball2->m;

                ball1->v = ball1->v + a1;
                ball2->v = ball2->v + a2;

                if (dist < (ball1->m + ball2->m)/2)
                    {
                    ball1->exist = 0;

                    ball2->m = ball1->m + ball2->m;
                    SVector p1 = ball2->v * ball2->m;
                    SVector p2 = ball2->v * ball2->m;
                    SVector p = p1 + p2;
                    ball2->v = p/ball2->m;
                    }
                }
            }
        }
    }
