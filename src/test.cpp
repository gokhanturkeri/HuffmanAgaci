
#include <iostream>
#include <algorithm>
#include <string>
#include <dirent.h> //Klasör içini okumak için kütüphane
#include <fstream>
#include <sstream>
#include "Liste.hpp"
#include "Agac.hpp"
#include "Islem.hpp"
using namespace std;

bool varmi_sonEk(const string& s, const string& sonEk) // Son ek kontrolü yapan fonksiyon
{
    return (s.size() >= sonEk.size()) && equal(sonEk.rbegin(), sonEk.rend(), s.rbegin());    
}

int main(int argc, char **argv)
{
	system("CLS"); //Komut ekranı temizleniyor
	string aranan;	//Aranan kelime değişkeni
	int secenek = 0;
	Liste *LB = NULL; //Heap bölgesinde liste başını tutacak işaretçi tanımlanıyor
	Islem *islemler = new Islem(); //Heap bölgesinde veri yapıları üzerinde işlem yapacak olan nesnemiz oluşturuluyor
    cout << "Dosya Yolu: "; 
    string yol;	//dosya yolu bilgisini tutmak için değişken tanınmanıyor
    getline(cin, yol); //Dosya yolunun girdisi string tipinde kaydediliyor
	DIR *dir = opendir(yol.c_str()); //yol değişkenindeki string girdisi okunuyor ve klasör yolu olarak kaydediliyor
    if(!dir) //Klasör yoksa
    {
        return 1;
    }
    dirent *girdi; //girdi değişkeni oluşturuluyor
    while((girdi = readdir(dir))!=NULL) //dir'e tanımladığımız klasör yolu okunup her bir dosya girdi olarak düşünülüyor
										//Eğer dosya kalmaz ise while döngüsü kapatılacak
    {
        if(varmi_sonEk(girdi->d_name, ".txt")) //Son ek i txt olan bir girdi ise
        {
			if(LB==NULL)
			{
				LB = islemler -> ListeEkle(LB, yol, girdi->d_name); //Liste başı için düğüm oluşturuluyor
			}
			else
			{
				islemler -> ListeEkle(LB, yol, girdi->d_name); //Liste'ye düğüm ekleniyor
			} 
        }
    }
	Liste* temp;	//Liste başının adresini tutacak geçici nesne oluşturuluyor
	temp=LB;
	do{
	cout << "1.Ara" << endl;	//Her düğümün içindeki ağaçları arayıp aranan kelimeyi ve yerini verir.
	cout << "2.Listele" << endl;	//Her düğümün içindeki agaçların düğümlerinde yazan isimleri verir.
	cout << "3.Cikis" << endl;	//Programı kapatır.
	cout << "Secenek: " ;
	cin >> secenek;	//Seçim yapılıyor
	system("CLS");
	switch(secenek)
	{
		
		case 1:
			cout << "Aranan kelime nedir ? :";
			cin >> aranan;	//aranan kelime değişkene kaydediliyor
			while (LB != NULL)	//LB listenin sonuna gelene kadar
			{
				if ((islemler->Ara(aranan, LB->kok)) == true)	//Ara fonksiyonuna parametre olarak aranan kelime ve LB nin 
																//içindeki kök nesnesinin adresi veriliyor
				{
					cout << "Aranan: " << aranan << endl;
					cout << "Aranan kelime " + LB->dosya_adi + " dosyasinin icinde bulunuyor." << endl;
					LB = LB -> pSonraki;	//LB listedeki bir sonraki düğümü gösteriyor
				}
				else
				{
					LB = LB -> pSonraki;	//LB listedeki bir sonraki düğümü gösteriyor
				}
			}
			LB = temp;	//LB ilk düğümü gösterir
			cout << endl;
			break;
		case 2:
			
			while (LB != NULL)	//LB listenin sonuna gelene kadar
			{
				cout << LB ->dosya_adi << " :" << endl;
				islemler->InOrder(LB->kok);	//Arama ağacındaki her bir düğüm yazdırılıyor
				cout << endl;
				LB = LB -> pSonraki;	//LB listedeki bir sonraki düğümü gösteriyor
			}
			LB = temp;	//LB ilk düğümü gösteriyor
			cout << endl;
			break;
			
		case 3:
			break;
		default:
			cout << "Sistemde olmayan secenek" ;
		}
	}
	while(secenek!=3);
    closedir(dir);	//Klasör kapatılıyor
	delete islemler; //islemler nesnesi siliniyor
	delete LB;	//Liste siliniyor
}
