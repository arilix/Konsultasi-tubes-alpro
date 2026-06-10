// ==== Header Files yang Diperlukan ====
#include <iostream>  // Untuk input/output stream (cout, cin)
#include <fstream>   // Untuk file stream (membaca dan menulis file)
#include <string>    // Untuk menggunakan tipe data string
#include <limits>    // Untuk menggunakan numeric_limits (digunakan dalam validasi input)
#include <sstream>   // Untuk menggunakan stringstream (mem-parsing string)
#include <cstdlib>
#include <cctype>
#include <ctime>   // Untuk fungsi system() (membersihkan layar konsol)

using namespace std;

// ==== FUNGSI UTILITAS ====

/**
 * @brief Membersihkan layar konsol.
 * Fungsi ini cross-platform, bisa berjalan di Windows (cls) dan Linux/macOS (clear).
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ==== KONSTANTA DAN TIPE DATA GLOBAL ====

// Konstanta untuk jumlah meja per masing-masing jenis
const int JUMLAH_MEJA_PER_JENIS = 5;

// Enum untuk merepresentasikan jenis-jenis meja.
// Menambahkan JUMLAH_JENIS di akhir memudahkan jika ingin menambah tipe meja baru.
enum JenisMeja { REGULER, VIP, VVIP, JUMLAH_JENIS };

// Struct untuk menyimpan detail waktu reservasi (tanggal dan jam)
struct WaktuReservasi {
    string tanggal;
    string jam;
};

// Struct untuk menyimpan detail data pemesan (nama dan kontak)
struct DetailPemesan {
    string nama;
    string kontak;
};

// Struct utama untuk merepresentasikan sebuah meja
struct Meja {
    int nomor;
    JenisMeja jenis;
    bool tersedia;
    DetailPemesan pemesan;
    WaktuReservasi waktu;
};

// ==== Prototipe Fungsi ====
// Mendeklarasikan fungsi ini di awal agar bisa dipanggil oleh fungsi lain
// sebelum definisi lengkapnya ditulis di bagian bawah.
void simpanSemuaDataKeFile(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]);


// ==== FUNGSI KONVERSI DAN HELPER ====

/**
 * @brief Mengubah tipe data enum JenisMeja menjadi string yang bisa dibaca.
 * @param jenis Tipe meja dalam bentuk enum.
 * @return String representasi dari jenis meja (e.g., "Reguler").
 */
string jenisToString(JenisMeja jenis) {
    switch (jenis) {
        case REGULER: return "Reguler";
        case VIP: return "VIP";
        case VVIP: return "VVIP";
        default: return "Tidak diketahui";
    }
}

/**
 * @brief Mengubah string dari file menjadi tipe data enum JenisMeja.
 * @param jenisStr String nama jenis meja (e.g., "Reguler").
 * @return Tipe meja dalam bentuk enum.
 */
JenisMeja stringToJenis(const string& jenisStr) {
    if (jenisStr == "Reguler") return REGULER;
    if (jenisStr == "VIP") return VIP;
    if (jenisStr == "VVIP") return VVIP;
    return REGULER; // Default fallback
}

/**
 * @brief Mengembalikan harga berdasarkan jenis meja.
 * @param jenis Tipe meja dalam bentuk enum.
 * @return Harga meja dalam integer.
 */
int hargaMeja(JenisMeja jenis) {
    switch (jenis) {
        case REGULER: return 50000;
        case VIP: return 100000;
        case VVIP: return 200000;
        default: return 0;
    }
}


// ==== FUNGSI MANAJEMEN DATA DAN FILE ====

/**
 * @brief Mengatur semua meja ke status awal (tersedia).
 * Fungsi ini dijalankan sekali setiap program dimulai.
 * @param meja Array 2D dari semua meja.
 */
void inisialisasiMeja(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    for (int i = 0; i < JUMLAH_JENIS; i++)
        for (int j = 0; j < JUMLAH_MEJA_PER_JENIS; j++) {
            meja[i][j].nomor = j + 1;
            meja[i][j].jenis = static_cast<JenisMeja>(i);
            meja[i][j].tersedia = true;
            meja[i][j].pemesan = {"", ""};
            meja[i][j].waktu = {"", ""};
        }
}

