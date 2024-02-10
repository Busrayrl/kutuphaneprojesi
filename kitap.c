#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct kitapbilgi {
    int barkod;
    char kitapAdi[50];
    char yazarAdi[50];
    char yayinEvi[50];
    char kitapTuru[50];
    char teminTuru[50];
    char teminTarih[50];
    int stokSayisi;
    int mevcut;
} kitap;

typedef struct Uye{
	char tc[11];
	char ad[50];
	char Soyad[50];
	char dogumTarihi[20];
	char cinsiyet[10];
	char telefon[11];
	char eposta[30];
	char adres[50];
	char uyeTarihi[20];
	int ID;
	int durum;
} uye;

typedef struct Emanet{
	char uyeTC[20];
	int kitapBarkod;
	time_t teslimTarihi;
	time_t iadeTarihi;
	int kullanacagiGunSayisi;    
    int kullandigiGunSayisi;     
	int gecikmeGunSayisi;
	int durum;
} emanet;
/*
Bu fonksiyon, kullanýcýdan bir dizi bilgi alýr ve bir kitap struct'ý þeklinde kaydeder. Daha sonra, bu struct'ý dosyaya ekler.

kitap struct'ý, barkod numarasý, kitap adý, yazar adý, yayýn evi, kitap türü, temin türü, temin tarihi ve stok sayýsý gibi kitap bilgilerini içerir.

Fonksiyon, kullanýcýdan bu bilgileri sýrayla alýr ve bir kitap structý þeklinde kaydeder. Daha sonra, kitapliste.dat adlý dosyayý açar ve fwrite iþlevi kullanarak kitap struct'ýný dosyaya yazar. Son olarak, dosyayý kapatýr ve kaydýn baþarýlý bir þekilde gerçekleþtirildiðini belirten bir mesaj gösterir.
*/

void KitapEkle() {
    printf("\n\tKitap ekleme\n\n");
    kitap k1;
    printf("\tBarkod      :       "); 
    scanf("%d", &k1.barkod);
    printf("\tKitap Adi   :       "); 
    scanf("%s", k1.kitapAdi);
    printf("\tYazar Adi   :       "); 
    scanf("%s", k1.yazarAdi);
    printf("\tYayin Evi   :       "); 
    scanf("%s", k1.yayinEvi);
    printf("\tKitap Turu  :       "); 
    scanf("%s", k1.kitapTuru);
    printf("\tTemin Turu  :       "); 
    scanf("%s", k1.teminTuru);
    printf("\tTemin Tarihi:       "); 
    scanf("%s", k1.teminTarih);
    printf("\tStok Sayisi :       "); 
    scanf("%d", &k1.stokSayisi);
    
    FILE* ptr = fopen("kitapliste.txt", "a"); 
    
    if (ptr == NULL) {
        printf("Kayit islemi basarili bir sekilde gerceklestirilemedi!");
        return;
    }
    
    fwrite(&k1, sizeof(kitap), 1, ptr); // Kitap bilgisini dosyaya yaz
    fclose(ptr);
    
    printf("\n\tKayit islemi basarili bir sekilde gerceklesti.\n\n");
}

/*
 Dosya iþlemleri kullanýldý. Bu fonksiyon, bir kitap barkod numarasý alýr ve o barkod numarasýna sahip kitabý kitap listesinden siler.

Fonksiyonun içinde kullanýlan kitap struct'ý tanýmlanmamýþ, ancak bu kodun geri kalaný bu struct'ý kullandýðýndan varsayýyorum ki bu struct baþka bir yerde tanýmlanmýþtýr.

Fonksiyon, kullanýcýdan barkod numarasýný alýr, kitapliste.dat adlý dosyayý açar ve fread iþlevini kullanarak dosyayý okur. Eðer dosyada verilen barkod numarasýna sahip bir kitap varsa, bu kitap dosyadan çýkarýlýr ve diðer bir dosyaya (yedekkitapliste.dat) yazýlýr. Eðer dosyada verilen barkod numarasýna sahip bir kitap yoksa, sonuc deðiþkeni sýfýr olarak býrakýlýr ve bir hata mesajý gösterilir.

Daha sonra, remove ve rename iþlevleri kullanýlarak orijinal kitapliste.dat dosyasý silinir ve yeni yedekkitapliste.dat dosyasý orijinal dosyanýn adýný alýr.*/

