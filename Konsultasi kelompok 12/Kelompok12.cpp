#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// ===== PROTOTYPE =====

void registerAkun();
bool login();

void tambahProduk();
void tampilProduk();
void cariProduk();
void updateProduk();
void hapusProduk();
void statistik();
void cetakLaporan();
void transaksi();
void lihatInvoice();
void beliProduk();
void lihatStruk();
void menuAdmin();
void menuUser();

string roleLogin;
string usernameLogin;

struct Produk {
    int id;
    string nama;
    int stok;
    double harga;
};

// ================= REGISTER =================
void registerAkun() {

    string username, password;

    cout << "\n=== REGISTER ===\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    ofstream file("akun.txt", ios::app);

    file << username
         << "|"
         << password
         << "|user"
         << endl;

    file.close();

    cout << "\nAkun berhasil dibuat!\n";
}

// ================= LOGIN =================
bool login() {

    string user, pass;

    cout << "\n=== LOGIN ===\n";

    cout << "Username : ";
    cin >> user;

    cout << "Password : ";
    cin >> pass;

    ifstream file("akun.txt");

    string username, password, role;

    while(getline(file, username, '|')) {

        getline(file, password, '|');
        getline(file, role);

        if(user == username && pass == password) {

            roleLogin = role;
            usernameLogin = username;

            file.close();

            cout << "\nLogin berhasil!\n";

            return true;
        }
    }

    file.close();

    cout << "\nUsername atau Password salah!\n";

    return false;
}

// ================= BELI PRODUK ==================
void beliProduk() {

    tampilProduk();

    int idCari;
    int jumlah;

    cout << "\nID Produk : ";
    cin >> idCari;

    cout << "Jumlah Beli : ";
    cin >> jumlah;

    ifstream file("produk.txt");
    ofstream temp("temp.txt");

    string id, nama, stok, harga;

    bool ditemukan = false;

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        if(stoi(id) == idCari) {

            ditemukan = true;

            int stokLama = stoi(stok);

            if(jumlah > stokLama) {

                cout << "\nStok tidak cukup!\n";

                temp << id << "|"
                     << nama << "|"
                     << stok << "|"
                     << harga << endl;

                continue;
            }

            double hargaProduk = stod(harga);

            double total = hargaProduk * jumlah;

            double bayar;

            cout << "\nTotal Belanja : Rp" << total << endl;

            cout << "Bayar : Rp";
            cin >> bayar;

            if(bayar < total) {

                cout << "\nUang tidak cukup!\n";

                temp << id << "|"
                     << nama << "|"
                     << stok << "|"
                     << harga << endl;

                continue;
            }

            double kembalian = bayar - total;

            int stokBaru = stokLama - jumlah;

            temp << id << "|"
                 << nama << "|"
                 << stokBaru << "|"
                 << harga << endl;

            ofstream struk("struk.txt");

            struk << "=================================\n";
            struk << "          STRUK BELANJA\n";
            struk << "=================================\n";
            struk << "Pembeli  : " << usernameLogin << endl;
            struk << "Produk   : " << nama << endl;
            struk << "Harga    : " << hargaProduk << endl;
            struk << "Jumlah   : " << jumlah << endl;
            struk << "---------------------------------\n";
            struk << "Total    : " << total << endl;
            struk << "Bayar    : " << bayar << endl;
            struk << "Kembali  : " << kembalian << endl;
            struk << "=================================\n";

            struk.close();

            cout << "\nPembelian berhasil!\n";
            cout << "Kembalian : Rp" << kembalian << endl;
            cout << "Struk berhasil dibuat!\n";
        }
        else {

            temp << id << "|"
                 << nama << "|"
                 << stok << "|"
                 << harga << endl;
        }
    }

    file.close();
    temp.close();

    remove("produk.txt");
    rename("temp.txt", "produk.txt");

    if(!ditemukan) {
        cout << "\nProduk tidak ditemukan!\n";
    }
}

// ================= Lihat Struk ==================
void lihatStruk() {

    ifstream file("struk.txt");

    if(!file) {

        cout << "\nBelum ada struk!\n";
        return;
    }

    string baris;

    cout << endl;

    while(getline(file, baris)) {

        cout << baris << endl;
    }

    file.close();
}