/**
 * @brief Memuat data reservasi yang ada dari file reservasi.txt ke dalam memori.
 * Fungsi ini dijalankan setelah inisialisasi untuk memperbarui status meja
 * yang sudah dipesan dari sesi sebelumnya.
 * @param meja Array 2D dari semua meja untuk diupdate.
 */
void muatReservasiDariFile(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    ifstream file("reservasi.txt");
    if (!file.is_open()) {
        // Jika file tidak ada, tidak melakukan apa-apa.
        return;
    }

    string baris;
    // Membaca file baris per baris
    while (getline(file, baris)) {
        stringstream ss(baris); // Menggunakan stringstream untuk mem-parsing baris
        string jenisStr, nomorStr, nama, kontak, tanggal, jam, hargaStr;

        // Mengambil setiap data yang dipisahkan oleh koma
        getline(ss, jenisStr, ',');
        getline(ss, nomorStr, ',');
        getline(ss, nama, ',');
        getline(ss, kontak, ',');
        getline(ss, tanggal, ',');
        getline(ss, jam, ',');
        getline(ss, hargaStr, ',');

        try {
            JenisMeja jenis = stringToJenis(jenisStr);
            int nomor = stoi(nomorStr); // Konversi string nomor ke integer

            // Memvalidasi data sebelum memperbarui state
            if (nomor > 0 && nomor <= JUMLAH_MEJA_PER_JENIS) {
                meja[jenis][nomor - 1].tersedia = false;
                meja[jenis][nomor - 1].pemesan = {nama, kontak};
                meja[jenis][nomor - 1].waktu = {tanggal, jam};
            }
        } catch (const std::exception& e) {
            // Menangani error jika ada baris yang korup di file
            cerr << "Peringatan: Baris data tidak valid di reservasi.txt: " << baris << endl;
        }
    }
    file.close();
    cout << "Data reservasi sebelumnya berhasil dimuat.\n";
}

/**
 * @brief Menambahkan satu data reservasi baru ke akhir file reservasi.txt.
 * Mode 'app' (append) memastikan data lama tidak terhapus.
 * @param meja Meja spesifik yang baru saja dipesan.
 */
void tambahkanReservasiKeFile(const Meja &meja) {
    ofstream file("reservasi.txt", ios::app);
    if (file.is_open()) {
        file << jenisToString(meja.jenis) << ","
             << meja.nomor << ","
             << meja.pemesan.nama << ","
             << meja.pemesan.kontak << ","
             << meja.waktu.tanggal << ","
             << meja.waktu.jam << ","
             << hargaMeja(meja.jenis) << endl;
        file.close();
    } else {
        cout << "Gagal menyimpan ke file.\n";
    }
}


// ==== FUNGSI TAMPILAN (USER INTERFACE) ====

/**
 * @brief Menampilkan representasi visual QR Code dalam bentuk ASCII art.
 * QR Code ini juga menyertakan detail reservasi untuk kemudahan.
 * @param meja Meja yang detailnya akan ditampilkan.
 */
void tampilkanQRCodeDummy(const Meja &meja) {
    cout << "\n";
    cout << "+===========================================================+\n";
    cout << "|                       QR CODE RESERVASI                   |\n";
    cout << "+===========================================================+\n";
    cout << "|  ########  ##    ##  ########  ########  ########         |\n";
    cout << "|  ##    ##  ##  ##    ##    ##  ##    ##  ##    ##         |\n";
    cout << "|  ##  ####  ########  ##  ####  ##  ####  ##  ####         |\n";
    cout << "|  ########  ##    ##  ########  ########  ########         |\n";
    cout << "|                                                           |\n";
    cout << "|   ######    ########  ##    ##    ########  ######         |\n";
    cout << "| ##########  ##    ##  ########  ##########  ######         |\n";
    cout << "|   ######    ##  ####  ##    ##    ######    ########       |\n";
    cout << "|                                                           |\n";
    cout << "|  ########  ##    ##  ########  ########  ########         |\n";
    cout << "|  ##    ##  ######    ##    ##  ##    ##  ########         |\n";
    cout << "|  ##  ####  ##    ##  ##  ####  ##  ####  ##    ##         |\n";
    cout << "|  ########  ########  ########  ########  ########         |\n";
    cout << "+===========================================================+\n";
    cout << "| Data Reservasi:                                           |\n";
    
    // Logika padding untuk membuat teks rata kiri-kanan
    string info;
    int padding;

    info = "> Meja: " + jenisToString(meja.jenis) + " No." + to_string(meja.nomor);
    cout << "| " << info;
    padding = 58 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";
    
    info = "> Nama: " + meja.pemesan.nama;
    cout << "| " << info;
    padding = 58 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";
    
    info = "> Waktu: " + meja.waktu.tanggal + " " + meja.waktu.jam;
    cout << "| " << info;
    padding = 58 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "> Kontak: " + meja.pemesan.kontak;
    cout << "| " << info;
    padding = 58 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";
    
    cout << "+===========================================================+\n";
    cout << "|          Tunjukkan QR Code ini saat datang!               |\n";
    cout << "+===========================================================+\n";
    cout << "\n";
}

