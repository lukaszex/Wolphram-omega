#include <stdio.h>
#include <math.h>

float wartosc(float x, int stopien, float a[]){ // przyda siê do rysowania
   float result=a[stopien]; int i;
   for(i=stopien-1; i>=0; i--)
      result = result * x + a[i];
   return result;
}

float calka(float x, int stopien, float a[]){
   float result=0; int i;
   for(i=stopien; i>=0; i--)
      result = result * x + a[i]/(i+1);
   return result;
}

int main () {
   const int NMAX=100;
   int stopien, i;
   float a, b, abc[NMAX];

   printf("Podaj stopien wielomianu:\n", NMAX );
   scanf ("%d", &stopien);                         // wyrazów jest stopieñ+1

   for (i=0; i<=stopien; i++) {
      printf(" x^%2d > ",i);      scanf("%f", &abc[i]);
   }

   printf("Podaj gorna granice calkowania:");    scanf("%f", &a);
   printf("Podaj dolna granice calkowania:");    scanf("%f", &b);

   for(i=stopien;i>=0;i--)
      printf("%0.3fx^%d + ",abc[i], i);
   printf("\b\n");
   printf("%0.3f <= x <= %0.3f\n", a, b);

   for(i=stopien;i>=0;i--)
        printf("%0.3fx^%d + ", abc[i]/(i+1), i+1);
   printf("\b C\n");
   printf("Wartosc calki na zadanym przedziale= %f\n", calka(b, stopien, abc) - calka(a, stopien, abc));

   return 0;
}
