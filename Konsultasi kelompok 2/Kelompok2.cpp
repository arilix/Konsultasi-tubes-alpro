#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

struct User {
    string username;
    string password;
};
const int MAX_USERS = 100;
User users[MAX_USERS];
int userCount = 0;

struct Barang {
    int id;
    string kategori;
    string nama;
    int harga;
    int stok;
    int tipeUkuran;
};

const int MAX_BARANG = 100;
int barangCount = 12;

Barang katalog[MAX_BARANG] = {
    {101, "ATASAN", "Kaos Polos Cotton", 85000, 50, 1},
    {102, "ATASAN", "Hoodie Oversize", 250000, 20, 1},
    {103, "ATASAN", "Kemeja Flanel", 185000, 15, 1},
    {104, "ATASAN", "Jaket Denim", 375000, 10, 1},
    {201, "BAWAHAN", "Celana Jeans Slimfit", 350000, 25, 1},
    {202, "BAWAHAN", "Celana Cargo", 275000, 15, 1},
    {203, "BAWAHAN", "Celana Chino", 225000, 20, 1},
    {204, "BAWAHAN", "Celana Jogger", 150000, 30, 1},
    {301, "SEPATU", "Sneakers Kanvas", 400000, 12, 2},
    {302, "SEPATU", "Sepatu Boots Kulit", 850000, 5, 2},
    {303, "SEPATU", "Sepatu Lari (Running)", 600000, 8, 2},
    {304, "SEPATU", "Sandal Gunung", 125000, 20, 2}
};

struct Keranjang {
    int id;
    string nama;
    string ukuran;
    int harga;
    int jumlah;
    int subtotal;
};
const int MAX_KERANJANG = 100;
Keranjang keranjangUser[MAX_KERANJANG];
int keranjangCount = 0;

struct ItemPesanan {
    string nama;
    string ukuran;
    int harga;
    int jumlah;
    int subtotal;
};

struct Riwayat {
    string idTransaksi;
    string waktu;
    ItemPesanan items[MAX_KERANJANG];
    int itemCount;
    long long totalBelanja;
    long long diskon;
    long long ongkir;
    long long totalAkhir;
    string metodeBayar;
    string layananKirim;
    string tujuanPengiriman;
};

const int MAX_RIWAYAT = 100;
Riwayat daftarRiwayat[MAX_RIWAYAT];
int riwayatCount = 0;

void tampilkanKatalogAdmin() {
    cout << "\n--- DAFTAR BARANG SAAT INI ---\n";
    cout << left << setw(5) << "ID" << setw(12) << "KATEGORI" << setw(25) << "NAMA BARANG"
         << setw(15) << "HARGA" << setw(10) << "STOK" << endl;
    for (int i = 0; i < barangCount; i++) {
        cout << left << setw(5) << katalog[i].id << setw(12) << katalog[i].kategori
             << setw(25) << katalog[i].nama << "Rp " << setw(12) << katalog[i].harga
             << setw(10) << katalog[i].stok << endl;
    }
    cout << "------------------------------\n";
}