/**
 * @brief Mencetak struk reservasi yang rapi dan terformat.
 * @param meja Meja yang detailnya akan dicetak.
 */
void cetakStruk(const Meja &meja) {
    clearScreen();
    cout << "\n+============================================================+\n";
    cout << "|                       STRUK RESERVASI                      |\n";
    cout << "|                     RESTORAN NUSANTARA                     |\n";
    cout << "+============================================================+\n";
    
    // Logika padding untuk membuat struk rapi
    string info;
    int padding;

    info = "Jenis Meja     : " + jenisToString(meja.jenis);
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "Nomor Meja     : " + to_string(meja.nomor);
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "Nama Pemesan   : " + meja.pemesan.nama;
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "Kontak         : " + meja.pemesan.kontak;
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "Tanggal        : " + meja.waktu.tanggal;
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    info = "Jam            : " + meja.waktu.jam;
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";
    
    info = "Harga          : Rp" + to_string(hargaMeja(meja.jenis));
    cout << "| " << info;
    padding = 57 - info.length();
    for(int i = 0; i < padding; i++) cout << " ";
    cout << "|\n";

    cout << "|                                                            |\n";
    cout << "+============================================================+\n";
    
    tampilkanQRCodeDummy(meja); // Tampilkan QR Code di bawah struk
}

/**
 * @brief Menampilkan status dari semua meja yang ada di restoran.
 * @param meja Array 2D dari semua meja.
 */
void tampilkanSemuaMeja(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    clearScreen();
    cout << "\n+============================================================+\n";
    cout << "|                          DAFTAR MEJA                       |\n";
    cout << "|                     RESTORAN NUSANTARA                     |\n";
    cout << "+============================================================+\n\n";
    
    for (int i = 0; i < JUMLAH_JENIS; i++) {
        JenisMeja jenis = static_cast<JenisMeja>(i);
        // Header untuk setiap jenis meja
        string header = jenisToString(jenis) + " (Harga: Rp" + to_string(hargaMeja(jenis)) + ")";
        cout << "+------------------------------------------------------------+\n";
        cout << "| " << header;
        int headerPadding = 57 - header.length();
        for(int k = 0; k < headerPadding; k++) cout << " ";
        cout << "|\n";
        cout << "+------------------------------------------------------------+\n";
        
        // Detail status untuk setiap meja
        for (int j = 0; j < JUMLAH_MEJA_PER_JENIS; j++) {
            if (meja[i][j].tersedia) {
                cout << "| Meja " << meja[i][j].nomor << " - [TERSEDIA]                                       |\n";
            } else {
                string status = "Meja " + to_string(meja[i][j].nomor) + " - [TERPESAN] oleh " + meja[i][j].pemesan.nama;
                cout << "| " << status;
                int statusPadding = 57 - status.length();
                for(int k = 0; k < statusPadding; k++) cout << " ";
                cout << "|\n";

                string waktu = "  Waktu: " + meja[i][j].waktu.tanggal + " " + meja[i][j].waktu.jam;
                cout << "| " << waktu;
                int waktuPadding = 57 - waktu.length();
                for(int k = 0; k < waktuPadding; k++) cout << " ";
                cout << "|\n";
            }
        }
        cout << "+------------------------------------------------------------+\n\n";
    }
}


