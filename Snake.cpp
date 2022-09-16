#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

//Global variables
bool gameOver;
const int width = 40; //Box skeleton
const int heigth = 20;

int x,y, fruitX, fruitY, score;
//Coordinates of head snake , fruit
//Tail
int tailX[100], tailY[100];
int nTail; // specìy the length ò xx

enum eDirection {
    STOP = 0,
    LEFT, RIGHT, UP, DOWN 
};
eDirection dir;

void Setup()
{
    bool gameOver = false;
    dir = STOP;
    //Location of Snake
    x = width/2;
    y = heigth/2;
    //Location of Fruit
    fruitX = rand() % width;
    fruitY = rand() % heigth;
    score = 0;
}

void clearScreen ()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize = NULL;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void Draw()
{
     //Display top border of map
     cout<<"SCORE: "<<score<<endl;
     for (int i = 0; i < width; i++)
          cout<<"#";
     cout<<endl;
     
     for (int i = 0; i < heigth; i++)
     {
        for (int j = 0; j < width; j++)
        {
            if(j==0 || j == width -1)
              cout<<"#";
            else if(i == y && j == x)
              cout<<"O";
            else if(i == fruitY && j == fruitX)
              cout<<"@";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                
                 if(!print)
                    cout<<" ";
            }
             
        }
        cout<<endl;
     }
     

     //Display bottom wall
     for (int i = 0; i < width ; i++)
          cout<<"#";
     cout<<endl;

}

void Input()
{   //Control the snake
    //function gets a character from console
    if(kbhit()) //if nothing is pressed, return 0
    {
        switch (getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    //Track the tail
    int prevX = tailX[0];
    int prevY = tailY[0]; 
    int prevX2, prevY2;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
    

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    } 
    
    //Hit the wall
    // if(x > width || x <  0 || y > heigth || y < 0)
    // {
    //     gameOver = true;
    // }
    if (x >= width)
        x = 0;
    else if(x < 0)
        x = width -1;
    if(y  >= heigth)
        y = 0;
    else if(y<0)
        y = heigth -1;

    //Hit the tail
    for(int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
           gameOver = true;
    }

    //Accummulator
    //Increase the tail
    if(x == fruitX && y == fruitY)
    {
        score += 1;
        nTail ++;
        fruitX = rand() % width;
        fruitY = rand() % heigth;
    }

}

int main ()
{
    Setup();
    while (!gameOver)
    {
        clearScreen();
        Draw();
        Input();
        Logic();
        Sleep(10);
    }

    return 0;
}