void menuAdmin() {
    int pilihanAdmin;
    do {
        system("cls");
        cout << "\n====================================\n";
        cout << "             MENU ADMIN\n";
        cout << "====================================\n";
        cout << "1. Restock Barang \n";
        cout << "2. Ubah Harga Barang \n";
        cout << "3. Tambah Produk \n";
        cout << "4. Hapus Produk \n";
        cout << "5. Logout Admin\n";

        while (true) {
            cout << "Pilih menu (1-5): ";
            if (cin >> pilihanAdmin && pilihanAdmin >= 1 && pilihanAdmin <= 5) break;
            cout << "[ERROR] Pilihan tidak valid!\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        if (pilihanAdmin == 1) {
            tampilkanKatalogAdmin();
            int idCari, stokTambahan;
            bool ditemukan = false;
            cout << "\nMasukkan ID Barang yang ingin di-restock: "; cin >> idCari;

            for (int i = 0; i < barangCount; i++) {
                if (katalog[i].id == idCari) {
                    ditemukan = true;
                    cout << "Barang ditemukan: " << katalog[i].nama << " (Stok saat ini: " << katalog[i].stok << ")\n";
                    cout << "Masukkan jumlah stok tambahan: "; cin >> stokTambahan;
                    katalog[i].stok += stokTambahan; // Logika: Menambah stok
                    cout << "[SUKSES] Stok berhasil ditambahkan! Stok baru: " << katalog[i].stok << "\n";
                    break;
                }
            }
            if (!ditemukan) cout << "[ERROR] ID Barang tidak ditemukan!\n";
            system("pause");

        } else if (pilihanAdmin == 2) {
            tampilkanKatalogAdmin();
            int idCari, hargaBaru;
            bool ditemukan = false;
            cout << "\nMasukkan ID Barang yang ingin diubah harganya: "; cin >> idCari;

            for (int i = 0; i < barangCount; i++) {
                if (katalog[i].id == idCari) {
                    ditemukan = true;
                    cout << "Barang ditemukan: " << katalog[i].nama << " (Harga lama: Rp " << katalog[i].harga << ")\n";
                    cout << "Masukkan harga baru: Rp "; cin >> hargaBaru;
                    katalog[i].harga = hargaBaru;
                    cout << "[SUKSES] Harga barang berhasil diubah!\n";
                    break;
                }
            }
            if (!ditemukan) cout << "[ERROR] ID Barang tidak ditemukan!\n";
            system("pause");

        } else if (pilihanAdmin == 3) {
            if (barangCount >= MAX_BARANG) {
                cout << "[ERROR] Kapasitas toko sudah penuh, tidak bisa menambah barang baru!\n";
            } else {
                int newId, newHarga, newStok, newTipe;
                string newKategori, newNama;

                cout << "\n--- TAMBAH PRODUK BARU ---\n";
                cout << "Masukkan ID Barang : "; cin >> newId;
                cout << "Masukkan Kategori Barang: "; cin >> newKategori;
                cin.ignore();
                cout << "Masukkan Nama Barang   : "; getline(cin, newNama);
                cout << "Masukkan Harga Barang  : Rp "; cin >> newHarga;
                cout << "Masukkan Stok Awal Barang  : "; cin >> newStok;
                cout << "Masukkan Tipe Ukuran (1=Baju / 2=Sepatu)   : "; cin >> newTipe;

                katalog[barangCount].id = newId;
                katalog[barangCount].kategori = newKategori;
                katalog[barangCount].nama = newNama;
                katalog[barangCount].harga = newHarga;
                katalog[barangCount].stok = newStok;
                katalog[barangCount].tipeUkuran = newTipe;

                barangCount++;
                cout << "[SUKSES] Barang baru berhasil ditambahkan ke katalog!\n";
            }
            system("pause");

        } else if (pilihanAdmin == 4) {
            tampilkanKatalogAdmin();
            int idCari;
            bool ditemukan = false;
            cout << "\nMasukkan ID Barang yang ingin dihapus: "; cin >> idCari;

            for (int i = 0; i < barangCount; i++) {
                if (katalog[i].id == idCari) {
                    ditemukan = true;
                    string namaDihapus = katalog[i].nama;

                    for (int j = i; j < barangCount - 1; j++) {
                        katalog[j] = katalog[j + 1];
                    }

                    barangCount--;
                    cout << "[SUKSES] Produk '" << namaDihapus << "' berhasil dihapus dari katalog!\n";
                    break;
                }
            }
            if (!ditemukan) cout << "[ERROR] ID Barang tidak ditemukan!\n";
            system("pause");
        }

    } while (pilihanAdmin != 5);

    cout << "\nKeluar dari Mode Admin...\n";
    this_thread::sleep_for(chrono::seconds(1));
}

void hapusBarangDariKeranjang() {
    int hapusIndex;
    while (true) {
        cout << "\nMasukkan Nomor (NO) barang yang ingin dihapus (atau 0 untuk batal): ";
        if (cin >> hapusIndex) {
            if (hapusIndex >= 0 && hapusIndex <= keranjangCount) break;
        }
        cout << "[ERROR] Masukkan nomor urut yang valid!\n";
        cin.clear(); cin.ignore(10000, '\n');
    }

    if (hapusIndex == 0) return;

    for (int i = hapusIndex - 1; i < keranjangCount - 1; i++) {
        keranjangUser[i] = keranjangUser[i + 1];
    }
    keranjangCount--;

    cout << "\n[SUKSES] Barang berhasil dihapus dari keranjang!\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(10000, '\n'); cin.get();
}