// ================= Menu User ====================
void menuUser() {

    int pilih;

    do {

        cout << "\n===== MENU USER =====\n";
        cout << "1. Tampilkan Produk\n";
        cout << "2. Cari Produk\n";
        cout << "3. Beli Produk\n";
        cout << "4. Lihat Struk\n";
        cout << "5. Logout\n";

        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                tampilProduk();
                break;

            case 2:
                cariProduk();
                break;

            case 3:
                beliProduk();
                break;

            case 4:
                lihatStruk();
                break;

            case 5:
                cout << "\nLogout...\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while(pilih != 5);
}

// ================= TAMBAH PRODUK =================
void tambahProduk() {

    Produk p;

    cout << "\n=== TAMBAH PRODUK ===\n";

    cout << "ID Produk : ";
    cin >> p.id;

    cin.ignore();

    cout << "Nama Produk : ";
    getline(cin, p.nama);

    cout << "Stok : ";
    cin >> p.stok;

    cout << "Harga : ";
    cin >> p.harga;

    ofstream file("produk.txt", ios::app);

    file << p.id << "|"
         << p.nama << "|"
         << p.stok << "|"
         << p.harga
         << endl;

    file.close();

    cout << "\nProduk berhasil ditambahkan!\n";
}

// ================= TAMPIL PRODUK =================
void tampilProduk() {

    ifstream file("produk.txt");

    string id, nama, stok, harga;

    cout << "\n===================================================\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Nama"
         << setw(10) << "Stok"
         << setw(15) << "Harga" << endl;
    cout << "===================================================\n";

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        cout << left
             << setw(10) << id
             << setw(20) << nama
             << setw(10) << stok
             << setw(15) << harga
             << endl;
    }

    file.close();
}

// ================= CARI PRODUK =================
void cariProduk() {

    string cari;
    bool ditemukan = false;

    cin.ignore();

    cout << "\nMasukkan nama produk : ";
    getline(cin, cari);

    ifstream file("produk.txt");

    string id, nama, stok, harga;

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        if(nama == cari) {

            cout << "\nData ditemukan!\n";

            cout << "ID    : " << id << endl;
            cout << "Nama  : " << nama << endl;
            cout << "Stok  : " << stok << endl;
            cout << "Harga : " << harga << endl;

            ditemukan = true;
            break;
        }
    }

    if(!ditemukan)
        cout << "\nProduk tidak ditemukan!\n";

    file.close();
}

// ================= HAPUS PRODUK =================
void hapusProduk() {

    int idHapus;

    cout << "\nMasukkan ID Produk : ";
    cin >> idHapus;

    ifstream file("produk.txt");
    ofstream temp("temp.txt");

    string id, nama, stok, harga;

    bool ditemukan = false;

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        if(stoi(id) != idHapus) {

            temp << id << "|"
                 << nama << "|"
                 << stok << "|"
                 << harga
                 << endl;
        }
        else {
            ditemukan = true;
        }
    }

    file.close();
    temp.close();

    remove("produk.txt");
    rename("temp.txt", "produk.txt");

    if(ditemukan)
        cout << "\nProduk berhasil dihapus!\n";
    else
        cout << "\nProduk tidak ditemukan!\n";
}

// ================= UPDATE PRODUK =================
void updateProduk() {

    int idCari;

    cout << "\nMasukkan ID Produk : ";
    cin >> idCari;

    ifstream file("produk.txt");
    ofstream temp("temp.txt");

    string id, nama, stok, harga;

    bool ditemukan = false;

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        if(stoi(id) == idCari) {

            Produk p;

            p.id = idCari;

            cin.ignore();

            cout << "Nama Baru : ";
            getline(cin, p.nama);

            cout << "Stok Baru : ";
            cin >> p.stok;

            cout << "Harga Baru : ";
            cin >> p.harga;

            temp << p.id << "|"
                 << p.nama << "|"
                 << p.stok << "|"
                 << p.harga
                 << endl;

            ditemukan = true;
        }
        else {

            temp << id << "|"
                 << nama << "|"
                 << stok << "|"
                 << harga
                 << endl;
        }
    }

    file.close();
    temp.close();

    remove("produk.txt");
    rename("temp.txt", "produk.txt");

    if(ditemukan)
        cout << "\nProduk berhasil diupdate!\n";
    else
        cout << "\nProduk tidak ditemukan!\n";
}

// ================= STATISTIK =================
void statistik() {

    ifstream file("produk.txt");

    string id, nama, stok, harga;

    int jumlahProduk = 0;
    int totalStok = 0;

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        jumlahProduk++;
        totalStok += stoi(stok);
    }

    file.close();

    cout << "\n=== STATISTIK ===\n";
    cout << "Jumlah Produk : " << jumlahProduk << endl;
    cout << "Total Stok    : " << totalStok << endl;
}

