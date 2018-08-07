
#include "Islem.hpp"


Liste* Islem::ListeEkle(Liste *pBas, string klasor_yolu, string rdosya_adi)	//Listeye eleman ekleme fonksiyonu
{
	if(pBas != NULL)
	{
		Liste* pY = new Liste(klasor_yolu , rdosya_adi);	//Bağıl liste için düğüm oluşturuluyor
		while (pBas->pSonraki != NULL)	//pBas sona ulaşana kadar
		{
			pBas = pBas->pSonraki;	//pBas bir sonraki düğüm gösteriyor
		}
		pBas->pSonraki = pY;	//pY düğümün sonuna ekleniyor
		pY=NULL;
		return pBas;
	}
	else
	{
		Liste* pY = new Liste(klasor_yolu , rdosya_adi);	//Bağıl liste için düğüm oluşturuluyor
		pBas = pY;	//pBas oluşturulan düğümün adresini gösteriyor
		pY=NULL;
		return pBas;	//Oluşturulan düğümün adresi döndürülüyor
	}
	
}


Agac* Islem::agacaEkle(Agac* kok, string kelime)	//Agaca düğüm ekleme fonksiyonu

{
	//Ağaç boş ise
	if (kok == NULL) {
		kok = new Agac();	//Yeni bir kök oluşturuluyor
		kok->kelime = kelime;	//ilk gelen kelime köke kaydediliyor
	}
	
	else if (kok->kelime == kelime)	//Kökteki kelime ile eklenecek kelime eşleşiyorsa
		return kok;	//kökün adresini döndür
	else if (kontrol(kok->kelime, kelime)) //kökteki kelimeden büyük olup olmadığı kontrol ediliyor
	{	
		if (kok->sag)				//eğer kökun sağ çocuğu varsa
			kok->sag = agacaEkle(kok->sag, kelime);	//agacaEkle fonksiyonuna kökün sağ çocuğunun adresi parametre olarak verilir
		else {				//eğer sağ çocuğu yoksa
			Agac*temp = new Agac();	//geçici nesne oluşturuluyor
			temp->kelime = kelime;
			kok->sag = temp;
			temp=NULL;
			}
	}
	else {			 //kökteki kelimeden küçükse
		if (kok->sol)			//eğer kokun sol çocuğu varsa
			kok->sol = agacaEkle(kok->sol, kelime);	//agacaEkle fonksiyonuna kökün sol çocuğunun adresi parametre olarak veriliyor
		else {			//eğer kökun sağ çocuğu yoksa
			Agac*temp = new Agac();	//geçici nesne oluşturuluyor
			temp->kelime = kelime;
			kok->sol = temp;
			temp=NULL;
		}
	}
	return kok;	//kökün adresini döndüyor
}


bool Islem::kontrol(string a, string b)	//Kontrol fonksiyonu
{
	if (a>b)
		return false;
	return true;
} 


void Islem::InOrder(Agac* dugum)	//inorder sıralama fonksiyonu
{
	if (dugum != NULL) {
		InOrder(dugum->sol);        //Sol taraftaki çocuklar getiriliyor
		cout << dugum->kelime << " ";  //Şuanki düğüm gösteriliyor
		InOrder(dugum -> sag);		//Sağ taraftaki çocuklar getiriliyor
	}
}

bool Islem::Ara(string aranan,Agac* kok)	//Ağaçta kelime arama fonksiyonu
{
	if (kok->kelime == aranan)	// kelime ile parametre olarak verilen düğümdeki kelime aynı ise
	{
		return true;
	}
	else if (kontrol(kok->kelime, aranan))	//	kelime parametre olarak verilen düğümdeki kelimeden büyük ise
	{
		if (kok->sag)	//	kelime parametre olarak verilen düğümün sağ çocuğu varsa
			return Ara(aranan, kok->sag);	//	parametre olarak düğümün sağ çocuğunun adresi veriliyor
		else
			return false;
	}
	else	//	kelime parametre olarak verilen adresteki kelimeden küçük ise
	{
		if (kok->sol)	//	kelime parametre olarak verilen düğümün sol çocuğu varsa
			return Ara(aranan, kok->sol);	//	parametre olarak düğümün sol çocuğunun adresi veriliyor
		else
			return false;
	}
}