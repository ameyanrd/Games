#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#define rows 23
#define cols 73
#define clear() printf("\033[H\033[J")
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
char a[rows][cols];
char c,prev;
int foodposx, foodposy;
int sx,sy;
int speed=100000,getchflag=1,score; //score acts as the snake length
int snakeUnitsx[100],snakeUnitsy[100];

void Initialisation(){
    sx=14;
    sy=14;
    score=0;
    prev='d';
    a[14][14]='@';
    c='d';
}
void fooddisplay(){
    srand(time(NULL));
    foodposy=(rand()%(rows-3)+2);
    foodposx=(rand()%(cols-3)+2);
    a[foodposy][foodposx]='*';
    //speed-=20000; For Speed change
}
void initial_frame(){
    int i,j;
    for(i=0; i<cols; i++)
        a[0][i]='#';
    for(i=1; i<rows-1; i++){
        a[i][0]='#';
        for(j=1; j<cols-1; j++)
            a[i][j]=' ';
        a[i][cols-1]='#';
    }
    for(i=0; i<cols; i++)
        a[rows-1][i]='#';
    fooddisplay();
}

int gameCheck(){
    int flag=0;
    for(int i=3; i<=score; i++){
        if(sx==snakeUnitsx[i] && sy==snakeUnitsy[i]){
            flag=1;
            break;
        }
    }
    return flag;
}

void frame_display(){
    clear();
    int i,j;
    if(foodposx==sx && foodposy==sy){
        score++;
        snakeUnitsx[score];
        snakeUnitsy[score];
        fooddisplay();
    }
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c",a[i][j]);
        }
        printf("\n");
    }
    printf("Score = %d\n",score);
    
}
void snakeUnitsMovement(){
    int i;
    if(score>1)
        a[snakeUnitsy[score]][snakeUnitsx[score]]=' ';
    a[0][0]='#';
    snakeUnitsy[0]=sy;
    snakeUnitsx[0]=sx;
    for(i=score; i>0; i--){
        snakeUnitsx[i]=snakeUnitsx[i-1];
        snakeUnitsy[i]=snakeUnitsy[i-1];
    }

    for(i=0; i<score; i++)
        a[snakeUnitsy[i+1]][snakeUnitsx[i+1]]='@';
}
void gamelevel(){
    clear();
    printf("1)Easy(e)\n2)Medium(m)\n3)Difficult(d)\n");
    printf("Choose the level of difficulty(e/m/d):");
    char ch;
    scanf("%c",&ch);
    switch(ch){
        case 'e':speed=300000;
        case 'm':speed=150000;
        case 'd':speed=80000;
    }
}

void *snake_movement(){
    Initialisation();
    while(1){
        while(c!='s' && c!='w'){
            a[sy][sx%(cols-2)+1]='@';
            a[sy][sx]=' ';
            sx+=1;
            if(sx>(cols-2)) sx%=(cols-2);
            snakeUnitsMovement();
            frame_display();
            usleep(speed);
        }
        if(c=='s' && prev!='w'){
            prev=c;
            while(c!='a' && c!= 'd'){
                a[sy%(rows-2)+1][sx]='@';
                a[sy][sx]=' ';
                sy+=1;
                if(sy>(rows-2)) sy%=(rows-2);
                snakeUnitsMovement();
                frame_display();
                if(gameCheck()){
                    break;
                }
                usleep(speed);
            }
        }
        if(c=='w' && prev!='s'){
            prev=c;
            while(c!='a' && c!= 'd'){
                a[(sy+(rows-4))%(rows-2)+1][sx]='@';
                a[sy][sx]=' ';
                sy-=1;
                if(sy==0) sy=(rows-2);
                snakeUnitsMovement();
                frame_display();
                if(gameCheck()){
                    break;
                }
                usleep(speed);
            }
        }
        if(c=='d' && prev!='a'){
            prev=c;
            while(c!='w' && c!= 's'){
                a[sy][sx%(cols-2)+1]='@';
                a[sy][sx]=' ';
                sx+=1;
                if(sx>71) sx%=(cols-2);
                snakeUnitsMovement();
                frame_display();
                if(gameCheck()){
                    break;
                }
                usleep(speed);
            }
        }
        if(c=='a' && prev!='d'){
            prev=c;
            while(c!='w' && c!= 's'){
                a[sy][(sx+(cols-4))%(cols-2)+1]='@';
                a[sy][sx]=' ';
                sx-=1;
                if(sx==0) sx=(cols-2);
                snakeUnitsMovement();
                frame_display();
                if(gameCheck()){
                    break;
                }
                usleep(speed);
            }
        }
        if (gameCheck()){
            printf("Game Over\n");
            printf("Do you want to play again?(y/n)\n");
            scanf("%c",&c);
            switch(c){
                case 'y':gamelevel();
                Initialisation();
                initial_frame();
                    continue;
                case 'n':
                        break;
            }
        }
    }
}


int main(){
    int i,j;
    gamelevel();
    initial_frame();
    frame_display();
    pthread_t tid; 
    pthread_create(&tid, NULL, snake_movement, (void *)&tid);
    while(getchflag){
      c=getch();
    }
    pthread_exit(NULL);
    return 0;
}
