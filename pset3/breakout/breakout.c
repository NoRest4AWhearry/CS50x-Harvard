/***********************************************************
** Allen Whearry Jr.
*
** instagram.com/NoRest4AWhearry
*
** Breakout:
*
** This is a solution of the "Breakout" game from
** pset3 of CS50x Harvard.
************************************************************/

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before starting
    waitForClick();
    
    // set velocity
    double velocity = drand48() * 4.0;
    double velocity_y = 5.0;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {

        // TODO
        // Scoreboard
        updateScoreboard(window, label, points);
        
        // move ball
        move(ball, velocity, velocity_y);
        
        // linger before ball moving again
        pause(10);
        
        // check for mouse event
        GEvent mouseMove = getNextEvent(MOUSE_EVENT);

        // move paddle with cursor
        if (mouseMove != NULL)
        {
            // if the event was movement
            if (getEventType(mouseMove) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(mouseMove) - getWidth(paddle) / 2;
                double y = 550;
                setLocation(paddle, x, y);
            }
        }

        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // If hits the paddle.
            if (object == paddle)
            {
                velocity_y = -velocity_y;
            }
            
            // If hits a brickck. Remove brick, add point.
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                velocity_y = -velocity_y;
                points++;
                bricks--;                
            }
        }
        
        // If hits right wall.
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity = -velocity;
        }
        
        // If hits left wall.
        if (getX(ball) <= 0)
        {
            velocity = -velocity;
        }
        
        // If hits top wall.
        if (getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        
        // If hits bottom, subtract life and start over.
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            int x = (getWidth(window) - 25) / 2;
            int y = (getHeight(window) - 25) / 2;
            lives--;
            // move ball to start
            setLocation(ball, x, y);
            // move paddle to start
            setLocation(paddle, (getWidth(window) - 100) / 2, 550);
            waitForClick();
        }

    }
    
    // You Lose Label Message for kicks.
    if (bricks > 0)
    {
        GLabel game_over = newGLabel("YOU LOSE!");
        setFont(game_over, "SansSerif-70");
        setColor(game_over, "RED");
        add(window, game_over);
        setLocation(game_over, 15, 300);
    }
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    GRect bricks[5][10];
    char *colors[5] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
    int y = 100;
    for (int i = 0; i < ROWS; i++)
    {
        int x = 2;
        for (int j = 0; j < COLS; j++)
        {
            bricks[i][j] = newGRect(x,y,36, 10);
            setColor(bricks[i][j], colors[i]);
            setFilled(bricks[i][j], true);
            add(window, bricks[i][j]);
            x = x + 36 + 4;
        }
        y = y + 10 + 4;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    int x = (getWidth(window) - 25) / 2;
    int y = (getHeight(window) - 25) / 2;
    GOval ball = newGOval(x,y, 25, 25);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    int x = (getWidth(window) - 100) / 2;
    int y = 550;
    GRect paddle = newGRect(x,y,100, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-50");
    setColor(label, "C0C0C0");
    add(window, label);
    setLocation(label, 185, 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