// ==== FUNGSI INPUT PENGGUNA ====

/**
 * @brief Meminta input angka dari pengguna dan memvalidasinya.
 * Akan terus meminta input sampai pengguna memasukkan angka yang valid
 * dalam rentang min dan max.
 * @param pesan Pesan yang ditampilkan ke pengguna.
 * @param min Nilai minimum yang diterima.
 * @param max Nilai maksimum yang diterima.
 * @return Angka valid yang dimasukkan pengguna.
 */
int inputAngka(string pesan, int min, int max) {
    int nilai;
    while (true) {
        cout << pesan;
        cin >> nilai;
        if (cin.fail() || nilai < min || nilai > max) {
            cout << "Input tidak valid. Coba lagi.\n";
            cin.clear(); // Menghapus status error dari cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input di buffer
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer setelah input valid
            return nilai;
        }
    }
}

/**
 * @brief Meminta input string dari pengguna dan memastikan tidak kosong.
 * @param pesan Pesan yang ditampilkan ke pengguna.
 * @return String valid yang dimasukkan pengguna.
 */
string inputString(string pesan) {
    string data;
    while (true) {
        cout << pesan;
        getline(cin, data); // Menggunakan getline untuk bisa membaca spasi
        if (data.empty()) {
            cout << "Input tidak boleh kosong. Coba lagi.\n";
        } else {
            return data;
        }
    }
}




// ==== VALIDASI INPUT TAMBAHAN ====
string targetTanggalGlobal="";

bool validNama(const string& nama){
    if(nama.empty()) return false;
    for(char c : nama){
        if(!isalpha((unsigned char)c) && c!=' ') return false;
    }
    return true;
}

bool validKontak(const string& kontak){
    if(kontak.length() < 10 || kontak.length() > 15) return false;
    for(char c : kontak){
        if(!isdigit((unsigned char)c)) return false;
    }
    return true;
}

bool validTanggal(const string& tgl){
    if(tgl.length() != 10) return false;
    if(tgl[4] != '-' || tgl[7] != '-') return false;

    int tahun, bulan, hari;
    try{
        tahun = stoi(tgl.substr(0,4));
        bulan = stoi(tgl.substr(5,2));
        hari = stoi(tgl.substr(8,2));
    }catch(...){
        return false;
    }

    if(bulan < 1 || bulan > 12) return false;
    if(hari < 1 || hari > 31) return false;

    time_t sekarang = time(0);
    tm *waktu = localtime(&sekarang);

    int tahunSekarang = waktu->tm_year + 1900;
    int bulanSekarang = waktu->tm_mon + 1;
    int hariSekarang = waktu->tm_mday;

    if(tahun < tahunSekarang) return false;
    if(tahun == tahunSekarang && bulan < bulanSekarang) return false;
    if(tahun == tahunSekarang && bulan == bulanSekarang && hari < hariSekarang) return false;

    return true;
}

bool validJam(const string& jam){
    if(jam.length()!=5 || jam[2] != ':') return false;

    try{
        int hh = stoi(jam.substr(0,2));
        int mm = stoi(jam.substr(3,2));

        if(hh < 0 || hh > 23) return false;
        if(mm < 0 || mm > 59) return false;

        // Jam operasional restoran 07:00 - 22:00
        if(hh < 7) return false;
        if(hh > 22) return false;
        if(hh == 22 && mm > 0) return false;

        return true;
    }catch(...){
        return false;
    }
}

bool validTanggalDanJamReservasi(const string& tanggal, const string& jam){
    time_t sekarang = time(0);
    tm *waktuSekarang = localtime(&sekarang);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", waktuSekarang);

    string hariIni = buffer;

    if(tanggal == hariIni){
        int hhInput = stoi(jam.substr(0,2));
        int mmInput = stoi(jam.substr(3,2));

        int hhNow = waktuSekarang->tm_hour;
        int mmNow = waktuSekarang->tm_min;

        if(hhInput < hhNow) return false;
        if(hhInput == hhNow && mmInput <= mmNow) return false;
    }

    return true;
}


