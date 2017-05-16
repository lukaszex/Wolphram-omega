#include <iostream>
#include <cstdlib>

using namespace std;

float dodaj(float a, float b)
{
    return a+b;
}

int NWD(int a, int b)
{
   if(a!=b)
     return NWD(a>b?a-b:a,b>a?b-a:b);
   return a;
}

int main()
{
    int z;
    
    while(z != 3){
        
        cout<<"Wybierz operacjê jak¹ chcesz wykonaæ wpisuj¹c odpowiedni¹ cyfrê wed³ug rozpisanych poni¿ej:"<<endl
            <<"1. Dodawanie"<<endl
            <<"2. Najwiekszy Wspolny Dzielnik"<<endl
            <<"3. Zakoncz program"<<endl;

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
                cout<<"Program zakonczy zadanie"<<endl;
                return 0;
                break;
            
            default: 
                cout<<"Wprowadzono zla liczbe"<<endl; 
                break;
    }
    return 0;
}
