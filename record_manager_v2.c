/* This is a student record manager program.
This program uses double linked list and bubble sort at its core.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "student_datasheet.txt" //file path

FILE *stud;

struct student{
    int id;
    char reg[10];
    char name[15];
    int roll;
    struct student *prev;
    struct student *next;
};

struct student *ptr = NULL;

//core functions 
void init(void);
void cont(void);
void close(void);
void eraselist(void);

//separated to make code look a bit clean
void menu(void);
void recall(void);

int cond(int, struct student *);
void out(struct student *o, int n);

int chartoint(char *);
void inttochar(int, char*);

//subfunctions
int add(struct student);
void erase(struct student *);
struct student *search(void);
void swap(struct student *, struct student *);

//functions as per the menu
void in(void);
void delete(void);
void modify(void);
void sort(void);
void srch(void);
void find(void);
void prt(void);

int main(){
    init();
    cont();
    close();
    eraselist();

    printf("\n**Exit**\n");

    return 0;
}

void init(){
    //reads from file into a fresh list

    //initializing variables
    int x, y, flag=0;
    char c[50], n[15], re[10], ro[10], i[10];
    struct student a;
    stud = fopen(PATH, "r");

    //check for unexpected conditions
    if(stud == NULL){
        printf("Cannot open file!\n");
        return ;
    }
    if(ptr!=NULL){
        eraselist();
    }

    //reads from file line by line
    while(fgets(c, 50, stud) && !flag){
        //break the line into specified parts separated by ';'
        for(x=0, y=0; c[y]!=';';  x+=1, y+=1) {i[x]  = c[y];} i[x]  = '\0';
        for(x=0, y++; c[y]!=';';  x+=1, y+=1) {n[x]  = c[y];} n[x]  = '\0';
        for(x=0, y++; c[y]!=';';  x+=1, y+=1) {ro[x] = c[y];} ro[x] = '\0';
        for(x=0, y++; c[y]!='\n'; x+=1, y+=1) {re[x] = c[y];} re[x] = '\0';

        //put data in the structure 'student'
        strcpy(a.name, n);
        strcpy(a.reg, re);
        a.id = chartoint(i);
        a.roll = chartoint(ro);
        //calls add() function and pass the data to be added to the list
        flag = add(a);
    }
    //free up file buffer :)
    fclose(stud);
    printf("Data loaded!\n");
}

void cont(){
    //menu function
    int n;
    menu(); //prints menu
    scanf("%d", &n);
    switch (n){
        case 1: in();     break;
        case 2: delete(); break;
        case 3: modify(); break;
        case 4: sort();   break;
        case 5: srch();   break;
        case 6: find();   break;
        case 7: prt();    break;
        case 8: init();   break;
        case 9: close();  break;
        case 0: return ;
        default: printf("Wrong input!\n");
    }
    recall(); //indirect recursion
}

void close(){
    //this function save data to the file
    int n;
    char a[50], x[16];
    struct student *c;

    if(ptr==NULL){
        printf("Empty list!\n");
        return ;
    }
    //final confirmation before saving
    printf("Apply changes to file?[1/0]: ");
    scanf("%d", &n);
    if(!n){
        printf("No changes applied!\n");
        return ;
    }
    c = ptr;

    //traverse to top of list
    while(c->prev!=NULL){
        c = c->prev;
    }
    stud = fopen(PATH, "w");
    while(c!=NULL){
        //concatonate all fields into a line
        inttochar(c->id, x);
        strcpy(a, x);
        strcat(a, ";");
        strcat(a, c->name);
        strcat(a, ";");
        inttochar(c->roll, x);
        strcat(a, x);
        strcat(a, ";");
        strcat(a, c->reg);
        strcat(a, "\n");
        //write the line into file
        if(fputs(a, stud)==EOF){
            printf("Error while writing(%d)!\n", c->roll);
            break;
        }
        c = c->next;
    }
    fclose(stud);
    printf("Saved sucessfully!\n");
}

void eraselist(){
    //erase entire list from bottom to top
    struct student *e;
    if(ptr==NULL){
        return ;
    }
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    while(ptr!=NULL){
        e = ptr->prev;
        free(ptr);
        ptr = e;
    }
}

void menu(){
    printf("\n MENU\n");
    printf("------\n");
    printf("1.Add\n");
    printf("2.Remove\n");
    printf("3.Modify\n");
    printf("4.Sort\n");
    printf("5.Search\n");
    printf("6.Range\n");
    printf("7.Print\n");
    printf("8.Reload\n");
    printf("9.Save\n");
    printf("(0-EXIT)\n");
    printf("\nEnter your choice[0-9]: ");
}
void recall(){
    int n;
    printf("Do you want to continue?[0/1]: ");
    scanf("%d", &n);
    if(n){
        cont();
    }else{
        return ;
    }
}

int cond(int n, struct student *s){
    //subfunction of sort() function
    switch(n){
        case 1: if(s->id > s->next->id)              {return 1;} break;
        case 2: if(s->roll > s->next->roll)          {return 1;} break;
        case 3: if(strcmp(s->name, s->next->name)>0) {return 1;} break;
        case 4: if(strcmp(s->reg, s->next->reg)>0)   {return 1;} break;
    }
    return 0;
}
void out(struct student *o, int n){
    //just a visually appealing way to print info (lol)
    switch (n){
        case 0:
        printf("    Id     |      Name      |  Roll no.  | Reg. no. \n");
        printf("-----------+----------------+------------+----------\n");
        break;
        case 1:
        printf("%10d | %14s | %10d | %s\n", o->id, o->name, o->roll, o->reg);
        break;
    }
    
}

int chartoint(char *c){
    //convert string to integer
    int i, x;
    for(i=0, x=0; *(c+i)!='\0'; i+=1){
        switch (*(c+i)){
            case '0': x = x*10;     break;
            case '1': x = x*10 + 1; break;
            case '2': x = x*10 + 2; break;
            case '3': x = x*10 + 3; break;
            case '4': x = x*10 + 4; break;
            case '5': x = x*10 + 5; break;
            case '6': x = x*10 + 6; break;
            case '7': x = x*10 + 7; break;
            case '8': x = x*10 + 8; break;
            case '9': x = x*10 + 9; break;
        }
    }
    return x;
}
void inttochar(int n, char *c){
    //convert integer to string
    int i, j;
    char t[10];
    for(i=n, j=0; i!=0; i=i/10, j++){
        switch(i%10){
            case 0: t[j]='0'; break;
            case 1: t[j]='1'; break;
            case 2: t[j]='2'; break;
            case 3: t[j]='3'; break;
            case 4: t[j]='4'; break;
            case 5: t[j]='5'; break;
            case 6: t[j]='6'; break;
            case 7: t[j]='7'; break;
            case 8: t[j]='8'; break;
            case 9: t[j]='9'; break;
        }
    }
    for(i=0, j-=1; j>-1; j--, i++){
        c[i]=t[j];
    }
    c[i] = '\0';
}

int add(struct student i){
    //add new node at bottom of the list
    struct student *a = NULL;
    a = (struct student*)malloc(sizeof(struct student));
    if (a!=NULL){
        *a = i;
        a->next = NULL;
        if(ptr!=NULL){
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            a->prev = ptr;
            ptr->next = a;
            if(!a->id){
                a->id = ptr->id+1;
            }
            ptr = ptr->next;
        }else{
            a->prev = NULL;
            ptr = a;
            if(!ptr->id){
                ptr->id = 1;
            }
        }
        return 0;
    }else{
        printf("Not enough memory!\n");
        return 1;
    }
}
void erase(struct student *r){
    //remove a node from the list
    /*remove keyword was causing conflict with a lib function
      so I renamed this to erase.*/
    struct student *rp, *rn;

    if(r==NULL){
        return ;
    }
    rp = r->prev;
    rn = r->next;

    if(rp!=NULL){rp->next = rn;}
    if(rn!=NULL){rn->prev = rp;}

    if(r == ptr){
        if(rn!=NULL){
            ptr = rn;
        }else if(rp!=NULL){
            ptr = rp;
        }else{
            ptr = NULL;
        }
    }
    free(r);
}
struct student *search(){
    //search
    int i, n;
    char c[15];

