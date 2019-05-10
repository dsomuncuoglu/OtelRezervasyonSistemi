#include <iostream>    
#include <string>      //------OTEL REZERVASYON SÝSTEMÝ------//
#include <conio.h>     //---------DENÝZ SOMUNCUOÐLU----------//
#include <fstream>     //-------------172120004--------------//
#include <stdio.h> 
#pragma GCC diagnostic ignored "-Wwrite-strings"  // ([Warning] deprecated conversion from string constant to 'char*' [-Wwrite-strings]) uyarisin kaldirir.  

using namespace std;

class EkleListeleAra{ // EkleListeleAra 1-Temel Class
	protected:
		void ekle(string veri,char *dosyaAdi){ // Ekle Fonksiyonu
		ofstream dosyaYaz(dosyaAdi, ios::app);
		dosyaYaz<< veri << endl;
		dosyaYaz.close();
		}
		void listele(char* dosyaAdi){ // Listele Fonksiyonu
			ifstream dosyaOku;
			dosyaOku.open(dosyaAdi, ios::in);
			if(dosyaOku.is_open()){//Eger dosya acik ise
				string veri;
				while(!dosyaOku.eof()){
					getline(dosyaOku,veri);
					cout << " " + veri << endl;
				}
				dosyaOku.close();
			}else{
				cout << "Dosya bulunamadi.";
			}
		}
		int ara(string aranan,char *dosyaAdi){ // Ara fonksiyonu
			ifstream dosya;
			dosya.open(dosyaAdi, ios::in);
			if(dosya.is_open()){//Eger dosya acik ise
				string veri;
				int satir=0;
				while(!dosya.eof()){
					satir++;
					getline(dosya, veri);
					if(veri.substr(0, (aranan.size()+1)) == aranan+"-"){//arama islemi kac karakter ise ve sonunda "-" olmasina bakar.
						return satir;//aranan islemin kacinci satirda oldugunu dondurur.
					}
				}
				dosya.close();
				return 0;
			}else{
				return 0;
			}
		}
};
class SilGuncelle{ //SilGuncelle 2-Temel Class
	protected:
		void sil(char* dosyaAdi,int satir){
			ifstream dosyaOku;
			char yedek[150]="yedek.txt";
			dosyaOku.open(dosyaAdi, ios::in);
			if(dosyaOku.is_open()){
				ofstream dosya2;
				dosya2.open(yedek,ios::out);
				string veri1;
				int i=0;
				while(!dosyaOku.eof()){
				getline(dosyaOku,veri1);
				i++;
				if(i==satir){
					continue;
				}
				if((veri1!="\0") && (veri1!=" ") && (veri1!="\n")){
					dosya2<<veri1<<endl;
				}
			}
			dosya2.close();
		}
		dosyaOku.close();
		remove(dosyaAdi);
		rename("yedek.txt",dosyaAdi);
	}
		void guncelle(char* dosyaAdi,string yeniVeri ,int satir){
			ifstream dosyaOku;
			char yedek[150]="yedek.txt";
			dosyaOku.open(dosyaAdi, ios::in);
			if(dosyaOku.is_open()){
				ofstream dosya2;
				dosya2.open(yedek,ios::out);
				string veri1;
				int i=0;
				while(!dosyaOku.eof()){
					getline(dosyaOku,veri1);
					i++;
					if(i == satir){
					dosya2 << yeniVeri << endl;	
					}
					else{
						dosya2 << veri1 << endl;
					}
				}
				dosya2.close();
				cout << "Guncelleme islemi basarili" << endl;
			}
			else{
				cout << "Guncelleme islemi yapilamadi" << endl;
			}
	
		
		dosyaOku.close();
		remove(dosyaAdi);
		rename(yedek,dosyaAdi);
	}	
};
class Musteri : virtual public EkleListeleAra,virtual public SilGuncelle{ //EkleListeleAra ve SilGuncelle den turetilmis 3. class
	private:
		string musteriAd,musteriSoyad,musteriNo,musteriTc; 
	public:
		void setMusteriAd(string ad){ // Set MusteriAd
			this->musteriAd = ad;
		}
		void setMusteriSoyad(string soyad){ // Set MusteriSoyad
			this->musteriSoyad = soyad;
		}
		void setMusteriNo(string musterino){ // Set MusteriNo
			this->musteriNo = musterino;
		}
		void setMusteriTc(string Tc){ // Set MusteriTC
			this->musteriTc = Tc;
	    }
	    string getMusteriNo(){ // Get MusteriNo
	    	return this->musteriNo;
		}
		private:
			string getMusteriNoBilgi(){ // Guncelle fonk icine yeni MusteriBilgilerini dondurur.
				return  this->musteriNo + "-" + this->musteriAd + "-" + this->musteriSoyad + "-" + this->musteriTc;
			}
		public:
		void getMusteriNoKontrol(){   //Musteri no kontrolleri(4 haneli,Sayi ve onceki numaralarla cakisiyor mu)
			string tut;
			cin >> tut;
			
			int satir = ara(tut, "musteriler.txt"); // MusteriNo hangi satirda oldugunu
			
			if(satir == 0){ // MusteriNo tekrar etmesi
				if(tut.size() == 4){ // MusteriNo 4 haneli olmasi
					for(int i=0; i < 4; i++){
						
						if ( (tut[i] >= '0') && (tut[i] <= '9') ){ // MusteriNo rakam olmasi
							setMusteriNo(tut);
						}
						else{
							cout << "Musteri numarasi sayidan olusmalidir." << endl << "Musteri No:";
							getMusteriNoKontrol();
							break;
						}
					}
				}
				else{
					cout << "Musteri numarasi 4 haneli olmalidir." << endl << "Musteri No:";
					getMusteriNoKontrol();
				}
			}
			else{
				cout << "Musteri numarasý daha önceden girilmiþ." << endl << "Musteri No:";
				getMusteriNoKontrol();
			}
		}
		void getMusteriTcKontrol(){ // MusteriTc(11 haneli ve sayidan olusmasina)
			string Tc;
			cin >> Tc;
			
				if(Tc.size()==11){ // MusteriTc 11 haneli olmasi
					setMusteriTc(Tc);
					
						for(int i=0; i < 11; i++){ // MusteriTc rakamdan olusmasi
						
						if ( (Tc[i] >= '0') && (Tc[i] <= '9') ){
							setMusteriTc(Tc);
						}
						else{
							cout << "Musteri Tc si sayidan olusmalidir." << endl << "Tc No:";
							getMusteriTcKontrol();
							break;
						}
					}
				}
				else{
					cout << "Tc no 11 haneli olmalidir." << endl << "Tc No:";
					getMusteriTcKontrol();
				}
		}
		void getMusteriAdSoyadKontrol(string kosul){ // Parametreli overloading || Ad-Soyadin harflerden olusmasi
				string tut;
				cin >> tut;
				
					for(int i=0; i < tut.length() ; i++){
						if ( (tut[i] >= 'a' && tut[i] <= 'z') || (tut[i] >= 'A' && tut[i] <= 'Z')){ // MusteriSoyadi harften olusmasi
							if(kosul == "Soyadi"){
						    	setMusteriSoyad(tut);
							}
						}
						else{
								cout << "Musteri " << kosul << " harften olusmalidir." << endl << "Musteri " <<kosul << " :";
								getMusteriAdSoyadKontrol(kosul);
								break;
						}
					}
					
				}
		void getMusteriAdSoyadKontrol(){  // Parametresiz overloading || Ad-Soyadin harflerden olusmasi
				string tut;
				cin >> tut;
				
					for(int i=0; i < tut.length() ; i++){
						if ( (tut[i] >= 'a' && tut[i] <= 'z') || (tut[i] >= 'A' && tut[i] <= 'Z')){ // MusteriAd harften olusmasi
							setMusteriAd(tut);
						}
						else{
								cout << "Musteri Adi harften olusmalidir." << endl << "Musteri Adi:";
								getMusteriAdSoyadKontrol();
								break;
						}
					}
					
				}
		void kontrolRezerveMusteriNo(){ //Rezerve numara kontrolu
			string tut;
			cin >> tut;
			int satir = ara(tut, "musteriler.txt"); // Rezerve ekle ve guncellemede MusteriNo olan satir
			
			if(satir != 0){ // MusteriNo mevcut olmasi
				if(tut.size() == 4){// MusteriNo 4 haneli olmasi
					for(int i=0; i < 4; i++){
						if ( (tut[i] >= '0') && (tut[i] <= '9') ){// MusteriNo rakamlardan olusmasi
							setMusteriNo(tut);
						}
						else{
							cout << "Musteri numarasi sayidan olusmalidir." << endl << "Musteri No:";
							kontrolRezerveMusteriNo();
							break;
						}
					}
				}
				else{
					cout << "Musteri numarasi 4 haneli olmalidir." << endl << "Musteri No:";
					kontrolRezerveMusteriNo();
				}
			}else{
				cout << "Boyle bir musteri numarasi yoktur" << endl << "Musteri no:";
				kontrolRezerveMusteriNo();
			}
			
		}
		
