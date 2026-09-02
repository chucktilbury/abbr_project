#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

float a = 0, b, c, d, i, m = 1;
int choice = 0;
char str[MAX], stack[MAX];
char stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;
int top = -1;
void __push(char k, char s[MAX], int* t_op);
char __pop(char s[MAX], int* t_op);
void _push(char k);
char _pop();
void push(char c) {
    stack[++top] = c;
}
char pop() {
    return stack[top--];
}
void infxtopr() {
    int l, i;
    char ch, e[MAX];
    printf("enter infix exp with () to convert to prefix \n");
    gets(e);
    gets(e);
    l = strlen(e);
    printf("the prefix is :\n");
    for(i = l - 1; i >= 0; i--) {
        ch = e[i];
        if(ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
            __push(ch, stack1, &top1);
        else if(ch != '(')
            __push(ch, stack2, &top2);
        else {
            do {
                ch = __pop(stack1, &top1);
                if(ch != ')')
                    __push(ch, stack2, &top2);
            } while(ch != ')');
        }
    }
    do {
        ch = __pop(stack2, &top2);
        putchar(ch);
    } while(top2 >= 0);
    getch();
}

int tm() {
    time_t mytime;
    mytime = time(NULL);
    printf(ctime(&mytime));

    return 0;
}

void post_in() {
    int i, n;
    char a, b, op;
    printf("Enter the postfix expression\n");
    gets(str);
    gets(str);
    n = strlen(str);
    for(i = 0; i < MAX; i++)
        // stack[i]=NULL;
        printf("Infix expression is:\t");
    printf("%c", str[0]);
    for(i = 1; i < n; i++) {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            b = pop();
            op = str[i];
            printf("%c%c", op, b);
        }
        else {
            push(str[i]);
        }
    }
    printf("%c", str[top--]);
}
void post_pre() {
    int i, n;
    printf("Enter the postfix expression\n");
    gets(str);
    gets(str);
    n = strlen(str);
    printf("Prefix expression is:\t");
    for(i = n - 1; i >= 0; i--)
        printf("%c", str[i]);
}
void pre_in() {
    int n, i;
    char a, b, op;
    printf("Enter the prefix expression\n");
    gets(str);
    gets(str);
    n = strlen(str);
    for(i = 0; i < MAX; i++)
        printf("Infix expression is:\t");
    for(i = 0; i < n; i++) {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            push(str[i]);
        }
        else {
            op = pop();
            a = str[i];
            printf("%c%c", a, op);
        }
    }
    printf("%c", str[top--]);
}
void _push(char k) {
    if(top + 1 == MAX)
        printf("stack is full\n");
    else {
        top++;
        stack[top] = k;
    }
    return;
}
char _pop() {
    char a;
    if(top < 0) {
        printf("stack is empty\n");
        return ('\0');
    }
    else {
        a = stack[top];
        top--;
        return (a);
    }
}
void __push(char k, char s[MAX], int* t_op) {
    if(*t_op + 1 == MAX)
        printf("stack is full\n");
    else {
        *t_op = *t_op + 1;
        s[*t_op] = k;
    }
    return;
}
char __pop(char s[MAX], int* t_op) {
    char a;
    if(*t_op < 0) {
        printf("stack is empty\n");
        return ('\0');
    }
    else {
        a = s[*t_op];
        *t_op = *t_op - 1;
        return (a);
    }
}
struct stack {
    int st[10];
    int tos;
};

int empty(struct stack* s) {
    if(s->tos < 1) {
        return 1;
    }
    else {
        return 0;
    }
}
char popo(struct stack* s) {

    s->tos--;
    return s->st[s->tos];
}

int oparand(char symbol) {
    if(symbol >= '0' && symbol <= '9')
        return 1;
    else
        return 0;
}
void pushu(struct stack* s, char cs) {
    s->st[s->tos] = cs;
    s->tos++;
}
int prec(char ts, char cs) {
    if(ts == '$' && (cs == '*' || cs == '/' || cs == '+' || cs == '-')) {
        return 1;
    }
    else if(ts == '*' && (cs == '*' || cs == '/' || cs == '+' || cs == '-')) {
        return 1;
    }
    else if(ts == '/' && (cs == '*' || cs == '/' || cs == '+' || cs == '-')) {
        return 1;
    }
    else if(ts == '+' && (cs == '+' || cs == '-')) {
        return 1;
    }
    else if(ts == '+' && (cs == '*' || cs == '/' || cs == '$')) {
        return 0;
    }
    else if(ts == '-' && (cs == '*' || cs == '/' || cs == '$')) {
        return 0;
    }
}

