#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define PI 3.1
#define WIDTH 20
#define HEIGHT 20
#define LOC 8
#define SLEEP_TIME 380
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define WHTHB "\e[0;107m"
int random1();
int random2();
void print_playground(char playground[WIDTH][HEIGHT], int score[1], int nextshape);
int shapes(char playground[WIDTH][HEIGHT], int t, int c, int score[1], int *current_shape, int *nextshape);
void clear(char playground[WIDTH][HEIGHT], int score[1]);
int gameover(char playground[WIDTH][HEIGHT]);

int main()
{
    char playground[WIDTH][HEIGHT];
    int i, j;

    // Initialize playground with spaces//
    int score[2] = {0, 0};
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            playground[i][j] = ' ';
    }
    /////////////////////////////////////////////////////////////////// GAME MENU ///////////////////////////////////////////////////////////////////////////////////////////
    // Display welcome messages//

    printf(WHT "\n\n\n\t\t\tHello there :)");
    Sleep(2000);
    printf(WHT "\n\n\t\t\tWellcom to the " YEL "Tetris" RED " game.\n\n\n");
    Sleep(2500);
    printf(CYN "\t\t|" YEL "*" CYN "|" WHT "You are in the ancient world! the           " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "persian army needs food in war, there       " CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "is food for 1 soldier inside each block,    " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "when you fill a row with blocks, you        " CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "deliver food to 10 soldiers, the army       " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "needs your help, you determine the result of" CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "the battle!***                              " CYN "|" YEL "*" CYN "|");
    Sleep(13000);

    // Display mission acceptance prompt//
    printf(WHT "\n\n\n ARE YOU ACCEPT THIS MISSION?\n1." GRN "yes\n" WHT "2." RED "no" WHT "\nif you enter wrong key, you betray persian army!!!");
    int choose = getch();

    // Process user's choice
    if (choose == 49)
    {

        int current_shape = random1();

        // game loop //
        while (1)
        {
            int nextshape = random2();
            int s = shapes(playground, 0, 10, score, &current_shape, &nextshape);
            clear(playground, score);

            // Check for game over//
            if (gameover(playground))
            {
                printf("\nGAME OVER!!\n\t\t");
                break;
            }

            // Exit if the user presses Esc//
            if (s == 27)
            {
                break;
            }
            current_shape = nextshape;
            fflush(stdin);
        }

        // Displaying the final score //
        printf(RED "WEll Done! YOUR SCORE IS:" YEL "%d" WHT " press any key to exit. By By :)", score[1]);
        getch();
    }
    if (choose == 50)
    {
        printf(RED "\n\nThe persian army is defeated!!\n\nsee you later");
        getch();
    }
}