void KitapSil() {
    printf("\n\tKitap silme\n\n");
     kitap k1;
    int barkod, sonuc = 0;
    printf("\tBarkod  :    ");
    scanf("%d", &barkod);
    
    FILE* ptr = fopen("kitapliste.txt", "r");
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi.\n\n");
        return;
    }

    FILE* xptr = fopen("yedekkitapliste.txt", "wb");
    if (xptr == NULL) {
        printf("\n\tYedek dosya olusturulamadi.\n\n");
        fclose(ptr);
        return;
    }

    while (fread(&k1, sizeof(kitap), 1, ptr) == 1) {
        if (barkod != k1.barkod) {
            fwrite(&k1, sizeof(kitap), 1, xptr);
        } else {
            sonuc = 1;
        }
    }
    fclose(ptr);
    fclose(xptr);
    
    if (sonuc == 0) {
        printf("\n\t%d barkod numarali kitap bulunamadi.\n\n", barkod);
    } else {
        if (remove("kitapliste.txt") == 0 && rename("yedekkitapliste.txt", "kitapliste.txt") == 0) {
            printf("\n\t%d barkod numarali kitap silindi.\n\n", barkod);
        } else {
            printf("\n\tSilme islemi gerceklestirilemedi.\n\n");
        }
    }
}


void KitapListele(){
    printf("\n\tKitap listeleme\n\n");
    
    kitap k1;
    FILE* ptr = fopen("kitapliste.txt", "rb");
    
    if (ptr == NULL) {
        printf("Dosya acilamadi.");
        return;
    }
    
    printf("%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s\n\n",
        "\tBarkod", "Kitap Adi", "Yazar Adi", "Yayin Evi",
        "Kitap Turu", "Temin Turu", "Temin Tarihi", "Stok Sayisi"
    );
    
    while (fread(&k1, sizeof(kitap), 1, ptr)) {
        printf("\t%-20d-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20d\n\n",
            k1.barkod, k1.kitapAdi, k1.yazarAdi, k1.yayinEvi,
            k1.kitapTuru, k1.teminTuru, k1.teminTarih, k1.stokSayisi
        );
    }
    
    fclose(ptr);
}


  

void KitapGuncelle() {
    FILE* ptr;
    kitap k1;
    int bulundu=0;
    
    int barkod;
    printf("\n\tGuncellenecek kitabin barkod numarasini giriniz:");
    scanf("%d",&barkod);
    ptr = fopen("kitapliste.txt", "rb+");
    if (ptr == NULL) {
        printf("\tDosya acilamadi!\n");
        return;
    }

    while (fread(&k1, sizeof(kitap), 1, ptr)) { 
        if (k1.barkod == barkod) {//mevcut kitap kaydýnýn barkod numarasýnýn aranan barkod numarasýna eþit olup olmadýðýný kontrol eder.
            bulundu = 1;
            printf("\n\tKitap bilgileri:\n\n");
            printf("\tBarkod      :       %d\n", k1.barkod);
            printf("\tKitap Adi   :       %s\n", k1.kitapAdi);
            printf("\tYazar Adi   :       %s\n", k1.yazarAdi);
            printf("\tYayin Evi   :       %s\n", k1.yayinEvi);
            printf("\tKitap Turu  :       %s\n", k1.kitapTuru);
            printf("\tTemin Turu  :       %s\n", k1.teminTuru);
            printf("\tTemin Tarihi:       %s\n", k1.teminTarih);
            printf("\tStok Sayisi :       %d\n", k1.stokSayisi);

            printf("\n\tGuncelleme yapmak icin yeni bilgileri girin:\n\n");
            printf("\tKitap Adi   :       "); 
            scanf("%s", k1.kitapAdi);
            printf("\tYazar Adi   :       "); 
            scanf("%s", k1.yazarAdi);
            printf("\tYayin Evi   :       "); 
            scanf("%s", k1.yayinEvi);
            printf("\tKitap Turu  :       "); 
            scanf("%s", k1.kitapTuru);
            printf("\tTemin Turu  :       "); 
            scanf("%s", k1.teminTuru);
            printf("\tTemin Tarihi:       "); 
            scanf("%s", k1.teminTarih);
            printf("\tStok Sayisi :       "); 
            scanf("%d", &k1.stokSayisi);

            fseek(ptr, -sizeof(kitap), SEEK_CUR); 
            fwrite(&k1, sizeof(kitap), 1, ptr); // yeni kitap bilgilerini dosyaya yazar. 
            printf("\n\tGuncelleme islemi basariyla gerceklesti.\n\n");
            break;
        }
    }

    if (!bulundu) {
        printf("\n\tAradiginiz barkoda sahip kitap bulunamadi!\n\n");
    }

    fclose(ptr);//dosyayý kapatýr.

}


