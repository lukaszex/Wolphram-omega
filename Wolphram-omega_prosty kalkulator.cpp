
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

float dodaj(float a, float b)
{
    return a+b;
}

float odejmij(float a, float b)
{
    return a-b;
}

float mnoz(float a, float b)
{
    return a*b;
}

float dziel(float a, float b)
{
    return a/b;
}

int NWD(int a, int b)
{
   if(a!=b)
     return NWD(a>b?a-b:a,b>a?b-a:b);
   return a;
}

float potega(float a,int b)
{
    float pom=a;
    if (b==0 && a!=0)
    {
        return 1;
    }
    if (b>0)
    {
        for (int i=1;i<b;i++)
           {
               pom*=a;
           }
           return pom;
    }
    if (b<0)
    {
        pom=1/pom;
        return potega(pom,b*(-1));
    }
}


int main()
{
    int z;

    while(z != 7){

        cout<<"Wybierz operacje jaka chcesz wykonac wpisujac odpowiednia cyfre wedlug rozpisanych ponizej:"<<endl
            <<"1. Dodawanie"<<endl
            <<"2. Najwiekszy Wspolny Dzielnik"<<endl
            <<"3. Potegowanie"<<endl
            <<"4. odejmowanie"<<endl
            <<"5. Mnozenie"<<endl
            <<"6. Dzielenie"<<endl
            <<"7. Funkcje trygonometryczne"<<endl
            <<"8. Zakoncz program"<<endl;

        cin>>z;

        switch(z){

            case 1:
                float a, b, w;
                cout<<"Podaj liczby, które chcesz dodac:"<<endl;
                cin>>a>>b;
                w=dodaj(a,b);
                cout<<"Wynik to:"<<w<<endl;
                break;

            case 2:
                int c, d;
                cout<<"Podaj dwie liczby: ";
                cin>>a>>b;
                cout<<"NWD("<<a<<","<<b<<") = "<<NWD(a,b)<<endl;
                break;

            case 3:

                float x;
                int y;
                cout<<"Podaj liczbe i do ktorej potegi chcesz ja podniesc"<<endl;
                cin>>x>>y;
                cout<<x<<" do potegi "<<y<<" wynosi "<< potega(x,y)<<endl;
                break;

            case 4:
                float e, f;
                cout<<"Podaj liczby na ktorych chcesz wykonac dzialanie (najpierw odjemna)"<<endl;
                cin>>e>>f;
                cout<<"Roznica liczb "<<e<<" oraz "<<f<<" to "<<odejmij(e,f);
                break;

            case 5:
                float g,h;
                cout<<"Podaj czynniki mnozenia:"<<endl;
                cin>>g>>h;
                cout<<"Iloczyn tych liczb to: "<<mnoz(g,h)<<endl;
                break;

            case 6:
                float i,j;
                cout<<"Podaj dzielna:"<<endl;
                cin>>i;
                cout<<"Podaj dzielnik:"<<endl;
                cin>>j;
                cout<<"Wynik dzielenia to: "<<dziel(i,j)<<endl;
                break;
            
            case 7:
                float x , i;
                cout<<"Wybierz funkcję"<<endl
                <<"1. sinus"<<endl
                <<"2. cosinus"<<endl
                <<"3. tangens"<<endl
                <<"4. cotangens"<<endl;
                cin>>i;
                cout<<"Wpisz argument"<<endl;
                cin>>x;
                switch (i)
                {
                    case 1:
                        cout<<"Sinus to: "<<sin (x)<<endl;
                        break;
                    case 2:
                        cout<<"Cosinus to: "<<cos (x)<<endl;
                        break;
                    case 3:
                        cout<<"Tangens to: "<<tan (x)<<endl;
                        break;
                    case 4:
                        cout << "Cotangens to: " << 1/(tan (x)) << endl;
                        break;
                }
                
            case 8:
                cout<<"Program zakonczy zadanie"<<endl;
                break;

            default:
                cout<<"Wprowadzono zla liczbe"<<endl;
                break;
    }
    }
    return 0;
}