void infix_to_postfix(char ifix[], char pstr[]) {
    struct stack s;
    char symbol, ts, cs, temp;
    int i = 0, j = 0, k, l;
    s.tos = 0;

    while(ifix[i] != '\0') {
        symbol = ifix[i];
        if(oparand(symbol)) {
            pstr[j] = symbol;
            j++;
        }
        else {
            cs = ifix[i];
            ts = s.st[s.tos - 1];
            while(!empty(&s) && prec(ts, cs)) {
                temp = popo(&s);
                pstr[j] = temp;
                j++;
            }
            pushu(&s, cs);
        }
        i++;
    }
    while(!empty(&s)) {
        pstr[j] = s.st[s.tos - 1];
        s.tos--;
        j++;
    }
    pstr[j] = '\0';
}

int oprate(int opr1, int opr2, char op) {
    int temp;
    if(op == '+')
        return (opr1 + opr2);
    else if(op == '-')
        return (opr1 - opr2);
    else if(op == '*')
        return (opr1 * opr2);
    else if(op == '/')
        return (opr1 / opr2);
    else {
        temp = pow(opr1, opr2);
        return temp;
    }
}
int ctoi(char t) {
    if(t == '0')
        return 0;
    else if(t == '1')
        return 1;
    else if(t == '2')
        return 2;
    else if(t == '3')
        return 3;
    else if(t == '4')
        return 4;
    else if(t == '5')
        return 5;
    else if(t == '6')
        return 6;
    else if(t == '7')
        return 7;
    else if(t == '8')
        return 8;
    else
        return 9;
}

int eval(char pstr[]) {
    struct stack s;
    int i = 0, opr1, opr2, ans, ans1;
    s.tos = 0;
    while(pstr[i] != '\0') {
        if(!oparand(pstr[i])) {
            opr1 = s.st[s.tos - 2];
            opr2 = s.st[s.tos - 1];
            s.tos = s.tos - 2;
            ans = oprate(opr1, opr2, pstr[i]);
            s.st[s.tos] = ans;
            s.tos++;
            i++;
        }
        else {
            s.st[s.tos] = ctoi(pstr[i]);
            i++;
            s.tos++;
        }
    }
    ans1 = s.st[s.tos - 1];
    return ans1;
}
void alll()

{
    char ifix[12], pstr[12];
    int ans;
    printf("\n Enter the Infix expression:");
    scanf("%s", ifix);
    infix_to_postfix(ifix, pstr);
    printf("Postfix expression is: %s", pstr);
    ans = eval(pstr);
    printf("\n Result of expression is: %d", ans);
    getch();
}

add() {
    printf("Enter how many number you want to add: ");
    scanf("%d", &choice);
    for(i = 0; i < choice; i++) {
        printf("Enter a number: \n");
        scanf("%f", &b);
        a = a + b;
    }
    printf("The addition is %f", a);
    getch();
}
min_() {
    printf("Enter 2 nmber: ");
    scanf("%f%f", &b, &c);
    printf("Subtraction is %f", d);
    d = b - c;
    getch();
}
mul() {
    printf("How many number you want to multipli: ");
    scanf("%d", &choice);
    for(i = 0; i < choice; i++) {
        printf("Enter number: \n");
        scanf("%f", &c);
        m = m * c;
        printf("the result is %f\n", m);
        getch();
    }
}
dib() {
    printf("Enter 2 number");
    scanf("%f%f", &c, &d);
    b = c / d;
    printf("Reult is: %f", b);
    getch();
}

cal() {
    printf("\t\tEnter your choice.\n\tFor--->\n # Addition press 1.\n # Subtraction press 2.\n # Multiplication press 3, and \n # Division press 4.");
    printf("\n\n\t So what u want??? : ");
    scanf("%d", &choice);
    if(choice == 1)
        add();
    else if(choice == 2)
        min_();
    else if(choice == 3)
        mul();
    else if(choice == 4)
        dib();
    else
        printf("Wrong choice\a");
}