void KitapIslemleri() {
	system("cls");
 
    printf("\t\t\t\t\t***KITAP ISLEMLERI***\n\n");
    int tercih;
    printf("\t1-Kitap Ekle \n");
    printf("\t2-Kitap sil \n");
    printf("\t3-Kitap Listele \n");
    printf("\t4-Kitap Guncelle \n");
    printf("\t0-Ana Menuye Don \n\n");
    printf("\tLutfen yapacaginiz islemi seciniz:");

    scanf("%d", &tercih);

    switch (tercih) {
        case 1:
            KitapEkle();
            break;
        case 2:
            KitapSil();
            break;
        case 3:
            KitapListele();
            break;
        case 4:
            KitapGuncelle();
            break;
        case 0:
            break;
        default:
            printf("\n\tHatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\a\n");
            
          break;
    }
}

  void  UyeEkle()
{
	system("cls");

	printf("\n\tUye ekleme\n\n");
    uye k1;
    printf("\tTC             :       "); 
    scanf("%s", k1.tc);
    printf("\tAd             :       "); 
    scanf("%s", k1.ad);
    printf("\tSoyad          :       "); 
    scanf("%s", k1.Soyad);
    printf("\tDogum Tarihi   :       "); 
    scanf("%s", k1.dogumTarihi);
    printf("\tCinsiyet       :       "); 
    scanf("%s", k1.cinsiyet);
    printf("\tTelefon        :       "); 
    scanf("%s", k1.telefon);
    printf("\tE-Posta        :       "); 
    scanf("%s", k1.eposta);
    printf("\tAdres          :       "); 
    scanf("%s", k1.adres);
    printf("\tUyelik Tarihi  :       "); 
    scanf("%s", k1.uyeTarihi);


    FILE* ptr = fopen("uyeliste.txt","a+b"); //w+b di
    if (ptr == NULL) {
        printf("\n\tKayit islemi basarili bir sekilde gerçeklesmedi!\n\n");
        return;
    }

    fwrite(&k1, sizeof(uye), 1, ptr);
    fclose(ptr);
    printf("\n\tKayit islemi basarili bir sekilde gerceklesti.\n\n");
}


void UyeSil()
{
    printf("\n\tUye Sil\n\n");

    uye u1;
    int sonuc = 0;
    char tc[11]; 
    printf("\tTC    :    ");
    scanf("%s", tc);

    FILE* ptr = fopen("uyeliste.txt", "rb");
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi.\n\n");
        return;
    }

    FILE* xptr = fopen("yedekuyeliste.txt", "wb");
    if (xptr == NULL) {
        printf("\n\tYedek dosya olusturulamadi.\n\n");
        fclose(ptr);
        return;
    }

    while (fread(&u1, sizeof(uye), 1, ptr) == 1) {
        if (strcmp(tc, u1.tc) != 0) {
            fwrite(&u1, sizeof(uye), 1, xptr);
        } else {
            sonuc = 1;
        }
    }

    fclose(ptr);
    fclose(xptr);

    if (sonuc == 0) {
        printf("\n\t%s TC numarali uye bulunamadi.\n\n", tc);
    } else {
        if (remove("uyeliste.txt") == 0 && rename("yedekuyeliste.txt", "uyeliste.txt") == 0) {
            printf("\n\t%s TC numarali uye kaydi basarili bir sekilde silindi.\n\n", tc);
        } else {
            printf("\n\tSilme islemi gerceklestirilemedi.\n\n");
        }
    }
}
	
	
	