string inputNama(){
    string s;
    do{
        cout<<"Nama Pemesan   : ";
        getline(cin,s);
        if(validNama(s)) return s;
        cout<<"Nama hanya boleh huruf dan spasi!\n";
    }while(true);
}

string inputKontak(){
    string s;
    do{
        cout<<"Kontak Pemesan : ";
        getline(cin,s);
        if(validKontak(s)) return s;
        cout<<"Kontak harus angka 10-15 digit!\n";
    }while(true);
}

string inputTanggal(){
    string s;
    do{
        cout<<"Tanggal (YYYY-MM-DD): ";
        getline(cin,s);
        if(validTanggal(s)) return s;
        cout<<"Tanggal tidak valid atau sudah lampau!\n";
    }while(true);
}

string inputJam(){
    string s;
    do{
        cout<<"Jam (HH:MM)    : ";
        getline(cin,s);
        if(validJam(s)) return s;
        cout<<"Restoran buka mulai pukul 07:00 sampai dengan 22:00\n";
    }while(true);
}


// ==== FUNGSI UTAMA APLIKASI ====

/**
 * @brief Membatalkan reservasi yang sudah ada (hanya admin).
 * @param meja Array 2D dari semua meja.
 */
void batalkanReservasi(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    clearScreen();
    cout << "\n--- Pembatalan Reservasi ---\n";
    int jenisInput = inputAngka("Pilih jenis meja (0:Reguler, 1:VIP, 2:VVIP): ", 0, 2);
    int nomor = inputAngka("Masukkan nomor meja (1-5): ", 1, 5);

    JenisMeja jenis = static_cast<JenisMeja>(jenisInput);
    if (meja[jenis][nomor - 1].tersedia) {
        cout << "Meja ini belum dipesan.\n";
    } else {
        // Mengubah status meja di memori
        meja[jenis][nomor - 1].tersedia = true;
        meja[jenis][nomor - 1].pemesan = {"", ""};
        meja[jenis][nomor - 1].waktu = {"", ""};
        cout << "Reservasi meja " << nomor << " (" << jenisToString(jenis) << ") telah dibatalkan.\n";
        
        // Menyimpan semua data terbaru ke file untuk membuat perubahan permanen
        simpanSemuaDataKeFile(meja);
        cout << "Data file telah diperbarui.\n";
    }
}

/**
 * @brief Mencari reservasi berdasarkan nama atau kontak pemesan (hanya admin).
 * @param meja Array 2D dari semua meja.
 */
void cariReservasi(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    clearScreen();
    cout << "\n--- Cari Reservasi ---\n";
    string keyword = inputString("Masukkan Nama atau Kontak Pemesan: ");
    bool ditemukan = false;

    // Looping ke semua meja untuk mencari kecocokan
    for (int i = 0; i < JUMLAH_JENIS; i++) {
        for (int j = 0; j < JUMLAH_MEJA_PER_JENIS; j++) {
            // Hanya periksa meja yang tidak tersedia (sudah dipesan)
            if (!meja[i][j].tersedia) {
                // string::npos berarti "tidak ditemukan"
                if (meja[i][j].pemesan.nama.find(keyword) != string::npos || meja[i][j].pemesan.kontak.find(keyword) != string::npos) {
                    if (!ditemukan) {
                        cout << "\n--- Hasil Pencarian ---\n";
                    }
                    cout << "Ditemukan di Meja " << jenisToString(meja[i][j].jenis) << " " << meja[i][j].nomor << endl;
                    cout << "  Atas Nama: " << meja[i][j].pemesan.nama << " (" << meja[i][j].pemesan.kontak << ")\n";
                    cout << "  Waktu    : " << meja[i][j].waktu.tanggal << " jam " << meja[i][j].waktu.jam << "\n\n";
                    ditemukan = true;
                }
            }
        }
    }
    if (!ditemukan) {
        cout << "Reservasi dengan kata kunci '" << keyword << "' tidak ditemukan.\n";
    }
}

/**
 * @brief Mengubah detail reservasi yang sudah ada (hanya admin).
 * @param meja Array 2D dari semua meja.
 */
