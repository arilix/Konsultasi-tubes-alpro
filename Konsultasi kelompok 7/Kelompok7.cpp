#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// ================= STRUCT =================
struct Akun {
    string username;
    string password;
    string role;
};

struct Tiket {
    int id;
    string username; // pemilik
    string asal;
    string tujuan;
    int harga;
};

// ================= GLOBAL =================
vector<Akun> daftarAkun;
vector<Tiket> daftarTiket;
int idCounter = 1;

// ================= REGISTER =================
void registerAkun() {
    Akun a;
    cout << "\n=== REGISTER ===\n";
    cout << "Username: "; cin >> a.username;
    cout << "Password: "; cin >> a.password;
    cout << "Role (admin/user): "; cin >> a.role;

    if (a.username == "" || a.password == "") {
        cout << "Data tidak boleh kosong!\n";
        return;
    }

    daftarAkun.push_back(a);
    cout << "Registrasi berhasil!\n";
}

// ================= LOGIN =================
Akun loginAkun() {
    string u, p;
    cout << "\n=== LOGIN ===\n";
    cout << "Username: "; cin >> u;
    cout << "Password: "; cin >> p;

    for (auto a : daftarAkun) {
        if (a.username == u && a.password == p) {
            cout << "Login berhasil!\n";
            return a;
        }
    }

    cout << "Login gagal!\n";
    return {"", "", ""};
}

// ================= TAMBAH =================
void tambahTiket(string user) {
    Tiket t;
    t.id = idCounter++;
    t.username = user;

    cout << "\n=== TAMBAH TIKET ===\n";
    cout << "Asal: "; cin >> t.asal;
    cout << "Tujuan: "; cin >> t.tujuan;
    cout << "Harga: "; cin >> t.harga;

    if (t.asal == "" || t.tujuan == "") {
        cout << "Data tidak boleh kosong!\n";
        return;
    }

    if (t.harga < 0) {
        cout << "Harga tidak boleh negatif!\n";
        return;
    }

    daftarTiket.push_back(t);
    cout << "Tiket berhasil ditambahkan. ID: " << t.id << endl;
}

// ================= TAMPIL (SHARED DATA) =================
void tampilTiket() {
    cout << "\n=== DATA SEMUA TIKET ===\n";
    if (daftarTiket.empty()) {
        cout << "Belum ada data.\n";
        return;
    }

    for (auto t : daftarTiket) {
        cout << "ID: " << t.id
             << " | Asal: " << t.asal
             << " | Tujuan: " << t.tujuan
             << " | Harga: " << t.harga
             << " | Pemesan: " << t.username << endl;
    }
}

// ================= TAMPIL MILIK SENDIRI =================
void tiketSaya(string user) {
    cout << "\n=== TIKET SAYA ===\n";
    bool ada = false;

    for (auto t : daftarTiket) {
        if (t.username == user) {
            cout << "ID: " << t.id
                 << " | " << t.asal << " -> " << t.tujuan
                 << " | Harga: " << t.harga << endl;
            ada = true;
        }
    }

    if (!ada) cout << "Tidak ada tiket.\n";
}

// ================= UPDATE =================
void updateTiket(string role, string user) {
    int id;
    cout << "Masukkan ID: "; cin >> id;

    for (auto &t : daftarTiket) {
        if (t.id == id) {
            if (role != "admin" && t.username != user) {
                cout << "Akses ditolak!\n";
                return;
            }

            cout << "Asal baru: "; cin >> t.asal;
            cout << "Tujuan baru: "; cin >> t.tujuan;
            cout << "Harga baru: "; cin >> t.harga;

            if (t.harga < 0) {
                cout << "Harga tidak valid!\n";
                return;
            }

            cout << "Update berhasil!\n";
            return;
        }
    }
    cout << "ID tidak ditemukan!\n";
}

// ================= HAPUS =================
void hapusTiket(string role, string user) {
    if (role == "admin") tampilTiket();
    else tiketSaya(user);

    int id;
    cout << "Masukkan ID: "; cin >> id;

    for (int i = 0; i < daftarTiket.size(); i++) {
        if (daftarTiket[i].id == id) {
            if (role != "admin" && daftarTiket[i].username != user) {
                cout << "Akses ditolak!\n";
                return;
            }

            daftarTiket.erase(daftarTiket.begin() + i);
            cout << "Data berhasil dihapus!\n";
            return;
        }
    }
    cout << "ID tidak ditemukan!\n";
}

// ================= STATISTIK =================
void statistik() {
    int total = daftarTiket.size();
    int totalHarga = 0;

    for (auto t : daftarTiket) {
        totalHarga += t.harga;
    }

    cout << "\n=== STATISTIK ===\n";
    cout << "Total Tiket: " << total << endl;
    cout << "Total Pendapatan: " << totalHarga << endl;
}

// ================= CETAK =================
void cetakLaporan() {
    ofstream file("laporan.txt");

    for (auto t : daftarTiket) {
        file << "ID: " << t.id
             << " | " << t.asal
             << " -> " << t.tujuan
             << " | Harga: " << t.harga
             << " | User: " << t.username << endl;
    }

    file.close();
    cout << "Laporan berhasil disimpan ke laporan.txt\n";
}

// ================= MAIN =================
int main() {
    int pilihan;

    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Login\n2. Register\n3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 2) registerAkun();

        else if (pilihan == 1) {
            Akun user = loginAkun();
            if (user.username == "") continue;

            int menu;
            do {
                cout << "\n=== MENU ===\n";
                cout << "1. Tambah Tiket\n";
                cout << "2. Tampil Semua Tiket\n";
                cout << "3. Tiket Saya\n";
                cout << "4. Update Tiket\n";
                cout << "5. Hapus Tiket\n";
                cout << "6. Statistik (Admin)\n";
                cout << "7. Cetak Laporan\n";
                cout << "8. Logout\n";
                cout << "Pilih: ";
                cin >> menu;

                switch(menu) {
                    case 1: tambahTiket(user.username); break;
                    case 2: tampilTiket(); break;
                    case 3: tiketSaya(user.username); break;
                    case 4: updateTiket(user.role, user.username); break;
                    case 5: hapusTiket(user.role, user.username); break;
                    case 6:
                        if (user.role == "admin") statistik();
                        else cout << "Akses ditolak!\n";
                        break;
                    case 7: cetakLaporan(); break;
                    case 8: break;
                    default: cout << "Inputan tidak valid!\n"; break;
                }

            } while (menu != 8);
        } else if (pilihan != 3) {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 3);
    
    return 0;
}