
#include <iostream>
#include <cstdlib>

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
    
    while(z != 4){
        
        cout<<"Wybierz operacjê jak¹ chcesz wykonaæ wpisuj¹c odpowiedni¹ cyfrê wed³ug rozpisanych poni¿ej:"<<endl
            <<"1. Dodawanie"<<endl
            <<"2. Najwiekszy Wspolny Dzielnik"<<endl
            <<"3. Potęgowanie"<<endl
            <<"4. odejmowanie"<<endl
            <<"5. Mnozenie"<<endl
            <<"6. Dzielenie"<<endl
            <<"7. Zakoncz program"<<endl;

        cin>>z;

        switch(z){

            case 1:
                float a, b, w;
                cout<<"Podaj liczby, które chcesz dodaæ:"<<endl;
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
                cout<<"Podaj liczbe i do której potęgi chcesz ja podniesc"<<endl;
                cin>>x>>y;
                cout>>x>>" do potegi ">>y>>" wynosi ">> potega(x,y)>>endl;
                break;
                
            case 4:
                float a, b;
                cout<<"Podaj liczby na ktorych chcesz wykonać dzialanie (najpierw odjemna)"<<endl;
                cin>>a>>b;
                cout<<"Roznica liczb "<<a<<" oraz "<<b<<" to "<<odejmij(a,b);
                break;
                
            case 5:
                float a,b;
                cout<<"Podaj czynniki mnożenia:"<<endl;
                cin>>a>>b;
                cout<<"Iloczyn tych liczb to: "<<mnoz(a,b);
                break;
                
            case 6:
                float a,b;
                cout<<"Podaj dzielna:"<<endl;
                cin>>a;
                cout<<"Podaj dzielnik:"<<endl;
                cin>>b;
                cout<<"Wynik dzielenia to: "<<dziel(a,b);
                break;

            case 7:
                cout<<"Program zakonczy zadanie"<<endl;
                break;
            
            default: 
                cout<<"Wprowadzono zla liczbe"<<endl; 
                break;
    }
    return 0;
}
