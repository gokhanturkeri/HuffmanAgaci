
#include "Liste.hpp"
#include "Agac.hpp"
#include "Islem.hpp"
Liste::Liste()	//Kurucu fonksiyon tanımlanır
{	
	kok = NULL;
	pSonraki = NULL;
}
Liste::Liste(string klasor_yolu , string rdosya_adi)	//Parametre alan kurucu fonksiyon
{	
	kok = NULL;
	pSonraki=NULL;
	Islem *islemler2 = new Islem();	//Heap bölgesinde veri yapıları üzerinde işlem yapacak olan nesnemiz oluşturuluyor
	dosya_adi = rdosya_adi; 
	ifstream dosya(klasor_yolu + "\\" + rdosya_adi);	//Okunacak dosyanın yolu ifstream fonksiyonuna veriliyor
	if (dosya) { //Eğer dosya varsa
		string satir, kelime;
		while (getline(dosya, satir)) { //Satırda yazanlar string tipinde kaydediliyor
			istringstream is(satir); //Satır için kontrol
			while (is >> kelime) { //Satırda kelime varsa
				kok = islemler2->agacaEkle(kok, kelime);  // Parametre olarak eklenecek kelime ve ağaç kökünün adresi veriliyor
			}
		}
	}
	dosya.close();	//Dosya kapatılıyor
	delete islemler2; //islemler2 nesnesi siliniyor
}

Liste::~Liste() //Yıkıcı fonksiyon
{
	
	delete kok; //kök nesnesi siliniyor
	
}