    struct student *s = ptr;

    if(ptr==NULL){
        printf("Empty list!\n");
        return NULL;
    }
    while(s->prev!=NULL){
        s = s->prev;
    }

    printf("Find by:\n1.Name\n2.Roll\n3.Reg. no.\n4.Id");
    printf("\n(0 to cancel)\nEnter choice[0-4]: ");
    scanf("%d", &i);
    printf("Enter value: ");
    switch (i){
        case 1: case 3:
        scanf("%s", c);
        break;
        case 2: case 4:
        scanf("%d", &n);
        break;
        default:
        printf("Invalid choice!\n");
        case 0:
        return NULL;
    }

    while(s!=NULL){
        switch (i){
            case 1:if(!strncmp(c, s->name, strlen(c))) {return s;} break;
            case 2:if(n == s->roll)                    {return s;} break;
            case 3:if(!strncmp(c, s->reg, strlen(c)))  {return s;} break;
            case 4:if(n == s->id)                      {return s;} break;
        }
        s = s->next;
    }
    return NULL;
}
void swap(struct student *a, struct student *b){
    //swap data without swapping pointer values
    struct student s;

    s = *a;
    *a = *b;

    a->prev = s.prev;
    a->next = s.next;

    s.prev = b->prev;
    s.next = b->next;

    *b = s;
}