			void musteriEkle(){ // EkleListeleAra dan Ekle fonk cagirir
	    	string musteriBilgisi= this->musteriNo + "-" + this->musteriAd + "-" + this->musteriSoyad + "-" + this->musteriTc;
	    	ekle(musteriBilgisi, "musteriler.txt");
			}
			bool musteri(){ // musteri kontrolu
			int satir=ara(this->musteriNo,"musteriler.txt");
			if(satir!=0){
				return true;
			}else{
				return false;
				}
			}
			void musteriSil(){ // SilGuncelle den Sil fonk cagirir
				cout << "Silinecek musteri no girin=";
				string musteriNo;
				cin >> musteriNo;
			int satir=ara(musteriNo,"musteriler.txt");
				if(satir!=0){
					sil("musteriler.txt", satir); // silme fonk
					cout << "Silme islemi gerceklesti." << endl;
				}
				else{
					cout << "Musteri numarasi bulunamadi" << endl;
				}
			}
			void musteriGuncelle(int satir){ // SilGuncelle den Guncelle fonk cagirir
			guncelle("musteriler.txt", getMusteriNoBilgi(), satir);
			}
			int musteriBilgisiKontrol(){
			cout << "Musteri no: ";
			string no;
			cin >> no;
			int satir=ara(no,"musteriler.txt");
			if(satir!=0){
				return satir;
			}
			else{
				cout << "Musteri bulunamadi." << endl;
				cout << "Tekrar musteri giriniz=";
				musteriBilgisiKontrol();
			}
		}
			void musteriListele(char* dosyaAdi){ // EkleListeleAra dan Listele fonk cagirir
				cout << "\n No -" << " Adi -" << " Soyadi -" << " TC " << endl << endl;
				listele(dosyaAdi);
			}
		
};
class Oda : virtual public EkleListeleAra,virtual public SilGuncelle{ //EkleListeleAra ve SilGuncelle den turetilmis 4. class
	private:
	 string odaNo,odaUcret;
	public:
		void setOdaNo(string odaNumarasi){ // setOdaNo
			this->odaNo = odaNumarasi;
		}
		void setOdaUcret(string odaUcret){ // setOdaUcret
			this->odaUcret = odaUcret;
		}
		string getOdaNo(){ // getOdaNo
			return this->odaNo;
		}
		void getOdaNoKontrol(){   //Oda kontrolleri
			string tut;
			cin >> tut;
			int satir = ara(tut, "odakayit.txt");
			
			if(satir == 0){ // Aranan OdaNo mevcut ise 
				if(tut.size() == 4){ // OdaNo 4 haneli olmasi
					for(int i=0; i < 4; i++){
						
						if ( (tut[i] >= '0') && (tut[i] <= '9') ){ // OdaNo rakamlardan olusmasi
							setOdaNo(tut);
						}
						else{
							cout << "Oda numarasi sayidan olusmalidir." << endl << "Oda No:";
							getOdaNoKontrol();
							break;
						}
					}
				}
				else{
					cout << "Oda numarasi 4 haneli olmalidir." << endl << "Oda No:";
					getOdaNoKontrol();
				}
			}
			else{
				cout << "Oda numarasý daha önceden girilmiþ." << endl << "Oda No:";
				getOdaNoKontrol();
			}
		}
		
