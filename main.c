#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#define PI 3.14
int random();
int shapes(char playground[20][20], int t, int c);
void print_playground(char print_playground[20][20]);
int clear(char playground[20][20]);

int main()
{
    char playground[20][20];
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            playground[i][j] = ' ';
    }
    while (1)
    {
        int s = shapes(playground, 0, 10);
        clear(playground);
        if (s == 27)
            break;
    }
}

void print_playground(char playground[20][20])
{
    int i, j;
    printf("\t\t||||||||||||||||||||||||||\n");
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
}

int random()
{
    srand(clock() + time(NULL) + PI);
    return rand() % 4;
}
int shapes(char playground[20][20], int t, int c)
{
    switch (random())
    {
    case 0:
    {
        int shape[8] = {c, c + 1, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        int f = 0;
        for (t; t < 20; t)
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
            print_playground(playground);

            if (t == 19)
                break;

            if (playground[t + 1][8 + f] != ' ' || playground[t + 1][10 + f] != ' ' || playground[t + 1][12 + f] != ' ')
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
            usleep(99999999999);
        }
        return 0;
    }
    case 1:
    {
        int f = 0;
        int shape[8] = {c, c + 1, c + 2, c + 3, c, c + 1, c + 2, c + 3};
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
            print_playground(playground);
            if (t == 19)
                break;

            if (playground[t + 1][10 + f] != ' ' || playground[t + 1][12 + f] != ' ')
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
            usleep(99999999999);
        }
        return 0;
    }

    case 2:
    {
        int f = 0;
        int shape[8] = {c - 4, c - 3, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t++)
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
            }
            for (int i = 0; i < 8; i += 2)
            {
                playground[t][shape[i] + f] = '[';
                playground[t][shape[i] + 1 + f] = ']';
            }
            system("cls");
            print_playground(playground);
            if (t == 19)
                break;

            if (playground[t + 1][6 + f] != ' ' || playground[t + 1][8 + f] != ' ' ||
                playground[t + 1][10 + f] != ' ' || playground[t + 1][12 + f] != ' ')
            {
                break;
            }

            for (int i = 0; i < 8; i += 2)
            {
                playground[t][shape[i] + f] = ' ';
                playground[t][shape[i] + 1 + f] = ' ';
            }
            usleep(99999999999);
        }
        return 0;
    }

    case 3:
    {
        int f = 0;
        int shape[8] = {c - 2, c - 1, c, c + 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t)
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
            print_playground(playground);
            if (t == 19)
                break;
            if (playground[t + 1][10 + f] != ' ' || playground[t + 1][12 + f] != ' ' || playground[t][8 + f] != ' ')
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
            usleep(99999999999);
        }
        return 0;
    }
    }
}

int clear(char playground[20][20])
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