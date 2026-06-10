#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Akun {
    string username;
    string password;
    string role;
};

struct Dokumen {
    int id;
    string namaDokumen;
    string namaPemilik;
    int jumlahHalaman;
    int estimasiWaktu;
    string status;
    string operatorInput;
};

Akun akun[100];
Dokumen dokumen[100];

int jumlahAkun = 0;
int jumlahDokumen = 0;

string userLogin = "";
string roleLogin = "";

void registrasi();
bool login();
void menuAdmin();
void menuUser();

void tambahDokumen();
void tampilDokumen();
void updateDokumen();
void hapusDokumen();

void cariDokumen();
void statistik();
void cetakLaporan();

int cariID(int id);

// --- Helper: cetak header ringkas ---
void header(const string& judul) {
    cout << "\n-- " << judul << " --\n";
}

int main() {
    akun[0] = {"admin", "admin123", "admin"};
    jumlahAkun++;

    int pilih;

    do {
        header("ANTREAN DOKUMEN PRINT");
        cout << "[1] Login\n";
        cout << "[2] Registrasi\n";
        cout << "[3] Keluar\n";
        cout << "> ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                if(login()) {
                    if(roleLogin == "admin") menuAdmin();
                    else menuUser();
                }
                break;
            case 2: registrasi(); break;
            case 3: cout << "Sampai jumpa.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while(pilih != 3);

    return 0;
}

void registrasi() {
    if(jumlahAkun >= 100) {
        cout << "Kapasitas akun penuh.\n";
        return;
    }

    header("REGISTRASI");
    cout << "Username : ";
    cin >> akun[jumlahAkun].username;
    cout << "Password : ";
    cin >> akun[jumlahAkun].password;

    akun[jumlahAkun].role = "user";
    jumlahAkun++;

    cout << "Registrasi berhasil.\n";
}

bool login() {
    string user, pass;

    header("LOGIN");
    cout << "Username : ";
    cin >> user;
    cout << "Password : ";
    cin >> pass;

    for(int i = 0; i < jumlahAkun; i++) {
        if(akun[i].username == user && akun[i].password == pass) {
            userLogin = akun[i].username;
            roleLogin = akun[i].role;
            cout << "Login berhasil. Halo, " << userLogin << ".\n";
            return true;
        }
    }

    cout << "Username atau password salah.\n";
    return false;
}

int cariID(int id) {
    for(int i = 0; i < jumlahDokumen; i++) {
        if(dokumen[i].id == id) return i;
    }
    return -1;
}

void tambahDokumen() {
    if(jumlahDokumen >= 100) {
        cout << "Kapasitas dokumen penuh.\n";
        return;
    }

    Dokumen d;
    d.id = jumlahDokumen + 1;

    cin.ignore();
    cout << "Nama Dokumen   : ";
    getline(cin, d.namaDokumen);
    cout << "Nama Pemilik   : ";
    getline(cin, d.namaPemilik);

    do {
        cout << "Jumlah Halaman : ";
        cin >> d.jumlahHalaman;
        if(d.jumlahHalaman <= 0)
            cout << "Harus lebih dari 0.\n";
    } while(d.jumlahHalaman <= 0);

    d.estimasiWaktu  = d.jumlahHalaman * 5;
    d.status         = "Menunggu";
    d.operatorInput  = userLogin;

    dokumen[jumlahDokumen++] = d;

    cout << "Dokumen ditambahkan. ID: " << d.id
         << ", Estimasi: " << d.estimasiWaktu << " detik.\n";
}

void tampilDokumen() {
    if(jumlahDokumen == 0) {
        cout << "Belum ada dokumen.\n";
        return;
    }

    header("DAFTAR DOKUMEN");

    for(int i = 0; i < jumlahDokumen; i++) {
        if(roleLogin == "user" && dokumen[i].operatorInput != userLogin)
            continue;

        cout << "\n  ID       : " << dokumen[i].id
             << "\n  Dokumen  : " << dokumen[i].namaDokumen
             << "\n  Pemilik  : " << dokumen[i].namaPemilik
             << "\n  Halaman  : " << dokumen[i].jumlahHalaman
             << "\n  Estimasi : " << dokumen[i].estimasiWaktu << " detik"
             << "\n  Status   : " << dokumen[i].status
             << "\n";
    }
}