		void kontrolRezerveOdaNo(string kosul = ""){ // OdaNo rezervede numara kontrolleri icin kullanilir.
			string tut;
			cin >> tut;
			int satir = ara(tut, "odakayit.txt");
			
			if(satir != 0){ // Eger oda mevcut ise
				if(tut.size() == 4){ // OdaNo 4 haneli olmasi
					for(int i=0; i < 4; i++){
						
						if ( (tut[i] >= '0') && (tut[i] <= '9') ){ // OdaNo rakamdan olusmasi
							
							if(kosul != "sil" && kosul != "guncelle"){ // Fonksiyon cagirilirken hangi islemde calisacagi
								int rezerveSatir = ara(tut, "rezerve.txt");
								
								if(rezerveSatir == 0){ // Rezervede o oda musait mi?
									setOdaNo(tut);
								}else{
									cout << "Bu oda rezerve edilmis tekrar giriniz." << endl << "Oda No:";
									kontrolRezerveOdaNo();
									break;
								}	
							}else{ // Eger sil ve guncelle degerleri yoksa yinede calissin
								setOdaNo(tut);
							}
						}
						else{
							cout << "Oda numarasi sayidan olusmalidir." << endl << "Oda No:";
							kontrolRezerveOdaNo();
							break;
						}
					}
				}
				else{
					cout << "Oda numarasi 4 haneli olmalidir." << endl << "Oda No:";
					kontrolRezerveOdaNo();
				}
			}else{
				cout << "Boyle bir oda numarasi yoktur" << endl << "Oda no:";
				kontrolRezerveOdaNo();
			}
			
		}
		
