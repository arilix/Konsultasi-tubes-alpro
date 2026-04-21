# Analisis Kesesuaian Kelompok 2

Tanggal analisis: 21 April 2026  
Objek analisis:
- Kode: Konsultasi kelompok 2/Kelompok2.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Secara umum, proyek Kelompok 2 sudah berada di jalur yang benar (topik valid, CLI C++, modular, ada login/registrasi, ada alur belanja lengkap). Namun, jika dinilai ketat terhadap ketentuan wajib pada acuan, program belum sepenuhnya memenuhi semua poin.

Estimasi tingkat kesesuaian saat ini: **sekitar 72% (parsial sesuai)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus, bukan tiket kereta | Sesuai | Kelompok2.cpp:801-806, tema Clothify Store | Topik toko/UMKM diperbolehkan oleh acuan. |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | Kelompok2.cpp:1-8, seluruh interaksi via cout/cin | Tidak ada GUI/framework lain. |
| 3 | Minimal 2 struct data inti | Sesuai | Kelompok2.cpp:12-79 | Ada User, Barang, Keranjang, ItemPesanan, Riwayat. |
| 4 | Modularisasi fungsi | Sesuai | Kelompok2.cpp:85-837 | Jumlah fungsi jauh di atas 8. |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Kelompok2.cpp:804-806 | Tersedia registrasi, login, keluar aplikasi. |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Kelompok2.cpp:721-753, 97-211 | Ada menu pelanggan dan menu admin. |
| 7 | CRUD data utama | Sesuai (dengan catatan) | Tambah/Hapus/Update produk admin di 155-204, tampil katalog 85-95 | CRUD kuat di data produk (admin). Untuk data transaksi user tidak full update/delete setelah checkout. |
| 8 | Validasi input dasar | Parsial | Validasi menu/angka banyak dipakai: 110-115, 304-309, 343-356, 735-742 | Beberapa input belum divalidasi negatif/kosong: stok tambahan 127-128, harga baru 146-147, registrasi 761-763. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Contoh 129, 148, 199, 367, 371, 636 | Notifikasi user cukup jelas dan konsisten. |
| 10 | Pencarian atau pengurutan data | Parsial | Pencarian ID sederhana di 313-319, 189-202 | Belum ada fitur pencarian/pengurutan eksplisit melalui menu khusus. |
| 11 | Ringkasan/statistik sederhana | Parsial cenderung sesuai | Ringkasan checkout 447-465, rincian tagihan 583-592, riwayat 692-715 | Ringkasan ada, tetapi statistik agregat toko (mis. total transaksi, produk terlaris) belum ada. |
| 12 | Cetak/simpan laporan ke file .txt | **Belum sesuai** | Tidak ada fstream/ofstream dan tidak ada proses write file | Ini kekurangan utama terhadap fitur wajib. |
| 13 | Setiap proses tambah data menampilkan ringkasan hasil dan ID data | Parsial | ID transaksi dibuat di 640, tapi tidak ditampilkan saat konfirmasi; tambah produk tidak merangkum ID hasil | Perlu konsisten menampilkan ID hasil tambah/transaksi. |

## Evaluasi Role (Admin/User) terhadap Rules

| Rule Role dari Acuan | Status | Bukti | Catatan |
|---|---|---|---|
| Role disimpan saat registrasi | Belum sesuai | User hanya username/password (12-15), registrasi 761-763 | Tidak ada atribut role dalam struct User. |
| Menu menyesuaikan role | Sesuai | Login return status 1/2 (768-793), routing menu 823-827 | Admin dan pelanggan dipisah menu. |
| Tiap aksi CRUD/laporan/statistik cek hak akses | Parsial | Pemisahan lewat menu, bukan guard per aksi | Belum ada pengecekan eksplisit + pesan akses ditolak di tiap fitur. |
| Jika akses tidak sesuai tampil "Akses ditolak" | Belum sesuai | Tidak ditemukan literal "Akses ditolak" | Saat ini akses dipisah lewat alur login saja. |
| User lihat data miliknya | Belum sesuai | Riwayat global (682-719), tidak terkait username | Semua riwayat dalam sesi berpotensi terlihat user lain. |

## Kekurangan Utama (Prioritas Tinggi)

1. **Belum ada simpan/cetak laporan ke file .txt** (fitur wajib acuan belum terpenuhi).
2. **Role belum dimodelkan di data akun** (hanya hardcoded admin + user biasa).
3. **Belum ada kontrol akses eksplisit per fitur dengan pesan "Akses ditolak"**.
4. **Fitur pencarian/pengurutan belum eksplisit sebagai menu fitur utama**.
5. **Riwayat transaksi belum per-user** (belum memenuhi batasan data milik sendiri).
6. **Validasi input belum konsisten** (masih bisa memasukkan nilai negatif/kosong di beberapa titik).

## Kekurangan Tambahan Teknis

1. Penggunaan `system("cls")` dan `system("pause")` (100, 134, 289, 756, dst) bersifat Windows-centric, kurang portabel untuk Linux.
2. Belum ada batas aman saat menambah keranjang/riwayat (`keranjangCount`, `riwayatCount`) terhadap kapasitas maksimum.
3. Belum ada validasi duplikasi username saat registrasi.
4. Belum ada validasi duplikasi ID produk saat admin menambah produk.

## Kesimpulan
Proyek Kelompok 2 **cukup baik secara fondasi** dan **sudah memenuhi banyak poin dasar**, tetapi **belum lulus penuh** terhadap ketentuan acuan karena ada beberapa fitur wajib yang masih kurang, terutama:
- simpan/cetak laporan ke file `.txt`,
- kepatuhan rules role secara eksplisit,
- pencarian/pengurutan yang lebih formal,
- konsistensi validasi input.

Jika kekurangan prioritas tinggi di atas diperbaiki, proyek ini berpotensi naik menjadi kategori **sesuai penuh**.