#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define WIDTH 15
#define HEIGHT 30
#define DOWN 1


//一个随机函数 获得砖的高度

//根据输入，飞行
void updateWithInput(void);
void updateWithoutInput(void);
void show(void);
void menu(void);
void starts(void);
int random(int min, int max);

int arr[WIDTH][HEIGHT] = {0};
int brid_x, brid_y;
int brick_x[4], brick_y[2];
int xueko[2], hinder[2];
int brick_width;

int random(int min, int max){
	time_t t;
	srand((unsigned int)time(&t));
	return rand()%max+min;
}
void gotoxy(int x, int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void updateWithInput(){
	char ch;
	if(kbhit()){
		ch = getch();
		switch(ch){
		case ' ':
			arr[brid_x][brid_y] = 0;
			brid_x -= 2;
			arr[brid_x][brid_y] = 1;

			break;
		default:
			break;
		}
	}
}
void starts(){
	int i;

	brick_y[0] = HEIGHT-1;
	brick_y[1] = brick_y[0]-10;
	brid_x = 1;
	brid_y = HEIGHT/20;
	xueko[0] = random(2, 5);
	xueko[1] = random(2, 5);

	hinder[1] = random(0, WIDTH-xueko[0]);
	hinder[0] = random(0, WIDTH-xueko[0]);

	for(i = 0; i<WIDTH; i++){
		if(i<hinder[0] || i>hinder[0]+xueko[0]){
			arr[i][brick_y[0]] = 2;
		}
		if(i<hinder[1] || i>hinder[1]+xueko[1]){
			arr[i][brick_y[1]] = 2;
		}
	}
	arr[brid_x][brid_y] = 1;

}
void updateWithoutInput(){
	int i;
	static int speed = 0;
	if(brick_y[0] >= 0){
		for(i = 0; i<WIDTH; i++){
			if(i<hinder[0] || i>hinder[0]+xueko[0]){
				arr[i][brick_y[0]] = 0;
			}
		}
		brick_y[0] -=  1;
		for(i = 0; i<WIDTH; i++){
			if(i<hinder[0] || i>hinder[0]+xueko[0]){
				arr[i][brick_y[0]] = 2;
			}
		}
	}else{
		brick_y[0] = HEIGHT-1;
		xueko[0] = random(2, 5);
		hinder[0] = random(0, WIDTH-xueko[0]);
		for(i = 0; i<WIDTH; i++){
			if(i<hinder[0] || i>hinder[0]+xueko[0]){
				arr[i][brick_y[0]] = 2;
			}
		}
	}
	if(brid_x <= 0){
		printf("\a");
		arr[brid_x][brid_y] = 0;
		brid_x = 1;
		arr[brid_x][brid_y] = 1;
	}
	else if(brid_x >= 14 ){
		gotoxy(0, 0);
		printf("游戏失败");
		exit(0);
	}
	else{	
		if(speed < 5){
			speed++;
		}
		if(speed == 5){
			arr[brid_x][brid_y] = 0;
			brid_x += DOWN;
			arr[brid_x][brid_y] = 1;
			speed = 0;
		}

	}
}
int main(){
	//初始化数据
	menu();

	starts();
	while(1){
		show();
		updateWithInput();
		updateWithoutInput();
	}

	return 0;
}

void menu(){
	
}

void show(){
	int i, j;
	gotoxy(0, 0);
	

	for(i = 0; i<WIDTH; i++){
		for(j = 0; j<HEIGHT; j++){
			if(arr[i][j] == 0){
				printf(" ");
			}
			else if(arr[i][j] == 1){
				printf("@");
			}
			else if(arr[i][j] == 2){
				printf("|");
			}
		}
		printf("|\n");
	}	
	for(i = 0; i<HEIGHT; i++){
		printf("-");
	}
	printf("\n");
	Sleep(30);
}