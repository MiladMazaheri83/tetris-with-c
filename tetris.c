#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
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
void printPlayground(char playground[WIDTH][HEIGHT], int score[1], int nextshape);
void shapeProducer(char playground[WIDTH][HEIGHT], int t, int c, int score[1], int *current_shape, int *nextshape);
void clear(char playground[WIDTH][HEIGHT], int score[1]);
bool gameover(char playground[WIDTH][HEIGHT]);
void printWelcome();
void initializePlayground(char playground[WIDTH][HEIGHT]);

void printWelcome()
{
    /////////////////////////////////////////////////////////////////// GAME MENU ///////////////////////////////////////////////////////////////////////////////////////////

    printf(WHT "\n\n\n\t\t\tHello there :)");
    Sleep(2000);
    printf(WHT "\n\n\t\t\tWellcom to the " YEL "Tetris" RED " game.\n\n\n");
    Sleep(2500);
    printf(CYN "\t\t|" YEL "*" CYN "|" WHT "You are in the ancient world! the           " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "persian army needs food in war, there       " CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "is food for 1 soldier inside each block,    " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "when you fill a row with blocks, you        " CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "deliver food to 10 soldiers, the army       " CYN "|" YEL "*" CYN "|\n\t\t|" YEL "*" CYN "|" WHT "needs your help, you determine the result of" CYN "|" YEL "*" CYN "|\n");
    printf("\t\t|" YEL "*" CYN "|" WHT "the battle!***                              " CYN "|" YEL "*" CYN "|");

    // Display mission acceptance prompt//
    printf(WHT "\n\n\n\t ARE YOU ACCEPT THIS MISSION?\n\t1." GRN "yes\n\t" WHT "2." RED "no" WHT);
}

void initializePlayground(char playground[WIDTH][HEIGHT])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
            playground[i][j] = ' ';
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

    printf(YEL "\t\tPRESS Enter To Stop\n\t\tPRESS Esc To Exit\n");
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

/* change shape_situation with space */
void changePos(int *sit, int *pos)
{
    if (*sit == *pos)
    {
        *sit = 1;
    }
    else
    {
        *sit += 1;
    }
}

/* check limit of each shape rotation*/
bool checkLimitShape_0(int *sit, int *delta)
{
    if (*sit == 2)
    {
        if (*delta > -10)
            return true;
        else
            return false;
    }
    else if (*sit == 4)
    {
        if (*delta < 8)
            return true;
        else
            return false;
    }
    return true;
}

bool checkLimitShape_2(char playground[WIDTH][HEIGHT], int *sit, int *delta, int *center, int *t)
{
    if (*sit == 1)
    {
        if (*t < 17 && (playground[*t + 3][*center + 2 + *delta] == ' '))
            return true;
        else
            return false;
    }
    if (*sit == 2)
    {
        if (*delta > -8)
            return true;
        else
            return false;
    }
    return true;
}

bool checkLimitShape_3(char playground[WIDTH][HEIGHT], int *sit, int *delta, int *center, int *t)
{
    if (*sit == 1)
    {
        if (*t < 19 && playground[*t + 3][*center + *delta] == ' ')
            return true;
        else
            return false;
    }
    if (*sit == 2)
    {
        if (*delta > -10 && playground[*t][*center - 4 + *delta] == ' ')
            return true;
        else
            return false;
    }
    return true;
}

/* check rotation limitation*/
bool checkBorder(char playground[WIDTH][HEIGHT], int *sit, int *currentShape, int *delta, int *center, int *t)
{
    switch (*currentShape)
    {
    case 0:
    {
        return checkLimitShape_0(sit, delta);
        break;
    }
    case 1:
    {
        return true;
        break;
    }
    case 2:
    {
        return checkLimitShape_2(playground, sit, delta, center, t);
        break;
    }
    case 3:
    {
        return checkLimitShape_3(playground, sit, delta, center, t);
        break;
    }
    default:
        break;
    }
    return false;
}

void rotate(char playground[WIDTH][HEIGHT], int *sit, int *pos, int *currentShape, int *delta, int *center, int *t)
{
    if (checkBorder(playground, sit, currentShape, delta, center, t))
    {
        changePos(sit, pos);
    }
}
/* control speed of the game*/
void speedUp(int *vlocity)
{
    if (*vlocity == 0 || *vlocity == 380)
    {
        *vlocity = -280;
    }
    else
    {
        *vlocity = 0;
    }
}

void speedDown(int *vlocity)
{
    if (*vlocity == 0 || *vlocity == -280)
    {
        *vlocity = 380;
    }
    else
    {
        *vlocity = 0;
    }
}

