#include <iostream>
#include <cstdlib>
using namespace std;
float dodaj(float a, float b)
{
    return a+b;
}
int main()
{
    cout<<"Wybierz operacj� jak� chcesz wykona� wpisuj�c odpowiedni� cyfr� wed�ug rozpisanych poni�ej:"<<endl<<"1 - dodawanie"<<endl;
    int z;
    cin>>z;
    switch(z)
    {
    case 1:
        {
            float a, b, w;
            cout<<"Podaj liczby, kt�re chcesz doda�:"<<endl;
            cin>>a>>b;
            w=dodaj(a,b);
            cout<<"Wynik to:"<<w<<endl;
        }
    }
    return 0;
}
