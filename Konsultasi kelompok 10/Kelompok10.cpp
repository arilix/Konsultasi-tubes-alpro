#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

struct Buku {
string judul;
string kode;
string tglPinjam;
string tglKembali;
long long durasi;
};

bool isAngka(string s) {
for (char c : s) {
if (!isdigit(c)) return false;
}
return true;
}

bool isGmail(string email) {
return email.find("@gmail.com") != string::npos;
}

long long hitungSelisih(string tglAwal, string tglAkhir) {
struct tm tm1 = {0}, tm2 = {0};
int d, m, y;

sscanf(tglAwal.c_str(), "%d/%d/%d", &d, &m, &y);
tm1.tm_mday = d;
tm1.tm_mon = m - 1;
tm1.tm_year = y + 100;

sscanf(tglAkhir.c_str(), "%d/%d/%d", &d, &m, &y);
tm2.tm_mday = d;
tm2.tm_mon = m - 1;
tm2.tm_year = y + 100;

time_t t1 = mktime(&tm1);
time_t t2 = mktime(&tm2);

if (t1 != -1 && t2 != -1) {
    return difftime(t2, t1) / (60 * 60 * 24);
}
return -1;

}

int main() {
string nama, telp, email;
int jumlahBuku;
char konfirmasi;

do {
    vector<Buku> daftarBuku;
    string tglPinjamGlobal;

    cout << "===========================================\n";
    cout << "   Selamat datang di Perpustakaan Negeri   \n";
    cout << "===========================================\n";

    cout << "Nama Peminjam : ";
    getline(cin >> ws, nama);

    do {
        cout << "No Telephone (12-13 digit): ";
        cin >> telp;
        if (telp.length() < 12 || telp.length() > 13 || !isAngka(telp)) {
            cout << "No HP harus 12-13 digit angka!\n";
        }
    } while (telp.length() < 12 || telp.length() > 13 || !isAngka(telp));

    do {
        cout << "Email (@gmail.com): ";
        cin >> email;
        if (!isGmail(email)) {
            cout << "Email harus mengandung @gmail.com!\n";
        }
    } while (!isGmail(email));

    do {
        cout << "Jumlah Buku (max 3): ";
        cin >> jumlahBuku;
        if (jumlahBuku < 1 || jumlahBuku > 3) {
            cout << "Maksimal 3 buku!\n";
        }
    } while (jumlahBuku < 1 || jumlahBuku > 3);

    daftarBuku.resize(jumlahBuku);

    for (int i = 0; i < jumlahBuku; i++) {
        cout << "\n--- Buku ke-" << i + 1 << " ---\n";

        cout << "Judul Buku: ";
        getline(cin >> ws, daftarBuku[i].judul);

        do {
            cout << "Kode Buku (4 angka): ";
            cin >> daftarBuku[i].kode;
            if (daftarBuku[i].kode.length() != 4 || !isAngka(daftarBuku[i].kode)) {
                cout << "Kode harus 4 digit angka!\n";
            }
        } while (daftarBuku[i].kode.length() != 4 || !isAngka(daftarBuku[i].kode));

        do {
            if (i == 0) {
                cout << "Tanggal Peminjaman (dd/mm/yy): ";
                cin >> tglPinjamGlobal;
            }

            daftarBuku[i].tglPinjam = tglPinjamGlobal;

            cout << "Tanggal Pengembalian (dd/mm/yy): ";
            cin >> daftarBuku[i].tglKembali;

            daftarBuku[i].durasi = hitungSelisih(
                daftarBuku[i].tglPinjam,
                daftarBuku[i].tglKembali
            );

            if (daftarBuku[i].durasi > 30) {
                cout << "Melebihi 30 hari!\n";
            } else if (daftarBuku[i].durasi < 0) {
                cout << "Tanggal tidak valid!\n";
            }

        } while (daftarBuku[i].durasi > 30 || daftarBuku[i].durasi < 0);
    }

    cout << "\n========== KONFIRMASI ==========\n";
    cout << "Nama: " << nama << " | Telp: " << telp << endl;

    for (int i = 0; i < jumlahBuku; i++) {
        cout << i + 1 << ". " << daftarBuku[i].judul
             << " (" << daftarBuku[i].durasi << " hari)\n";
    }

    cout << "Sudah benar? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {

        // OUTPUT STRUK
        cout << "==============================================================================\n";
        cout << "=                             STRUK PEMINJAMAN                               =\n";
        cout << "==============================================================================\n";

        cout << "Nama  : " << nama << endl;
        cout << "Telp  : " << telp << endl;
        cout << "Email : " << email << endl;

        for (int i = 0; i < jumlahBuku; i++) {
            cout << "\nBuku ke-" << i + 1 << endl;
            cout << "Judul   : " << daftarBuku[i].judul << endl;
            cout << "Kode    : " << daftarBuku[i].kode << endl;
            cout << "Pinjam  : " << daftarBuku[i].tglPinjam << endl;
            cout << "Kembali : " << daftarBuku[i].tglKembali << endl;
            cout << "Durasi  : " << daftarBuku[i].durasi << " hari\n";
        }

        // PILIH SIMPAN ATAU TIDAK
        char simpan;
        cout << "\nSimpan invoice ke file? (y/n): ";
        cin >> simpan;

        if (simpan == 'y' || simpan == 'Y') {

            string namaFile = "invoice_" + nama + ".txt";
            ofstream file(namaFile);

            if (file.is_open()) {
                file << "=============================================\n";
                file << "        STRUK PEMINJAMAN PERPUSTAKAAN        \n";
                file << "=============================================\n";

                file << "Nama  : " << nama << endl;
                file << "Telp  : " << telp << endl;
                file << "Email : " << email << endl;

                for (int i = 0; i < jumlahBuku; i++) {
                    file << "\nBuku ke-" << i + 1 << endl;
                    file << "Judul   : " << daftarBuku[i].judul << endl;
                    file << "Kode    : " << daftarBuku[i].kode << endl;
                    file << "Pinjam  : " << daftarBuku[i].tglPinjam << endl;
                    file << "Kembali : " << daftarBuku[i].tglKembali << endl;
                    file << "Durasi  : " << daftarBuku[i].durasi << " hari\n";
                }

                file << "=============================================\n";
                file.close();

                cout << "Invoice berhasil disimpan: " << namaFile << endl;
            } else {
                cout << "Gagal menyimpan file!\n";
            }

        } else {
            cout << "Invoice tidak disimpan.\n";
        }
    }

} while (konfirmasi == 'n' || konfirmasi == 'N');

return 0;

}
