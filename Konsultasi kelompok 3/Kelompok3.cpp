#include <iostream>
#include <iomanip>
using namespace std;

// Struct Obat
struct Obat {
    string nama;
    int harga;
};

int main() {
    // Daftar obat klinik (umum)
    Obat daftarObat[] = {
        {"Paracetamol", 5000},
        {"Amoxicillin", 10000},
        {"OBH Combi", 15000},
        {"Vitamin C", 8000},
        {"Antasida", 7000},
        {"Ibuprofen", 12000},
        {"CTM", 4000},
        {"Betadine", 13000}
    };

    int jumlahObat = sizeof(daftarObat) / sizeof(daftarObat[0]);

    int pilihan, qty;
    char lagi;

    int totalSemua = 0;

    // Array untuk menyimpan pembelian
    int beli[100] = {0};

    do {
        cout << "\n===== DAFTAR OBAT =====\n";
        for (int i = 0; i < jumlahObat; i++) {
            cout << i+1 << ". " << daftarObat[i].nama 
                 << " - Rp" << daftarObat[i].harga << endl;
        }

        cout << "\nPilih obat (1-" << jumlahObat << "): ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > jumlahObat) {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

        cout << "Jumlah beli: ";
        cin >> qty;

        beli[pilihan-1] += qty;

        cout << "Tambah obat lagi? (y/n): ";
        cin >> lagi;

    } while (lagi == 'y' || lagi == 'Y');

    // OUTPUT STRUK
    cout << "\n\n===== STRUK KLINIK =====\n";
    cout << left << setw(15) << "Obat" 
         << setw(10) << "Harga" 
         << setw(10) << "Qty" 
         << setw(10) << "Subtotal" << endl;

    cout << "----------------------------------------\n";

    for (int i = 0; i < jumlahObat; i++) {
        if (beli[i] > 0) {
            int subtotal = beli[i] * daftarObat[i].harga;
            totalSemua += subtotal;

            cout << left << setw(15) << daftarObat[i].nama
                 << setw(10) << daftarObat[i].harga
                 << setw(10) << beli[i]
                 << setw(10) << subtotal << endl;
        }
    }

    cout << "----------------------------------------\n";
    cout << "TOTAL BAYAR: Rp" << totalSemua << endl;
    cout << "===============================\n";

    return 0;
}