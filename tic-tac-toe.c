#include <stdio.h>

char a[9];

char intro(void);
void builder(void);
void buildereditor(int, int, int);

int checker(int);
int logic(int);
int editorcall(int, int *);

int main(){
    int n, i, x=2;
    if(intro()=='0'){
        printf("\n**QUIT**\n");
        return 0;
    }
    buildereditor(10, 10, 10);
    do{
        x = x!=1?1:2;
        printf("\nPerson %d's turn(1-9): ", x);
        do{
            scanf("%d", &n);
        }while(checker(--n));
        a[n] = x!=2?'O':'X';
        builder();
        i = logic(x);
    }while(!i);
    switch (i){
        case 1: case 2:
        printf("\nPerson %d Wins!", i);
        break;
        case 3:
        printf("\nIt's a tie!");
        break;
    }
    builder();
    printf("\nWant to play again?[1/0]: ");
    scanf("%d", &n);
    if(n){
        main();
    }
    printf("\n**EXIT**\n");
    return 0;
}

char intro(void){
    char c;
    printf("\nWelcome to Tic-Tac-Toe!\n\n");
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n");
    printf("\nInstructions:\n1.Enter number(1-9) for the moves.\n");
    printf("2.Person 1 is O and person 2 is X!\n");
    printf("3.Game begins from person 1.\n");
    printf("\nEnter any character to begin(0 to quit): ");
    scanf("%c", &c);
    return c;
}
void builder(void){
    printf("\n %c | %c | %c ",  a[0], a[1], a[2]);
    printf("\n-----------");
    printf("\n %c | %c | %c ",  a[3], a[4], a[5]);
    printf("\n-----------");
    printf("\n %c | %c | %c \n",a[6], a[7], a[8]);
}
void buildereditor(int p, int q, int r){
    int i;
    for(i=0; i<9; i++){
        if(i==p||i==q||i==r){
            continue;
        }
        a[i] = ' ';
    }
}

int checker(int n){
    int i;
    if(n<0||n>8||a[n]=='O'||a[n]=='X'){
        printf("Wrong input!\nAvailable moves are |");
        for(i=0; i<9; i++){
            if(a[i]==' ')
                printf(" %d |", i+1);
        }
        printf("\nEnter your move: ");
        return 1;
    }
    return 0;
}
int logic(int x){
    int i, j, k, b, d[3];
    char c='X';
    for(k=0; k<2; k++){
        c = c=='O'?'X':'O';
        for(i=0; i<3; i++){
            d[0]=0; d[1]=0; d[2]=0;
            for(j=i, b=0; j<9; j+=3){
                if(a[j]==c){
                    d[b]=j;
                    b++;
                }else break;
            }
            if(editorcall(b, &d[0])){
                return c=='O'?1:2;
            }
        }
        for(j=0; j<9; j+=3){
            d[0]=0; d[1]=0; d[2]=0;
            for(i=j, b=0; i<j+3; i++){
                if(a[i]==c){
                    d[b]=i;
                    b++;
                }
            }
            if(editorcall(b, &d[0])){
                return c=='O'?1:2;
            }
        }
        d[0]=0; d[1]=0; d[2]=0;
        for(i=0, b=0; i<9; i+=4){
            if(a[i]==c){
                d[b]=i;
                b++;
            }
        }
        if(editorcall(b, &d[0])){
            return c=='O'?1:2;
        }
        d[0]=0; d[1]=0; d[2]=0;
        for(i=2, b=0; i<7; i+=2){
            if(a[i]==c){
                d[b]=i;
                b++;
            }
        }
        if(editorcall(b, &d[0])){
            return c=='O'?1:2;
        }
    }
    for(i=0; i<9; i++){
        if(a[i] == ' ')
            return 0;
    }
    return 3;
}
int editorcall(int b, int *d){
    if(b==3){
        buildereditor(*(d+0), *(d+1), *(d+2));
        return 1;
    }else{
        return 0;
    }
}