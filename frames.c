#include <stdio.h>
#include <windows.h>
#include <time.h>

#define height 25
#define width 100
#define frate 60

char buffer[height][width];
int fcount = 0;

void cubegenerator(void);
void frame_rescale(int *, int, int, int);

void linearmatrix(void);

void frameout(void);

int main(){
    time_t seed;
    seed = time(NULL);
    srand(seed);

    while (1){

        //cubegenerator();
        linearmatrix();

        frameout();
        Sleep(1000/frate);
    }
    return 0;
}

void linearmatrix(void){
    int n, r, i, j;
    char trail[] = {'o', '|','!', ':', '.'};

    r = rand()%width;

    for(i=height-1; i>0; i--){
        n = i-1;
        for(j=0; j<width; j++){
            buffer[i][j] = buffer[n][j];
        }
    }
    for(j=0; j<width; j++){
        switch (buffer[1][j]){
            case 'o': buffer[0][j] = trail[1]; break;
            case '|': buffer[0][j] = trail[2]; break;
            case '!': buffer[0][j] = trail[3]; break;
            case ':': buffer[0][j] = trail[4]; break;
            default:
            buffer[i][j] = ' ';
        }
    }
    
    if(!(rand()%4)){
        buffer[0][r] = trail[0];
    }
}

void cubegenerator(void){
    int a = 255;
    int h=10, w=40, b[10][40] = {0};
    static int i=1, hi=0, j=2, wj=0;

    b[hi][wj]=30;

    hi = hi + i;
    wj = wj + j;

    if(hi>=h-1){
        i = -1;
    }else if(hi<=0){
        i = 1;
    }
    if(wj>=w-1){
        j = -2;
    }else if(wj<=0){
        j = 2;
    }
    printf("\x1b[2;1H");
    printf ("| %d, %d |", i, j);
    frame_rescale(&b[0][0], h, w, a);
}
void frame_rescale(int *frm, int h, int w, int a){
    int i, j, k, x, y, z;
    char d[12] = {' ', '.', '^', '*', 'o', 'O', '8', '#', '$', '&', '@'};

    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            x = (i*h/height*w);
            y = (j*w/width);
            z = x + y;
            k = (*(frm + z)*10/a);
            buffer[i][j] = d[k];
        }
    }
}

void frameout(void){
    int i, j;
    printf("\x1b[2;0H");
    printf("Frame: %d\n", fcount);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            printf("%c", buffer[i][j]);
        }
        printf("\n");
    }
    fcount += 1;
}
