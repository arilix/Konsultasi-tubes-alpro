#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime> // Ditambahkan untuk penanganan waktu real-time

using namespace std;

// Global variabel untuk session login
string loggedInUser = ""; 
string userRole = "";     

// Deklarasi fungsi-fungsi agar bisa saling memanggil
void menuUtama();
void menuAwal();
void menuSetelahLogin();
void lakukanPemesanan();
void lihatPesananAnda();
void lihatGame();
void lihatJamKosong();
void menuProfile();
void menuSetting();
void menuAdmin();
void tambahGameOlehAdmin(); 

// Helper untuk memecah string berdasarkan delimiter '#'
vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;
    while (getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    return internal;
}

// Helper untuk mendapatkan tanggal dan jam real-time saat ini
string getWaktuSekarang() {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    
    char buffer[80];
    // Format: DD-MM-YYYY HH:MM:SS
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", now);
    return string(buffer);
}

// Helper untuk menghitung jumlah pesanan berjalan berdasarkan Konsol & Waktu
int hitungSlotTerpakai(string konsol, string waktu) {
    ifstream file("rental.txt");
    string line;
    int count = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> data = split(line, '#');
            // Format rental.txt baru: ID#User#Konsol#Durasi#Harga#Total#WaktuMain#WaktuOrderRealTime
            if (data.size() >= 7 && data[2] == konsol && data[6] == waktu) {
                count++;
            }
        }
        file.close();
    }
    return count;
}

// Inisialisasi Game Default jika file games.txt belum ada
void inisialisasiGameDefault() {
    ifstream fileCek("games.txt");
    if (!fileCek.is_open()) { 
        ofstream fileOut("games.txt");
        fileOut << "PS2#GTA San Andreas, Downhill Domination, Basara 2" << endl;
        fileOut << "PS3#PES 2013, God of War III, GTA V" << endl;
        fileOut << "PS4#FIFA 24, Ghost of Tsushima, Spider-Man" << endl;
        fileOut << "PS5#Resident Evil 4 Remake, Tekken 8, FC 25" << endl;
        fileOut << "Nintendo#Mario Kart 8, Zelda: Breath of the Wild" << endl;
        fileOut << "PS Box#Paket Koper Premium (Isi Game Bebas Request)" << endl;
        fileOut.close();
    } else {
        fileCek.close();
    }
}

void daftarAkun() {
    string username, password;
    cout << "\n===== DAFTAR AKUN =====\n";
    cout << "Username : "; cin >> username;
    cout << "Password : "; cin >> password;

    ifstream fileIn("users.txt");
    string line;
    bool sudahAda = false;
    if (fileIn.is_open()) {
        while (getline(fileIn, line)) {
            vector<string> data = split(line, '#');
            if (data.size() >= 1 && data[0] == username) {
                sudahAda = true;
                break;
            }
        }
        fileIn.close();
    }

    if (sudahAda) {
        cout << "\n[ERROR] Username \"" << username << "\" sudah terdaftar!\n";
        system("pause");
        return;
    }

    ofstream fileOut("users.txt", ios::app);
    fileOut << username << "#" << password << "#user" << endl;
    fileOut.close();

    cout << "\nAkun berhasil dibuat! Silakan kembali ke menu awal untuk Login.\n";
    system("pause");
}

bool login() {
    string username, password;
    cout << "\n===== LOGIN PAGE =====\n";
    cout << "Username : "; cin >> username;
    cout << "Password : "; cin >> password;

    // Bypass Admin Default
    if (username == "admin" && password == "admin") {
        loggedInUser = "admin";
        userRole = "admin";
        cout << "\nLogin Berhasil! Selamat Datang, Admin.\n";
        system("pause");
        return true;
    }

    ifstream file("users.txt");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> data = split(line, '#');
            if (data.size() >= 3 && data[0] == username && data[1] == password) {
                loggedInUser = data[0];
                userRole = data[2];
                file.close();
                cout << "\nLogin Berhasil! Selamat Datang, " << loggedInUser << ".\n";
                system("pause");
                return true;
            }
        }
        file.close();
    }

    cout << "\nUsername atau Password salah!\n";
    system("pause");
    return false;
}

