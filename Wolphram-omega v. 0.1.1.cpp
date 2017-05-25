
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

float mnozmacierz(float m1[i][j],float m2[j][k])
{
    float Wynik[i][k];
    for(int m=0;m<i;m++)
        for(int d=0;d<k;d++)
            for(int l=0;l<j;l++)
                Wynik[m][d]+=m1[m][l]*m2[l][d];
    return Wynik;
}
float dodajmacierz(float m1[i][j],float m2[i][j])
{
    for(int r=0;r<i;r++)
        for(int s=0;s<j;s++)
            m1[r][s]+=m2[r][s];
    return m1;
}
float odejmijmacierz(float m1[i][j], float[i][j])
{
    for(int r=0;r<i;r++)
        for(int s=0;s<j;s++)
            m1[r][s]-=m2[r][s];
    return m1;
}
  
float wyznacznikmacierzy( float m[2][2])
{
    float wyznacznik=(m[0][0]*m[1][1])-(m[1][0]*m[0][1]);
    return wyznacznik;
}
int main()
{
    int z;

    while(z != 11){

        cout<<"Wybierz operacje jaka chcesz wykonac wpisujac odpowiednia cyfre wedlug rozpisanych ponizej:"<<endl
            <<"1. Dodawanie"<<endl
            <<"2. Najwiekszy Wspolny Dzielnik"<<endl
            <<"3. Potegowanie"<<endl
            <<"4. odejmowanie"<<endl
            <<"5. Mnozenie"<<endl
            <<"6. Dzielenie"<<endl
            <<"7. Mnozenie macierzy"<<endl
            <<"8. Dodawanie macierzy"<<endl
            <<"9. Odejmowanie macierzy"<<endl
            <<"10. Wyznacznik macierzy 2x2"<<endl
            <<"11. Zakoncz program"<<endl;

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
                int k,l,m,n;
                cout<<"Podaj wymiary macierzy 1.:";
                cin>>k>>l;
                cout<<"Podaj wymiary macierzy 2.:";
                cin>>m>>n;
                if(l!=m){
                    cout<<"Nie można mnozyc";
                    break;
                }
                float mac1[k][l];
                float mac2[m][n];
                cout<<"Podaj elementy macierzy 1.:";
                for(int o=0;i<k;o++)
                    for(int p=0;p<l;p++)
                        cin>>mac1[o][p];
                cout<<"Podaj elementy macierzy 2.:";
                for(o=0;i<m;o++)
                    for(p=0;p<n;p++)
                        cin>>mac2[o][p];
                float wynik[k][n];
                wynik=mnozmacierz(mac1,mac2);
                for(o=0;i<k;o++)
                {
                    for(p=0;p<n;p++)
                        cout<<wynik[o][p];
                    endl;
                }
                break;
            case 8:
                int t,u;
                cout<<"Podaj wymiary macierzy";
                cin>>t>>u;
                float macierz1[t][u];
                float macierz2[t][u];
                cout<<"Podaj elementy macierzy 1.:";
                for(int o=0;o<t;o++)
                    for(int p=0;p<u;p++)
                        cin>>macierz1[o][p];
                cout<<"Podaj elementy macierzy 2.:";
                for(o=0;o<t;o++)
                    for(p=0;p<u;p++)
                        cin>>macierz2[o][p];
                macierz1=dodajmacierz(macierz1, macierz2);
                for(o=0;o<t;o++){
                    for(p=0;p<u;p++)
                        cout<<macierz1[o][p];
                    cout<< endl;
                }
                break;
            case 9:
                int v,w;
                cout<<"Podaj wymiary macierzy";
                cin>>t>>u;
                float macierz1[t][u];
                float macierz2[t][u];
                cout<<"Podaj elementy macierzy 1.:";
                for(int o=0;o<v;o++)
                    for(int p=0;p<w;p++)
                        cin>>macierz1[o][p];
                cout<<"Podaj elementy macierzy 2.:";
                for(o=0;o<v;o++)
                    for(p=0;p<w;p++)
                        cin>>macierz2[o][p];
                macierz1=odejmijmacierz(macierz1, macierz2);
                for(o=0;o<t;o++){
                    for(p=0;p<u;p++)
                        cout<<macierz1[o][p];
                    cout<< endl;
                }
                break;
            case 10:
                int mac[2][2];
                cout<<"Podaj elementy macierzy 2x2:";
                for(o=0;o<2;o++)
                    for(p=0;p<2;p++)
                        cin>>mac[o][p];
                int z=wyznacznikmacierzy(mac);
                cout<<z;
                break;
            case 11:
                cout<<"Program zakonczy zadanie"<<endl;
                break;

            default:
                cout<<"Wprowadzono zla liczbe"<<endl;
                break;
    }
    }
    return 0;
}
