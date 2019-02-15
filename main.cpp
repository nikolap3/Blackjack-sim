#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

struct karta
{
    int karakter;
    string suit;
    char simbol;
};

void setcolor(karta dek[],int tk,int b)
{
    switch(b)
    {
    case 0:
        dek[tk].suit="srce";
        break;
    case 1:
        dek[tk].suit="karo";
        break;
    case 2:
        dek[tk].suit="pik";
        break;
    case 3:
        dek[tk].suit="tref";
        break;
    }
    if(b<4)dek[tk].karakter=b;
    if(tk==0)return;
    else
    {
        if(!b)b=4;
        b=b-1;
        setcolor(dek,tk-1,b);
    }
    return;
}

void setnumber (karta dek[],int tk,char i)
{
    if(((int)i<=58 && (int)i>49) || i=='J' || i=='Q' || i=='K' || i=='A')
    {
        dek[tk].simbol=i;
    }
    if(tk==0)return;
    else
    {
        if(((int)i)<58 && (int)i>49)setnumber(dek,tk-1,i+1);
        else if(((int)i)==58)
        {
            setnumber(dek,tk-1,'J');
        }
        else if(i=='J')
        {
            setnumber(dek,tk-1,'Q');
        }
        else if(i=='Q')
        {
            setnumber(dek,tk-1,'K');
        }
        else if(i=='K')
        {
            setnumber(dek,tk-1,'A');
        }
        else if(i=='A')
        {
            setnumber(dek,tk-1,'2');
        }
        else setnumber(dek,tk-1,i+1);
    }
    return;
}

karta izvucikartu(karta dek[],int blocked[],int brblocked)
{
    g:
    int kar=rand() %52;
    for(int i=0;i<brblocked;i++)
    {
        if(blocked[i]==kar)
        {
            goto g;
        }
    }
    blocked[brblocked]=kar;
    return dek[kar];
}

int skor(karta ruka[],int brojkarti)
{
    int sum=0,kec[5],l=0;
    bool lim;
    for(int i=0;i<brojkarti;i++)
    {
        if(ruka[i].simbol=='A')
        {
            kec[l]=i;
            l++;
        }
    }
    for(int i=0;i<brojkarti;i++)
    {
        lim=false;
        for(int j=0;j<l;j++)if(kec[j]==i)
        {
            lim=true;
            break;
        }
        if(!lim)
        {
            if(ruka[i].simbol=='J' || ruka[i].simbol=='Q' || ruka[i].simbol=='K' || ruka[i].simbol==':')sum+=10;
            else sum+=(int)ruka[i].simbol-48;
        }
    }
    if(sum>10)
    {
        sum+=l;
    }
    else if(l>1)
    {
        sum+=9+l;
    }
    else
    {
        sum+=10;
    }
    return sum;
}

string writesim(char sim)
{
    string s;
    if(sim==':')
        return "10";
    else return s+sim;
}

int main()
{
    srand(time(0));
    time_t tstart = clock();
    time_t tstop;
    karta dek[52],tiruka[6],pruka[6];
    int blocked[52]={-1},brojblocked=0,l,tvskor,pskor,vruka=0,vpruka=0;
    bool gameover=false;
    setcolor(dek,52,4);
    setnumber(dek,52,'1');
    for(int i=0;i<2;i++)
    {
        tiruka[i]=izvucikartu(dek,blocked,brojblocked);
        brojblocked++;
        vruka++;
        tvskor=skor(tiruka,vruka);
        pruka[i]=izvucikartu(dek,blocked,brojblocked);
        brojblocked++;
        vpruka++;
    }
    while(!gameover)
    {
        s:
        cout<<"Value of your hand: "<<tvskor<<endl;
        cout<<"Your hand has:"<<endl;
        for(int i=0;i<vruka;i++)cout<<tiruka[i].suit<<" "<<writesim(tiruka[i].simbol)<<endl;
        cout<<"1= Hit , 2=stay"<<endl;
        cin>>l;
        switch(l)
        {
        case 1:
            tiruka[vruka]=izvucikartu(dek,blocked,brojblocked);
            vruka++;
            brojblocked++;
            tvskor=skor(tiruka,vruka);
            if(tvskor>21)
            {
                cout<<"Value of your hand is over 21, you lost"<<endl;
                gameover=true;
                break;
            }
            pruka[vpruka]=izvucikartu(dek,blocked,brojblocked);
            vpruka++;
            brojblocked++;
            pskor=skor(pruka,vpruka);
            if(pskor>21)
            {
                cout<<"Congratulations , you won , The dealer's score is "<<pskor<<endl;
                goto endi;
            }
            else goto s;
            break;
        case 2:
            gameover=true;
            tvskor=skor(tiruka,vruka);
            pskor=skor(pruka,vpruka);
            if(pskor<21)
            {
                if(tvskor>pskor)cout<<"Congratulations , you won , The dealer's score is "<<pskor<<endl;
                else cout<<"Sadly you lost , The dealer's score was "<<pskor<<endl;
            }
            else if(pskor>21)
            {
                cout<<"Congratulations , you won , The dealer's score is "<<pskor<<endl;
            }
            else if(pskor==21)
            {
                if(tvskor==21)
                {
                    int vkarta=0,pkarta=0,mkarta=0;
                    for(int i=0;i<vruka;i++)
                    {
                        switch(tiruka[i].simbol)
                        {
                            case 'K':
                                vkarta=13;
                                break;
                            case 'Q':
                                vkarta=12;
                                break;
                            case 'J':
                                vkarta=11;
                                break;
                            case 'A':
                                vkarta=11;
                                break;
                            case ':':
                                vkarta=10;
                                break;
                            case '9':
                                vkarta=9;
                                break;
                            case '8':
                                vkarta=8;
                                break;
                            case '7':
                                vkarta=7;
                                break;
                            case '6':
                                vkarta=6;
                                break;
                            case '5':
                                vkarta=5;
                                break;
                            case '4':
                                vkarta=4;
                                break;
                            case '3':
                                vkarta=3;
                                break;
                            case '2':
                                vkarta=2;
                                break;
                        }
                        if(vkarta>mkarta)mkarta=vkarta;
                    }
                    for(int i=0;i<vpruka;i++)
                    {
                        switch(pruka[i].simbol)
                        {
                            case 'K':
                                vkarta=13;
                                break;
                            case 'Q':
                                vkarta=12;
                                break;
                            case 'J':
                                vkarta=11;
                                break;
                            case 'A':
                                vkarta=11;
                                break;
                            case ':':
                                vkarta=10;
                                break;
                            case '9':
                                vkarta=9;
                                break;
                            case '8':
                                vkarta=8;
                                break;
                            case '7':
                                vkarta=7;
                                break;
                            case '6':
                                vkarta=6;
                                break;
                            case '5':
                                vkarta=5;
                                break;
                            case '4':
                                vkarta=4;
                                break;
                            case '3':
                                vkarta=3;
                                break;
                            case '2':
                                vkarta=2;
                                break;
                        }
                        if(vkarta>pkarta)pkarta=vkarta;
                    }
                    if(pkarta>mkarta)cout<<"Sadly you lost, i won by having a higher card"<<endl;
                    else cout<<"Congratulations, you won, you had a higher card"<<endl;
                }
                else
                {
                    if(tvskor>pskor)cout<<"Congratulations , you won , The dealer's score is "<<pskor<<endl;
                    else cout<<"Sadly you lost , The dealer's score was "<<pskor<<endl;
                }
            }
            break;
        default:
            cout<<"Invalid value"<<endl;
            goto s;
        }
    }
    endi:
    return 0;
}
