#include <stdio.h>
#include <stdlib.h>
void pochodna();
void calka();
int main()
{
    pochodna();
    return 0;
}

void pochodna(void)
{
    int st=0, i=0;
    char wybor;
    printf("Podaj stopien wielomianu\n");
    scanf("%d", &st);
    if(st<0)
    {
        printf("Wpisano nieprawidlowe dane\n");
        printf("Kontynuowac T/N?");
        getchar();
        scanf("%c", &wybor);
        switch (wybor)
        {
        case 't':
            {
                printf("Podaj stopien wielomianu\n");
                scanf("%d", &st);
            }
            break;
        case 'T':
            {
                printf("Podaj stopien wielomianu\n");
                scanf("%d", &st);
            }
        case 'n':
            {
                printf("Zakonczono dzialanie funkcji\n");
                return;
            }
        case 'N':
            {
                printf("Zakonczono dzialanie funkcji\n");
                return;
            }
        }
    }
    int*tab=malloc((st+1)*sizeof(int));
    printf("Teraz wpisuj kolejne wspolczynniki przy potegach, zaczynajac od x^0, x^1 itd...\n");
    for(i=0; i<st+1; i++)
    {
        putchar('\n');
        putchar(':');
        scanf("%d", tab[i]);
        getchar();
    }
    printf("wspolczynniki przy kolejnych potegach:\n");
    for(i=1; i<st; i++)
    {
        printf("%d * x^%d", i*tab[i], i);
    }
    free(tab);
    return;
}