void UyeListele()
{
    printf("\n\tUye Listeleme\n\n");
    
    uye u1;
    FILE* ptr = fopen("uyeliste.txt", "rb");
    
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi.");
        return;
    }
    
    printf("%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s\n\n",
        "\tTC", "Ad", "Soyad", "Dogum Tarihi", "Cinsiyet", "Telefon", "E-Posta", "Adres"
    );
    
    while (fread(&u1, sizeof(uye), 1, ptr) == 1) {
        printf("\t%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s-%-20s\n",
            u1.tc, u1.ad, u1.Soyad, u1.dogumTarihi, u1.cinsiyet, u1.telefon, u1.eposta, u1.adres
        );
    }
    
    fclose(ptr);
}


void UyeGuncelle()
{
    FILE* ptr;
    uye u1;
    int bulundu = 0;
    char tc[11];
    printf("\n\tGuncellenecek uyenin TC numarasini giriniz:");
    scanf("\t%s", tc);

    ptr = fopen("uyeliste.txt", "r+b");
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi!\n");
        return;
    }

    while (fread(&u1, sizeof(uye), 1, ptr) == 1) {
        if (strcmp(tc, u1.tc) == 0) {
            bulundu = 1;
            printf("\n\tUye bilgileri:\n\n");
            printf("\tTC             :       %s\n", u1.tc);
            printf("\tAd             :       %s\n", u1.ad);
            printf("\tSoyad          :       %s\n", u1.Soyad);
            printf("\tDogum Tarihi   :       %s\n", u1.dogumTarihi);
            printf("\tCinsiyet       :       %s\n", u1.cinsiyet);
            printf("\tTelefon        :       %s\n", u1.telefon);
            printf("\tE-Posta        :       %s\n", u1.eposta);
            printf("\tAdres          :       %s\n", u1.adres);

            printf("\n\tGuncelleme yapmak icin yeni bilgileri girin:\n\n");
            printf("\tAd             :       "); 
            scanf("%s", u1.ad);
            printf("\tSoyad          :       "); 
            scanf("%s", u1.Soyad);
            printf("\tDogum Tarihi   :       "); 
            scanf("%s", u1.dogumTarihi);
            printf("\tCinsiyet       :       "); 
            scanf("%s", u1.cinsiyet);
            printf("\tTelefon        :       "); 
             scanf("%s", u1.telefon);
            printf("\tE-Posta        :       "); 
            scanf("%s", u1.eposta);
            printf("\tAdres          :       "); 
            scanf("%s", u1.adres);

            fseek(ptr, -sizeof(uye), SEEK_CUR); // Dosyada geriye gitmek için pozisyonu ayarlama
            fwrite(&u1, sizeof(uye), 1, ptr); // Güncellenen üye bilgilerini dosyaya yaz

            printf("\n\tUye bilgileri basariyla guncellendi.\n\n");
            break; 
        }
    }

    if (!bulundu) {
        printf("\n\t%d TC numarali kisi bulunamadi.\n\n", tc);
    }

    fclose(ptr);
}





void uyeIslemleri() {
   system("cls"); 
   
    printf("\t\t\t\t\t\tUye islemleri\n\n");
    int secim;
    printf("\t1-Uye Ekle \n");
    printf("\t2-Uye sil \n");
    printf("\t3-Uye Listele \n");
    printf("\t4-Uye Guncelle \n");
    printf("\t0-Ana Menuye Don \n\n");
    printf("\tLutfen yapacaginiz islemi seciniz:");

    scanf("%d", &secim);

    switch (secim) {
        case 1:
            UyeEkle();
            break;
        case 2:
            UyeSil();
            break;
        case 3:
            UyeListele();
            break;
        case 4:
            UyeGuncelle();
            break;
        case 0:
            break;
        default:
            printf("Hatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\a\n");
          break;
    }
    
}

void stokGuncelle(int barkod, int sayi) {
    kitap k1;
    int sayac = 0;

    FILE* ptr = fopen("kitapliste.txt", "r+b");

    while (fread(&k1, sizeof(kitap), 1, ptr) != 0) {
        if (barkod == k1.barkod)
            break;
        sayac++;
    }
    rewind(ptr);

    fseek(ptr, sayac * sizeof(kitap), SEEK_SET);
    fread(&k1, sizeof(kitap), 1, ptr);
    k1.stokSayisi += sayi;
    fseek(ptr, -sizeof(kitap), SEEK_CUR);
    fwrite(&k1, sizeof(kitap), 1, ptr);
    fclose(ptr);
    printf("\tStok guncellendi.\n");
}

