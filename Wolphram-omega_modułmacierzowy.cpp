#include <iostream>
#include <cstdlib>
const int W=4;
const int K=4;
const int R1=2;
using namespace std;
int main ()
{
     int z;
    float Macierz1[W][K];
    float Macierz2[W][K];
    float Macierz3[W][K];
    float macierz[R1][R1];
    int i, j, n;
    float skalar;
    float wyznacznik;
    for(i=0;i<W;i++)
        for(j=0;j<K;j++)
            Macierz3[i][j]=0;
    while(z != 6)
        {
            cout<<"Wybierz operacje jaka chcesz wykonac wpisujac odpowiednia cyfre wedlug rozpisanych ponizej:"<<endl
            <<"1. Mnozenie macierzy"<<endl
            <<"2. Dodawanie macierzy"<<endl
            <<"3. Odejmowanie macierzy"<<endl
            <<"4. Wyznacznik macierzy 2x2"<<endl
            <<"5. Mnozenie macierzy przez skalar"<<endl
            <<"6. Zakoncz program"<<endl;
            cin>>z;
            switch(z){

            case 1:
                cout<< "Wypelnij macierz pierwsza!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                    cin>>Macierz1[i][j];
                cout<<"Wypelnij macierz druga!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        cin>>Macierz2[i][j];
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        for( n=0;n<K;n++)
                            Macierz3[i][j]+=Macierz1[i][n]*Macierz2[n][j];
                for(i=0;i<W;i++)
                    {
                        for(j=0;j<K;j++)
                            cout<<Macierz3[i][j];
                        cout<<endl;
                    }
                break;
            case 2:
                cout<< "Wypelnij macierz pierwsza!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                    cin>>Macierz1[i][j];
                cout<<"Wypelnij macierz druga!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        cin>>Macierz2[i][j];
                for(i=0;i<W;i++)
                    {
                        for(j=0;j<K;j++)
                            cout<<Macierz1[i][j]+Macierz2[i][j];
                        cout<<endl;
                    }
                break;
            case 3:
                cout<< "Wypelnij macierz pierwsza!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                    cin>>Macierz1[i][j];
                cout<<"Wypelnij macierz druga!";
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        cin>>Macierz2[i][j];
                for(i=0;i<W;i++)
                    {
                        for(j=0;j<K;j++)
                            cout<<Macierz1[i][j]-Macierz2[i][j];
                        cout<<endl;
                    }
                break;
            case 4:
                cout<<"Podaj elementy macierzy!"<<endl;
                for(i=0;i<R1;i++)
                    for(j=0;j<R1;j++)
                        cin>>macierz[i][j];
                wyznacznik=(macierz[0][0]*macierz[1][1])-(macierz[0][1]*macierz[1][0]);
                cout<<"Wyznacznik tej macierzy to:"<<wyznacznik;
                break;

            case 5:
                cout<<"Wypelnij macierz!"<<endl;
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        cin>>Macierz1[i][j];
                cout<<"Podaj skalar!";
                cin>>skalar;
                for(i=0;i<W;i++)
                    for(j=0;j<K;j++)
                        Macierz1[i][j]=Macierz1[i][j]*skalar;
                for(i=0;i<W;i++)
                    {
                        for(j=0;j<K;j++)
                            cout<<Macierz1[i][j];
                        cout<<endl;
                    }
                break;
            case 6:
                cout<<"Program zakonczy zadanie"<<endl;
                break;

            default:
                cout<<"Wprowadzono zla liczbe"<<endl;
                break;
        }
    }
    return 0;
}