// ================= LAPORAN =================
void cetakLaporan() {

    ifstream file("produk.txt");
    ofstream laporan("laporan.txt");

    string id, nama, stok, harga;

    laporan << "===== LAPORAN PRODUK =====\n\n";

    while(getline(file, id, '|')) {

        getline(file, nama, '|');
        getline(file, stok, '|');
        getline(file, harga);

        laporan << "ID    : " << id << endl;
        laporan << "Nama  : " << nama << endl;
        laporan << "Stok  : " << stok << endl;
        laporan << "Harga : " << harga << endl;
        laporan << "-------------------------\n";
    }

    file.close();
    laporan.close();

    cout << "\nLaporan berhasil dibuat!\n";
}

// ================= MENU TRANSAKSI =================
void transaksi() {

    tampilProduk();

    int idCari;
    int jumlah;

    cout << "\nID Produk : ";
    cin >> idCari;

    cout << "Jumlah Beli : ";
    cin >> jumlah;

    ifstream file("produk.txt");
    ofstream temp("temp.txt");

    string id,nama,stok,harga;

    bool ditemukan = false;

    while(getline(file,id,'|')) {

        getline(file,nama,'|');
        getline(file,stok,'|');
        getline(file,harga);

        if(stoi(id) == idCari) {

            ditemukan = true;

            int stokLama = stoi(stok);

            if(jumlah > stokLama) {

                cout << "\nStok tidak cukup!\n";

                temp << id << "|"
                     << nama << "|"
                     << stok << "|"
                     << harga << endl;

                continue;
            }

            int stokBaru = stokLama - jumlah;

            double hargaProduk = stod(harga);

            double total = hargaProduk * jumlah;

            temp << id << "|"
                 << nama << "|"
                 << stokBaru << "|"
                 << harga << endl;

            ofstream invoice("invoice.txt");

            invoice << "=========== INVOICE ===========" << endl;
            invoice << "Kasir : " << usernameLogin << endl;
            invoice << "Produk : " << nama << endl;
            invoice << "Harga : " << hargaProduk << endl;
            invoice << "Jumlah : " << jumlah << endl;
            invoice << "Total : " << total << endl;
            invoice << "===============================" << endl;

            invoice.close();

            cout << "\nTransaksi berhasil!\n";
            cout << "Invoice tersimpan.\n";
        }
        else {

            temp << id << "|"
                 << nama << "|"
                 << stok << "|"
                 << harga << endl;
        }
    }

    file.close();
    temp.close();

    remove("produk.txt");
    rename("temp.txt","produk.txt");

    if(!ditemukan)
        cout << "\nProduk tidak ditemukan!\n";
}

// ================= MENU INVOICE ===============
void lihatInvoice() {

    ifstream file("invoice.txt");

    string baris;

    cout << endl;

    while(getline(file, baris)) {

        cout << baris << endl;
    }

    file.close();
}

// ================= MENU ADMIN =================
void menuAdmin() {

    int pilih;

    do {

        cout << "\n===== MENU ADMIN =====\n";

        cout << "Login Sebagai : "
             << usernameLogin
             << endl;

        cout << "\n1. Tambah Produk\n";
        cout << "2. Tampilkan Produk\n";
        cout << "3. Cari Produk\n";
        cout << "4. Update Produk\n";
        cout << "5. Hapus Produk\n";
        cout << "6. Statistik\n";
        cout << "7. Cetak Laporan\n";
        cout << "8. Transaksi\n";
        cout << "9. Lihat Invoice\n";
        cout << "10. Logout\n";

        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih) {

    case 1: tambahProduk(); break;
    case 2: tampilProduk(); break;
    case 3: cariProduk(); break;
    case 4: updateProduk(); break;
    case 5: hapusProduk(); break;
    case 6: statistik(); break;
    case 7: cetakLaporan(); break;
    case 8: transaksi(); break;
    case 9: lihatInvoice(); break;
    case 10:
        cout << "\nLogout...\n";
        break;

    default:
        cout << "\nPilihan tidak valid!\n";
      }

    } while(pilih != 10);
}

// ================= MAIN =================
int main() {

    int pilih;

    do {

        cout << "\n===== SISTEM KASIR TOKO =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih) {

            case 1:
            if(login()) {
                
                if(roleLogin == "admin") {

                    menuAdmin();

                } else {

                    menuUser();
                }
            }

            break; 

    

            case 2:
                registerAkun();
                break;

            case 3:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while(pilih != 3);

    return 0;
}