/////////////////////////////////////////////////////////////// Function to print the game playground ////////////////////////////////////////////////////////////////////
void print_playground(char playground[WIDTH][HEIGHT], int score[1], int nextshape)
{
    int s = score[1];
    int i, j;

    // Print the top border of the playground //
    printf("\n");
    printf(REDHB "\t\t||||||" YELHB "||" REDHB "|" YELHB "||||||||" REDHB "|" YELHB "||" REDHB "||||||\n");
    printf(RED "\t\t----" YEL "----" RED "----" YEL "----" RED "-----" YEL "-----\n");

    // Print the playground rows //
    for (i = 0; i < 20; i++)
    {

        // Print the left border of each row //
        printf(CYN "\t\t|" YEL "*" CYN "|");
        for (j = 0; j < 20; j++)
        {
            // print playground //
            printf(WHT "%c", playground[i][j]);
        }

        // Print the right border of each row //
        printf(CYN "|" YEL "*" CYN "|\n");
    }

    // Print the bottom border of the playground //
    printf(MAG "\t\t----" YEL "----" MAG "----" YEL "----" MAG "-----" YEL "-----\n");
    printf(YEL "\t\t++++++++++++++++++++++++++\n");

    // Print the score and information about the next shape //
    printf(WHT "\n\t\tscore: %d  press Esc to exit :)\t\t next shape:\t", s);

    // Print the representation of the next shape based on its type //
    switch (nextshape)
    {
    case 0:
        printf(YEL "  []  \n\t\t\t\t\t\t\t\t\t[][][]\n\n");
        break;
    case 1:
        printf(BLU "[][]\n\t\t\t\t\t\t\t\t\t[][]\n\n");
        break;
    case 2:
        printf(GRN "[][][][]\n\n");
        break;
    case 3:
        printf(RED "[][]\n\t\t\t\t\t\t\t\t\t  [][]\n\n");
        break;
    }

    printf(YEL "\t\tPRESS button\n");
}
// Function to generate a random integer within a specified range (0, 1, 2, 3)//
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
// This function is designed to draw different shapes. this function do:
// (move left, move right, move down, stop, quit the game, generate shapes, rotate shapes, speed up and down, and update playground)
int shapes(char playground[WIDTH][HEIGHT], int t, int c, int score[1], int *current_shape, int *nextshape)
{
    int v = 0;
    switch (*current_shape)
    {
    //   []
    // [][][]
    case 0:
    {
        int sit = 1;
        int shape[LOC] = {c, c + 1, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        int f = 0;
        for (t; t < 20; t)
        {
            //   []
            // [][][]
            // number of sit show that what shape status in rotate position //
            if (sit == 1)
            {
                // Handling user input for movement and rotation //
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -8 && playground[t + 1][c - 4 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6 && playground[t + 1][c + 4 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27) // Escape key for exiting the game //
                        return ch;
                    else if (ch == 32) // Space key for changing sit to 2 //
                    {
                        sit = 2;
                    }
                    else if (ch == 's' || ch == 'S') // s key for speed up the game //
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W') // w key for speed down the game //
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13) // Enter key for stop //
                    {
                        getch();
                    }
                }

                // Drawing the shape on the playground //
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
                print_playground(playground, score, *nextshape);

                // Break if reaching the bottom //
                if (t == 19)
                    break;

                // Break if there's an obstacle below the shape //
                if (playground[t + 1][c - 2 + f] != ' ' || playground[t + 1][c + f] != ' ' || playground[t + 1][c + 2 + f] != ' ')
                {
                    break;
                }
                // Clear the previous position of the shape //
                for (int i = 0; i < 8; i += 2)
                {

                    playground[t - 1][shape[i] + f] = ' ';
                    playground[t - 1][shape[i] + 1 + f] = ' ';
                    if (i == 0)
                    {
                        t++;
                    }
                }
                // Delay for animation //
                Sleep(SLEEP_TIME + v);
            }

            // []
            // [][]
            // []

            if (sit == 2)
            {
                t -= 2;
                int shape[LOC] = {c, c + 1, c, c + 1, c + 2, c + 3, c, c + 1};
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -10 && playground[t + 2][c - 2 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6 && playground[t + 1][c + 4 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        if (f > -10)
                            sit = 3;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);

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
                Sleep(SLEEP_TIME + v);
            }
            // [][][]
            //   []
            if (sit == 3)
            {
                int shape[LOC] = {c - 2, c - 1, c, c + 1, c + 2, c + 3, c, c + 1};
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -8 && playground[t][c - 4 + f] == ' ' && playground[t + 2][c - 2 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6 && playground[t + 1][c + 4 + f] == ' ' && playground[t + 2][c + 2 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        sit = 4;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);

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
                Sleep(SLEEP_TIME + v);
            }

            //  []
            //[][]
            //  []
            if (sit == 4)
            {
                int shape[LOC] = {c, c + 1, c - 2, c - 1, c, c + 1, c, c + 1};
                t -= 2;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -8 && playground[t + 1][c - 4 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 8 && playground[t + 2][c + 2 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        if (f < 8)
                            sit = 1;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);

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
                Sleep(SLEEP_TIME + v);
            }
        }
        return 0;
    }

    //[][]
    //[][]
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
                if (ch == 'a' || ch == 'A')
                {
                    if (f > -10 && playground[t + 1][c - 2 + f] == ' ')
                        f -= 2;
                }
                else if (ch == 'd' || ch == 'D')
                {
                    if (f < 6 && playground[t + 1][c + 4 + f] == ' ')
                        f += 2;
                }
                else if (ch == 27)
                    return ch;
                else if (ch == 's' || ch == 'S')
                {
                    if (v == 0 || v == 380)
                    {
                        v = -280;
                    }
                    else
                    {
                        v = 0;
                    }
                }
                else if (ch == 'w' || ch == 'W')
                {
                    if (v == 0 || v == -280)
                    {
                        v = 380;
                    }
                    else
                    {
                        v = 0;
                    }
                }
                else if (ch == 13)
                {
                    getch();
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
            print_playground(playground, score, *nextshape);
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
            Sleep(SLEEP_TIME + v);
        }
        return 0;
    }

    // [][][][]
    case 2:
    {
        int sit = 1;
        int f = 0;
        int shape[LOC] = {c - 4, c - 3, c - 2, c - 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t++)
        {
            // [][][][]
            if (sit == 1)
            {
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -6 && (playground[t + 1][c - 6 + f] == ' '))
                        {
                            f -= 2;
                        }
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6 && (playground[t + 1][c + 4 + f] == ' '))
                        {
                            f += 2;
                        }
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        if (t < 17 && (playground[t + 3][c + 2 + f] == ' '))
                            sit = 2;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
                    }
                }
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                }
                system("cls");
                print_playground(playground, score, *nextshape);
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
                Sleep(SLEEP_TIME + v);
            }

            //[]
            //[]
            //[]
            //[]
            if (sit == 2)
            {
                int shape[LOC] = {c + 2, c + 3, c + 2, c + 3, c + 2, c + 3, c + 2, c + 3};
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -12 && playground[t + 3][c + f] == ' ')
                        {
                            f -= 2;
                        }
                    }
                    else if (ch == 'd' || ch == 'D')
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
                        if (f > -8)
                            sit = 1;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);
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
                Sleep(SLEEP_TIME + v);
                t -= 4;
            }
        }
        return 0;
    }

    //[][]
    //  [][]
    case 3:
    {
        int sit = 1;
        int f = 0;
        int shape[LOC] = {c - 2, c - 1, c, c + 1, c, c + 1, c + 2, c + 3};
        for (t; t < 20; t)
        {
            //[][]
            //  [][]
            if (sit == 1)
            {
                t--;
                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -8)
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6)
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        if (t < 19 && playground[t + 3][c + f] == ' ')
                            sit = 2;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);
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
                Sleep(SLEEP_TIME + v);
            }
            //[]
            //[][]
            //  []
            if (sit == 2)
            {
                int shape[LOC] = {c + 2, c + 3, c, c + 1, c + 2, c + 3, c, c + 1};

                if (_kbhit())
                {
                    char ch = _getch();
                    if (ch == 'a' || ch == 'A')
                    {
                        if (f > -10 && playground[t + 2][c - 2 + f] == ' ')
                            f -= 2;
                    }
                    else if (ch == 'd' || ch == 'D')
                    {
                        if (f < 6 && playground[t + 1][c + 4 + f] == ' ')
                            f += 2;
                    }
                    else if (ch == 27)
                        return ch;
                    else if (ch == 32)
                    {
                        if (f > -10 && playground[t][c - 4 + f] == ' ')
                            sit = 1;
                    }
                    else if (ch == 's' || ch == 'S')
                    {
                        if (v == 0 || v == 380)
                        {
                            v = -280;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 'w' || ch == 'W')
                    {
                        if (v == 0 || v == -280)
                        {
                            v = 380;
                        }
                        else
                        {
                            v = 0;
                        }
                    }
                    else if (ch == 13)
                    {
                        getch();
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
                print_playground(playground, score, *nextshape);
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
                Sleep(SLEEP_TIME + v);
                t -= 2;
            }
        }
        return 0;
    }
    }
}

// Function to clear a line and shift down the above lines //
void clear(char playground[WIDTH][HEIGHT], int score[1])
{
    // Loop through each column in the specified line
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
            // increase score//
            score[1] += 10;
            // Shift down each element above the specified line
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
// this function check the line 1, if there is any blocks, it breaks the main loop and say game over!//
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