		private:
			string getOdaBilgisi(){ // Guncelle fonk icine yeni OdaBilgilerini dondurur.
				return this->odaNo + "-" + this->odaUcret;
			}
		public:
		void odaEkle(){ // EkleListeleAra classinda Ekle fonk
			string odaBilgisi=this->odaNo + "-" + this->odaUcret;
			ekle(odaBilgisi,"odakayit.txt");
		}
		void odaListele(char* dosyaAdi){ // EkleListeleAra classinda Listele fonk
			cout << "\n No -" << " Ucret " << endl << endl;
			listele(dosyaAdi);
		}
		bool oda(){ // oda kontrolu
		int satir=ara(this->odaNo,"odakayit.txt");
			if(satir!=0){
				return true;
			}else{
				return false;
			}
		}
		void odaSil(){ // SilGuncelle classinda Sil fonk
			int satir=ara(this->odaNo,"odakayit.txt");
			int satir2=ara(this->odaNo,"rezerve.txt");
				if(satir!=0){
					 if(satir2 !=0){
					 	sil("rezerve.txt", satir2); // Eger oda silinirse Rezervasyon da silinir.
					 	sil("odakayit.txt", satir); // Oda silme fonk
						cout << "Silme islemi gerceklesti." << endl;
						cout << "Bilgi:Bu odanin rezervasyonu vardi. "<< endl;
					}
					else{
						sil("odakayit.txt", satir); // Oda silme fonk
						cout << "Silme islemi gerceklesti." << endl;
					}
				}
				else{
					cout << "Oda numarasi bulunamadi" << endl;
				}
		}
		void odaGuncelle(int satir){ // SilGuncelle classinda Guncelle fonk
			guncelle("odakayit.txt", getOdaBilgisi(), satir);
		}
		int odaBilgisiKontrol(){
			cout << "Oda No: ";
			string no;
			cin >> no;
			int satir=ara(no,"odakayit.txt");
			if(satir!=0){
				return satir;
			}
			else{
				cout << "Oda bulunamadi." << endl;
				cout << "Tekrar oda giriniz=";
				odaBilgisiKontrol();
			}
		}
};
class Rezerve: public Oda, Musteri{ // Oda ve Musteri den turetilmis 5. class
	public:
		Rezerve(){ // Yapici fonk ilk bastaki ekrana yazdirma isini yapiyor.
			cout << endl << endl;
			cout << "   Otel Rezervasyon Sistemi" << endl;
		for(int i=0;i<30;i++){
			cout<< "-";
		}
	        cout << endl;
		    cout << "   1.Oda Islemleri" << endl;
			cout << "   2.Musteri Islemleri" << endl;
			cout << "   3.Rezervasyon Islemleri" << endl;
			cout << "   9.Cikis" << endl;
			cout << "   Seciminizi Girin=";
		}
		~Rezerve(){ // Yikici fonksiyon (Geri cikilirken kullanilir)
			system("cls");
			cout << ".........Geri Cikildi.........";
		}
	private:
			string getRezerveBilgisi(string odaNo,string musteriNo){ 		//classtaki rezerve bilgilerini get ile dondurur.
				return odaNo + "-" + musteriNo;
			}
	public:
		void rezerveEkle(string odaNo, string musteriNo){ // EkleListeleAra classindaki Ekle fonk
			string rezerveBilgileri = odaNo + "-" + musteriNo;
			ekle(rezerveBilgileri, "rezerve.txt");
		}
		void rezerveSil(string rezerveNo){ // SilGuncelle classindaki Sil Fonk
			int satir=ara(rezerveNo , "rezerve.txt");
				if(satir!=0){
					sil("rezerve.txt" , satir); // silme fonk cagirir.
					cout << "Silme islemi gerceklesti." << endl;
				}
				else{
					cout << "Rezervasyon numarasi bulunamadi" << endl;
				}
		}
		
