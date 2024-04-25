// EEM120 Group Project : Railway Ticket Reservation System
// Simüle bir şekilde tren seferleri oluşturabilen, rezervasyon, sorgulama menülerini içinde barındırmaktadır
// Oluşturduğumuz havuzdan sefer isimleri alan, 2 vagonlu, her vagonu 20'şer koltuklu seferler
// Detaylı rezervasyon menüsü ve koltuklar boş ise boş olduğunu, doluysa da kullanıcı bilgilerini veren sorgu sistemini içermektedir.

#include <iostream> // Standart giriş/çıkış işlemleri için gerekli kütüphane
#include <string> // String işlemleri için gerekli kütüphane
#include <cstdlib> // Ekran temizlemek için sistem komutlarını çalıştırmak için gerekli kütüphane
#include <ctime> // Zamanı almak ve rastgele sayı üretmek için gerekli kütüphane
#include <algorithm> // Algoritma işlemleri için gerekli kütüphane

using namespace std; // Standard kütüphane kullanım alanı [Kodların başına std koymaktan kurtarıyor]

class Tren { // Tren sınıfı tanımlanıyor
private: 
    string kimlik; // Trenin kimliği
    string seferAdi; // Trenin sefer adı
    string koltukBilgileri[2][20][3]; // 2 vagon, her biri 20 koltuk, her birinde 3 bilgi (ad, yaş, cinsiyet)

public: 
    static const int vagonSayisi = 2; // Sabit vagon sayısı [Her tren 2 vagona ve vagon başı 20 koltuğa sahip]
    static const int koltukSayisi = 20; // Sabit koltuk sayısı

    Tren(string kimlik, string seferAdi) : kimlik(kimlik), seferAdi(seferAdi) { // Tren yapıcı fonksiyonu
        // Her koltuğun bilgilerini boş olarak başlat
        for (int i = 0; i < vagonSayisi; ++i) { // Vagon sayısı kadar döngü [ 2 ]
            for (int j = 0; j < koltukSayisi; ++j) { // Koltuk sayısı kadar döngü [ 20 ]
                koltukBilgileri[i][j][0] = ""; // Ad
                koltukBilgileri[i][j][1] = ""; // Yaş
                koltukBilgileri[i][j][2] = ""; // Cinsiyet
            }
        }
    }

    Tren() : kimlik("Bos Tren"), seferAdi("Bilinmiyor") { // Boş tren yapıcı fonksiyonu.
        // Boş yapıcı
    }

    string kimlikAl() const { // Trenin kimliğini alıyoruz.
        return kimlik;
    }

    string seferAdiAl() const { // Trenin sefer adını alıyoruz.
        return seferAdi;
    }

    void bosKoltuklariGoster() const { // Boş koltukları göstermek için
        for (int i = 0; i < vagonSayisi; ++i) { // Vagon sayısı kadar döngü [2]
            cout << "Vagon " << i + 1 << ": "; // Vagon numarasını ekrana yazıyorum
            bool bosKoltukVar = false; // Boş koltuk var mı kontrolü
            for (int j = 0; j < koltukSayisi; ++j) { // Koltuk sayısı kadar döngü [20]
                if (koltukBilgileri[i][j][0] == "") { // Eğer koltuk boşsa
                    cout << (i * koltukSayisi + j + 1) << " "; // Koltuk numarasını ekrana yaz
                    bosKoltukVar = true; // Boş koltuk var olduğunu belirt
                }
            }
            if (!bosKoltukVar) { // Eğer boş koltuk yoksa
                cout << "Seferde Bos Yer Kalmamistir"; 
            }
            cout << endl; 
        }
    }

    bool koltukRezerveEt(int koltukNumarasi, const string& ad, int yas, const string& cinsiyet) { // Koltuk rezervasyonu yapmak için
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi; // Koltuğun bulunduğu vagonun indeksi
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi; // Koltuğun bulunduğu sıranın indeksi

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi || koltukBilgileri[vagonIndeksi][koltukIndeksi][0] != "") { // Eğer koltuk numarası geçersizse veya koltuk doluysa
            return false; // Rezervasyon başarısız
        }
        koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = ad; // Adı kaydetmek için
        koltukBilgileri[vagonIndeksi][koltukIndeksi][1] = to_string(yas); // Yaşı kaydetmek için
        koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = cinsiyet; // Cinsiyeti kaydetmek için
        return true; // Rezervasyon başarılı
    }

    string koltukSahibi(int koltukNumarasi) const { // Koltuğun sahibini sorgulamak için
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi; // Koltuğun bulunduğu vagonun indeksi
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi; // Koltuğun bulunduğu sıranın indeksi

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi) { // Eğer koltuk numarası geçersizse [1 ila 40 arasında değilse (vagon sayısı * koltuk sayisi -> 2*20 = 40)]
            return "Gecersiz koltuk numarasi."; 
        }
        else if (koltukBilgileri[vagonIndeksi][koltukIndeksi][0] == "") { // Eğer koltuk boşsa
            return "Koltuk Sahipsizdir";
        }
        else { // Diğer durumlarda
            return koltukBilgileri[vagonIndeksi][koltukIndeksi][0] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][1] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2]; // Koltuk sahibinin bilgilerini döndür
        }
    }

    void ekranTemizle() const { // Ekranı temizleme fonksiyonu
#ifdef _WIN32 // Windows işletim sistemi için temizleme kodu
        system("cls"); 
#else // Diğer işletim sistemleri için temizleme kodu
        system("clear"); 
#endif
    }
};

