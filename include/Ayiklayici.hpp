
#ifndef Ayiklayici_HPP
#define Ayiklayici_HPP
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
using namespace std;

class Ayiklayici
{
	

	public:
	struct Dugum			//Huffman ağacının düğüm yapısı oluşturuluyor
		{
		unsigned char karakter;		//Karakter değişkeni oluşturuluyor
		Dugum* sol;						//Düğümün sol çocuğu tanımlanıyor
		Dugum* sag;					//Düğümün sağ çocuğu tanımlanıyor
		Dugum(char c,Dugum* l=NULL,Dugum* r=NULL)		//Parametleri düğüm oluşturuluyor
		{
			karakter=c;
			sol=l;
			sag=r;
		}

		};
	Ayiklayici(string dosya_yolu);
	Dugum* Huffman_Agaci_Yap(ifstream &girdi)
		{
		char ch;
		girdi.get(ch);
		if(ch=='1')
		{
			girdi.get(ch);
			return (new Dugum(ch));
		}
		else
		{
			Dugum* sol=Huffman_Agaci_Yap(girdi);
			Dugum* sag=Huffman_Agaci_Yap(girdi);
			return(new Dugum(-1,sol,sag));
		}
		}
	void Ayikla(ifstream &girdi,string dosya_yolu,Dugum* Kok,long long int Toplam_Frekans);
	void DosyaOku(string dosyaYolu);
};














#endif