#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define MAX_ROW 30
#define MAX_COL 30
#define MAX_MINE 250

int playermap[MAX_ROW + 2][MAX_COL + 2] = {0}, minesmap[MAX_MINE] = {0}, map[MAX_ROW + 2][MAX_COL + 2] = {0};
int k, r, minesNum, s;
int x, y, z, step, ALL_MINE;
int ROW, COL, MINE;
clock_t start, end; //宣告時間變數

int selectmines(int,int), count(), count2();
void menu(), game(), gameover(), gamewin();
void type(int, int);
void search(int, int);
void initialmap(), printMAP(), reset();
void SetColor(int color);
int judge(int, int), judge2(int, int, int);

int main()
{
    while(1){
        menu();
        ALL_MINE = ROW * COL;
        initialmap();
        while(1){
            game();
            if(ALL_MINE == MINE && count2() == 0){
                end = clock();
                break;
            }
        }
        gamewin();
        reset();
    }
    return 0;
}

void reset(){
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            playermap[i][j] = 0;
        }
    }
    for(int i = 0; i < MINE; i++){
        minesmap[i] = 0;
    }
    for(int j = 0; j < COL + 2; j++){
        for(int i = 0; i < ROW + 2; i++){
            map[i][j] = 0;
        }
    }
    step = 0;
}

void gamewin(){
    SetColor(14);
    MessageBox(0, "You win! Congratulation! : )", "Hi", 0 | MB_ICONASTERISK);
    printf("遊戲結束！恭喜勝利！\n");
    printf("您用了%d步", step);
    double diff = end - start;
    printf("遊戲所用時間: %.2f sec\n", diff / CLOCKS_PER_SEC);
    SetColor(7);
}

void menu(){
    int INmenu = 0;
    printf("\t歡迎來到\"踩地雷\"遊戲！\n");
    printf("----------------------------------------\n");
    Sleep(500);
    printf("\t1: 開始遊戲\n\t2: 退出遊戲\n\n");
    printf("\t請選擇遊戲清單:");
    scanf("%d", &INmenu);
    printf("----------------------------------------\n");
    switch (INmenu)
    {
    case 1:
        while (1)
        {
            printf("\t請輸入地圖大小(x, y)，x和y值不可超過%d:", MAX_ROW);
            scanf("%d %d", &ROW, &COL);
            if(judge(ROW, COL) == 1) break;
        }
        while(1){
            printf("\t請輸入地雷數量，輸入數字不可超過%d:", MAX_MINE);
            scanf("%d", &MINE);
            if(judge2(MINE, ROW, COL) == 1) break;
        }
        printf("\t遊戲開始!\n");
        printf("----------------------------------------\n");
        for(int i = 1; i < ROW + 1; i++){
            Sleep(20);
            if(i == 1) printf("%4d", i);
            if(i != 1) printf("%3d", i);
        }
        printf(" X");
        printf("\n");
    
        for(int i = 0; i < COL; i++){
            if(i < 10) printf("%2d", i+1);
            if(i >= 10) printf("%d", i+1);
            Sleep(20);
            for(int j = 0; j < ROW; j++){
                Sleep(20);
                printf(" ■ ");
            }
            printf("\n");
        }
        Sleep(20);
        printf("Y\n");
        start = clock();
        break;
    case 2:
        exit(0);
    default:
        SetColor(12);
        printf("\t輸入的數字有誤！請再輸入一次！\n\n");
        SetColor(7);
        return menu();
    }
} 
//row col值輸入防雷
int judge(int input1, int input2){
    if(input1 < 0 || input1 > MAX_ROW || input2 < 0 ||input2 > MAX_COL){
        SetColor(12);
        printf("\t輸入的數字不在範圍內，請重新輸入\n");
        SetColor(7);
        return 0;
    }
    return 1;
}
//mine值輸入防雷
int judge2(int input, int row, int col){
    if(input < 0 || input > MAX_MINE || row*col < input){
        SetColor(12);
        printf("\t輸入的數字不在範圍內，請重新輸入\n");
        SetColor(7);
        return 0;
    }
    return 1;
}
//map初始化
void initialmap(){
    //get 棋盤數列(playermap)
    k = 1;
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            playermap[i][j] = k;
            k++;
        }
    }
    //get 地雷數列
    for(int i = 0; i < MINE; i++){
        srand((unsigned int)time(NULL));
        r = (rand()% ALL_MINE) + 1;
        minesmap[i] = selectmines(i,r);
    }
    //畫地雷(地雷 = -1)
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            //看是不是地雷
            for(int k = 0; k < MINE; k++){
                if((playermap[i][j]) == minesmap[k]){
                    playermap[i][j] = -1;
                }
            }
        }
    }
    //畫數字
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            minesNum = 0;
            //搜尋周圍
            if((playermap[i][j]) != -1){
                for(int k = i - 1; k <= i + 1 ; k++){
                    for(int w = j - 1; w <= j + 1; w++){
                        if((playermap[k][w]) == -1){
                            minesNum ++;
                        }
                    }
                }   
                playermap[i][j] = minesNum;
            }
        }
    }
    //設map初始陣列
    for(int j = 0; j < COL + 2; j++){
        for(int i = 0; i < ROW + 2; i++){
            if(i == 0 || i == ROW + 1){
                map[i][j] = 99;
            }
            else if(j == 0 || j == COL + 1){
                map[i][j] = 99;
            }
            else{
                map[i][j] = 10;
            }         
        }
    }
}  

