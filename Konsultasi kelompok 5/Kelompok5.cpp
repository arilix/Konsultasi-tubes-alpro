#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Akun {
    string username;
    string password;
    string role;
};

struct Tiket {
    string pembeli;
    string judul;
    string hari;
    string jam;
    string kursi;
    int harga;
};

struct Film {
    int id;
    string judul;
    string genre;
    int harga;
    bool kursi[5][5]; //denah kursi 5x5
};


vector<Akun> daftarAkun;
vector<Film> daftarFilm;
vector<Tiket> riwayatTiket;
Akun akunLogin;
int filmIdCounter = 101;

void header();
void registerAkun();
bool loginAkun();
void menuAdmin();
void menuUser();
void tambahFilm();
void tampilkanFilm();
void tampilkanKursi(int idx);
void beliTiket();
void lihatTiketSaya();


int main() {
    daftarAkun.push_back({"admin", "123", "admin"});

    Film f1 = {filmIdCounter++, "The Batman", "Action", 50000, {false}};
    Film f2 = {filmIdCounter++, "Spirited Away", "Anime", 45000, {false}};
    daftarFilm.push_back(f1);
    daftarFilm.push_back(f2);

    int pilihan;
    do {
        header();
        cout << "Selamat Datang di Bioskop Gashima" << endl;
        cout << "1. Login\n2. Buat Akun\n0. Keluar\nPilih: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (pilihan == 1) {
            if (loginAkun()) {
                if (akunLogin.role == "admin") menuAdmin();
                else menuUser();
            }
        } else if (pilihan == 2) {
            registerAkun();
        }
    } while (pilihan != 0);

    return 0;
}


void header() {
    cout << "\n==========================================" << endl;
    cout << "        BIOSKOP GASHIMA MANAGEMENT        " << endl;
    cout << "==========================================" << endl;
}

void registerAkun() {
    Akun baru;
    cout << "\n--- REGISTRASI USER ---" << endl;
    cout << "Masukkan Username: "; cin >> baru.username;
    cout << "Masukkan Password: "; cin >> baru.password;
    baru.role = "user";
    daftarAkun.push_back(baru);
    cout << "Registrasi Berhasil! Silakan Login.\n";
}

bool loginAkun() {
    string u, p;
    cout << "\n--- LOGIN ---" << endl;
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    for (const auto& a : daftarAkun) {
        if (a.username == u && a.password == p) {
            akunLogin = a;
            cout << "Login Berhasil! Selamat datang, " << u << ".\n";
            return true;
        }
    }
    cout << "Login Gagal! Username atau Password salah.\n";
    return false;
}

void menuAdmin() {
    int pil;
    do {
        header();
        cout << "Role: ADMIN | User: " << akunLogin.username << endl;
        cout << "1. Tambah Film\n2. Lihat Daftar Film\n0. Logout\nPilih: ";
        cin >> pil;
        switch(pil) {
            case 1: tambahFilm(); break;
            case 2: tampilkanFilm(); break;
        }
    } while (pil != 0);
}

void menuUser() {
    int pil;
    do {
        header();
        cout << "Role: USER | User: " << akunLogin.username << endl;
        cout << "1. Beli Tiket Bioskop\n2. Lihat Tiket Saya\n0. Logout\nPilih: ";
        cin >> pil;
        switch(pil) {
            case 1: beliTiket(); break;
            case 2: lihatTiketSaya(); break;
        }
    } while (pil != 0);
}

void tambahFilm() {
    Film f;
    f.id = filmIdCounter++;
    cin.ignore();
    cout << "Masukkan Judul Film: "; getline(cin, f.judul);
    cout << "Masukkan Genre     : "; getline(cin, f.genre);
    cout << "Masukkan Harga     : "; cin >> f.harga;

    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++) f.kursi[i][j] = false;

    daftarFilm.push_back(f);
    cout << "Film Berhasil Ditambahkan!\n";
}

void tampilkanFilm() {
    if (daftarFilm.empty()) {
        cout << "Belum ada film yang tersedia.\n";
        return;
    }
    cout << "\n" << left << setw(5) << "ID" << setw(20) << "Judul" << setw(15) << "Genre" << "Harga" << endl;
    cout << "------------------------------------------------------------\n";
    for (const auto& f : daftarFilm) {
        cout << left << setw(5) << f.id << setw(20) << f.judul << setw(15) << f.genre << "Rp" << f.harga << endl;
    }
}