void ubahReservasi(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    clearScreen();
    cout << "\n--- Ubah Reservasi ---\n";
    int jenisInput = inputAngka("Pilih jenis meja yang akan diubah (0:Reguler, 1:VIP, 2:VVIP): ", 0, 2);
    int nomor = inputAngka("Masukkan nomor meja (1-5): ", 1, 5);
    
    JenisMeja jenis = static_cast<JenisMeja>(jenisInput);
    if (meja[jenis][nomor - 1].tersedia) {
        cout << "Meja ini tidak memiliki reservasi untuk diubah.\n";
        return;
    }

    Meja& targetMeja = meja[jenis][nomor - 1]; // Menggunakan referensi (&) agar perubahan langsung terjadi pada array
    cout << "\nData saat ini:\n";
    cout << "1. Nama   : " << targetMeja.pemesan.nama << "\n";
    cout << "2. Kontak : " << targetMeja.pemesan.kontak << "\n";
    cout << "3. Tanggal: " << targetMeja.waktu.tanggal << "\n";
    cout << "4. Jam    : " << targetMeja.waktu.jam << "\n";
    
    int pilihan = inputAngka("\nPilih data yang ingin diubah (1-4, atau 0 untuk selesai): ", 0, 4);

    switch(pilihan) {
        case 1: targetMeja.pemesan.nama = inputString("Masukkan nama baru: "); break;
        case 2: targetMeja.pemesan.kontak = inputString("Masukkan kontak baru: "); break;
        case 3: targetMeja.waktu.tanggal = inputString("Masukkan tanggal baru (YYYY-MM-DD): "); break;
        case 4: targetMeja.waktu.jam = inputString("Masukkan jam baru (HH:MM): "); break;
        case 0: cout << "Tidak ada perubahan.\n"; return;
    }

    cout << "Data berhasil diubah.\n";
    simpanSemuaDataKeFile(meja); // Menyimpan perubahan ke file
    cout << "Data file telah diperbarui.\n";
}

/**
 * @brief Memproses alur untuk melihat daftar meja dan membuat reservasi baru.
 * @param meja Array 2D dari semua meja.
 * @return false jika pengguna memilih untuk keluar, true jika ingin melanjutkan.
 */
bool prosesLihatDanReservasi(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    tampilkanSemuaMeja(meja);

    int jenisInput = inputAngka("Pilih jenis meja (0: Reguler, 1: VIP, 2: VVIP): ", 0, 2);
    JenisMeja jenis = static_cast<JenisMeja>(jenisInput);
    int nomor = inputAngka("Pilih nomor meja (1-5): ", 1, 5);

    if (!meja[jenis][nomor - 1].tersedia) {
        cout << "Meja sudah dipesan! Silakan pilih meja lain.\n";
        return true; // Kembali ke menu
    }

    // Menggunakan referensi agar lebih efisien
    Meja& targetMeja = meja[jenis][nomor - 1];
    targetMeja.pemesan.nama = inputNama();
    targetMeja.pemesan.kontak = inputKontak();
    targetMeja.waktu.tanggal = inputTanggal();
    targetMeja.waktu.jam = inputJam();
    targetMeja.tersedia = false;
    
    // Menambahkan reservasi baru ini ke file
    tambahkanReservasiKeFile(targetMeja);

    cout << "\nReservasi berhasil!\n";
    cetakStruk(targetMeja); // Cetak struk setelah berhasil
    int lanjutkan = inputAngka("Apakah Anda ingin melakukan transaksi lain? (1: Ya, 2: Tidak): ", 1, 2);
    return lanjutkan == 1;
}

/**
 * @brief Memproses login untuk admin.
 * @return true jika login berhasil, false jika gagal.
 */
bool loginSebagaiAdmin() {
    clearScreen();
    string username, password;
    cout << "\n===== LOGIN ADMIN =====\n";
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    if (username == "admin" && password == "admin123") {
        cout << "Login berhasil sebagai admin.\n";
        return true;
    } else {
        cout << "Login gagal. Username atau password salah.\n";
        return false;
    }
}


/**
 * @brief Fungsi menu utama yang menjadi pusat navigasi program.
 * Menampilkan menu yang berbeda untuk Admin dan Customer.
 * @param meja Array 2D dari semua meja.
 */