void emanetKitapVer() {
    printf("\n\tEmanet Kitap Verme\n\n");
    emanet e1;
    uye u1;
    kitap k1;
    int usonuc = 0, ksonuc = 0;

    printf("\tTC: ");
    scanf("%s", e1.uyeTC);
    printf("\tBarkod: ");
    scanf("%d", &e1.kitapBarkod);

    FILE* uptr = fopen("uyeliste.txt", "r+b"); // r di r+b ohem okuma hem yazma iþlemine çevirdim.
    while (fread(&u1, sizeof(uye), 1, uptr) != NULL) {
        if (strcmp(e1.uyeTC, u1.tc) == 0) {
            usonuc = 1;
            break;
        }
    }
    fclose(uptr);

    if (usonuc == 0) {
        printf("\t%s TC numarali uye bulunamadi. Ana menuye yonlendiriliyorsunuz.\n", e1.uyeTC);
        return;
    }

    if (u1.durum == -1) {
        printf("\t%s TC numarali üye YASAKLI. Ana menuye yonlendiriliyorsunuz.\n", e1.uyeTC);
        return;
    }

    FILE* kptr = fopen("kitapliste.txt", "r+b");
    while (fread(&k1, sizeof(kitap), 1, kptr) != 0) {
        if (e1.kitapBarkod == k1.barkod) {
            ksonuc = 1;
            break;
        }
    }
    fclose(kptr);

    if (ksonuc == 0) {
        printf("\t%d Barkod numarali kitap kaydi bulunamadi. Ana menüye yönlendiriliyorsunuz.\n", e1.kitapBarkod);
        return;
    }

    if (k1.stokSayisi < 1) {
        printf("\t%d Barkod numarali kitaptan stokta kalmamistir! Ana menüye yönlendiriliyorsunuz.\n", e1.kitapBarkod);
        return;
    }

    FILE* ptr = fopen("emanetliste.txt", "a+b");
    printf("\tKac gun kullanacak: ");
    scanf("%d", &e1.kullanacagiGunSayisi);
    e1.teslimTarihi = time(0);
    fwrite(&e1, sizeof(emanet), 1, ptr);//fread
    fclose(ptr);
    printf("\tEmanet Kaydi Basarili\n");
    stokGuncelle(e1.kitapBarkod,-1);
   
}

 void uyeGuncelle(char*tcPtr){
 	printf("\n\tUye Sil\n\n");

    uye u1;
    int sonuc = 0, sayac=0;
    char tc[11]; 
   
    FILE* ptr = fopen("uyeliste.txt", "rb"); //r+b

    while (fread(&u1, sizeof(uye), 1, ptr) !=NULL ) {
        if (strcmp(tcPtr, u1.tc) == 0) {
           sonuc=1;
           break;
        }
        sayac++;

    }
    if(sonuc==1){
    	rewind(ptr);
        fseek(ptr,(sayac)*sizeof(uye),0);
        u1.durum=-1;
        fwrite(&u1,sizeof(uye),1,ptr);
        printf("\tUye Durumu Guncellendi");
	}
  
    fclose(ptr);

	
 }
void emanetKitabiIadeAl() {
    printf("\n\tEmanet Kitap Iade Alma\n\n");
    emanet e1;
    uye u1;
    kitap k1;
    int sonuc = 0, sayac = 0;
    char uyeTC[20];
    int kitapBarkod;

    printf("\tTC: ");
    scanf("%s", uyeTC);
    printf("\tBarkod: ");
    scanf("%d", &kitapBarkod);

     FILE* ptr = fopen("emanetliste.txt", "a+b");

    while (fread(&e1, sizeof(emanet), 1, ptr) != NULL) {
        if (strcmp(e1.uyeTC, uyeTC) == 0 && e1.kitapBarkod == kitapBarkod) {
            sonuc = 1;
            break;
        }
        sayac++;
    }

    if (sonuc == 0) {
        fclose(ptr);
        printf("\t%s TC veya %d barkod numarali emanet kaydi bulunamadi. Ana menuye yonlendiriliyorsunuz.\n", uyeTC, kitapBarkod);
        return;
    } else {
        rewind(ptr);
        e1.iadeTarihi = time(0);
        float saniye, dakika, saat, gun;
        saniye = difftime(e1.iadeTarihi, e1.teslimTarihi);
        dakika = saniye / 60;
        saat = dakika / 60;
        gun = saat / 24;
        e1.kullandigiGunSayisi = gun;
        printf("\tKullandiginiz saniye: %.2f\n", saniye);
        printf("\tKullandiginiz dakika: %.2f\n", dakika);
        printf("\tKullandiginiz saat: %.2f\n", saat);
        printf("\tKullandiginiz gun: %.2f\n", gun);

        e1.gecikmeGunSayisi = e1.kullanacagiGunSayisi - e1.kullandigiGunSayisi;

        if (e1.gecikmeGunSayisi > 10)
            e1.durum = -1;
        else
            e1.durum = 1;

        fseek(ptr, (sayac) * sizeof(emanet), 0);
        fwrite(&e1, sizeof(emanet), 1, ptr);
        fclose(ptr);
        printf("\tEmanet Iade Kaydi Basarili\n");

        stokGuncelle(e1.kitapBarkod, 1);

        if (e1.durum == 1)
            uyeGuncelle(e1.uyeTC); // Düzeltme yapýldý
    }
}


