
#ifndef Sikistirici_HPP
#define Sikistirici_HPP

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
using namespace std;
#define Karakter_boyutu 256
class Sikistirici
{
	public:
	Sikistirici(string dosya_yolu);
	struct Dugum						//Huffman ağacının düğüm yapısı oluşturuluyor
{
    unsigned char karakter;				//Karakter değişkeni oluşturuluyor
    long long int Frekans;				//Frekans değişkeni oluşturuluyor
    Dugum* sol;
    Dugum* sag;
    Dugum(unsigned char c,long long int f,Dugum* l=NULL,Dugum* r=NULL)			//Parametreli düğüm oluşturuluyor
    {
        karakter=c;
        Frekans=f;
        sol=l;
        sag=r;
    }
};
void Mindownheap(vector<Dugum*> &A,int i,int uzunluk);
Dugum* Minheap_Ayikla(vector<Dugum*> &A)										//minheap'den karakter ayıklanıyor
{
    if(A.size()<1)
        return NULL;
    Dugum* minimum=A[0];
    A[0]=A.back();
    A.pop_back();
    Mindownheap(A,0,A.size()-1);
    return minimum;
}
void Minheap_Ekle(vector<Dugum*> &A,Dugum* eleman);
void Minheap_Olustur(vector<Dugum*> &A,int uzunluk);
void kod_depolama(Dugum* Kok,char tekil_kod[],int indeks,vector<long long int> &kod_haritasi);
void depo_agaci(ofstream &girdi,Dugum* Kok);
Dugum* Huffman(long long int Sayac[])
{
    vector<Dugum*>minheap;
    for(int i=0;i<Karakter_boyutu;i++)
        if(Sayac[i]!=0)
            minheap.push_back(new Dugum(i,Sayac[i]));
    Minheap_Olustur(minheap,minheap.size()-1);
    while(minheap.size()!=1)
    {
        Dugum* Z=new Dugum(-1,0,Minheap_Ayikla(minheap),Minheap_Ayikla(minheap));
        Z->Frekans=Z->sol->Frekans+Z->sag->Frekans;
        Minheap_Ekle(minheap,Z);
    }
    return(minheap[0]);
}
void Sikistirma(ifstream &girdi,ofstream &cikti,vector<long long int > &kod_haritasi)   ;
};









#endif