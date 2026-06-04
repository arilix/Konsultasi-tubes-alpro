#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>  // ✅ Untuk waktu dan tanggal
using namespace std;

struct Menu {
    string nama;
    double harga;
};

struct Pesanan {
    Menu item;
    int jumlah;
};

// ✅ Fungsi untuk mendapatkan waktu dan tanggal saat ini
string getWaktuSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y  %H:%M:%S", ltm);
    return string(buffer);
}

int main() {
    vector<Menu> daftarMenu = {
        {"Nasi Goreng Spesial", 25000},
        {"Ayam Geprek", 20000},
        {"Mie Ayam Bakso", 18000},
        {"Sate Ayam", 30000},
        {"Dumpling Basah", 30000},
        {"Kambing Guling", 30000},
        {"Babat Sapi", 30000},
        {"Tahu Tek", 30000},
        {"Ikan Goreng", 30000},
        {"Babi Guling", 30000},
        {"Mie Gacoan", 30000}
    };

    int opsi;
    do {
        cout << "=============================================\n";
        cout << "   SELAMAT DATANG DI APLIKASI GOOFOOD FAST  \n";
        cout << "=============================================\n";
        cout << "1. Mulai Pemesanan\n";
        cout << "2. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> opsi;

        if (opsi == 2) {
            cout << "\nTerima kasih, sampai jumpa!\n";
            break;
        } else if (opsi != 1) {
            cout << "\nOpsi tidak valid. Silakan coba lagi.\n";
            continue;
        }

        vector<Pesanan> keranjang;
        string alamat, namaPemesan;
        int pilihan, jumlah;
        char lanjut;
        double total = 0;

        // Input nama pemesan
        cin.ignore();
        cout << "\nMasukkan nama pemesan: ";
        getline(cin, namaPemesan);

        // ✅ Simpan waktu pemesanan tepat saat user mulai memesan
        string waktuPesan = getWaktuSekarang();

        cout << "\n=== SISTEM PEMESANAN MAKANAN ONLINE ===\n\n";
        cout << "Halo, " << namaPemesan << "! Silakan pilih menu Anda.\n\n";
        cout << "Menu Tersedia:\n";
        for (int i = 0; i < (int)daftarMenu.size(); i++) {
            cout << i+1 << ". " << left << setw(22) << daftarMenu[i].nama
                 << "Rp " << daftarMenu[i].harga << endl;
        }

        do {
            cout << "\nPilih nomor menu: ";
            cin >> pilihan;
            if (pilihan < 1 || pilihan > (int)daftarMenu.size()) {
                cout << "Pilihan tidak valid!\n";
                continue;
            }
            cout << "Jumlah pesanan: ";
            cin >> jumlah;

            keranjang.push_back({daftarMenu[pilihan-1], jumlah});

            cout << "Tambah pesanan lain? (y/n): ";
            cin >> lanjut;
        } while (lanjut == 'y' || lanjut == 'Y');

        cin.ignore();
        cout << "\nMasukkan alamat pengiriman: ";
        getline(cin, alamat);

        // Pilih ongkir
        cout << "\nPilih opsi ongkir:\n";
        cout << "1. Reguler (Rp 10.000)\n";
        cout << "2. Ekspres (Rp 20.000)\n";
        cout << "Pilih: ";
        int ongkirPilihan;
        cin >> ongkirPilihan;
        double ongkir = (ongkirPilihan == 2) ? 20000 : 10000;
        string jenisOngkir = (ongkirPilihan == 2) ? "Ekspres" : "Reguler";

        // Hitung total
        for (auto &p : keranjang) {
            total += p.item.harga * p.jumlah;
        }
        total += ongkir;

        // ✅ Pilih metode pembayaran
        int metodePilihan;
        cout << "\nPilih metode pembayaran:\n";
        cout << "1. Tunai\n";
        cout << "2. Transfer Bank\n";
        cout << "Pilih: ";
        cin >> metodePilihan;

        string metodeBayar;
        double uangBayar = 0, kembalian = 0;

        if (metodePilihan == 1) {
            // ✅ Pembayaran tunai + hitung kembalian
            metodeBayar = "Tunai";
            cout << "\nTotal yang harus dibayar: Rp " << total << endl;
            do {
                cout << "Masukkan jumlah uang yang dibayarkan: Rp ";
                cin >> uangBayar;
                if (uangBayar < total) {
                    cout << "Uang tidak cukup! Kurang Rp " << (total - uangBayar) << ". Coba lagi.\n";
                }
            } while (uangBayar < total);
            kembalian = uangBayar - total;
        } else {
            // ✅ Pembayaran transfer
            metodeBayar = "Transfer Bank";
            cout << "\n--- INFO TRANSFER ---\n";
            cout << "Bank    : BCA\n";
            cout << "No. Rek : 1234-5678-9012\n";
            cout << "A/N     : GooFood Fast\n";
            cout << "Nominal : Rp " << total << "\n";
            cout << "---------------------\n";
            cout << "Pastikan nominal transfer sesuai dengan total bayar.\n";
        }

        // ✅ Cetak invoice lengkap
        cout << "\n";
        cout << "=============================================\n";
        cout << "          INVOICE PEMESANAN GOOFOOD         \n";
        cout << "=============================================\n";
        cout << "Tanggal & Waktu : " << waktuPesan << "\n";         // ✅ Tanggal & waktu
        cout << "Nama Pemesan    : " << namaPemesan << "\n";
        cout << "Alamat          : " << alamat << "\n";
        cout << "Metode Bayar    : " << metodeBayar << "\n";        // ✅ Metode bayar
        cout << "Pengiriman      : " << jenisOngkir << "\n";
        cout << "---------------------------------------------\n";
        cout << left << setw(22) << "Item"
             << setw(8)  << "Qty"
             << setw(15) << "Subtotal" << "\n";
        cout << "---------------------------------------------\n";
        for (auto &p : keranjang) {
            cout << left << setw(22) << p.item.nama
                 << setw(8)  << p.jumlah
                 << "Rp " << p.item.harga * p.jumlah << "\n";
        }
        cout << "---------------------------------------------\n";
        cout << left << setw(22) << ("Ongkir (" + jenisOngkir + ")")
             << setw(8)  << "-"
             << "Rp " << ongkir << "\n";
        cout << "---------------------------------------------\n";
        cout << "TOTAL BAYAR     : Rp " << total << "\n";

        // ✅ Tampilkan info uang jika tunai
        if (metodePilihan == 1) {
            cout << "Uang Dibayar    : Rp " << uangBayar << "\n";
            cout << "Kembalian       : Rp " << kembalian << "\n";   // ✅ Kembalian
        }

        cout << "=============================================\n";
        cout << "  Selamat Menikmati Makanan Anda, " << namaPemesan << "!\n";
        cout << "        Terima kasih telah memesan!         \n";
        cout << "=============================================\n\n";

        // Opsi kembali ke menu awal
        cout << "Apakah Anda ingin kembali ke menu awal?\n";
        cout << "1. Ya\n";
        cout << "2. Tidak (Keluar)\n";
        cout << "Pilih opsi: ";
        cin >> opsi;

        if (opsi == 2) {
            cout << "\nProgram berakhir. Sampai jumpa!\n";
            break;
        }

    } while (true);

    return 0;
}