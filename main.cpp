#include <iostream>
#include <string>
#include <cstdlib> // Ekran temizlemek için
#include <ctime>   // Rastgele sayı üretmek için

using namespace std;

class Tren {
private:
    string kimlik;
    string seferAdi;
    string koltukBilgileri[2][20][3]; // 2 vagon, her biri 20 koltuk, her birinde 3 bilgi (ad, yaş, cinsiyet)

public:
    static const int vagonSayisi = 2;
    static const int koltukSayisi = 20;

    Tren(string kimlik, string seferAdi) : kimlik(kimlik), seferAdi(seferAdi) {
        // Her koltuğun bilgilerini boş olarak başlat
        for (int i = 0; i < vagonSayisi; ++i) {
            for (int j = 0; j < koltukSayisi; ++j) {
                koltukBilgileri[i][j][0] = ""; // Ad
                koltukBilgileri[i][j][1] = ""; // Yas
                koltukBilgileri[i][j][2] = ""; // Cinsiyet
            }
        }
    }

    Tren() : kimlik("Bos Tren"), seferAdi("Bilinmiyor") {
        // Bos yapıcı
    }

    string kimlikAl() const {
        return kimlik;
    }

    string seferAdiAl() const {
        return seferAdi;
    }

    void bosKoltuklariGoster() const {
        for (int i = 0; i < vagonSayisi; ++i) {
            cout << "Vagon " << i + 1 << ": ";
            bool bosKoltukVar = false;
            for (int j = 0; j < koltukSayisi; ++j) {
                if (koltukBilgileri[i][j][0] == "") {
                    cout << (i * koltukSayisi + j + 1) << " ";
                    bosKoltukVar = true;
                }
            }
            if (!bosKoltukVar) {
                cout << "Seferde Bos Yer Kalmamistir";
            }
            cout << endl;
        }
    }

    bool koltukRezerveEt(int koltukNumarasi, const string& ad, int yas, const string& cinsiyet) {
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi;
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi;

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi || koltukBilgileri[vagonIndeksi][koltukIndeksi][0] != "") {
            return false; // Geçersiz koltuk numarasi veya rezerve edilmemis koltuk
        }
        koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = ad;
        koltukBilgileri[vagonIndeksi][koltukIndeksi][1] = to_string(yas);
        koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = cinsiyet;
        return true;
    }

    string koltukSahibi(int koltukNumarasi) const {
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi;
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi;

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi) {
            return "Gecersiz koltuk numarasi.";
        }
        else if (koltukBilgileri[vagonIndeksi][koltukIndeksi][0] == "") {
            return "Koltuk Sahipsizdir";
        }
        else {
            return koltukBilgileri[vagonIndeksi][koltukIndeksi][0] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][1] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2];
        }
    }

    void ekranTemizle() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

void menuGoster() {
    cout << "Ana Menu:" << endl;
    cout << "1. Mevcut trenleri ve bos koltuklari goruntule" << endl;
    cout << "2. Koltuk rezervasyonu yap" << endl;
    cout << "3. Koltuk sahibini sorgula" << endl;
    cout << "4. Cikis" << endl;
    cout << "Seciminizi girin: ";
}

void ekranTemizle() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {

    Tren aktifTrenler[3]; // En fazla 3 tren
    string seferAdlari[] = { "Ankara-Kocaeli", "Ankara-Eskisehir", "Ankara-Sivas", "Ankara-Istanbul", "Ankara-Antalya" };
    srand(time(nullptr)); // Rastgelelik için zamanı kullan

    // Rastgele sefer adlarını belirle
    string seciliSeferler[3];
    for (int i = 0; i < 3; ++i) {
        seciliSeferler[i] = "[" + to_string(i + 1) + "] " + seferAdlari[rand() % 5]; // Tren adına indeks ekleyin
        aktifTrenler[i] = Tren("Tren " + to_string(i + 1), seciliSeferler[i]); // Trenleri oluştururken sefer adını ekleyin
    }

    cout << "RailYou'ya Hosgeldiniz!" << endl;

    int secim;

    do {
        menuGoster();
        cin >> secim;
        cout << endl;

        switch (secim) {
        case 1: {
            system("CLS");
            // Olusturulan aktif trenleri goster
            cout << "Aktif trenler:" << endl;
            for (int i = 0; i < 3; ++i) {
                cout << seciliSeferler[i] << ": " << endl;
                aktifTrenler[i].bosKoltuklariGoster();
                cout << endl;
            }
            cout << endl;
            break;
        }
        case 2: {
            // Belirli bir tren için koltuk rezervasyonu yap
            int trenIndeksi;
            cout << "Rezervasyon yapmak istediginiz trenin numarasini girin (1-3): ";
            cin >> trenIndeksi;
            --trenIndeksi; // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır

            int koltukNumarasi;
            cout << "Rezervasyon yapmak istediginiz koltuk numarasini girin: ";
            cin >> koltukNumarasi;

            string ad;
            int yas;
            string cinsiyet;
            cout << "Adinizi girin: ";
            cin >> ad;
            cout << "Yasinizi girin: ";
            cin >> yas;
            cout << "Cinsiyetinizi girin (Erkek/Kadin): ";
            cin >> cinsiyet;

            // Rezervasyon yapılırken yaş ve cinsiyet bilgileri ekleniyor
            if (aktifTrenler[trenIndeksi].koltukRezerveEt(koltukNumarasi, ad, yas, cinsiyet)) {
                cout << endl << "-----------------------------------------------------------------------";
                cout << endl << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << ad << " adina basariyla rezerve edildi." << endl;
                cout << "-----------------------------------------------------------------------" << endl;
            }
            else {
                cout << "Rezervasyon basarisiz oldu. Lutfen gecerli bir koltuk numarasi girin." << endl;
            }
            cout << endl;
            break;
        }
        case 3: {
            system("CLS");
            // Belirli bir trenin belirli bir koltuğunun sahibini sorgula
            int trenIndeksi;
            cout << "Koltuk sahibini sorgulamak istediginiz trenin indeksini girin (1-3): ";
            cin >> trenIndeksi;
            --trenIndeksi; // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır

            int koltukNumarasi;
            cout << "Sorgulamak istediginiz koltuk numarasini girin: ";
            cin >> koltukNumarasi;

            if (koltukNumarasi >= 1 && koltukNumarasi <= Tren::vagonSayisi * Tren::koltukSayisi) {
                string koltukSahibi = aktifTrenler[trenIndeksi].koltukSahibi(koltukNumarasi);
                if (koltukSahibi == "Koltuk Sahipsizdir") {
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << aktifTrenler[trenIndeksi].seferAdiAl() << " trenindeki " << koltukNumarasi << ". koltuk " << "Sahipsizdir" << endl;
                    //cout << "Koltuk Sahipsizdir." << endl;
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else if (koltukSahibi != "") {
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << koltukSahibi << " tarafindan rezerve edilmistir." << endl;
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else {
                    cout << "Belirtilen koltuk numarasi bos veya gecersiz." << endl;
                }
            }
            else {
                cout << "Gecersiz koltuk numarasi. Lutfen tekrar deneyin." << endl;
            }
            cout << endl;
            break;
        }

        case 4: {
            system("CLS");
            cout << "RailYou'u kullandiginiz icin tesekkur ederiz. Iyi gunler dileriz!" << endl;
            break;
        }
        default: {
            cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl;
        }
        }

        // Ekranı temizleme sadece 2. ve 3. menü kullanıldığında yapılır
        if (secim == 2 || secim == 3) {
            system("pause");
            system("CLS");
        }

    } while (secim != 4);

    return 0;
}
