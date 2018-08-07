
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Sikistirici.hpp"
#include "Ayiklayici.hpp"
using namespace std;

int main(int argc,char *argv[])
{
	Sikistirici *sikistir;
	Ayiklayici *ayikla;
	string dosya_yolu;
    cout<<"Dosya yolunu giriniz: ";
    cin>>dosya_yolu;
	int secenek;
	system("CLS");
	do{
	cout<<"1. Dosyayi Sikistir" << endl;
	cout<<"2. Sikistirilmis Dosyayi Ekrana Yaz" << endl;
	cout<<"3. Cikis" << endl;
	cout<< "Secenek: ";
	cin >> secenek;
	system("CLS");
	switch(secenek)
	{
		case 1:
		sikistir = new Sikistirici(dosya_yolu);
		//if(remove(dosya_yolu.c_str())!=0)							//txt dosyası siliniyor
        //perror("Error deleting the compressed file:\t");
		break;
	
		case 2:
		ayikla = new Ayiklayici(dosya_yolu + ".bat");
		ayikla->DosyaOku(dosya_yolu);
		//if(remove((dosya_yolu+".bat").c_str())!=0)				//.bat dosyası siliniyor
        //perror("Error deleting the compressed file:\t");
		break;
		
		case 3:
		cout <<"Cikis Yaptiniz";
		break;
		
		default:
		cout << "Sistemde olmayan secenek";
		break;
	}
	}while(secenek!=3);
}