		int rezerveBilgisiKontrol(){ // Girilen OdaNo mevcut mu?
			cout << "Oda No: ";
			string odaNo;
			cin >> odaNo;
			
			int satir = ara (odaNo, "rezerve.txt");
			
			if(satir != 0){
				return satir;
			}
			else{
				cout << "Oda bulunamadi." << endl;
				cout << "Tekrar oda no giriniz=";
				rezerveBilgisiKontrol();
			}
		}

		void rezerveGuncelle(int satir, string odaNo, string musteriNo){ // SilGuncelle classindaki Guncelle Fonk
			string veri = odaNo + "-" + musteriNo;
			guncelle("rezerve.txt", veri, satir);
		}
		
		void rezerveListele(char* dosyaAdi){ // EkleListeleAra classindaki Listele fonk
			cout << "\nOda No-"<< "-Musteri No" << endl << endl;
			listele(dosyaAdi);
		}	
};
int main(){
	system("color 06");// Arka plan rengi ve yazi rengi icin kullanilan kod
	setlocale(LC_ALL,"Turkish"); // Turkce karakter girilmesi icin kullanilan fonksiyon
	
    Musteri m;  	// Musteri Classi
    Oda o;      	// Oda Classi
    Rezerve r; 		// Rezerve class
    
	char secim, devam; // Secim ve secimden sonra devam edip etmiyecegini soran degiskenler.
	
	while(1){
		system("cls"); // ekrani temizler
	    bas1: // goto fonksiyonu ile (GERÝ DONME ÝSLEMÝNÝ) gerceklestirir.
		Rezerve r;	// Yapici Fonksiyon (Ýlk degerleri ekrana basar).
		secim = getche();// Anlik olarak karakter almasina yarayan fonksiyon

		switch(secim){
			case '1' : {
				devam = 'E';
				while(devam == 'E' || devam == 'e'){
					char secim1, devam1;
					system("cls");
					cout << endl << endl; 
				   				 //---------------------------------------1.MENU---------------------------------------
					cout << "   Oda Islemleri" << endl;
					for(int i=0;i<30;i++){
					cout<< "-";
					}
					cout << endl;
		    		cout << "   1.Oda Ekle" << endl;
				    cout << "   2.Oda Sil" << endl;
			 	    cout << "   3.Oda Guncelle" << endl;
			 	    cout << "   4.Oda Listele" << endl;
				    cout << "   9.Geri" << endl;
			 	    cout << "   Seciminizi Girin=";			
		
					secim1 = getche();
					
					switch(secim1){
						case '1' : {	//Oda Ekleme Islemi
							devam1='E';
							while(devam1 == 'E' || devam1 == 'e'){
							system("cls");
							cout << endl << endl;
											 //------------------------------------1.MENU 1.SECENEGÝ------------------------------------
									cout << "Oda Ekleme Islemi" << endl;
									cout << "Oda Numarasi Giriniz=";
									o.getOdaNoKontrol();
									
									//Ucret Girme
									string odaUcret;
									cout << "Oda Ucretini Giriniz=";
									cin >> odaUcret;
									o.setOdaUcret(odaUcret);

									o.odaEkle();
							
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam1=getche();
								
							}
							break;
						}
						case '2' : {  //Oda Silme Islemi
							devam1='E';
							while(devam1 == 'E' || devam1 == 'e'){
							system("cls");
							cout << endl << endl;
		                                          //------------------------------------1.MENU 2.SECENEGÝ------------------------------------
									cout << "Oda Silme Islemi" << endl;
									cout << "Silinecek oda numarasi=";
									string no;
									cin >> no;
									o.setOdaNo(no);
									o.odaSil();
								
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam1=getche();
						}
							break;
						}
						case '3' : {   //Oda Guncelleme Islemi
							devam1='E';
							while(devam1 == 'E' || devam1 == 'e'){
							system("cls");
							cout << endl << endl;
											//------------------------------------1.MENU 3.SECENEGÝ------------------------------------
									cout << "Oda Guncelleme Islemi" << endl;
									int satir=o.odaBilgisiKontrol();
							
								if(satir!=0){
									system("cls");
									cout << "Oda bilgisi bulundu." << endl;
									
									cout << "Oda Numarasi Giriniz=";
									o.getOdaNoKontrol();
									cout << "Oda Ucretini Giriniz=";
									string odaUcret;
									cin >> odaUcret;
									o.setOdaUcret(odaUcret); 
									
									o.odaGuncelle(satir);
								}
							
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam1=getche();
						}
							break;
						}
						case '4' : {//Oda Listeleme Islemi
							system("cls");
							cout << endl << endl;
													//------------------------------------1.MENU 4.SECENEGÝ------------------------------------
									cout << "Oda Listeleme Islemi" << endl;
									o.odaListele("odakayit.txt");
									
							system("pause");
							break;
						}
						
						case '9' : {
									system("cls");
									goto bas1;
									break;
						}
					}
						
		
		
				}
			}
			
			case '2' : {
				system("cls");
				devam = 'E';
				while(devam == 'E' || devam == 'e'){
					char secim2,devam2;
					system("cls");
					cout << endl << endl; 
				    					//---------------------------------------1.MENU---------------------------------------
					cout << "   Musteri Islemleri" << endl;
					for(int i=0;i<30;i++){
					cout<< "-";
					}
					cout << endl;
		    		cout << "   1.Musteri Ekle" << endl;
				    cout << "   2.Musteri Sil" << endl;
			 	    cout << "   3.Musteri Guncelle" << endl;
			 	    cout << "   4.Musteri Listele" << endl;
				    cout << "   9.Geri" << endl;
			 	    cout << "   Seciminizi Girin=";			
		
					secim2 = getche();
					
					switch(secim2){
						case '1' : {	//Musteri Ekleme Islemi
							devam2='E';
							while(devam2 == 'E' || devam2 == 'e'){
							system("cls");
							cout << endl << endl;
 											//------------------------------------2.MENU 1.SECENEGÝ------------------------------------
									cout << "Musteri Ekleme Islemi" << endl;//Musteri ekleme yap
									cout << "Musteri Numarasi Giriniz=";
									m.getMusteriNoKontrol();
									cout << "Musteri Adi Giriniz=";

									m.getMusteriAdSoyadKontrol();
									
									cout << "Musteri Soyadi Giriniz=";
									
									m.getMusteriAdSoyadKontrol("Soyadi");
									
									cout << "Musteri Tc Giriniz=";
									m.getMusteriTcKontrol();
									
									m.musteriEkle();
	
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam2=getche();
								
							}
							break;
						}
						case '2' : {//Musteri Silme Islemi
							devam2='E';
							while(devam2 == 'E' || devam2 == 'e'){
							system("cls");
							cout << endl << endl;
												 //------------------------------------2.MENU 2.SECENEGÝ------------------------------------
									cout << "Musteri Silme Islemi" << endl; // Musteri silme islemi
								    
									m.musteriSil();
									
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam2=getche();
						}
							break;
						}
						case '3' : {//Musteri Guncelleme Islemi
							devam2='E';
							while(devam2 == 'E' || devam2 == 'e'){
							system("cls");
							cout << endl << endl;
											//------------------------------------2.MENU 3.SECENEGÝ------------------------------------
									cout << "Musteri Guncelleme Islemi" << endl;
								
									int satir= m.musteriBilgisiKontrol();
								
									if(satir!=0){
									system("cls");
									cout << "Musterisi bilgisi bulundu." << endl;
									
									cout << "Yeni Musteri Numarasi Giriniz=";
									m.getMusteriNoKontrol();
									cout << "Yeni Musteri Adi Giriniz=";
									m.getMusteriAdSoyadKontrol();
									cout << "Yeni Musteri Soyadi Giriniz=";
									m.getMusteriAdSoyadKontrol("Soyadi");
									cout << "Yeni Musteri Tc si Giriniz=";
									m.getMusteriTcKontrol();
									
									m.musteriGuncelle(satir);
							}
							
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam2=getche();
						}
							break;
						}
						case '4' : { //Musteri Listeleme Islemi
							system("cls");
							cout << endl << endl;
												//------------------------------------2.MENU 4.SECENEGÝ------------------------------------
									cout << "Musteri Listeleme Islemi" << endl;
									m.musteriListele("musteriler.txt");
									
							system("pause");
							break;
						}
						
						case '9' : {
									system("cls");
									goto bas1;
									break;
						}
					}
				}
				system("pause");
				break;
			}
			case '3' : {
				
				system("cls");
				devam = 'E';
				while(devam == 'E' || devam == 'e'){
					char secim3,devam3;
					system("cls");
					cout << endl << endl; 
				    			//---------------------------------------3.MENU---------------------------------------
					cout << "   Rezervasyon Islemleri" << endl;
					for(int i=0;i<30;i++){
					cout<< "-";
					}
					cout << endl;
		    		cout << "   1.Rezervasyon Ekle" << endl;
				    cout << "   2.Rezervasyon Sil" << endl;
			 	    cout << "   3.Rezervasyon Guncelle" << endl;
			 	    cout << "   4.Rezervasyon Listele" << endl;
				    cout << "   9.Geri" << endl;
			 	    cout << "   Seciminizi Girin=";			
		
					secim3 = getche();
					
					switch(secim3){
						case '1' : {			//Rezervasyon Ekleme Islemi 	
							devam3='E';
							while(devam3 == 'E' || devam3 == 'e'){
							system("cls");
							cout << endl << endl;
											//------------------------------------3.MENU 1.SECENEGÝ------------------------------------
									cout << "Rezervasyon Ekleme Islemi" << endl; 
									
									cout << "Oda numarasi:";
									o.kontrolRezerveOdaNo();
									
									cout << "Musteri no:";
									m.kontrolRezerveMusteriNo();
									
									r.rezerveEkle(o.getOdaNo(), m.getMusteriNo());
									
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam3=getche();
							}
							break;
						}
						case '2' : {			// Rezervasyon silme islemi
							devam3='E';
							while(devam3 == 'E' || devam3 == 'e'){
							system("cls");
							cout << endl << endl;
												//------------------------------------3.MENU 2.SECENEGÝ------------------------------------
									cout << "Rezervasyon Silme Islemi" << endl <<"Silinecek rezervasyon icin oda numarasi girin=";
									
									o.kontrolRezerveOdaNo("sil");
									
									r.rezerveSil(o.getOdaNo());
									
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam3=getche();
							}
								break;
						}
						case '3' : {		//Rezervasyon Guncelleme Islemi
							devam3='E';
							while(devam3 == 'E' || devam3 == 'e'){
							system("cls");
							cout << endl << endl;
											//------------------------------------3.MENU 3.SECENEGÝ------------------------------------
									cout << "Rezervasyon Guncelleme Islemi" << endl;
								
									int satir = r.rezerveBilgisiKontrol();
								
									if(satir!=0){
									system("cls");
									cout << "Rezerve bilgisi bulundu." << endl;
									
									cout << "Oda Numarasi Giriniz= ";
									o.kontrolRezerveOdaNo("guncelle");
									
									cout << "Musteri Numarasi Giriniz= ";
									m.kontrolRezerveMusteriNo();
									
									r.rezerveGuncelle(satir, o.getOdaNo(), m.getMusteriNo());								
								}
							cout << "Baska bir islem yapmak istiyor musunuz ";
							devam3=getche();
							}
							break;
						}
						case '4' : {//Rezervasyon Listeleme Islemi	
							system("cls");
							cout << endl << endl;
												//------------------------------------3.MENU 4.SECENEGÝ------------------------------------
									cout << "Rezervasyon Listeleme Islemi" << endl;
									r.rezerveListele("rezerve.txt");
							system("pause");
							break;
						}
						case '9' : {
									system("cls");
									goto bas1;
									break;
						}
					}
				}
			}
			case '9': {
			system("cls");
			cout << "Programdan Cikiliyor...";
			exit(0);
			break;
			}
		}
	}
	return 0;
}