void tampilkanKursi(int idx) {
    cout << "\nDenah Kursi (X = Terisi, [ ] = Kosong):" << endl;
    cout << "    1   2   3   4   5" << endl;
    for (int i = 0; i < 5; i++) {
        cout << (char)('A' + i) << " ";
        for (int j = 0; j < 5; j++) {
            if (daftarFilm[idx].kursi[i][j]) cout << "[X] ";
            else cout << "[ ] ";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
}

void beliTiket() {
    tampilkanFilm();
    int idCari, idx = -1;
    cout << "\nPilih ID Film (0 untuk Batal): "; cin >> idCari;
    if (idCari == 0) return;

    for (int i = 0; i < (int)daftarFilm.size(); i++) {
        if (daftarFilm[i].id == idCari) { idx = i; break; }
    }

    if (idx == -1) { cout << "ID Film tidak ditemukan!\n"; return; }

    // jadwal film
    string jamArr[] = {"14:00", "17:00", "20:00"};
    string hariArr[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

    cout << "\n>>> INFORMASI PENAYANGAN FILM: " << daftarFilm[idx].judul << " <<<" << endl;
    cout << "Tersedia setiap hari (" << hariArr[0] << "-" << hariArr[6] << ")" << endl;
    cout << "Jam Tayang: ";
    for(int i=0; i<3; i++) cout << "[" << jamArr[i] << "] ";
    cout << "\n------------------------------------------------" << endl;

    // pilih hari
    int hPil;
    cout << "Pilih Hari:\n";
    for(int i=0; i<7; i++) cout << i+1 << ". " << hariArr[i] << endl;
    cout << "Pilih (1-7 atau 0 untuk Batal): "; cin >> hPil;
    if (hPil < 1 || hPil > 7) return;

    // pilih jam
    int jPil;
    cout << "\nPilih Jam Tayang untuk hari " << hariArr[hPil-1] << ":" << endl;
    for(int i=0; i<3; i++) cout << i+1 << ". " << jamArr[i] << endl;
    cout << "Pilih (1-3 atau 0 untuk Batal): "; cin >> jPil;
    if (jPil < 1 || jPil > 3) return;

    // jumlah tiket
    int jml;
    cout << "\nBerapa tiket yang ingin dibeli? "; cin >> jml;
    if (jml <= 0) return;

    vector<Tiket> tempKeranjang;
    for (int i = 1; i <= jml; i++) {
        tampilkanKursi(idx);
        char barisInput; int kolom;
        cout << "Tiket ke-" << i << " dari " << jml << endl;
        cout << "Pilih Kursi (Contoh: A 1) atau Ketik '0 0' untuk BATAL SEMUA: ";
        cin >> barisInput >> kolom;

        if (barisInput == '0') {
            for(auto& t : tempKeranjang) {
                int rb = t.kursi[0] - 'A';
                int rk = (t.kursi[1] - '0') - 1;
                daftarFilm[idx].kursi[rb][rk] = false;
            }
            cout << "Pemesanan dibatalkan!\n";
            return;
        }

        int b = toupper(barisInput) - 'A';
        int k = kolom - 1;

        if (b >= 0 && b < 5 && k >= 0 && k < 5 && !daftarFilm[idx].kursi[b][k]) {
            daftarFilm[idx].kursi[b][k] = true;
            Tiket t = {akunLogin.username, daftarFilm[idx].judul, hariArr[hPil-1], jamArr[jPil-1],
                       string(1, toupper(barisInput)) + to_string(kolom), daftarFilm[idx].harga};
            tempKeranjang.push_back(t);
        } else {
            cout << "Kursi tidak valid atau sudah terisi! Silakan pilih kursi lain.\n";
            i--;
        }
    }

    for(const auto& t : tempKeranjang) riwayatTiket.push_back(t);

    //struk pembelian
    cout << "\n==========================================" << endl;
    cout << "          STRUK PEMBELIAN BERHASIL        " << endl;
    cout << "==========================================" << endl;
    cout << "Pembeli  : " << akunLogin.username << endl;
    cout << "Film     : " << daftarFilm[idx].judul << endl;
    cout << "Jadwal   : " << hariArr[hPil-1] << " | " << jamArr[jPil-1] << endl;
    cout << "Kursi    : ";
    for(auto& t : tempKeranjang) cout << "[" << t.kursi << "] ";
    cout << "\nTotal    : Rp" << jml * daftarFilm[idx].harga << endl;
    cout << "==========================================" << endl;
    cout << "Pemesanan sukses! Kembali ke menu utama..." << endl;
}

void lihatTiketSaya() {
    header();
    cout << "DAFTAR TIKET SAYA (" << akunLogin.username << ")" << endl;
    bool found = false;
    int no = 1;
    for (const auto& t : riwayatTiket) {
        if (t.pembeli == akunLogin.username) {
            cout << no++ << ". " << t.judul << " | " << t.hari << ", " << t.jam << " | Kursi: " << t.kursi << endl;
            found = true;
        }
    }
    if (!found) cout << "Anda belum memiliki riwayat pembelian tiket.\n";
    cout << "------------------------------------------" << endl;
}
