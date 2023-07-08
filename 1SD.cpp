#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
using namespace std;

struct UTM{
    string busena;
    char sim;
    char n_sim;
    string kryptis;
    string n_busena;
};

struct UTM2{
    string busena1;
    string busena2;
    char sim1;
    char sim2;
    char n_sim1;
    char n_sim2;
    string kryptis1;
    string kryptis2;
    string n_busena1;
    string n_busena2;
};

//funkcija nuskaito dokumento turinį
void Skaitymas(string &juosta, int &juostu_sk, int &pozicija, struct UTM utm[], int &n,
string &juosta1, string &juosta2, int &pozicija1, int &pozicija2, struct UTM2 utm2[])
{
    string pav;
    cout << "Iveskite dokumento pavadinima: "; cin >> pav; cout << endl;
    ifstream in(pav);

    if(!in.is_open()){
        cout << "Toks dokumentas neegzistuoja, bandykite ivesti kita dokumento pavadinima." << endl;
        exit(1);
    }

    in >> juostu_sk;

    if(juostu_sk==1){
        in >> juosta;
        in >> pozicija;
        pozicija=pozicija-1;

        int i=0;

        while(!in.eof()){
            in >> utm[i].busena >> utm[i].sim >> utm[i].n_sim >> utm[i].kryptis >> utm[i].n_busena;
            i++;
            n++;
        }
        in.close();
    }

    else if(juostu_sk==2){
        in >> juosta1;
        in >> juosta2;
        in >> pozicija1 >> pozicija2;

        pozicija1=pozicija1-1;
        pozicija2=pozicija2-1;

        int i=0;

        while(!in.eof()){
            in >> utm2[i].busena1 >> utm2[i].sim1 >> utm2[i].sim2 >> utm2[i].n_sim1 >> utm2[i].n_sim2 >> utm2[i].kryptis1 >> utm2[i].kryptis2 >> utm2[i].n_busena1;
            i++;
            n++;
        }
        in.close();

        for(int i=0;i<n;i++){
            utm2[i].busena2=utm2[i].busena1;
            utm2[i].n_busena2=utm2[i].n_busena1;
        }
    }
}

//UTM
void UTM(int juostu_sk, string &juosta, int n, int pozicija, struct UTM utm[], string &juosta1, string &juosta2, int pozicija1, int pozicija2, struct UTM2 utm2[])
{
    bool halt=false;
    string pbusena="0", pbusena1="0", pbusena2="0";
    int yra=-1, yra1=-1, yra2=-1;

    //1 juostos UTM
    if(juostu_sk==1){
        int k=0;
        while(halt!=true){
            system("CLS");
            
            for(int i=0;i<n;i++){
            int m=0;

            if(utm[i].busena==pbusena){
                    if(juosta[pozicija]==utm[i].sim){
                        juosta[pozicija]=utm[i].n_sim;
                        if(utm[i].kryptis=="R") pozicija++;
                        else if(utm[i].kryptis=="L") pozicija--;
                        pbusena=utm[i].n_busena;
                    }
                }

                yra=pbusena.find("halt");
                if(yra>-1){
                    cout << "Masina sustojo sekmingai" << endl;
                    cout << juosta << endl;
                    exit(1);
                }
                
                if(pbusena!=utm[i].busena){
                    for(int j=0;j<n;j++){
                        if(pbusena!=utm[j].busena) m++;
                    }
                }

                if(m==n){
                    cout << "Masina sustojo. Nera taisykliu " << pbusena << " busenai ir " << juosta[pozicija] << " simboliui." << endl;
                    halt=true;
                    break;
                }

                if(pozicija<0 || pozicija>=juosta.length()){
                    cout << "Galvutes pozicija yra uz juostos ribu." << endl;
                    halt=true;
                    break;
                }
                
            }
            
            cout << juosta << endl;
            if(kbhit()){
                cout << "Masina buvo sustabdyta." << endl;
                break;
            }
        } 
    }

    //2 juostu UTM
    if(juostu_sk==2){
        while(halt!=true){
            system("CLS");
        
            for(int i=0;i<n;i++){
                int m1=0, m2=0;

                if(utm2[i].busena1==pbusena1){
                    if(juosta1[pozicija1]==utm2[i].sim1){
                        juosta1[pozicija1]=utm2[i].n_sim1;
                        if(utm2[i].kryptis1=="R") pozicija1++;
                        else if(utm2[i].kryptis1=="L") pozicija1--;
                        pbusena1=utm2[i].n_busena1;
                    }
                }
            
                if(utm2[i].busena2==pbusena2){
                    if(juosta2[pozicija2]==utm2[i].sim2){
                        juosta2[pozicija2]=utm2[i].n_sim2;
                        if(utm2[i].kryptis2=="R") pozicija2++;
                        else if(utm2[i].kryptis2=="L") pozicija2--;
                        pbusena2=utm2[i].n_busena2;
                    }
                }
            
                yra1=pbusena1.find("halt");
                if(yra>-1){
                    cout << "Masina sustojo sekmingai" << endl;
                    cout << juosta1 << endl;
                    exit(1);
                }

                yra2=pbusena2.find("halt");
                if(yra>-1){
                    cout << "Masina sustojo sekmingai" << endl;
                    cout << juosta2 << endl;
                    exit(1);
                }

                if(pbusena1!=utm2[i].busena1){
                    for(int j=0;j<n;j++){
                        if(pbusena1!=utm2[j].busena1) m1++;
                    }
                }

                if(pbusena2!=utm2[i].busena2){
                    for(int j=0;j<n;j++){
                        if(pbusena2!=utm2[j].busena2) m2++;
                    }
                }

                if(m1==n){
                    cout << "Masina sustojo. Nera taisykliu 1-osios juostos " << pbusena1 << " busenai ir " << juosta1[pozicija1] << " simboliui." << endl;
                    halt=true;
                    break;
                }

                if(m2==n){
                    cout << "Masina sustojo. Nera taisykliu 2-osios juostos " << pbusena2 << " busenai ir " << juosta2[pozicija2] << " simboliui." << endl;
                    halt=true;
                    break;
                }

                if(pozicija1<0 || pozicija1>=juosta1.length()){
                    cout << "Galvutes pozicija yra uz 1-osios juostos ribu." << endl;
                    halt=true;
                    break;
                }

                if(pozicija2<0 || pozicija2>=juosta2.length()){
                    cout << "Galvutes pozicija yra uz 2-osios juostos ribu." << endl;
                    halt=true;
                    break;
                }
            }
            cout << juosta1 << endl;
            cout << juosta2 << endl;
            if(kbhit()){
                cout << "Masina buvo sustabdyta." << endl;
                break;
            }
        }
    }
}

int main()
{
    struct UTM utm[100];
    struct UTM2 utm2[100];
    string juosta, juosta1, juosta2;
    int juostu_sk, pozicija, pozicija1, pozicija2, n=0;
    
    Skaitymas(juosta, juostu_sk, pozicija, utm, n, juosta1, juosta2, pozicija1, pozicija2, utm2);
    UTM(juostu_sk, juosta, n, pozicija, utm, juosta1, juosta2, pozicija1, pozicija2, utm2);

    return 0;
}