void menuGoster() { // Ana menüyü gösteren fonksiyon
    cout << "Ana Menu:" << endl; // Başlık
    cout << "1. Mevcut trenleri ve bos koltuklari goruntule" << endl; // Menü seçeneği 1
    cout << "2. Koltuk rezervasyonu yap" << endl; // Menü seçeneği 2
    cout << "3. Koltuk sahibini sorgula" << endl; // Menü seçeneği 3
    cout << "4. Cikis" << endl; // Menü seçeneği 4
    cout << "Seciminizi girin: "; // Kullanıcıdan seçim yapması istenir
}

void ekranTemizle() { // Ekranı temizleyen fonksiyon
#ifdef _WIN32 // Windows işletim sistemi için temizleme kodu
    system("cls"); 
#else // Diğer işletim sistemleri için temizleme kodu
    system("clear"); 
#endif
}

int main() { // Ana fonksiyon
    Tren aktifTrenler[3]; // En fazla 3 tren oluşturuyoruz
    string seferAdlari[] = { "Ankara-Kocaeli", "Ankara-Eskisehir", "Ankara-Sivas", "Ankara-Istanbul", "Ankara-Antalya" }; // Tren sefer adları [Keyfimizce rastgele isimler verilmesi için 5 sefer adı]
    srand(time(nullptr)); // Rastgelelik için zamanı kullan

    // Rastgele sefer adlarını belirliyoruz
    string seciliSeferler[3];
    for (int i = 0; i < 3; ++i) { // 3 tren için
        seciliSeferler[i] = "[" + to_string(i + 1) + "] " + seferAdlari[rand() % 5]; // Rastgele sefer adı belirle
        aktifTrenler[i] = Tren("Tren " + to_string(i + 1), seciliSeferler[i]); // Trenleri oluştururken sefer adını ekliyoruz
    }

    cout << "RailYou'ya Hosgeldiniz!" << endl; // Kullanıcıya hoş geldiniz mesajı

    int secim;

    do { // Ana menü döngüsü [while şartı 4 Girilmediği sürece]
        menuGoster(); // Ana menüyü göster
        cin >> secim; // Kullanıcıdan seçim alma
        cout << endl; 

        switch (secim) { // Kullanıcının seçimine göre işlem yapıyoruz [Switch Case ile]
        case 1: { //Aktif Trenleri gösterme menüsü
            system("CLS"); // Ekranı temizle
            // Olusturulan aktif trenleri goster
            cout << "Aktif trenler:" << endl; 
            for (int i = 0; i < 3; ++i) { // 3 tren için
                cout << seciliSeferler[i] << ": " << endl; // Sefer adını ekrana yazma
                aktifTrenler[i].bosKoltuklariGoster(); // Boş koltukları gösterme
                cout << endl; 
            }
            cout << endl; 
            break; 
        }
        case 2: { //Rezervasyon menüsü
            // Belirli bir tren için koltuk rezervasyonu yap
            int trenIndeksi; 
            cout << "Rezervasyon yapmak istediginiz trenin numarasini girin (1-3): "; // Kullanıcıdan tren numarası al
            cin >> trenIndeksi; // Kullanıcının girdiği tren numarasını al
            --trenIndeksi; // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır [Çünkü indekste 1.tren 0'dır haliyle 1 azaltacağız]

            int koltukNumarasi; // Koltuk numarası
            cout << "Rezervasyon yapmak istediginiz koltuk numarasini girin: "; // Kullanıcıdan koltuk numarası al
            cin >> koltukNumarasi; // Kullanıcının girdiği koltuk numarasını al

            string ad; 
            string yasString; // Yaş için string olarak alınacak [Yaşın rakam olarak girildiğini kontrol etmek adına]
            int yas; // Yaş
            string cinsiyet; // Cinsiyet
            bool dogruYas = false; // Doğru yaş kontrolü

            cout << "Adinizi girin: "; // Kullanıcıdan ad al
            cin >> ad; // Kullanıcının girdiği adı al

            // Doğru yaş girişi yapılıncaya kadar döngüyü devam ettir [string olarak alıyoruz ki rakam mı diye kontrol edeceğiz]
            while (!dogruYas) {
                cout << "Yasinizi girin: "; // Kullanıcıdan yaş al
                cin >> yasString; // Kullanıcının girdiği yaş bilgisini al

                // Yaş girişinin doğru olup olmadığını kontrol et
                for (char c : yasString) {
                    if (!isdigit(c)) { // Eğer girdide rakam dışında bir karakter varsa [Kelime varrsa]
                        cout << "Yas sadece rakam iceriyor olmalidir. Lutfen tekrar deneyin." << endl; // Uyarı mesajı gösteririm
                        break; 
                    }
                }

                // Eğer girişte sadece rakamlar varsa, stringi integera çevir
                if (all_of(yasString.begin(), yasString.end(), ::isdigit)) { 
                    yas = stoi(yasString); // Stringi integera çevir [C++11 versyionundaki dönüştürücü fonksiyonu kullandım]
                    dogruYas = true;  // Olur da bu kodda bir hata çıkarsa C++11 verisyonunu kullanın lütfen, eski modellerde hata olabiliyor]
                }
            }

            cout << "Cinsiyetinizi girin (Erkek/Kadin): "; // Kullanıcıdan cinsiyet bilgisi alıyoruz
            cin >> cinsiyet; 

            // Rezervasyon yapılırken yaş ve cinsiyet bilgileri de dahil edilyor
            if (aktifTrenler[trenIndeksi].koltukRezerveEt(koltukNumarasi, ad, yas, cinsiyet)) { // Koltuk rezervasyonu yapılırsa
                cout << endl << "-----------------------------------------------------------------------"; 
                cout << endl << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << ad << " adina basariyla rezerve edildi." << endl; // Rezervasyon başarılı mesajı
                cout << "-----------------------------------------------------------------------" << endl; 
            }
            else { // Koltuk rezervasyonu yapılamazsa
                cout << "Rezervasyon basarisiz oldu. Lutfen gecerli bir koltuk numarasi girin." << endl; 
            }
            cout << endl; 
            break; 
        }

        case 3: { // Sorgulama Menüsü
            system("CLS"); // Ekranı temizle
            // Belirli bir trenin belirli bir koltuğunun sahibini sorgula
            int trenIndeksi; 
            cout << "Koltuk sahibini sorgulamak istediginiz trenin indeksini girin (1-3): "; // Kullanıcıdan tren numarası al.
            cin >> trenIndeksi; // Kullanıcının girdiği tren numarasını al.
            --trenIndeksi; // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır [Tren 1 aslında indekste 0 olarak kayıtlı, bu yüzden 1 azaltılır]

            int koltukNumarasi; // Koltuk numarası
            cout << "Sorgulamak istediginiz koltuk numarasini girin: "; // Kullanıcıdan koltuk numarası al
            cin >> koltukNumarasi;

            if (koltukNumarasi >= 1 && koltukNumarasi <= Tren::vagonSayisi * Tren::koltukSayisi) { // Eğer koltuk numarası geçerliyse [1-40 arası]
                string koltukSahibi = aktifTrenler[trenIndeksi].koltukSahibi(koltukNumarasi); // Koltuğun sahibini sorgula.
                if (koltukSahibi == "Koltuk Sahipsizdir") { // Eğer koltuk boşsa
                    cout << endl << "-----------------------------------------------------------------------" << endl; 
                    cout << aktifTrenler[trenIndeksi].seferAdiAl() << " trenindeki " << koltukNumarasi << ". koltuk " << "Sahipsizdir" << endl; // Koltuk sahibi yok mesajı yazdırılır.
                    cout << "-----------------------------------------------------------------------" << endl; 
                }
                else if (koltukSahibi != "") { // Eğer koltuk doluysa
                    cout << endl << "-----------------------------------------------------------------------" << endl; 
                    cout << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << koltukSahibi << " tarafindan rezerve edilmistir." << endl; // Koltuk sahibi bilgileri yazdırılır.
                    cout << "-----------------------------------------------------------------------" << endl; 
                }
                else { // Diğer durumlarda
                    cout << "Belirtilen koltuk numarasi bos veya gecersiz." << endl; // Uyarı mesajı gösteririz
                }
            }
            else { // Eğer koltuk numarası geçersizse
                cout << "Gecersiz koltuk numarasi. Lutfen tekrar deneyin." << endl; // Uyarı mesajı gösteririz
            }
            cout << endl; 
            break; 
        }

        case 4: { // Çıkış menüsü
            system("CLS"); // Ekranı temizle
            cout << "RailYou'yu kullandiginiz icin tesekkur ederiz. Iyi gunler dileriz!" << endl; // Kullanıcıya veda mesajı
            break; 
        }
        default: { // Diğer durumlarda
            cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl; // 1-4 değerleri dışında bir şey girilirse
        }
        }

        // Ekranı temizleme sadece 2. ve 3. menü kullanıldığında yapılır
        if (secim == 2 || secim == 3) { // Eğer seçim 2 veya 3 ise
            system("pause"); // Ekranın kapanmasını bekletir
            system("CLS"); // Ekranı temizle
        }

    } while (secim != 4); // Kullanıcı çıkış yapana kadar döngüyü devam ettir

    return 0; // Programı sonlandır
}