void EmanettekiKitaplariListele(){
    printf("\n\tEmanet Kitap Listeleme\n\n");
    emanet e1;
    int sayac=0;
    FILE*ptr=fopen("emanetliste.txt","rb");
    printf("\t%-20s\t%-20s\t%-20s\t%-20s\n","\tTC","\tBARKOD","\tTARIH","\tDURUM");
    while(fread(&e1,sizeof(emanet),1,ptr) !=NULL)
    {
        struct tm*tbilgi=localtime(&e1.teslimTarihi);
        char tarih[11];
        strftime(tarih,sizeof(tarih),"%d.%m.%Y",tbilgi);
        if(e1.durum==0){
            printf("\t\t%-20s\t\t%-20d\t\t%-20s\t\t%-20d\n\n",e1.uyeTC,e1.kitapBarkod,tarih,e1.durum);
            sayac++;
        }
        
    }
    fclose(ptr);
    printf("\n\tEmanet kayit sayisi : %d \n",sayac);
}


void emanetIslemleri() {
	system("cls");

	
    printf("\t\t\t\t\t***EMANET ISLEMLERI***\n\n");
    int secim;
    printf("\t1-Emanet Kitap Ver \n");
    printf("\t2-Emanet Kitap Iade Al \n");
    printf("\t3-Emanetteki Kitaplari Listele \n");
    printf("\t0-Ana Menuye Don \n\n");
    printf("\tLutfen yapacaginiz islemi seciniz:");

    scanf("%d", &secim);

    switch (secim) {
        case 1:
            emanetKitapVer();
            break;
        case 2:
            emanetKitabiIadeAl();
            break;
        case 3:
            EmanettekiKitaplariListele();
            break;
        case 0:
            break;
        default:
            printf("\n\tHatali secim yaptiniz, ana menuye yonlendiriliyorsunuz...\a\n");
          break;
    }
    
    
}

  int menu() {
  	
    int secim;
  

    printf("\t\t\t\t\t\t***KUTUPHANE OTOMASYONU***\n\n");
    printf("\t1-KITAP ISLEMLERI\n");
    printf("\t2-UYE ISLEMLERI\n");
    printf("\t3-EMANET ISLEMLERI\n");
    printf("\t0-PROGRAMI KAPAT\n\n");

    printf("\tLutfen yapacaginiz islemi seciniz:");
    scanf("%d", &secim);

    return secim;
}

void admin_paneli() {
    char kullaniciAdi[20];
    char sifre[20];
    int deneme = 0;
    system("cls");
    
    printf("\n\t\t\t\t\t***KUTUPHANE PROGRAMINA HOS GELDINIZ***\n\n");
   printf("\n\tKullanici Bilgilerinizi Giriniz:\n");

    while (deneme < 3) {
        printf("\n\tKullanici adi: ");
        scanf("%s", kullaniciAdi);

        printf("\n\tSifre: ");
        scanf("%s", sifre);

        if (strcmp(kullaniciAdi, "admin") == 0 && strcmp(sifre, "123") == 0) {
            printf("\n\tGiris basarili.\n");
            break;
        } else {
            printf("\n\tKullanici adi veya sifre hatali!\n");
            deneme++;
        }
    }

    if (deneme == 3) {
        printf("\n\tUc kez yanlis giris yaptiniz. Program sonlandiriliyor.\n");
        return;
    }

    int secim = menu();
    while (secim != 0) {
        switch (secim) {
            case 1:
                KitapIslemleri();
                break;
            case 2:
                uyeIslemleri();
                break;
            case 3:
                emanetIslemleri();
                break;
            case 0:
                printf("\n\tProgramdan cikis yapiliyor...\n");
                return;
            default:
                printf("\n\tHatali islem yaptiniz!\n");
        }
        secim = menu();
    }

    printf("\n\tIslemi sonlandirdiniz...\n");
}