void lakukanPemesanan() {
    int pilihanKonsol, durasi, pilihanWaktu;
    string jenisKonsol, slotWaktu;
    int hargaSatuan = 0; 

    cout << "\n===== LAKUKAN PEMESANAN (CREATE) =====\n";
    cout << "Pilih Konsol:\n";
    cout << "1. PS2 (Rp 3.000/jam - Di Rental)\n";
    cout << "2. PS3 (Rp 5.000/jam - Di Rental)\n";
    cout << "3. PS4 (Rp 8.000/jam - Di Rental)\n";
    cout << "4. PS5 (Rp 15.000/jam - Di Rental)\n";
    cout << "5. Nintendo Switch (Rp 10.000/jam - Di Rental)\n";
    cout << "6. PS Box (Rp 120.000/24 Jam - Dibawa Pulang)\n"; 
    cout << "Pilihan Anda: "; 
    cin >> pilihanKonsol;

    // Ambil waktu transaksi saat ini secara real-time
    string waktuOrder = getWaktuSekarang();

    // JIKA PILIH PS BOX (LOGIKA KHUSUS 24 JAM)
    if (pilihanKonsol == 6) {
        jenisKonsol = "PS Box";
        hargaSatuan = 120000;
        slotWaktu = "Paket 24J"; 
        
        int terpakai = hitungSlotTerpakai(jenisKonsol, slotWaktu);
        if (terpakai >= 3) {
            cout << "\n[MAAF] Semua unit PS Box sudah dibawa pulang pelanggan lain! (Maks 3 unit)\n";
            system("pause");
            return;
        }

        cout << "Mau sewa berapa hari? (1 hari = 24 Jam): "; 
        int hari; cin >> hari;
        durasi = hari * 24; 
        int totalHarga = hargaSatuan * hari;

        int idOrder = 1; string line; ifstream fileIn("rental.txt");
        while (getline(fileIn, line)) { idOrder++; } fileIn.close();

        ofstream fileOut("rental.txt", ios::app);
        // Menambahkan kolom waktuOrder di bagian akhir
        fileOut << idOrder << "#" << loggedInUser << "#" << jenisKonsol << "#" << durasi << "#" << hargaSatuan << "#" << totalHarga << "#" << slotWaktu << "#" << waktuOrder << endl;
        fileOut.close();

        cout << "\n====================================\n";
        cout << "       INVOICE RENTAL PS BOX        \n";
        cout << "====================================\n";
        cout << "Waktu Order: " << waktuOrder << "\n"; // Real-time
        cout << "ID Order   : " << idOrder << "\n";
        cout << "Pelanggan  : " << loggedInUser << "\n";
        cout << "Konsol     : " << jenisKonsol << " (Home Delivery)\n";
        cout << "Durasi     : " << hari << " Hari (" << durasi << " Jam)\n";
        cout << "Harga/Hari : Rp " << hargaSatuan << "\n";
        cout << "------------------------------------\n";
        cout << "TOTAL BAYAR: Rp " << totalHarga << "\n";
        cout << "====================================\n";
        cout << "Pesanan PS Box Berhasil Disimpan!\n";
        system("pause");
        return;
    }

    // JIKA PILIH OPSI RENTAL BIASA (1-5)
    switch(pilihanKonsol) {
        case 1: jenisKonsol = "PS2"; hargaSatuan = 3000; break;
        case 2: jenisKonsol = "PS3"; hargaSatuan = 5000; break;
        case 3: jenisKonsol = "PS4"; hargaSatuan = 8000; break;
        case 4: jenisKonsol = "PS5"; hargaSatuan = 15000; break;
        case 5: jenisKonsol = "Nintendo"; hargaSatuan = 10000; break;
        default: cout << "Pilihan tidak valid!\n"; system("pause"); return;
    }

    cout << "\nPilih Waktu Rental:\n";
    cout << "1. Pagi  (08:00 - 12:00)\n2. Siang (13:00 - 17:00)\n3. Malam (18:00 - 23:00)\nPilihan Waktu: ";
    cin >> pilihanWaktu;

    if (pilihanWaktu == 1) slotWaktu = "Pagi";
    else if (pilihanWaktu == 2) slotWaktu = "Siang";
    else if (pilihanWaktu == 3) slotWaktu = "Malam";
    else { cout << "Waktu tidak valid!\n"; system("pause"); return; }

    int terpakai = hitungSlotTerpakai(jenisKonsol, slotWaktu);
    if (terpakai >= 3) {
        cout << "\n[MAAF] Slot untuk " << jenisKonsol << " pada waktu " << slotWaktu << " Penuh! (Maks 3 device)\n";
        system("pause");
        return;
    }

    cout << "Durasi Rental (Jam): "; cin >> durasi;
    int totalHarga = hargaSatuan * durasi;

    int idOrder = 1; string line; ifstream fileIn("rental.txt");
    while (getline(fileIn, line)) { idOrder++; } fileIn.close();

    ofstream fileOut("rental.txt", ios::app);
    // Menambahkan kolom waktuOrder di bagian akhir
    fileOut << idOrder << "#" << loggedInUser << "#" << jenisKonsol << "#" << durasi << "#" << hargaSatuan << "#" << totalHarga << "#" << slotWaktu << "#" << waktuOrder << endl;
    fileOut.close();

    cout << "\n====================================\n";
    cout << "         INVOICE RENTAL PS          \n";
    cout << "====================================\n";
    cout << "Waktu Order: " << waktuOrder << "\n"; // Real-time
    cout << "ID Order   : " << idOrder << "\n";
    cout << "Pelanggan  : " << loggedInUser << "\n";
    cout << "Konsol     : " << jenisKonsol << "\n";
    cout << "Waktu Main : " << slotWaktu << "\n";
    cout << "Durasi     : " << durasi << " Jam\n";
    cout << "Harga/Jam  : Rp " << hargaSatuan << "\n";
    cout << "------------------------------------\n";
    cout << "TOTAL BAYAR: Rp " << totalHarga << "\n";
    cout << "====================================\n";
    cout << "Pesanan Berhasil Disimpan!\n";
    system("pause");
}

