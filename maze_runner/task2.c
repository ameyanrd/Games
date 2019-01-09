#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define rows 23
#define cols 73
#define clear() printf("\033[H\033[J")
int posr,posc;
char a[rows][cols]={"#########################################################################","#   #               #               #           #                   #   #","#   #   #########   #   #####   #########   #####   #####   #####   #   #","#               #       #   #           #           #   #   #       #   #","#########   #   #########   #########   #####   #   #   #   #########   #","#       #   #               #           #   #   #   #   #           #   #","#   #   #############   #   #   #########   #####   #   #########   #   #","#   #               #   #   #       #           #           #       #   #","#   #############   #####   #####   #   #####   #########   #   #####   #","#           #       #   #       #   #       #           #   #           #","#   #####   #####   #   #####   #   #########   #   #   #   #############","#       #       #   #   #       #       #       #   #   #       #       #","#############   #   #   #   #########   #   #####   #   #####   #####   #","#           #   #           #       #   #       #   #       #           #","#   #####   #   #########   #####   #   #####   #####   #############   #","#   #       #           #           #       #   #   #               #   #","#   #   #########   #   #####   #########   #   #   #############   #   #","#   #           #   #   #   #   #           #               #   #       #","#   #########   #   #   #   #####   #########   #########   #   #########","#   #       #   #   #           #           #   #       #               #","#   #   #####   #####   #####   #########   #####   #   #########   #   #","#   #                   #           #               #               #   #","# X #####################################################################"};
void setup(){
	int i,j;
	srand(time(NULL));
	while(a[posr][posc]!=' '){
		posr=rand()%rows;
		posc=rand()%cols;
	}
	a[posr][posc]='@';
	clear();
	for(i=0; i<rows; i++){
                for(j=0; j<cols; j++)
                        printf("%c",a[i][j]);
                printf("\n");
        }
}
void game_loop(){
	char c;
	int i,j;
	while((posr!=22)||(posc!=2)){
		printf("Enter the key:");
		scanf("%c",&c);
		if(c=='a'){
			if(a[posr][posc-1]=='#'){
				continue;
			}else{
				a[posr][posc-1]='@';
				a[posr][posc]=' ';
				posc=posc-1;
			}
		}else if(c=='d'){
                        if(a[posr][posc+1]=='#'){
                                continue;
                        }else{
                                a[posr][posc+1]='@';
                                a[posr][posc]=' ';
				posc=posc+1;
                        }
                }else if(c=='w'){
                        if(a[posr-1][posc]=='#'){
                                continue;
                        }else{
                                a[posr-1][posc]='@';
                                a[posr][posc]=' ';
				posr=posr-1;
                        }
                }else if(c=='s'){
                        if(a[posr+1][posc]=='#'){
                                continue;
                        }else{
                                a[posr+1][posc]='@';
                                a[posr][posc]=' ';
				posr=posr+1;
                        }
                }
		clear();
		for(i=0; i<rows; i++){
                	for(j=0; j<cols; j++)
                        	printf("%c",a[i][j]);
                	printf("\n");
        	}
	}
}
int main(){
        setup();
	game_loop();
        return 0;
}