void kitap_ara() {
    FILE* ptr;
    kitap k1;
    int Kbulundu = 0;
    char kitapAdi[50];
    printf("\n\tAramak istediginiz kitabin adini giriniz: ");
    scanf("%s", kitapAdi);
    printf("\n\tKitap araniyor lutfen bekleyiniz ...\n");
    
    ptr = fopen("kitapliste.txt", "rb+");
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi!\n");
        return;
    }
    
    while (fread(&k1, sizeof(kitap), 1, ptr)) {
        if (strcmp(k1.kitapAdi, kitapAdi) == 0) {
            Kbulundu = 1;
            printf("\n\tKitap bilgileri:\n\n");
            printf("\tKitap Adi      :       %s\n", k1.kitapAdi);
        }
    }
    if (!Kbulundu) {
        printf("\n\tAradiginiz kitap bulunamadi.\n\n");
    }
    fclose(ptr);
}

void kitap_durumu_sorgula() {
	
	FILE* ptr;
    kitap k1;
    char kitapAdi[50];
    char yazarAdi[50];
    int kitapMevcut = 0;
   
    printf("\n\tSorgulamak istediginiz kitabin adini giriniz: ");
    scanf("%s", kitapAdi);
    printf("\n\tSorgulamak istediginiz kitabin yazarin adini giriniz: ");
    scanf("%s", yazarAdi);
    
    printf("\n\tKitap guncel durumu sorgulaniyor...\n");
    
    ptr = fopen("kitapliste.txt", "rb");
    if (ptr == NULL) {
        printf("\n\tDosya acilamadi!\n");
        return;
    }
    
      while (fread(&k1, sizeof(kitap), 1, ptr)) {
        if (strcmp(k1.kitapAdi, kitapAdi) == 0 && strcmp(k1.yazarAdi, yazarAdi) == 0) {
            kitapMevcut = 1;
            if (k1.mevcut != 0) {
                printf("\n\tKitap mevcut.\n");
            } else {
                printf("\n\tKitap su an alinmistir.\n");
            }
            break;
        }
    }
    
    if (!kitapMevcut) {
        printf("\n\tKitap kayitlarda bulunamadi.\n");
    }
    
    fclose(ptr);
}



void uye_paneli() {
    int secim;

    
    printf("\n\n\tUYE ISLEMLERI\n\n");
    printf("\t1- KITAP ARA\n\n");
    printf("\t2- KITABIN DURUMUNU SORGULA\n\n");
    printf("\t0- PROGRAMI KAPAT\n");
    
    printf("\n\tYapacaginiz islemi seciniz: ");
    scanf("%d", &secim);
    
    switch (secim) {
        case 1:
            kitap_ara();
            break;
        case 2:
            kitap_durumu_sorgula();
            break;
        case 0:
            printf("\t\nUye islemi sonlandý.\n\a");
            break;
        default:
            printf("\t\nHatali secim!\n");
            break;
    }
}

int panelmenu(){
	 int sec;

    printf("\n\n\t\t\t\t\t\t*** SEHIR KUTUPHANESI***\n\n");
    printf("\t1- Admin girisi\n\n");
    printf("\t2- Uye girisi\n\n");
    printf("\tYapmak istediginiz islemi seciniz: ");
    scanf("%d", &sec);
	
	return sec;
	
}


int main() {
    system("cls");
    int sec = panelmenu();
     while (sec != 0) {
    switch (sec) {
        case 1:
            admin_paneli();
            break;
        case 2:
            uye_paneli();
            break;
        default:
            printf("\n\tHatali secim!\n");
            break;
    }
     sec = panelmenu();
 }
    printf("\n\tProgram sonlandirildi.\n");
    return 0;
}
