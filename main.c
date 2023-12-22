#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define PI 3.1
#define WIDTH 20
#define HEIGHT 20
#define ROW 2
#define COL 8
#define LOC 8
#define SLEEP_TIME 99999999999
int random1();
int random2();
void next_shape(int *nextshape, char newshape[ROW][COL]);
void print_playground(char print_playground[WIDTH][HEIGHT], int score[1], char newshape[ROW][COL]);
int shapes(char playground[WIDTH][HEIGHT], int t, int c, int score[1], int *current_shape, char newshape[ROW][COL]);
void clear(char playground[WIDTH][HEIGHT], int score[1]);
int gameover(char playground[WIDTH][HEIGHT]);

int main()
{
    char playground[WIDTH][HEIGHT];
    char newshape[ROW][COL];
    int i, j;
    int score[2] = {0, 0};
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            playground[i][j] = ' ';
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 8; j++)
            newshape[i][j] = ' ';
    }

    int current_shape = random1();
    while (1)
    {
        int nextshape = random2();
        next_shape(&nextshape, newshape);
        int s = shapes(playground, 0, 10, score, &current_shape, newshape);
        clear(playground, score);
        if (gameover(playground))
        {
            printf("\nGAME OVER!!");
            break;
        }
        if (s == 27)
        {
            break;
        }
        current_shape = nextshape;
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 8; j++)
                newshape[i][j] = ' ';
        }
    }
    scanf("%d");
}