void in(){
    //provides data from the user to add() function
    struct student i;
    printf("Enter name(max 15, no space):\n\t"); scanf("%s", i.name);
    printf("Enter roll no.: "); scanf("%d", &i.roll);
    printf("Enter reg. no.: "); scanf("%s", i.reg);
    printf("Enter id(0 to self count): "); scanf("%d", &i.id);
    if(!add(i)){
        printf("Student added!\n");
    }else{
        printf("Student not added!\n");
    }
}
void delete(){
    //find node using search() then pass it to erase()
    //to be removed from the list
    struct student *d, dt;
    if(ptr!=NULL){
        d = search();
        if(d!=NULL){
            dt = *d;
            erase(d);
            printf("Student %d removed!\n", dt.id);
        }else{
            printf("No match found!\n");
        }
    }else{
        printf("Empty list!\n");
    }
}
void modify(){
    //update student info
    int n;
    char c[15];
    struct student *m;

    if(ptr==NULL){
        printf("Empty list!\n");
        return ;
    }
    
    m = search();

    if(m!=NULL){
        printf("You can enter 0 to skip the fields.\n");
        printf("Enter new name(%s): ", m->name);
        scanf("%s", c);
        if(c!="0"){
            strcpy(m->name, c);
        }
        printf("Enter new roll(%d): ", m->roll);
        scanf("%d", &n);
        if(n!=0){
            m->roll = n;
        }
        printf("Enter new reg(%s): ", m->reg);
        scanf("%s", c);
        if(c!="0"){
            strcpy(m->reg, c);
        }
        printf("Enter new Id(%d): ", m->id);
        scanf("%d", &n);
        if(n!=0){
            m->id = n;
        }
        printf("Changes saved!\n");
    }else{
        printf("No match found!\n");
    }
}
void sort(){
    //arrange in ascending order
    int n;

    struct student *s, *t;

    if(ptr == NULL){
        printf("Empty list!\n");
        return ;
    }
    s = ptr;
    while(s->prev!=NULL){
        s = s->prev;
    }
    t = s;

    printf("*Warning: Sorting will change the order of\n");
    printf("\tentire list.\nSort by:\n");
    printf("1.Id\n2.Roll\n3.Name\n4.Reg\n");
    printf("(0 to cancle)\nEnter choice[0-4]: ");
    scanf("%d", &n);

    switch (n){
        case 1: case 2: case 3: case 4: break;
        default: printf("Wrong choice!\n");
        case 0: printf("No sorting done!\n"); return ;
    }
    //uses bubble sort
    int i=1;
    while(i){
        i = 0;
        s = t;
        while(s->next!=NULL){
            if(cond(n, s)){
                swap(s, s->next);
                i+=1;
            }
            s = s->next;
        }
    }
    printf("List sorted!\n");
}
void srch(){
    //single item search
    struct student *s;

    if(ptr==NULL){
        printf("Empty list!\n");
        return ;
    }

    s = search();
    if(s==NULL){
        printf("No match found!\n");
        return ;
    }
    out(NULL, 0);
    out(s, 1);
}
void find(){
    //find in the given range
    int i, nl, nu;
    char cl[15], cu[15];

    struct student *f = ptr;

    if(ptr==NULL){
        printf("Empty list!\n");
        return ;
    }

    printf("Field:-\n1.Roll\n2.Id");
    printf("\n3.Reg. no\n4.Name\n");
    printf("(0 to cancle)\nEnter choice[0-4]: ");
    scanf("%d", &i);

    switch (i){
        case 1: case 2:
        printf("Enter lower limit(0 for none): ");
        scanf("%d", &nl);
        printf("Enter upper limit(0 for none): ");
        scanf("%d", &nu);
        break;
        case 3: case 4:
        printf("Enter lower limit(0 for none): ");
        scanf("%s", cl);
        printf("Enter upper limit(0 for none): ");
        scanf("%s", cu);
        break;
        default:
        printf("Wrong input!\n");
        case 0:
        return ;
    }

    while(f->prev!=NULL){
        f = f->prev;
    }

    printf("Following are the matches found:\n");
    out(NULL, 0);
    while(f!=NULL){
        switch (i){
            case 1:
            if((nl?(f->roll>=nl):1) && (nu?(f->roll<=nu):1))
            {out(f, 1);} break;

            case 2:
            if((nl?(f->id>=nl):1) && (nu?(f->id<=nu):1))
            {out(f, 1);} break;

            case 3:
            if((cl[0]=='0'?1:(strncmp(f->reg, cl, strlen(cl))>=0)) &&
                (cu[0]=='0'?1:(strncmp(cu, f->reg, strlen(cu))>=0)))
            {out(f, 1);} break;

            case 4:
            if((cl[0]=='0'?1:(strncmp(f->name, cl, strlen(cl))>=0)) &&
                (cu[0]=='0'?1:(strncmp(cu, f->name, strlen(cu))>=0)))
            {out(f, 1);} break;
        }
        f = f->next;
    }
}
void prt(){
    //print entire list
    struct student *p = ptr;
    if(ptr==NULL){
        printf("Empty list!\n");
        return ;
    }
    while (p->prev!=NULL){
        p = p->prev;
    }

    out(NULL, 0);
    while(p!=NULL){
        out(p, 1);
        p = p->next;
    }
}
