#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#define MAX_ITEM 5

char Menu[MAX_ITEM][255] = {
    "0. Cappucino",
    "1. Americano",
    "2. Latte",
    "3. Freeze",
    "4. Matcha",

};
int menuSelection()
{
    int n = 0;
    int index = 0, select;
    while (1)
    {

        printf("-------------------Use w (up)---s (down) to navigate------c to choose-------q to quit------------\n");
        for (int i = 0; i <= MAX_ITEM; ++i)
        {

            if (i == index)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
                printf("%s\n", Menu[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 << 0));
                continue;
            }
            printf("%s\n", Menu[i]);
        }
        switch (n)
        {
        case 'c':
            return index;
        case 'q':
            return -1;
        case 'w':
            index--;
            break;
        case 's':
            index++;
            break;
        }
        if (index > MAX_ITEM - 1)
        {
            index = 0;
        }
        if (index < 0)
        {
            index = 0;
        }
        scanf("%c", &n);
        system("cls");
    }
    return index;
}
int main()
{
    printf("\nYour choice is: %d", menuSelection());
}