/*move shapes to right and left*/
void moveRight(int *sit, char playground[WIDTH][HEIGHT], int *center, int *t, int *delta, int *currentShape)
{
    if ((*currentShape == 0 && *sit == 1) && (*delta < 6 && playground[*t + 1][*center + 4 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 0 && *sit == 2) && (*delta < 6 && playground[*t + 1][*center + 4 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 0 && *sit == 3) && (*delta < 6 && playground[*t + 1][*center + 4 + *delta] == ' ' && playground[*t + 2][*center + 2 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 0 && *sit == 4) && (*delta < 8 && playground[*t + 2][*center + 2 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 1 && *sit == 1) && (*delta < 6 && playground[*t + 1][*center + 4 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 2 && *sit == 1) && (*delta < 6 && (playground[*t + 1][*center + 4 + *delta] == ' ')))
    {
        *delta += 2;
    }
    if ((*currentShape == 2 && *sit == 2) && (*delta < 6 && playground[*t + 3][*center + 4 + *delta] == ' '))
    {
        *delta += 2;
    }
    if ((*currentShape == 3 && *sit == 1) && (*delta < 6))
    {
        *delta += 2;
    }
    if ((*currentShape == 3 && *sit == 2) && (*delta > -10 && playground[*t][*center - 4 + *delta] == ' '))
    {
        *delta += 2;
    }
}

void moveLeft(int *sit, char playground[WIDTH][HEIGHT], int *center, int *t, int *delta, int *currentShape)
{
    if ((*currentShape == 0 && *sit == 1) && (*delta > -8 && playground[*t + 1][*center - 4 + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 0 && *sit == 2) && (*delta > -10 && playground[*t + 2][*center - 2 + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 0 && *sit == 3) && (*delta > -8 && playground[*t][*center - 4 + *delta] == ' ' && playground[*t + 2][*center - 2 + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 0 && *sit == 4) && (*delta > -8 && playground[*t + 1][*center - 4 + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 1 && *sit == 1) && (*delta > -10 && playground[*t + 1][*center - 2 + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 2 && *sit == 1) && (*delta > -6 && (playground[*t + 1][*center - 6 + *delta] == ' ')))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 2 && *sit == 2) && (*delta > -12 && playground[*t + 3][*center + *delta] == ' '))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 3 && *sit == 1) && (*delta > -8))
    {
        *delta -= 2;
    }
    else if ((*currentShape == 3 && *sit == 2) && (*delta > -10 && playground[*t + 2][*center - 2 + *delta] == ' '))
    {
        *delta -= 2;
    }
}

void changeDirection(int *sit, char playground[WIDTH][HEIGHT], int *center, int *t, int *delta, int *vlocity, int *pos, int *currentShape)
{
    if (_kbhit())
    {
        char ch = _getch();
        switch (ch)
        {
        case 'a':
        {
            moveLeft(sit, playground, center, t, delta, currentShape);
        }
        break;
        case 'd':
        {
            moveRight(sit, playground, center, t, delta, currentShape);
        }
        break;
        case ' ':
        {
            rotate(playground, sit, pos, currentShape, delta, center, t);
        }
        break;
        case 's':
        {
            speedUp(vlocity);
        }
        break;
        case 'w':
        {
            speedDown(vlocity);
        }
        break;
        case 27:
        {
            fprintf(stderr, WHT"\n\t\tIm very happy to see you, goodbyyyy!\n");
            Sleep(3900);
            exit(1);
        }
        break;
        case 13:
            getch();

        default:
            break;
        }
    }
}

// This function is designed to draw different shapes. this function do:
// (move left, move right, move down, stop, quit the game, generate shapes, rotate shapes, speed up and down, and update playground)
void shapeProducer(char playground[WIDTH][HEIGHT], int t, int center, int score[1], int *current_shape, int *nextshape)
{
    int v = 0;
    int shapeNumber = *current_shape;
    switch (shapeNumber)
    {
    //   []
    // [][][]
    case 0:
    {
        int sit = 1;
        int pos = 4;
        int shape[LOC] = {center, center + 1, center - 2, center - 1, center, center + 1, center + 2, center + 3};
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
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
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
                if (playground[t + 1][center - 2 + f] != ' ' || playground[t + 1][center + f] != ' ' || playground[t + 1][center + 2 + f] != ' ')
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
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
                int shape[LOC] = {center, center + 1, center, center + 1, center + 2, center + 3, center, center + 1};

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

                if (playground[t + 1][center + f] != ' ' || playground[t][center + 2 + f] != ' ')
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
                int shape[LOC] = {center - 2, center - 1, center, center + 1, center + 2, center + 3, center, center + 1};
                t--;
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);

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

                if (playground[t][center - 2 + f] != ' ' || playground[t + 1][center + f] != ' ' || playground[t][center + 2 + f] != ' ')
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
                int shape[LOC] = {center, center + 1, center - 2, center - 1, center, center + 1, center, center + 1};
                t -= 2;
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);

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

                if (playground[t][center - 2 + f] != ' ' || playground[t + 1][center + f] != ' ')
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
        return;
    }

    //[][]
    //[][]
    case 1:
    {
        int f = 0;
        int pos = 1;
        int sit = 1;
        int shape[LOC] = {center, center + 1, center + 2, center + 3, center, center + 1, center + 2, center + 3};
        for (t; t < 20; t)
        {
            t--;
            changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);

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

            if (playground[t + 1][center + f] != ' ' || playground[t + 1][center + 2 + f] != ' ')
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
        return;
    }

    // [][][][]
    case 2:
    {
        int sit = 1;
        int f = 0;
        int pos = 2;
        int shape[LOC] = {center - 4, center - 3, center - 2, center - 1, center, center + 1, center + 2, center + 3};
        for (t; t < 20; t++)
        {
            // [][][][]
            if (sit == 1)
            {
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
                for (int i = 0; i < 8; i += 2)
                {
                    playground[t][shape[i] + f] = '[';
                    playground[t][shape[i] + 1 + f] = ']';
                }
                system("cls");
                print_playground(playground, score, *nextshape);
                if (t == 19)
                    break;

                if (playground[t + 1][center - 4 + f] != ' ' || playground[t + 1][center - 2 + f] != ' ' ||
                    playground[t + 1][center + f] != ' ' || playground[t + 1][center + 2 + f] != ' ')
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
                int shape[LOC] = {center + 2, center + 3, center + 2, center + 3, center + 2, center + 3, center + 2, center + 3};
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
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

                if (playground[t][center + 2 + f] != ' ')
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
        return;
    }

    //[][]
    //  [][]
    case 3:
    {
        int sit = 1;
        int f = 0;
        int pos = 2;
        int shape[LOC] = {center - 2, center - 1, center, center + 1, center, center + 1, center + 2, center + 3};
        for (t; t < 20; t)
        {
            //[][]
            //  [][]
            if (sit == 1)
            {
                t--;
                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
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
                if (playground[t + 1][center + f] != ' ' || playground[t + 1][center + 2 + f] != ' ' || playground[t][center - 2 + f] != ' ')
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
                int shape[LOC] = {center + 2, center + 3, center, center + 1, center + 2, center + 3, center, center + 1};

                changeDirection(&sit, playground, &center, &t, &f, &v, &pos, &shapeNumber);
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
                if (playground[t + 1][center + f] != ' ' || playground[t][center + 2 + f] != ' ')
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
        return;
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
bool gameover(char playground[WIDTH][HEIGHT])
{
    if (playground[0][0] != ' ' || playground[0][2] != ' ' ||
        playground[0][4] != ' ' || playground[0][6] != ' ' || playground[0][8] != ' ' || playground[0][10] != ' ' ||
        playground[0][12] != ' ' || playground[0][14] != ' ' || playground[0][16] != ' ' || playground[0][18] != ' ')
    {
        return true;
    }
    return false;
}

void menu(char playground[WIDTH][HEIGHT])
{
    // Initialize playground with spaces//
    initializePlayground(playground);
    printWelcome();
}

void run(char playground[WIDTH][HEIGHT], int score[2])
{
    char choose = getch();

    switch (choose)
    {
    case '1':
    {
        int current_shape = random1();

        // game loop //
        while (true)
        {
            int nextshape = random2();
            shapeProducer(playground, 0, 10, score, &current_shape, &nextshape);
            clear(playground, score);

            // Check for game over//
            if (gameover(playground))
            {
                printf("\n\t\tGAME OVER!!\n\t\t");
                break;
            }

            current_shape = nextshape;
            fflush(stdin);
        }

        // Displaying the final score //
        printf(RED "WEll Done! YOUR SCORE IS:" YEL " %d" WHT "\n\t\tpress any key to exit. By By :)", score[1]);
        getch();
    }
    break;
    case '2':
    {
        printf(RED "\n\n\tThe persian army is defeated!!\n\n\tsee you later");
        getch();
    }
    break;
    default:
        run(playground, score);
    }
}

int main()
{
    char playground[WIDTH][HEIGHT];
    int score[2] = {0, 0};
    menu(playground);
    run(playground, score);
}