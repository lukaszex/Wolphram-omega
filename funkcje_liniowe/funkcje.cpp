#include "funkcje.hpp"

float miejsce_zerowe(const float& a, const float& b){
    return -b/(2*a);
}

float tangens_kata(const float& a, const float& b){
    return a+b;
}

float pochodna(const float& a){
    return a;
}

int funkcje_liniowe(){
    float a, b;
    cout<<"Program do obslugi funkcji liniowej ax+b"<<endl
        <<"Posze podac wspolczynnik a:";
    cin>>a;
    cout<<endl<<"Posze podac wspolczynnik b:";
    cin>>b;
    cout<<endl<<"f: "<<a<<"x+"<<b<<endl;
    int n = 0;
    while(n != 4){
        switch(n){

            case 0:
                cout<<"0.MENU"<<endl
                    <<"1.Oblicz miejsce zerowe funkcji f"<<endl
                    <<"2.Oblicz tangens kata nachylenia wykresu funkcji f do osi OX"<<endl
                    <<"3.Oblicz pochodna funkcji f"<<endl
                    <<"4.Zakoncz program"<<endl;
                cin>>n;
                break;

            case 1:
                cout<<"Miejsce zerowe funkcji f, to: x = "<<miejsce_zerowe(a,b)<<endl;
                n=0;
                break;
            case 2:
                cout<<"Tangens kata nachylenia wykresu funkcji f do osi OX, jest rowny: tg(f) = "<<tangens_kata(a,b)<<endl;
                n=0;
                break;
            case 3:
                cout<<"Pochodna funkcji f, jest rowna: f' = "<<pochodna(a)<<endl;
                n=0;
                break;
            case 4:
                return 0;
                break;
            default:
                cout<<"Podano zla liczbe";
        }
    }
    return 0;
}
