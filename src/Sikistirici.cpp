
#include "Sikistirici.hpp"

Sikistirici::Sikistirici(string dosya_yolu)
{
    vector<long long int > kod_haritasi;                                                       //huffman kodlarını tutması için 2 boyutlu vektör tanımlanıyor
    kod_haritasi.resize(Karakter_boyutu);
    long long int Sayac[Karakter_boyutu]={0};                                                  //Karakter sayma dizisi oluşturuluyor
    ifstream girdi_dosyasi(dosya_yolu.c_str(),ios::binary);                                             //girdi stream set ediliyor
    if(!girdi_dosyasi.good())                                                                          //Eğer dosya varsa
    {
        perror("Hata:\t");
        exit(-1);
    }
    cout<<"\n\n ********* Dosya sikistiriliyor *********\n\n";
    char ch;
    while(girdi_dosyasi.get(ch))                                                                       //Dosyayı karakter karakter okuyup sayac dizisinde
    Sayac[static_cast<unsigned char>(ch)]++;											   //karakterin kaç tane olduğunu yazılıyor
    girdi_dosyasi.clear();                                                                             //Dosya işaretçileri sıfırlanıyor
    girdi_dosyasi.seekg(0);                                                                            //Dosya işaretçileri sıfırlanıyor
    Dugum* agac=Huffman(Sayac);                                                                //Huffman ağacı oluşturuluyor
    ofstream cikti_dosyasi((dosya_yolu+".bat").c_str(),ios::binary);                                   //Sıkıştırılmış dosya oluşturuluyor
    if(!cikti_dosyasi.good())                                                                         //Eğer böyle bir dosya varsa
    {
        perror("Hata:\t");
        exit(-1);
    }
    cikti_dosyasi<<agac->Frekans;                                                                      //Dosyaya yazılıyor
    cikti_dosyasi<<',';
    depo_agaci(cikti_dosyasi,agac);
    cikti_dosyasi<<' ';
    char tekil_kod[16];                                                                         //tekil kodları tutması için dizi oluşturuluyor
    kod_depolama(agac,tekil_kod,0,kod_haritasi);                                                //Kodlar vektörde tutuluyor
    Sikistirma(girdi_dosyasi,cikti_dosyasi,kod_haritasi);                                       					//Dosyaya yazılıyor
    girdi_dosyasi.close();                                                                              //Dosya kapatılıyor
    cikti_dosyasi.close();
}

void Sikistirici::Mindownheap(vector<Dugum*> &A,int i,int uzunluk)
{
    int en_dusuk=i;
    if(2*i+1<=uzunluk&&A[2*i+1]->Frekans<A[i]->Frekans)
    {
        en_dusuk=2*i+1;
        if(2*i+2<=uzunluk&&A[2*i+2]->Frekans<A[2*i+1]->Frekans)
            en_dusuk=2*i+2;
    }
    else if(2*i+2<=uzunluk&&A[2*i+2]->Frekans<A[i]->Frekans)
        en_dusuk=2*i+2;
    if(en_dusuk!=i)
    {
        swap(A[i],A[en_dusuk]);
        Mindownheap(A,en_dusuk,uzunluk);
    }
}

void Sikistirici::Minheap_Ekle(vector<Dugum*> &A,Dugum* eleman)										   //minheap'den karakter ekleniyor
{
    A.push_back(eleman);
    int i=A.size()-1;
    while(i>0&&A[(i-1)/2]->Frekans>A[i]->Frekans)
    {
        swap(A[i],A[(i-1)/2]);
        i=(i-1)/2;
    }
}
void Sikistirici::Minheap_Olustur(vector<Dugum*> &A,int uzunluk)										  //minheap oluşturuluyor
{
    for(int i=(uzunluk-1)/2;i>=0;i--)
    {
        Mindownheap(A,i,uzunluk);
    }
}
void Sikistirici::kod_depolama(Dugum* Kok,char tekil_kod[],int indeks,vector<long long int> &kod_haritasi)			//Her karakter için vektöre kodlar depolanıyor
{
    if(Kok->sol)
    {
        tekil_kod[indeks]='0';
        kod_depolama(Kok->sol,tekil_kod,indeks+1,kod_haritasi);

    }
    if(Kok->sag)
    {
        tekil_kod[indeks]='1';
        kod_depolama(Kok->sag,tekil_kod,indeks+1,kod_haritasi);
    }
    if(!Kok->sol&&!Kok->sol)
    {
        for(int i=indeks;i>=0;i--)
        {
          if(i!=indeks)
          {
            kod_haritasi[Kok->karakter]*=10;
            kod_haritasi[Kok->karakter]+=tekil_kod[i]-'0';
          }
          else
            kod_haritasi[Kok->karakter]=1;
        }
    }
}
void Sikistirici::depo_agaci(ofstream &girdi,Dugum* Kok)															 //Ağaç dosyaya yazılıyor
{
    if(!Kok->sol&&!Kok->sag)
    {
        girdi<<'1';
        girdi<<Kok->karakter;
    }
    else
    {
        girdi<<'0';
        depo_agaci(girdi,Kok->sol);
        depo_agaci(girdi,Kok->sag);
    }
}

void Sikistirici::Sikistirma(ifstream &girdi,ofstream &cikti,vector<long long int > &kod_haritasi)   				//Dosya sıkıştırılıp yeni dosyaya yazılıyor
{
    char ch;
    unsigned char bits_8;
    long long int sayac=0;
    while(girdi.get(ch))
    {
        long long int temp=kod_haritasi[static_cast<unsigned char>(ch)];
        while(temp!=1)
        {
          bits_8<<=1;
          if((temp%10)!=0)
                bits_8|=1;
          temp/=10;
          sayac++;
          if(sayac==8)
            {
                cikti<<bits_8;
                sayac=bits_8=0;
            }
        }
    }
    while(sayac!=8)
    {
        bits_8<<=1;
        sayac++;
    }
    cikti<<bits_8;
    cikti.close();
}