void lihatPesananAnda() {
    cout << "\n===== DATA RIWAYAT PESANAN (READ) =====\n";
    ifstream file("rental.txt");
    string line;
    vector<string> allRecords;
    int jumlahPesanan = 0;

    while (getline(file, line)) {
        allRecords.push_back(line);
        vector<string> data = split(line, '#');
        if (userRole == "admin" || data[1] == loggedInUser) {
            cout << "ID Order: " << data[0] << " | Pelanggan: " << data[1] << " | Konsol: " << data[2] 
                 << " | Sesi Waktu: " << data[6] << " | Durasi: " << data[3] << " Jam | Total: Rp " << data[5] << "\n";
            jumlahPesanan++;
        }
    }
    file.close();

    if (jumlahPesanan == 0) {
        cout << "Tidak ada riwayat pesanan.\n";
        system("pause");
        return;
    }

    int pilihan;
    cout << "\n1. Lihat Ulang Invoice\n2. Batalkan/Hapus Pesanan (Delete)\n0. Kembali\nPilihan: ";
    cin >> pilihan;

    if (pilihan == 1) {
        string idOrder;
        cout << "Masukkan ID Order: "; cin >> idOrder;
        bool found = false;
        for (const string& rec : allRecords) {
            vector<string> data = split(rec, '#');
            if (data[0] == idOrder && (userRole == "admin" || data[1] == loggedInUser)) {
                
                // Cek jika data waktu transaksi tersedia di file teks (indeks ke-7)
                string cetakWaktu = (data.size() >= 8) ? data[7] : "Tidak tercatat (Data Lama)";

                cout << "\n====================================\n";
                cout << "     INVOICE RENTAL PS (REPRINT)    \n";
                cout << "====================================\n";
                cout << "Waktu Order: " << cetakWaktu << "\n"; // Menampilkan waktu yang tersimpan
                cout << "ID Order   : " << data[0] << "\n";
                cout << "Pelanggan  : " << data[1] << "\n";
                cout << "Konsol     : " << data[2] << "\n";
                cout << "Waktu Sesi : " << data[6] << "\n";
                cout << "Durasi     : " << data[3] << " Jam\n";
                cout << "Harga Unit : Rp " << data[4] << "\n";
                cout << "------------------------------------\n";
                cout << "TOTAL BAYAR: Rp " << data[5] << "\n";
                cout << "====================================\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "\n[Error] ID Order tidak ditemukan!\n";
    } 
    else if (pilihan == 2) {
        string idOrder;
        cout << "Masukkan ID Order yang ingin dihapus: "; cin >> idOrder;
        ofstream fileOut("rental.txt");
        bool berhasilHapus = false;
        for (const string& rec : allRecords) {
            vector<string> data = split(rec, '#');
            if (data[0] == idOrder && (userRole == "admin" || data[1] == loggedInUser)) {
                berhasilHapus = true;
                continue;
            }
            fileOut << rec << endl;
        }
        fileOut.close();
        if (berhasilHapus) cout << "Pesanan ID " << idOrder << " berhasil dibatalkan (Slot dibebaskan)!\n";
        else cout << "Gagal menghapus pesanan.\n";
    }
    system("pause");
}

void lihatGame() {
    cout << "\n===== DAFTAR REKOMENDASI GAME =====\n";
    ifstream file("games.txt");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> data = split(line, '#');
            if (data.size() >= 2) {
                cout << "- " << data[0] << " : " << data[1] << endl;
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka data game.\n";
    }
    system("pause");
}

void lihatJamKosong() {
    cout << "\n===== STATUS SLOT DEVICE SINKRON (Sisa Device/Maks 3) =====\n";
    string daftarKonsol[] = {"PS2", "PS3", "PS4", "PS5", "Nintendo", "PS Box"};

    for (const string& k : daftarKonsol) {
        cout << "> KONSOL " << k << " :\n";
        if (k == "PS Box") {
            int terpakai = hitungSlotTerpakai(k, "Paket 24J");
            int sisa = 3 - terpakai;
            cout << "  - Status Home Delivery : Terbawa " << terpakai << "/3 Unit (Sisa Unit Ready: " << sisa << ")\n";
        } else {
            string daftarWaktu[] = {"Pagi", "Siang", "Malam"};
            for (const string& w : daftarWaktu) {
                int terpakai = hitungSlotTerpakai(k, w);
                int sisa = 3 - terpakai;
                cout << "  - Sesi " << w << " : Terisi " << terpakai << "/3 (Sisa Unit Ready: " << sisa << ")\n";
            }
        }
        cout << "--------------------------------------------------------\n";
    }
    system("pause");
}

void tambahGameOlehAdmin() {
    cout << "\n===== TAMBAH REKOMENDASI GAME BARU (ADMIN) =====\n";
    int pil;
    string targetKonsol, gameBaru;
    cout << "Pilih Konsol yang ingin ditambah gamenya:\n";
    cout << "1. PS2\n2. PS3\n3. PS4\n4. PS5\n5. Nintendo\n6. PS Box\nPilihan: "; cin >> pil;

    switch(pil) {
        case 1: targetKonsol = "PS2"; break;
        case 2: targetKonsol = "PS3"; break;
        case 3: targetKonsol = "PS4"; break;
        case 4: targetKonsol = "PS5"; break;
        case 5: targetKonsol = "Nintendo"; break;
        case 6: targetKonsol = "PS Box"; break;
        default: cout << "Pilihan salah.\n"; system("pause"); return;
    }

    cin.ignore(); 
    cout << "Masukkan Judul Game Baru: "; 
    getline(cin, gameBaru);

    ifstream fileIn("games.txt");
    string line;
    vector<string> updateGames;
    while (getline(fileIn, line)) {
        vector<string> data = split(line, '#');
        if (data[0] == targetKonsol) {
            string barisBaru = data[0] + "#" + data[1] + ", " + gameBaru;
            updateGames.push_back(barisBaru);
        } else {
            updateGames.push_back(line);
        }
    }
    fileIn.close();

    ofstream fileOut("games.txt");
    for (const string& g : updateGames) { fileOut << g << endl; }
    fileOut.close();

    cout << "\nGame \"" << gameBaru << "\" berhasil ditambahkan ke kategori " << targetKonsol << "!\n";
    system("pause");
}

void menuProfile() {
    cout << "\n===== PROFILE ANDA (READ & UPDATE) =====\n";
    ifstream fileIn("users.txt");
    string line, currentPass = "";
    vector<string> allUsers;

    while (getline(fileIn, line)) {
        allUsers.push_back(line);
        vector<string> data = split(line, '#');
        if (data[0] == loggedInUser) currentPass = data[1];
    }
    fileIn.close();

    cout << "1. Username : " << loggedInUser << "\n";
    cout << "2. Password : " << currentPass << "\n";
    cout << "Role Status : " << userRole << "\n";

    int pilihan;
    cout << "\n1. Ubah Username\n2. Ubah Password\n0. Kembali\nPilihan: "; cin >> pilihan;

    string dataBaru;
    if (pilihan == 1) {
        cout << "Username Baru: "; cin >> dataBaru;
        ofstream fileOut("users.txt");
        for (const string& usr : allUsers) {
            vector<string> data = split(usr, '#');
            if (data[0] == loggedInUser) fileOut << dataBaru << "#" << data[1] << "#" << data[2] << endl;
            else fileOut << usr << endl;
        }
        fileOut.close();
        loggedInUser = dataBaru;
        cout << "Username berhasil diperbarui!\n";
    } else if (pilihan == 2) {
        cout << "Password Baru: "; cin >> dataBaru;
        ofstream fileOut("users.txt");
        for (const string& usr : allUsers) {
            vector<string> data = split(usr, '#');
            if (data[0] == loggedInUser) fileOut << data[0] << "#" << dataBaru << "#" << data[2] << endl; 
            else fileOut << usr << endl;
        }
        fileOut.close();
        cout << "Password berhasil diperbarui!\n";
    }
    system("pause");
}

void menuSetting() {
    int pilihan;
    while(true) {
        system("cls");
        cout << "===== MENU SETTING =====\n";
        cout << "1. Pilih Bahasa (Current: Indonesia)\n2. Tentang Aplikasi\n3. Riwayat Rental\n4. Kembali\nPilihan: "; 
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "\n1. Bahasa Indonesia\n2. English\nPilihan: "; int p; cin >> p;
            if(p == 2) { system("start index_en.exe"); exit(0); }
        } 
        else if (pilihan == 2) {
            cout << "\n--- TENTANG APLIKASI ---\nNama APK  : Rental PS & Nintendo Dynamic File System\nDeveloper : Raviga Aringgo Pamungkas\n";
            system("pause");
        } 
        else if (pilihan == 3) { lihatPesananAnda(); } 
        else if (pilihan == 4) { return; }
    }
}

void menuAdmin() {
    int pilihan;
    while (true) {
        system("cls");
        cout << "===== PANEL KONTROL ADMIN =====\n";
        cout << "1. Lihat & Batalkan Semua Pesanan Pelanggan (CRUD)\n";
        cout << "2. Tambah Rekomendasi Game Baru\n";
        cout << "3. Cek Daftar Game Aktif\n";
        cout << "4. Cek Monitor Sinkronisasi Jam Kosong\n";
        cout << "5. Setting Aplikasi\n";
        cout << "6. Log Out\n";
        cout << "Pilihan Admin: "; cin >> pilihan;

        switch (pilihan) {
            case 1: lihatPesananAnda(); break;
            case 2: tambahGameOlehAdmin(); break;
            case 3: lihatGame(); break;
            case 4: lihatJamKosong(); break;
            case 5: menuSetting(); break;
            case 6:
                loggedInUser = ""; userRole = "";
                cout << "\nAdmin berhasil Log Out.\n"; system("pause"); return;
            default: cout << "Pilihan salah!\n"; system("pause");
        }
    }
}

void menuSetelahLogin() {
    if (userRole == "admin") { menuAdmin(); return; }
    int pilihan;
    while (true) {
        system("cls");
        cout << "===== MENU UTAMA RENTAL (LOGGED IN) =====\n";
        cout << "1. Lakukan pemesanan\n2. Pesanan Anda\n3. Lihat Game\n4. Lihat Jam Kosong\n5. Profile\n6. Setting\n7. Log Out\nPilihan: "; 
        cin >> pilihan;

        switch (pilihan) {
            case 1: lakukanPemesanan(); break;
            case 2: lihatPesananAnda(); break;
            case 3: lihatGame(); break;
            case 4: lihatJamKosong(); break;
            case 5: menuProfile(); break;
            case 6: menuSetting(); break;
            case 7: loggedInUser = ""; userRole = ""; return; 
            default: system("pause");
        }
    }
}

void menuAwal() {
    int pilihan;
    while (true) {
        system("cls");
        cout << "===== MENU DAFTAR / LOGIN =====\n";
        cout << "1. Login\n2. Daftar Akun\n0. Kembali\nPilihan: "; cin >> pilihan;
        if (pilihan == 1) { if (login()) menuSetelahLogin(); }
        else if (pilihan == 2) daftarAkun();
        else break;
    }
}

void menuUtama() {
    int pilihan;
    while (true) {
        system("cls");
        cout << "===== APLIKASI RENTAL PS & NINTENDO =====\n";
        cout << "1. Masuk APK\n0. Keluar APK\nPilihan: "; cin >> pilihan;
        if (pilihan == 1) menuAwal();
        else break;
    }
}

int main() {
    inisialisasiGameDefault(); 
    menuUtama();       
    return 0;
}