void print_playground(char playground[WIDTH][HEIGHT], int score[1], char newshape[ROW][COL])
{
    int s = score[1];
    int i, j;
    for (i = 0; i < 2; i++)
    {
        printf("\t\t");
        for (j = 0; j < 8; j++)
        {
            printf("%c", newshape[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\t\t||||||||||||||||||||||||||\tnext shape:\n");
    printf("\t\t--------------------------\n");
    for (i = 0; i < 20; i++)
    {
        printf("\t\t|*|");
        for (j = 0; j < 20; j++)
        {
            printf("%c", playground[i][j]);
        }
        printf("|*|\n");
    }
    printf("\t\t--------------------------\n");
    printf("\t\t++++++++++++++++++++++++++\n");
    printf("\n\t\tscore: %d  press Esc to exit :)\n\n press button:\n", s);
}

int random1()
{
    srand(clock() + time(NULL) + PI);
    return rand() % 4;
}

int random2()
{
    srand(clock() + time(NULL) + PI);
    return rand() % 4;
}

void next_shape(int *nextshape, char newshape[ROW][COL])
{
    switch (*nextshape)
    {
    case 0:
    {
        int t = 0;
        int temp[LOC] = {4, 5, 2, 3, 4, 5, 6, 7};
        for (int i = 0; i < 8; i += 2)
        {
            newshape[t][temp[i]] = '[';
            newshape[t][temp[i] + 1] = ']';
            if (i == 0)
            {
                t++;
            }
        }
        break;
    }
    case 1:
    {
        int t = 0;
        int temp[LOC] = {2, 3, 4, 5, 2, 3, 4, 5};
        for (int i = 0; i < 8; i += 2)
        {
            newshape[t][temp[i]] = '[';
            newshape[t][temp[i] + 1] = ']';
            if (i == 2)
            {
                t++;
            }
        }
        break;
    }
    case 2:
    {
        int t = 0;
        int temp[LOC] = {1, 2, 3, 4, 5, 6, 7, 8};
        for (int i = 0; i < 8; i += 2)
        {
            newshape[t][temp[i]] = '[';
            newshape[t][temp[i] + 1] = ']';
        }
        break;
    }
    case 3:
    {
        int t = 0;
        int temp[LOC] = {1, 2, 3, 4, 3, 4, 5, 6};
        for (int i = 0; i < 8; i += 2)
        {
            newshape[t][temp[i]] = '[';
            newshape[t][temp[i] + 1] = ']';
            if (i == 2)
            {
                t++;
            }
        }
        break;
    }
    }
}

int shapes(char playground[WIDTH][HEIGHT], int t, int c, int score[1], int *current_shape, char newshape[ROW][COL])
{
    switch (*current_shape)
    {
    case 0:
    {
        int sit = 1;
        int shape[LOC] = {c, c + 1, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        int f = 0;
        for (t; t < 20; t)
        {
            if (sit == 1)
            {
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -8)
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 2;
                    }
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 0)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);

                if (t == 19)
                    break;

                if (playground[t + 1][c - 2 + f] != ' ' || playground[t + 1][c + f] != ' ' || playground[t + 1][c + 2 + f] != ' ')
                {
                    break;
                }
                for (int i = 0; i < 8; i += 2)
                {

                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    if (i == 0)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
            }

            if (sit == 2)
            {
                t -= 2;
                int shape[LOC] = {c, c + 1, c, c + 1, c + 2, c + 3, c, c + 1};
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -10)
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 3;
                    }
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 0 || i == 4)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);

                if (t == 19)
                    break;

                if (playground[t + 1][c + f] != ' ' || playground[t][c + 2 + f] != ' ')
                {
                    break;
                }
                for (int i = 0; i < 8; i += 2)
                {

                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    playground[t - 2][shape[i] + f] = ' ';
                    playground[t - 2][shape[i] + 1 + f] = ' ';
                    if (i == 0)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
            }

            if (sit == 3)
            {
                int shape[LOC] = {c - 2, c - 1, c, c + 1, c + 2, c + 3, c, c + 1};
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -8)
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 4;
                    }
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 4)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);

                if (t == 19)
                    break;

                if (playground[t][c - 2 + f] != ' ' || playground[t + 1][c + f] != ' ' || playground[t][c + 2 + f] != ' ')
                {
                    break;
                }
                for (int i = 0; i < 8; i += 2)
                {

                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    if (i == 4)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
            }

            if (sit == 4)
            {
                int shape[LOC] = {c, c + 1, c - 2, c - 1, c, c + 1, c, c + 1};
                t-=2;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -8)
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 8)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 1;
                    }
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 0 || i == 4)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);

                if (t == 19)
                    break;

                if (playground[t][c - 2 + f] != ' ' || playground[t + 1][c + f] != ' ')
                {
                    break;
                }
                for (int i = 0; i < 8; i += 2)
                {

                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    playground[t - 2][shape[i] + f] = ' ';
                    playground[t - 2][shape[i] + 1 + f] = ' ';
                    if (i == 0)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
            }
        }
        return 0;
    }
    case 1:
    {
        int f = 0;
        int shape[LOC] = {c, c + 1, c + 2, c + 3, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t)
        {
            t--;
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == 'a')
                {
                    if (f > -10)
                        f -= 2;
                }
                else if (ch == 'd')
                {
                    if (f < 6)
                        f += 2;
                }
                else if (ch == 27)
                    return ch;
            }

            for (int i = 0; i < 8; i += 2)
            {
                playground[t][shape[i] + f] = '[';
                playground[t][shape[i] + 1 + f] = ']';
                if (i == 2)
                {
                    t++;
                }
            }
            system("cls");
            print_playground(playground, score, newshape);
            if (t == 19)
                break;

            if (playground[t + 1][c + f] != ' ' || playground[t + 1][c + 2 + f] != ' ')
            {
                break;
            }

            for (int i = 0; i < 8; i += 2)
            {
                playground[t - 1][shape[i] + f] = ' ';
                playground[t - 1][shape[i] + 1 + f] = ' ';
                if (i == 2)
                {
                    t++;
                }
            }
            usleep(SLEEP_TIME);
        }
        return 0;
    }

    case 2:
    {
        int sit = 1;
        int f = 0;
        int shape[LOC] = {c - 4, c - 3, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t++)
        {
            if (sit == 1)
            {
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -6)
                        {
                            f -= 2;
                        }
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6)
                        {
                            f += 2;
                        }
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 2;
                    }
                }
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                }
                system("cls");
                print_playground(playground, score, newshape);
                if (t == 19)
                    break;

                if (playground[t + 1][c - 4 + f] != ' ' || playground[t + 1][c - 2 + f] != ' ' ||
                    playground[t + 1][c + f] != ' ' || playground[t + 1][c + 2 + f] != ' ')
                {
                    break;
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = ' ';
                    playground[t][shape[i] + 1 + f] = ' ';
                }
                usleep(SLEEP_TIME);
            }

            if (sit == 2)
            {
                int shape[LOC] = {c + 2, c + 3, c + 2, c + 3, c + 2, c + 3, c + 2, c + 3};
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -12 && playground[t + 3][c + f] == ' ')
                        {
                            f -= 2;
                        }
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6 && playground[t + 3][c + 4 + f] == ' ')
                        {
                            f += 2;
                        }
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 1;
                    }
                }
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 0 || i == 2 || i == 4 || i == 6)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);
                if (t == 20)
                    break;

                if (playground[t][c + 2 + f] != ' ')
                {
                    break;
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    playground[t - 2][shape[i] + f] = ' ';
                    playground[t - 2][shape[i] + 1 + f] = ' ';
                    playground[t - 3][shape[i] + f] = ' ';
                    playground[t - 3][shape[i] + 1 + f] = ' ';
                    playground[t - 4][shape[i] + f] = ' ';
                    playground[t - 4][shape[i] + 1 + f] = ' ';
                }
                usleep(SLEEP_TIME);
                t -= 4;
            }
        }
        return 0;
    }

    case 3:
    {
        int sit = 1;
        int f = 0;
        int shape[LOC] = {c - 2, c - 1, c, c + 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t)
        {
            if (sit == 1)
            {
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -8)
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 2;
                    }
                }
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 2)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);
                if (t == 19)
                    break;
                if (playground[t + 1][c + f] != ' ' || playground[t + 1][c + 2 + f] != ' ' || playground[t][c - 2 + f] != ' ')
                {
                    break;
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    if (i == 2)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
            }

            if (sit == 2)
            {
                int shape[LOC] = {c + 2, c + 3, c, c + 1, c + 2, c + 3, c, c + 1};

                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a')
                    {
                        if (f > -10 && playground[t + 2][c - 2 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd')
                    {
                        if (f < 6 && playground[t + 1][c + 4 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 1;
                    }
                }
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                    if (i == 0 || i == 4)
                    {
                        t++;
                    }
                }
                system("cls");
                print_playground(playground, score, newshape);
                if (t == 19)
                    break;
                if (playground[t + 1][c + f] != ' ' || playground[t][c + 2 + f] != ' ')
                {
                    break;
                }

                for (int i = 0; i < 8; i += 2)
                {
                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    playground[t - 2][shape[i] + f] = ' ';
                    playground[t - 2][shape[i] + 1 + f] = ' ';
                    if (i == 2)
                    {
                        t++;
                    }
                }
                usleep(SLEEP_TIME);
                t -= 2;
            }
        }
        return 0;
    }
    }
}

void clear(char playground[WIDTH][HEIGHT], int score[1])
{
    for (int t = 0; t < 20; t++)
    {
        int count = 0;
        for (int c = 0; c < 20; c += 2)
        {
            if (playground[t][c] != ' ')
                count++;
        }
        int h = t;
        if (count == 10)
        {
            score[1] += 10;
            for (t; t > 0; t--)
            {
                for (int c = 0; c < 20; c++)
                {
                    if (t == h)
                        playground[t][c] = ' ';
                    playground[t][c] = playground[t - 1][c];
                }
            }
        }
    }
}

int gameover(char playground[WIDTH][HEIGHT])
{
    if (playground[0][0] != ' ' || playground[0][2] != ' ' ||
        playground[0][4] != ' ' || playground[0][6] != ' ' || playground[0][8] != ' ' || playground[0][10] != ' ' ||
        playground[0][12] != ' ' || playground[0][14] != ' ' || playground[0][16] != ' ' || playground[0][18] != ' ')
    {
        return 1;
    }
    return 0;
}