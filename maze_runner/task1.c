#include<stdio.h>
#define rows 23
#define cols 73
#define clear() printf("\033[H\033[J")
void setup(){
	int i,j;
	clear();
	char a[rows][cols]={"#########################################################################","#   #               #               #           #                   #   #","#   #   #########   #   #####   #########   #####   #####   #####   #   #","#               #       #   #           #           #   #   #       #   #","#########   #   #########   #########   #####   #   #   #   #########   #","#       #   #               #           #   #   #   #   #           #   #","#   #   #############   #   #   #########   #####   #   #########   #   #","#   #               #   #   #       #           #           #       #   #","#   #############   #####   #####   #   #####   #########   #   #####   #","#           #       #   #       #   #       #           #   #           #","#   #####   #####   #   #####   #   #########   #   #   #   #############","#       #       #   #   #       #       #       #   #   #       #       #","#############   #   #   #   #########   #   #####   #   #####   #####   #","#           #   #           #       #   #       #   #       #           #","#   #####   #   #########   #####   #   #####   #####   #############   #","#   #       #           #           #       #   #   #               #   #","#   #   #########   #   #####   #########   #   #   #############   #   #","#   #           #   #   #   #   #           #               #   #       #","#   #########   #   #   #   #####   #########   #########   #   #########","#   #       #   #   #           #           #   #       #               #","#   #   #####   #####   #####   #########   #####   #   #########   #   #","#   #                   #           #               #               #   #","# X #####################################################################"};
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++)
			printf("%c",a[i][j]);
		printf("\n");
	}
}
int main(){
	setup();
	return 0;
}