void updateDokumen() {
    int id;
    cout << "ID Dokumen : ";
    cin >> id;

    int index = cariID(id);
    if(index == -1) { cout << "ID tidak ditemukan.\n"; return; }
    if(roleLogin == "user" && dokumen[index].operatorInput != userLogin) {
        cout << "Akses ditolak.\n"; return;
    }

    cin.ignore();
    cout << "Nama Dokumen Baru  : ";
    getline(cin, dokumen[index].namaDokumen);
    cout << "Jumlah Halaman Baru: ";
    cin >> dokumen[index].jumlahHalaman;

    dokumen[index].estimasiWaktu = dokumen[index].jumlahHalaman * 5;
    cout << "Dokumen diperbarui.\n";
}

void hapusDokumen() {
    int id;
    cout << "ID Dokumen : ";
    cin >> id;

    int index = cariID(id);
    if(index == -1) { cout << "ID tidak ditemukan.\n"; return; }
    if(roleLogin == "user" && dokumen[index].operatorInput != userLogin) {
        cout << "Akses ditolak.\n"; return;
    }

    for(int i = index; i < jumlahDokumen - 1; i++)
        dokumen[i] = dokumen[i + 1];

    jumlahDokumen--;
    cout << "Dokumen dihapus.\n";
}

void cariDokumen() {
    int id;
    cout << "ID Dokumen : ";
    cin >> id;

    int index = cariID(id);
    if(index == -1) { cout << "Data tidak ditemukan.\n"; return; }

    cout << "\n  Dokumen  : " << dokumen[index].namaDokumen
         << "\n  Pemilik  : " << dokumen[index].namaPemilik
         << "\n  Halaman  : " << dokumen[index].jumlahHalaman
         << "\n  Estimasi : " << dokumen[index].estimasiWaktu << " detik\n";
}

void statistik() {
    int totalHalaman = 0, totalEstimasi = 0;

    for(int i = 0; i < jumlahDokumen; i++) {
        totalHalaman  += dokumen[i].jumlahHalaman;
        totalEstimasi += dokumen[i].estimasiWaktu;
    }

    header("STATISTIK");
    cout << "  Dokumen       : " << jumlahDokumen    << "\n"
         << "  Total Halaman : " << totalHalaman     << "\n"
         << "  Total Estimasi: " << totalEstimasi    << " detik\n";
}

void cetakLaporan() {
    ofstream file("laporan_dokumen.txt");
    if(!file) { cout << "Gagal membuat file.\n"; return; }

    file << "LAPORAN DOKUMEN\n\n";
    for(int i = 0; i < jumlahDokumen; i++) {
        file << "ID       : " << dokumen[i].id           << "\n"
             << "Dokumen  : " << dokumen[i].namaDokumen  << "\n"
             << "Pemilik  : " << dokumen[i].namaPemilik  << "\n"
             << "Halaman  : " << dokumen[i].jumlahHalaman << "\n"
             << "Estimasi : " << dokumen[i].estimasiWaktu << "\n\n";
    }
    file.close();
    cout << "Laporan disimpan ke laporan_dokumen.txt\n";
}

void menuAdmin() {
    int pilih;
    do {
        header("MENU ADMIN");
        cout << "[1] Tambah Dokumen\n"
             << "[2] Tampilkan Dokumen\n"
             << "[3] Update Dokumen\n"
             << "[4] Hapus Dokumen\n"
             << "[5] Cari Dokumen\n"
             << "[6] Statistik\n"
             << "[7] Cetak Laporan\n"
             << "[8] Logout\n"
             << "> ";
        cin >> pilih;

        switch(pilih) {
            case 1: tambahDokumen(); break;
            case 2: tampilDokumen(); break;
            case 3: updateDokumen(); break;
            case 4: hapusDokumen();  break;
            case 5: cariDokumen();   break;
            case 6: statistik();     break;
            case 7: cetakLaporan();  break;
            case 8: cout << "Logout.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while(pilih != 8);
}

void menuUser() {
    int pilih;
    do {
        header("MENU USER");
        cout << "[1] Tambah Dokumen\n"
             << "[2] Dokumen Saya\n"
             << "[3] Update Dokumen\n"
             << "[4] Hapus Dokumen\n"
             << "[5] Cetak Laporan\n"
             << "[6] Logout\n"
             << "> ";
        cin >> pilih;

        switch(pilih) {
            case 1: tambahDokumen(); break;
            case 2: tampilDokumen(); break;
            case 3: updateDokumen(); break;
            case 4: hapusDokumen();  break;
            case 5: cetakLaporan();  break;
            case 6: cout << "Logout.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while(pilih != 6);
}