void menu(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    bool lanjut = true;
    bool isAdmin = false;

    clearScreen();
    cout << "\nSelamat datang di Sistem Reservasi Restoran!\n";
    cout << "\nLogin sebagai:\n1. Admin\n2. Customer\n";
    int tipe = inputAngka("Pilih (1-2): ", 1, 2);
    if (tipe == 1) {
        isAdmin = loginSebagaiAdmin();
        if (!isAdmin) return; // Jika login admin gagal, langsung keluar dari program
    }

    // Loop utama program
    while (lanjut) {
        clearScreen();
        cout << "\n======= SISTEM RESERVASI RESTORAN =======\n";
        
        // Tampilan menu dinamis berdasarkan peran pengguna
        if (isAdmin) {
            cout << "Anda login sebagai ADMIN.\n\n";
            cout << "1. Lihat Daftar Meja & Buat Reservasi\n";
            cout << "2. Cari Reservasi\n";
            cout << "3. Ubah Reservasi\n";
            cout << "4. Batalkan Reservasi\n";
            cout << "5. Keluar\n";
            int pilihan = inputAngka("Pilih menu (1-5): ", 1, 5);
            switch (pilihan) {
                case 1: if (!prosesLihatDanReservasi(meja)) lanjut = false; break;
                case 2: cariReservasi(meja); break;
                case 3: ubahReservasi(meja); break;
                case 4: batalkanReservasi(meja); break;
                case 5: lanjut = false; break;
            }
        } else { // Jika login sebagai Customer
            cout << "Anda login sebagai CUSTOMER.\n\n";
            cout << "1. Lihat Daftar Meja & Buat Reservasi\n";
            cout << "2. Keluar\n";
            int pilihan = inputAngka("Pilih menu (1-2): ", 1, 2);
            switch (pilihan) {
                case 1: if (!prosesLihatDanReservasi(meja)) lanjut = false; break;
                case 2: lanjut = false; break;
            }
        }
        
        // Jeda setelah setiap aksi agar pengguna bisa membaca output
        if (lanjut) {
            cout << "\nTekan Enter untuk kembali ke menu utama...";
            cin.get(); // Menunggu pengguna menekan Enter
        }
    }
     cout << "\nTerima kasih telah menggunakan sistem reservasi.\n";
}


/**
 * @brief Titik masuk utama program.
 */
int main() {
    Meja daftarMeja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS];
    
    // Alur program utama
    inisialisasiMeja(daftarMeja);     // 1. Siapkan semua meja sebagai tersedia
    muatReservasiDariFile(daftarMeja); // 2. Timpa status dengan data dari file
    
    menu(daftarMeja);                  // 3. Jalankan menu utama
    
    return 0; // Mengindikasikan program berakhir dengan sukses
}


/**
 * @brief Menulis ulang seluruh data reservasi dari memori ke file.
 * Fungsi ini sangat penting untuk operasi Ubah dan Batal.
 * Mode 'trunc' (truncate) akan menghapus isi file lama sebelum menulis yang baru.
 * @param meja Array 2D dari semua meja yang menyimpan state terbaru.
 */
void simpanSemuaDataKeFile(Meja meja[JUMLAH_JENIS][JUMLAH_MEJA_PER_JENIS]) {
    ofstream file("reservasi.txt", ios::trunc); 
    if (!file.is_open()) {
        cerr << "Kritis: Gagal membuka file untuk menyimpan perubahan!\n";
        return;
    }

    // Looping ke semua meja dan hanya menulis yang statusnya terpesan
    for (int i = 0; i < JUMLAH_JENIS; i++) {
        for (int j = 0; j < JUMLAH_MEJA_PER_JENIS; j++) {
            if (!meja[i][j].tersedia) {
                file << jenisToString(meja[i][j].jenis) << ","
                     << meja[i][j].nomor << ","
                     << meja[i][j].pemesan.nama << ","
                     << meja[i][j].pemesan.kontak << ","
                     << meja[i][j].waktu.tanggal << ","
                     << meja[i][j].waktu.jam << ","
                     << hargaMeja(meja[i][j].jenis) << endl;
            }
        }
    }
    file.close();
}