char info[500];
COORD coord = { 0, 0 };
COORD max_res, cursor_size;

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while(goal > clock())
        ;
}
int main() {
    system("cls");
    system("color e0");
    int i, j, l, l1, sleep;
    char name[50] = "\n\n\n\n\t\t\t  WELCOME TO OUR PROJECT\n\n";
    printf("\t\n");
    for(i = 0; i < 50; i++) {
        printf("%c", name[i]);
        delay(50);
    }
    printf("\n\t   ");
    for(j = 0; j < 59; j++) {
        printf("%c", 2);
        delay(30);
    }
    printf("\n\n\n\n");
    system("pause");
    system("cls");
    system("color 0f");
    printf("\n\n\n");
    printf("\t\tName Of The Group is.........\n\n\n");
    printf("\n\n\t");
    for(j = 0; j < 6; j++) {
        printf("%c ", 1678);
        delay(50);
    }
    printf(" ARTIFICIAL  INTELLIGENCE  GROUP ");
    for(j = 0; j < 6; j++) {
        printf("%c ", 1678);
        delay(50);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    system("color 1f");
    printf("\n\n\n");
    printf("\tName Of The Group Members Of \n\t\t");
    char ame[10] = "\tA I G :\n\n";
    printf("\t\n");
    for(l1 = 0; l1 < 10; l1++) {
        printf("%c", ame[l1]);
        delay(150);
    }
    printf(" \n\t * ID:  - Group Member Name 01\n\n");
    printf(" \t * ID:  - Group Member Name 02\n\n");
    printf(" \t * ID:  - Group Member Name 03\n\n");
    printf(" \t * ID:  - Group Member Name 04\n\n");
    printf(" \t * ID:  - Group Member Name 05\n\n");
    printf(" \t * ID:  - Group Member Name 06\n");
    printf("\n");
    system("pause");
    system("cls");
    system("color 5e");
    printf("\n\n\n\n\n\n");
    printf("\t\t\tOue project on:\n\n");
    printf("\n");
    char nam[] = "\n\n\t\t\tSmall Calculator (Infix, Prefix, Postfix conversion) \n\n";
    printf("\t\n");
    for(l = 0; l < 59; l++) {
        printf("%c", nam[l]);
        delay(40);
    }
    printf("\n\n\n");
    system("pause");
    system("cls");
    system("color 1a");
    printf("\n\n\n\n\n\n");
    printf("      \t    \t    SMALL CALCULATOR   \n");
    printf("                                                           \n");
    printf("                                                           \n");
    printf("                      \t  Please Wait...\n\n\n\n\n");
    printf("                     ______________ _____________               \n");
    printf("                    /                             \\          \n");
    printf("                   |     Loading.............      |           \n");
    printf("\t\t   |\t");
    for(j = 0; j < 24; j++) {
        printf("%c", 219);
        delay(50);
    }
    printf("   |\n                    \\______________ ______________/           \n");
    printf("                                                           \n");
    printf("\n\n\n");
fst:
    system("pause");
    system("cls");
    system("color c1");
    printf("\n\n\n");
    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1  Main Menu[1]  \xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2  About [2]     \xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2  Simple Calculator[3]\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2  Exit[4]       \xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  ----------  \xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB2\xB1\xB2\xB2\xB1\xB1\xB1\xB2\xB1\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    printf("\n\ntoday is: ");
    tm(); // time call
    printf("\n");
    printf("Enter your key : ");
    float a, b;
    int c, q, i1;
    scanf("%d", &c);
    switch(c) {
        case 1:
            system("pause");
            system("cls");
            system("color b9");
            {
                int opt;
                while(1) {
                    printf("\n\t\tMENU.......");
                    // Sub Menu
                    printf("\n\n");
                    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB1\xB1\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB1\xB2\xB2\xB1\xB1\xB2 1.\xB1Infix to prifix  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2 2.\xB1Infix to postfix**\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2 3.\xB1Prefix to Infix  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2 4.\xB1Postfix to Prefix  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB1\xB1\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2 5.\xB1Postfix to Infix  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB2\xB2\xB1\xB1\xB1\xB1\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB1\xB1\xB2\xB2\xB1\xB1\xB2\xB2\xB1\xB1\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
                    printf("\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
                    printf("\n");
                    printf("Your choice: ");
                    scanf("%d", &opt);
                    switch(opt) {
                        case 1:
                            infxtopr();
                            break;
                        case 2:
                            alll();
                            break;
                        case 3:
                            pre_in();
                            break;
                        case 4:
                            post_pre();
                            break;
                        case 5:
                            post_in();
                            break;
                        default:
                            printf("Invalid choice");
                            break;
                    }
                }
            }

        case 2: // About//
        {
            system("pause");
            system("cls");
            system("color 2f");
            printf("\n\t\t\tThis program was build by---");
            printf("\n\n\t--->www.programmingboss.com----");
            printf("\n\n\t--->Visit for more project----");
            printf("\n\n\t\t---------------------------------------------");
            printf("\n\n\t\t---------------------------------------------\n");
            break;
            goto fst;
        }
        case 3: // calculator//
            system("pause");
            system("cls");
            system("color B1");
            cal();
            getchar();

        case 4: // Exit//
        {
            system("cls");
            system("color 20");
            printf("\n\n\n\t\t-----Good bye-----\n\n (press any key to exit)\n ");
            break;
        }
        default:
            system("color 20");
            printf(" \a\n\t\t\tCode Error\n\a");
    }
    return 0;
}
