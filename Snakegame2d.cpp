#include<iostream>
#include<conio.h>           // for getch() and system("cls")
#include<Windows.h>         // for sleep() function
using namespace std;

enum Direction{STOP = 0, LEFT, RIGHT, UP, DOWN};    //possible directions of snake
Direction dir;
bool gameOver;                                      // indicates state of the game,if true that means game is over
const int height = 20;                              // for height of border of game
const int width = 20;                               // for width of border of game
int headX, headY;                                   // coedinates for indicating head of the snake
int  fruitX, fruitY;                                // coedinates for indicating the fruit 
int score;                                          // indicates current score                         
int tailx[100], taily[100];
int tail_len;                                       // storing length of the snake's tail

void setup();                   // this function will tell the initial stage of game
void draw();
void input();
void logic();

int main(){
    char start;
    cout << "\t-------------------------------" << endl;
    cout << "\t\t :Snake King:" << endl;
    cout << "\t-------------------------------" << endl;
    cout<< " \t\t : INSTRUCTIONS : "<<endl;
    cout<< " Press 'w' to move snake up "<<endl;
    cout<< " Press 'a' to move snake left "<<endl;
    cout<< " Press 'd' to move snake right "<<endl;
    cout<< " Press 's' to move snake down "<<endl;
    cout<<" if snake's head touches its body game overs "<<endl;
    cout<< "\tPress 's' to start: ";
    cin >> start;
    if(start == 's'){
        setup();
        while(!gameOver){          // loop will run till gameover becomes false
            draw();
            input();
            logic();
            Sleep(60);             //will slow down our loop
            system("cls");         // to clear previous output
        }
    }
    cout<<" \t\tGAMEOVER \n";
    cout<<" your score was score = "<<score<<endl;
    cout<<" \n "<<endl;
}

void setup(){                       
    gameOver = false;
    dir = STOP;                             
    headX = width/2;                // for snake to come in centre in start
    headY = height/2;
    fruitX = rand()%width;          // to randomly generate fruit at any point on x axis    
    fruitY = rand()%height;         // to randomly generate fruit at any point on y axis
    score = 0;                      // initially score is 0
}

void draw(){
    system("cls");
    // Uper Border
    cout << "\t\t";
    for(int i = 0; i < width-8; i++){
        cout << "||";
    }
    cout << endl;

    // Snake, fruit, space and side borders
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            // left border
            if(j == 0){
                cout << "\t\t||";
            }
            // snake head
            if(i == headY && j == headX){
                cout << "O";
            }
            // fruit
            else if(i == fruitY && j == fruitX){
                cout << "*";
            }
            // space, snake tail
            else{
                bool print = false;                                 // will tell whether tail is completely printed or not
                // tail
                for(int k = 0; k < tail_len; k++){
                    if(tailx[k] == j && taily[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                // space
                if(!print){
                    cout << " ";
                }
            } 
            // right border
            if(j == width-1){
                cout << "||";
            }
        }
        cout << endl;
    }
    // Lower Border
    cout << "\t\t";
    for(int i = 0; i < width-8; i++){
        cout << "||";
    }
    cout << endl;
    cout << "\t\t    Current Score: " << score << endl;
}

void input(){                       // to manage control, how our snake will move
    if(kbhit())                    // keyboard hit- will return true till something is pressed on keyboard
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
    default:
        break;
    }
}

void logic(){
    // tail logic
    int prevx = tailx[0];                       //will store the current tail's axis   
    int prevy = taily[0];
    int prev2x, prev2y;                         //to store the tail's next elements
    tailx[0] = headX;                           // storing head's axis
    taily[0] = headY;
    for(int i = 1; i < tail_len; i++){          // loop to move snake's tail element one behind other
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    // direction logic
    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    // touch walls
    if(headX >= width){
        headX = 0;
    }
    else if(headX < 0){
        headX = width - 1;
    }
    if(headY >= height){
        headY = 0;
    }
    else if(headY < 0){
        headY = height - 1;
    }

    // snake bite itself
    for(int i = 0; i < tail_len; i++){
        if(tailx[i] == headX && taily[i] == headY){
            gameOver = true;
        }
    }

    // snake eat fruit
    if(headX == fruitX && headY == fruitY){
        score += 1;
        fruitX = rand()%width;
        fruitY = rand()%height;
        tail_len++;
    }
}