void ubahJumlahBarangDiKeranjang() {
    int ubahIndex;
    while (true) {
        cout << "\nMasukkan Nomor (NO) barang yang ingin diubah jumlahnya (atau 0 untuk batal): ";
        if (cin >> ubahIndex) {
            if (ubahIndex >= 0 && ubahIndex <= keranjangCount) break;
        }
        cout << "[ERROR] Masukkan nomor urut yang valid!\n";
        cin.clear(); cin.ignore(10000, '\n');
    }

    if (ubahIndex == 0) return;

    int realIndex = ubahIndex - 1;
    int jumlahBaru;
    int stokMaksimal = 0;

    for (int i = 0; i < barangCount; i++) {
        if (katalog[i].id == keranjangUser[realIndex].id) {
            stokMaksimal = katalog[i].stok;
            break;
        }
    }

    while (true) {
        cout << "Masukkan jumlah baru untuk " << keranjangUser[realIndex].nama
             << " (Stok maksimal saat ini: " << stokMaksimal << "): ";
        if (!(cin >> jumlahBaru)) {
            cout << "[ERROR] Input harus berupa angka!\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }

        if (jumlahBaru <= 0) {
            cout << "[ERROR] Jumlah minimal adalah 1! Jika ingin membatalkan, gunakan fitur Hapus.\n";
        } else if (jumlahBaru > stokMaksimal) {
            cout << "[ERROR] Maaf, stok tidak mencukupi!\n";
        } else {
            break;
        }
    }

    keranjangUser[realIndex].jumlah = jumlahBaru;
    keranjangUser[realIndex].subtotal = jumlahBaru * keranjangUser[realIndex].harga;

    cout << "\n[SUKSES] Jumlah barang berhasil diperbarui!\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(10000, '\n'); cin.get();
}

void menuKatalog() {
    int idPilihan;

    do {
        system("cls");
        cout << "===================================================================================\n";
        cout << "                            KATALOG CLOTHIFY STORE\n";
        cout << "===================================================================================\n";
        cout << left << setw(5) << "ID" << setw(12) << "KATEGORI" << setw(25) << "NAMA BARANG"
             << setw(15) << "HARGA" << setw(10) << "STOK" << endl;
        cout << "-----------------------------------------------------------------------------------\n";

        for (int i = 0; i < barangCount; i++) {
            cout << left << setw(5) << katalog[i].id << setw(12) << katalog[i].kategori
                 << setw(25) << katalog[i].nama << "Rp " << setw(12) << katalog[i].harga
                 << setw(10) << katalog[i].stok << endl;
        }
        cout << "===================================================================================\n";

        while (true) {
            cout << "\nMasukkan ID Barang yang ingin dibeli (atau 0 untuk kembali): ";
            if (cin >> idPilihan) break;
            cout << "[ERROR] Masukkan harus berupa angka!\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        if (idPilihan == 0) return;

        int indexDitemukan = -1;
        for (int i = 0; i < barangCount; i++) {
            if (katalog[i].id == idPilihan) {
                indexDitemukan = i;
                break;
            }
        }

        if (indexDitemukan != -1) {
            string ukuranPilihan;
            int jumlahBeli;

            cout << "\nBarang pilihan Anda: " << katalog[indexDitemukan].nama << "\n";

            bool ukuranValid = false;
            while (!ukuranValid) {
                if (katalog[indexDitemukan].tipeUkuran == 1) {
                    cout << "Pilih Ukuran (S / M / L / XL) : ";
                    cin >> ukuranPilihan;
                    for (char &c : ukuranPilihan) c = toupper(c);
                    if (ukuranPilihan == "S" || ukuranPilihan == "M" || ukuranPilihan == "L" || ukuranPilihan == "XL") ukuranValid = true;
                    else cout << "[ERROR] Ukuran pakaian tidak valid. Silakan coba lagi.\n";
                } else {
                    cout << "Pilih Ukuran (39 / 40 / 41 / 42 / 43) : ";
                    cin >> ukuranPilihan;
                    if (ukuranPilihan == "39" || ukuranPilihan == "40" || ukuranPilihan == "41" || ukuranPilihan == "42" || ukuranPilihan == "43") ukuranValid = true;
                    else cout << "[ERROR] Ukuran sepatu tidak valid. Silakan coba lagi.\n";
                }
            }

            while (true) {
                cout << "Masukkan jumlah yang ingin dibeli : ";
                if (!(cin >> jumlahBeli)) {
                    cout << "[ERROR] Input harus berupa angka!\n";
                    cin.clear(); cin.ignore(10000, '\n'); continue;
                }
                if (jumlahBeli <= 0) {
                    cout << "[ERROR] Jumlah minimal pembelian adalah 1!\n";
                } else if (jumlahBeli > katalog[indexDitemukan].stok) {
                    cout << "[ERROR] Maaf, sisa stok tidak mencukupi. Stok saat ini: " << katalog[indexDitemukan].stok << "\n";
                } else {
                    break;
                }
            }

            int subtotal = jumlahBeli * katalog[indexDitemukan].harga;
            keranjangUser[keranjangCount].id = katalog[indexDitemukan].id;
            keranjangUser[keranjangCount].nama = katalog[indexDitemukan].nama;
            keranjangUser[keranjangCount].ukuran = ukuranPilihan;
            keranjangUser[keranjangCount].harga = katalog[indexDitemukan].harga;
            keranjangUser[keranjangCount].jumlah = jumlahBeli;
            keranjangUser[keranjangCount].subtotal = subtotal;
            keranjangCount++;

            cout << "\n[SUKSES] Barang berhasil ditambahkan ke keranjang!\n";
            cout << "Subtotal Sementara: Rp " << subtotal << "\n";

        } else {
            cout << "\n[GAGAL] ID Barang " << idPilihan << " tidak ditemukan. Silakan cek kembali.\n";
        }

        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore(10000, '\n'); cin.get();

    } while (idPilihan != 0);
}

void menuKeranjang() {
    int pilihanKeranjang;
    do {
        system("cls");

        if (keranjangCount == 0) {
            cout << "\n[INFORMASI] Keranjang belanja Anda masih kosong.\n";
            cout << "Silakan pilih barang di menu Katalog terlebih dahulu.\n";
            cout << "\nTekan Enter untuk kembali ke Menu Utama...";
            cin.ignore(10000, '\n'); cin.get();
            return;
        }

        cout << "=========================================================================\n";
        cout << "                           ISI KERANJANG ANDA\n";
        cout << "=========================================================================\n";
        cout << left << setw(5) << "NO" << setw(25) << "NAMA BARANG" << setw(10) << "UKURAN"
             << setw(10) << "JUMLAH" << setw(15) << "SUBTOTAL" << endl;
        cout << "-------------------------------------------------------------------------\n";

        int totalHarga = 0;
        for (int i = 0; i < keranjangCount; i++) {
            cout << left << setw(5) << (i + 1)
                 << setw(25) << keranjangUser[i].nama
                 << setw(10) << keranjangUser[i].ukuran
                 << setw(10) << keranjangUser[i].jumlah
                 << "Rp " << setw(12) << keranjangUser[i].subtotal << endl;
            totalHarga += keranjangUser[i].subtotal;
        }
        cout << "=========================================================================\n";
        cout << "TOTAL SEMENTARA: Rp " << totalHarga << "\n";
        cout << "=========================================================================\n";

        cout << "\nMenu Keranjang:\n";
        cout << "1. Ubah Jumlah Barang Dari Keranjang Anda\n";
        cout << "2. Hapus Barang dari Keranjang Anda\n";
        cout << "3. Kembali ke Menu Utama\n";

        while (true) {
            cout << "Pilih menu (1-3): ";
            if (cin >> pilihanKeranjang && pilihanKeranjang >= 1 && pilihanKeranjang <= 3) break;
            cout << "[ERROR] Pilihan tidak valid!\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        if (pilihanKeranjang == 1) {
            ubahJumlahBarangDiKeranjang();
        } else if (pilihanKeranjang == 2) {
            hapusBarangDariKeranjang();
        }

    } while (pilihanKeranjang != 3);
}

void menuCheckout() {
    int pilihanCheckout;
    do {
        system("cls");

        if (keranjangCount == 0) {
            cout << "\n[INFORMASI] Belum ada barang untuk di-checkout.\n";
            cout << "Silakan isi keranjang belanja Anda terlebih dahulu.\n";
            cout << "\nTekan Enter untuk kembali...";
            cin.ignore(10000, '\n'); cin.get();
            return;
        }

        cout << "=========================================================================\n";
        cout << "                         RINGKASAN PESANAN ANDA\n";
        cout << "=========================================================================\n";
        cout << left << setw(5) << "NO" << setw(25) << "NAMA BARANG" << setw(10) << "UKURAN"
             << setw(10) << "JUMLAH" << setw(15) << "SUBTOTAL" << endl;
        cout << "-------------------------------------------------------------------------\n";

        long long totalBelanja = 0;
        for (int i = 0; i < keranjangCount; i++) {
            cout << left << setw(5) << (i + 1)
                 << setw(25) << keranjangUser[i].nama
                 << setw(10) << keranjangUser[i].ukuran
                 << setw(10) << keranjangUser[i].jumlah
                 << "Rp " << setw(12) << keranjangUser[i].subtotal << endl;
            totalBelanja += keranjangUser[i].subtotal;
        }
        cout << "=========================================================================\n";
        cout << "TOTAL BARANG: Rp " << totalBelanja << "\n";
        cout << "=========================================================================\n";

        cout << "\nOpsi Checkout:\n";
        cout << "1. Lanjut ke Pengiriman\n";
        cout << "2. Ubah Jumlah Pesanan\n";
        cout << "3. Batal & Kembali ke Menu Utama\n";

        while (true) {
            cout << "Pilih opsi (1-3): ";
            if (cin >> pilihanCheckout && pilihanCheckout >= 1 && pilihanCheckout <= 3) break;
            cout << "[ERROR] Masukkan angka 1 sampai 3!\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        if (pilihanCheckout == 2) {
            ubahJumlahBarangDiKeranjang();
        } else if (pilihanCheckout == 3) {
            return;
        } else if (pilihanCheckout == 1) {

            int wilayah;
            cout << "\n-------------------------------------------------------------------------\n";
            cout << "                     INFORMASI PENGIRIMAN\n";
            cout << "-------------------------------------------------------------------------\n";
            cout << "Pilih Wilayah Tujuan Anda:\n";
            cout << "1. Surabaya\n";
            cout << "2. Pulau Jawa (Selain Surabaya)\n";
            cout << "3. Luar Pulau Jawa\n";

            while (true) {
                cout << "Pilihan wilayah (1-3): ";
                if (cin >> wilayah && wilayah >= 1 && wilayah <= 3) break;
                cout << "[ERROR] Pilihan tidak valid!\n";
                cin.clear(); cin.ignore(10000, '\n');
            }

            long long ongkirDasar = 0;
            string sWilayah = "";
            if (wilayah == 1) {
                sWilayah = "Surabaya";
                ongkirDasar = 0;
                cout << "\n[INFO] Yeay! Tujuan Surabaya mendapatkan BEBAS ONGKIR dengan layanan Express!\n";
            } else if (wilayah == 2) {
                sWilayah = "Pulau Jawa";
                ongkirDasar = 15000;
            } else {
                sWilayah = "Luar Pulau Jawa";
                ongkirDasar = 25000;
            }

            long long ongkirLayanan = 0;
            string layananDipilih = "Express (1-2 Hari)";
            if (wilayah != 1) {
                int layanan;
                cout << "\nPilih layanan pengiriman:\n";
                cout << "1. Express (1-2 Hari)     : + Rp 25.000\n";
                cout << "2. Reguler (3-5 Hari)     : + Rp 10.000\n";
                cout << "3. Hemat (6-8 Hari)       : + Rp 5.000\n";

                while (true) {
                    cout << "Pilihan layanan (1-3): ";
                    if (cin >> layanan && layanan >= 1 && layanan <= 3) break;
                    cout << "[ERROR] Pilihan tidak valid!\n";
                    cin.clear(); cin.ignore(10000, '\n');
                }

                if (layanan == 1) { ongkirLayanan = 25000; layananDipilih = "Express (1-2 Hari)"; }
                else if (layanan == 2) { ongkirLayanan = 10000; layananDipilih = "Reguler (3-5 Hari)"; }
                else { ongkirLayanan = 5000; layananDipilih = "Hemat (6-8 Hari)"; }
            }

            long long diskonVoucher = 0;
            long long diskonOngkir = 0;
            bool isVoucherHahayApplied = false;
            bool isVoucherOngkirApplied = false;

            char tanyaVoucher;
            cout << "\nApakah Anda ingin memasukkan kode voucher promo? (Y/N): ";
            cin >> tanyaVoucher;

            while (toupper(tanyaVoucher) == 'Y') {
                string kode;
                cout << "Masukkan kode voucher: ";
                cin >> kode;
                for (char &c : kode) c = toupper(c);

                if (kode == "HAHAY10") {
                    if (!isVoucherHahayApplied) {
                        diskonVoucher = totalBelanja * 0.10;
                        isVoucherHahayApplied = true;
                        cout << "[SUKSES] Voucher HAHAY10 berhasil!Anda mendapatkan Potongan harga sebesar 10% (Rp " << diskonVoucher << ")\n";
                    } else {
                        cout << "[INFO] Voucher HAHAY10 sudah digunakan.\n";
                    }
                } else if (kode == "ONGKIR5") {
                    if (wilayah != 1) {
                        if (!isVoucherOngkirApplied) {
                            diskonOngkir = 5000;
                            isVoucherOngkirApplied = true;
                            cout << "[SUKSES] Voucher ongkir5 berhasil! Anda mendapatkan potongan ongkir sebesar Rp 5.000\n";
                        } else {
                            cout << "[INFO] Voucher ONGKIR5 sudah digunakan.\n";
                        }
                    } else {
                        cout << "[GAGAL] Voucher ONGKIR5 tidak berlaku! untuk wilayah Surabaya karena sudah mendapatkan layanan BEBAS ONGKIR\n";
                    }
                } else {
                    cout << "[GAGAL] Kode voucher tidak valid!\n";
                }

                cout << "\nApakah Anda ingin memasukkan kode voucher lagi? (Y/N): ";
                cin >> tanyaVoucher;
            }

            long long totalOngkir = (ongkirDasar + ongkirLayanan) - diskonOngkir;
            if (totalOngkir < 0) totalOngkir = 0;
            long long totalAkhir = (totalBelanja - diskonVoucher) + totalOngkir;

            cout << "\n=================================================================\n";
            cout << "                      RINCIAN TAGIHAN\n";
            cout << "=================================================================\n";
            cout << left << setw(25) << "Total Belanja" << ": Rp " << totalBelanja << "\n";
            if (diskonVoucher > 0) cout << left << setw(25) << "Diskon Voucher" << ": -Rp " << diskonVoucher << "\n";
            cout << left << setw(25) << "Ongkos Kirim" << ": Rp " << (ongkirDasar + ongkirLayanan) << " (" << layananDipilih << ")\n";
            if (diskonOngkir > 0) cout << left << setw(25) << "Diskon Voucher Ongkir" << ": -Rp " << diskonOngkir << "\n";
            cout << "-----------------------------------------------------------------\n";
            cout << left << setw(25) << "TOTAL BAYAR" << ": Rp " << totalAkhir << "\n";
            cout << "=================================================================\n";

            int met;
            cout << "\nPilih Metode Pembayaran Online:\n1. QRIS\n2. Bank BCA\n0. Batal & Kembali\nPilih: ";
            while (true) {
                if (cin >> met && (met == 1 || met == 2 || met == 0)) break;
                cout << "[ERROR] Masukkan angka 1, 2, atau 0: ";
                cin.clear(); cin.ignore(10000, '\n');
            }

            if (met == 0) return;

            string namaMetode;
            cout << "\n=================================================================\n";
            cout << "                      MENUNGGU PEMBAYARAN\n";
            cout << "=================================================================\n";
            cout << "Segera untuk melakukan pembayaran sebesar Rp " << totalAkhir << "\n";

            if (met == 1) {
                cout << "Silakan scan kode QRIS Clothify Store menggunakan E-Wallet Anda.\n";
                namaMetode = "QRIS";
            } else {
                cout << "Silakan transfer ke Rekening Bank BCA 2118201080 a.n Clothify Store\n";
                namaMetode = "Bank BCA";
            }

            cout << "Batas waktu pembayaran adalah 24 Jam.\n";

            string ketikBayar;
            while (true) {
                cout << "\nKetik kata 'BAYAR' untuk mensimulasikan proses transfer Anda: ";
                cin >> ketikBayar;
                for (char &c : ketikBayar) c = toupper(c);
                if (ketikBayar == "BAYAR") break;
                else cout << "[ERROR] Harus mengetik 'BAYAR' untuk simulasi!\n";
            }

            cout << "\nMemeriksa status pembayaran";
            for (int i = 0; i < 4; i++) {
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(900));
            }

            cout << "\n\n=================================================================\n";
            cout << "             [SUKSES] PEMBAYARAN ANDA TELAH DIVERIFIKASI!\n";
            cout << "=================================================================\n";
            cout << "Pesanan Anda segera diproses dan dikirim melalui layanan " << layananDipilih << ".\n";

            string idTrx = "TRX" + to_string(rand() % 90000 + 10000);
            time_t now = time(0);
            string waktuTrx = ctime(&now);

            daftarRiwayat[riwayatCount].idTransaksi = idTrx;
            daftarRiwayat[riwayatCount].waktu = waktuTrx;
            daftarRiwayat[riwayatCount].totalBelanja = totalBelanja;
            daftarRiwayat[riwayatCount].diskon = diskonVoucher + diskonOngkir;
            daftarRiwayat[riwayatCount].ongkir = totalOngkir;
            daftarRiwayat[riwayatCount].totalAkhir = totalAkhir;
            daftarRiwayat[riwayatCount].layananKirim = layananDipilih;
            daftarRiwayat[riwayatCount].metodeBayar = namaMetode;
            daftarRiwayat[riwayatCount].tujuanPengiriman = sWilayah;
            daftarRiwayat[riwayatCount].itemCount = keranjangCount;

            for (int i = 0; i < keranjangCount; i++) {
                daftarRiwayat[riwayatCount].items[i].nama = keranjangUser[i].nama;
                daftarRiwayat[riwayatCount].items[i].ukuran = keranjangUser[i].ukuran;
                daftarRiwayat[riwayatCount].items[i].harga = keranjangUser[i].harga;
                daftarRiwayat[riwayatCount].items[i].jumlah = keranjangUser[i].jumlah;
                daftarRiwayat[riwayatCount].items[i].subtotal = keranjangUser[i].subtotal;
            }
            riwayatCount++;

            for (int i = 0; i < keranjangCount; i++) {
                for (int j = 0; j < barangCount; j++) {
                    if (katalog[j].id == keranjangUser[i].id) {
                        katalog[j].stok -= keranjangUser[i].jumlah;
                        break;
                    }
                }
            }

            keranjangCount = 0;

            cout << "\nTekan Enter untuk kembali ke Menu Utama...";
            cin.ignore(10000, '\n'); cin.get();
            return;
        }
    } while (pilihanCheckout != 3 && keranjangCount > 0);
}

void menuRiwayat() {
    system("cls");
    if (riwayatCount == 0) {
        cout << "\n[INFORMASI] Maaf, belum ada riwayat transaksi Anda.\n";
        cout << "Silakan lakukan pembelian di Clothify Store terlebih dahulu.\n";
        cout << "\nTekan Enter untuk kembali ke Menu Utama...";
        cin.ignore(10000, '\n'); cin.get();
        return;
    }

    cout << "=========================================================================\n";
    cout << "                       DETAIL RIWAYAT TRANSAKSI ANDA\n";
    cout << "=========================================================================\n";

    for (int i = 0; i < riwayatCount; i++) {
        cout << "ID Transaksi      : " << daftarRiwayat[i].idTransaksi << "\n";
        cout << "Waktu Transaksi   : " << daftarRiwayat[i].waktu;
        cout << "Tujuan Pengiriman : " << daftarRiwayat[i].tujuanPengiriman << "\n";
        cout << "Layanan Kirim     : " << daftarRiwayat[i].layananKirim << "\n";
        cout << "Metode Bayar      : " << daftarRiwayat[i].metodeBayar << "\n";
        cout << "Status            : LUNAS (SUCCESS)\n";
        cout << "-------------------------------------------------------------------------\n";

        for(int j = 0; j < daftarRiwayat[i].itemCount; j++) {
            cout << left << setw(25) << daftarRiwayat[i].items[j].nama
                 << setw(10) << daftarRiwayat[i].items[j].ukuran
                 << "x" << setw(5) << daftarRiwayat[i].items[j].jumlah
                 << "Rp " << setw(12) << daftarRiwayat[i].items[j].subtotal << "\n";
        }

        cout << "-------------------------------------------------------------------------\n";
        cout << left << setw(40) << "TOTAL PEMBAYARAN" << ": Rp " << daftarRiwayat[i].totalAkhir << "\n";
        cout << "=========================================================================\n\n";
    }

    cout << "Tekan Enter untuk kembali ke Menu Utama...";
    cin.ignore(10000, '\n'); cin.get();
}

void menuUtamaPelanggan(string loggedInUser) {
    int pilihan;
    do {
        system("cls");
        cout << "\n====================================\n";
        cout << "           MENU UTAMA\n";
        cout << "   Halo, " << loggedInUser << "! Selamat berbelanja.\n";
        cout << "====================================\n";
        cout << "1. Katalog Barang\n";
        cout << "2. Lihat Keranjang\n";
        cout << "3. Checkout & Pembayaran\n";
        cout << "4. Riwayat Transaksi\n";
        cout << "5. Logout (Keluar akun)\n";

        while (true) {
            cout << "Pilih menu (1-5): ";
            if (cin >> pilihan) {
                if (pilihan >= 1 && pilihan <= 5) break;
            }
            cout << "[ERROR] Pilihan tidak valid! Masukkan angka 1 sampai 5.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        switch (pilihan) {
            case 1: menuKatalog(); break;
            case 2: menuKeranjang(); break;
            case 3: menuCheckout(); break;
            case 4: menuRiwayat(); break;
            case 5: cout << "\nLogout berhasil! Terima kasih telah berkunjung ke Clothify Store, " << loggedInUser << "!\n";
                    this_thread::sleep_for(chrono::seconds(1)); break;
        }
    } while (pilihan != 5);
}

void menuRegistrasi() {
    system("cls");
    cout << "\n=== MENU REGISTRASI ===\n";
    if (userCount >= MAX_USERS) {
        cout << "Maaf, kapasitas pengguna sudah penuh!\n"; return;
    }
    cout << "Masukkan Username baru : "; cin >> users[userCount].username;
    cout << "Masukkan Password baru : "; cin >> users[userCount].password;
    userCount++;
    cout << "Registrasi berhasil! Silakan Login.\n";
    system("pause");
}

int menuLogin(string &loggedInUser) {
    system("cls");
    string inputUsername, inputPassword;
    cout << "\n=== MENU LOGIN ===\n";
    cout << "Masukkan Username : "; cin >> inputUsername;
    cout << "Masukkan Password : "; cin >> inputPassword;

    if (inputUsername == "admin" && inputPassword == "admin123") {
        loggedInUser = "Administrator";
        cout << "\nLogin Mode Admin berhasil! \n";
        system("pause");
        return 2;
    }

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == inputUsername && users[i].password == inputPassword) {
            loggedInUser = inputUsername;
            cout << "\nLogin berhasil! Selamat datang, " << loggedInUser << ".\n";
            system("pause");
            return 1;
        }
    }
    cout << "[ERROR] Login gagal! Username atau Password salah.\n";
    system("pause");
    return 0;
}

int main() {
    srand(time(0));
    int pilihan;
    string loggedInUser = "";
    do {
        system("cls");
        cout << "\n====================================\n";
        cout << "      WELCOME TO CLOTHIFY STORE  \n";
        cout << "====================================\n";
        cout << "1. Registrasi Akun\n";
        cout << "2. Login\n";
        cout << "3. Keluar dari Aplikasi\n";

        while (true) {
            cout << "Pilih menu (1-3): ";
            if (cin >> pilihan) {
                if (pilihan >= 1 && pilihan <= 3) break;
            }
            cout << "[ERROR] Pilihan tidak valid! Masukkan angka 1 sampai 3.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        switch (pilihan) {
            case 1:
                menuRegistrasi();
                break;
            case 2:
                {
                    int statusLogin = menuLogin(loggedInUser);
                    if (statusLogin == 1) {
                        menuUtamaPelanggan(loggedInUser);
                    } else if (statusLogin == 2) {
                        menuAdmin();
                    }
                }
                break;
            case 3:
                cout << "\nProgram selesai. Sampai jumpa kembali di Clothify Store.\n";
                break;
        }
    } while (pilihan != 3);
    return 0;
}
