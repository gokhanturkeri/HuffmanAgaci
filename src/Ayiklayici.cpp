
#include "Ayiklayici.hpp"

Ayiklayici::Ayiklayici(string dosya_yolu)
{
    ifstream girdi_dosyasi(dosya_yolu.c_str(),ios::binary);                                           //Dosya açılıyor
    if(!girdi_dosyasi.good())                                                                        //Eğer dosya açılıyorsa
    {
        perror("Hata:\t");
        exit(-1);
    }
    if(dosya_yolu.find(".bat")==string::npos)                                                     	 //.bat uzantılı dosya aranıyor
    {
        cout<<"Hata: Dosya zaten Ayiklaulmus\n\n";
        exit(-1);
    }
    cout<<"\nDosya Ayiklauluyor";
    long long int Toplam_Frekans=0;
    char ch;
    while(girdi_dosyasi.get(ch))                                                                  //toplam frekans okunuyor
    {
        if(ch==',')
            break;
        Toplam_Frekans*=10;
        Toplam_Frekans+=ch-'0';
    }
    Dugum* huffman_agaci=Huffman_Agaci_Yap(girdi_dosyasi);                                         //Huffman ağacı yeniden yapılandırılıyor
    girdi_dosyasi.get(ch);
    Ayikla(girdi_dosyasi,dosya_yolu,huffman_agaci,Toplam_Frekans);									//Ayikla fonksiyonu çalıştırılıyor
    girdi_dosyasi.close();
	
}


void Ayiklayici::Ayikla(ifstream &girdi,string dosya_yolu,Dugum* Kok,long long int Toplam_Frekans)			//Sıkıştırılmış dosya çözülüyor
{
    ofstream cikti((dosya_yolu.erase(dosya_yolu.size()-4)).c_str(),ios::binary);
    if(!cikti.good())
    {
        perror("Hata:\t");
        exit(-1);
    }
    bool eof_bayragi=false;
    char bits_8;
    Dugum* isaretci=Kok;
    while(girdi.get(bits_8))
    {
        int sayac=7;
        while(sayac>=0)
        {
            if(!isaretci->sol&&!isaretci->sag)
            {
                cikti<<isaretci->karakter;
                Toplam_Frekans--;
                if(!Toplam_Frekans)
                {
                    eof_bayragi=true;
                    break;
                }
                isaretci=Kok;
                continue;
            }
            if((bits_8&(1<<sayac)))
            {
                isaretci=isaretci->sag;
                sayac--;
            }
            else
            {
                isaretci=isaretci->sol;
                sayac--;
            }
        }
        if(eof_bayragi)
            break;
    }
    cikti.close();
}

	void Ayiklayici::DosyaOku(string dosyaYolu)
	{
	string girdi ="";
	string satir;
	ifstream dosya(dosyaYolu.c_str());
	if (dosya.is_open())
	{
		while (getline(dosya,satir))
		{
			girdi+=satir;
			girdi+='\n';
		}
		dosya.close();
		cout<< girdi ;
	}
	else throw "Dosya acilamadi"; 
}