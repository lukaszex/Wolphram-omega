#include <stdio.h>
#include <conio.h>


int n;
float a[100],b[100],c[100];
float x;


float wart(int k)            //wartosc wielomianu
{
if (k==n)
{return b[n];}
else
{return wart(k+1)*x+b[k];}
}

float wspol(int k)           //wspolczynniki wielomianu po podzieleniu
{
if (k==n) {c[k-1]=b[k]; return b[k];}
else {if (k>0) {c[k-1]=wspol(k+1)*x+b[k];} return wspol(k+1)*x+b[k]; }
}

main()
{
int i,j,s;
float tmp;
//clrscr();
printf("Algorytm Hornera - obliczanie wartosci znormalizowanych pochodnych wielomianu\nPodaj stopien wielomianu\n");
scanf("%d", &n);
if (n>100)
{printf("Za duzy stopien wielomianu"); getche(); return(1); }
printf("\nPodaj teraz kolejne wspolczynniki wielomianu.\nZaczynij od tego z najwieksza potega.\n");
for(i=n; i>=0; i--)
{printf("a%d ", i);
scanf("%e", &a[i]);}
printf("Podaj punkt x\n");
scanf("%e", &x);
printf("Podaj stopien pochodnej\n");
scanf("%d", &s);
if ((s<0)||(s>n)) {printf("zle wpisany stopien pochodnej"); getche(); return(1); }

for (i=0; i<=n; i++) {b[i]=a[i];}
for (j=1; j<=s; j++)
{tmp=wspol(0);
for (i=0; i<=n; i++) {b[i]=c[i];}}

printf("Wartosc pochodnej znormalizowanej %d stopnia wynosi: %f",s,wart(0));

getche();
return(0);
}