int selectmines(int i,int r){
        int k = 0;
        while(k < i){
            if(minesmap[k] == r){
                r = (rand()% ALL_MINE) + 1;
                r = selectmines(i,r);
                break;
            }
            else{
                k++;
            }
        }
        return r;
}

int count(){
    s = 0;
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            if((map[i][j]) == 10 || (map[i][j]) == 9) s++;
        }
    }
    return s;
}

int count2(){
    s = 0;
    for(int j = 1; j < COL + 1; j++){
        for(int i = 1; i < ROW + 1; i++){
            if((map[i][j]) == 10) s++;
        }
    }
    return s;
}

void game(){
    SetColor(10);
    printf("功能: 1. 打開位置  2. 標記/取消標記\n");
    printf("想要結束請輸入(0, 0, 0)\n");
    printf("請輸入座標與動作(X, Y, 功能):");
    scanf("%d%d%d", &x, &y, &z);
    SetColor(7);
    if(z == 0){
        printf("好的，遊戲結束");
        exit(0);
    }
    else if(z == 1){
        type(x, y);    
        step++;
        printMAP();
        SetColor(13);
        printf("步數:%d\n剩餘地雷個數:%d\n\n", step, ALL_MINE); 
        SetColor(7);   
    }
    else if(z == 2){
        if((map[x][y]) == 10){
            map[x][y] = 9;
            step++;
        }
        else if((map[x][y]) == 9){
            map[x][y] = 10;
            step++;
        }
        else{
            SetColor(12);
            printf("\n!!!錯誤的動作!!!請再輸入一次\n");
            SetColor(7);
            return game(); 
        }
        printMAP();
        SetColor(13);
        printf("步數:%d\n剩餘地雷個數:%d\n\n", step, ALL_MINE); 
        SetColor(7);
    }
    else{
        SetColor(12);
        printf("\n!!!錯誤的動作!!!請再輸入一次\n");
        SetColor(7);
        return game(); 
    }
}

void type(int x, int y){
    if(map[x][y] != 10){
        SetColor(12);
        printf("操作錯誤請再試一次\n");
        SetColor(7);
    }
    else if(playermap[x][y] == -1){
        for(int i = 1; i < ROW + 1; i++){
            if(i == 1) printf("%4d", i);
            if(i != 1) printf("%3d", i);
        }
        printf(" X");
        printf("\n");

        for(int j = 1; j < COL + 1; j++){
            if(j < 10) printf("%2d", j);
            if(j >= 10) printf("%d", j);

            for(int i = 1; i < ROW + 1; i++){
                if(playermap[i][j] == -1 && map[i][j] != 9){
                    SetColor(11);
                    printf(" * ");
                    SetColor(7);
                }
                else if(playermap[i][j] == -1 && map[i][j] == 9){
                    SetColor(27);
                    printf(" P ");
                    SetColor(7);                    
                }
                else if(map[i][j] == 9){
                    SetColor(12);
                    printf(" P ");
                    SetColor(7);
                }
                else if((map[i][j]) != 10){
                    if((playermap[i][j]) == 0){
                        printf("   ");
                    }
                    else{
                        printf(" %d ", (map[i][j]));
                    }
                }
                else{
                    printf(" ■ ");
                }
            }
            printf("\n");
        }
        printf("Y\n");
        step++;
        end = clock();
        gameover();
        reset();
        printf("----------------------------------------\n");
        main();
    }
    else if(playermap[x][y] == 0){
        map[x][y] = 11;
        search(x, y);
        ALL_MINE = count();
    }
    else{
        map[x][y] = playermap[x][y];
        ALL_MINE = count();
    }
}

void gameover(){
    MessageBox(0, "You lose! haha : D", "hi", 0 | MB_ICONHAND);
    SetColor(14);
    printf("遊戲結束！再接再厲！\n");
    printf("您用了%d步\n", step);
    double diff = end - start;
    printf("遊戲所用時間: %.2f sec\n", diff / CLOCKS_PER_SEC);
    SetColor(7);
}

void search(int x, int y){
    for(int j = y - 1; j < y + 2; j++){
        for(int i = x - 1; i < x + 2; i++){
            if(map[i][j] == 10 && map[i][j] != 9 && playermap[i][j] != -1){
                type(i, j);
            }   
            
        }
    }
}

void printMAP(){
    for(int i = 1; i < ROW + 1; i++){
        if(i == 1) printf("%4d", i);
        if(i != 1) printf("%3d", i);
    }
    printf(" X");
    printf("\n");
    
    for(int j = 1; j < COL + 1; j++){
        if(j < 10) printf("%2d", j);
        if(j >= 10) printf("%d", j);
        
        for(int i = 1; i < ROW + 1; i++){
            if((map[i][j]) == 9){
                SetColor(12);
                printf(" P ");
                SetColor(7);
            }
            else if((map[i][j]) != 10){
                if((playermap[i][j]) == 0){
                    printf("   ");
                }
                else{
                    printf(" %d ", (map[i][j]));
                }
            }
            else{
                printf(" ■ ");
            }
        }
        printf("\n");
    }
    printf("Y\n");
}
//設定文字顏色
void SetColor(int color)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}