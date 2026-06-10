
# Analisis Kesesuaian Kelompok 3

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 3/Kelompok3.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program Kelompok 3 adalah aplikasi CLI sederhana untuk penjualan obat yang menyediakan daftar produk, pemilihan jumlah, dan pencetakan struk di layar. Implementasi berfungsi sebagai demonstrasi alur transaksi dasar, namun belum memenuhi banyak persyaratan pada `tubes.md` — khususnya modularisasi, model akun, CRUD yang lengkap, dan persistensi ke file. Tingkat kesesuaian saat ini dinilai sekitar 30% (parsial rendah).

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Topik aplikasi penjualan obat (Klinik) | Topik boleh menurut acuan. |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | Program seluruhnya menggunakan `iostream` | ✅ |
| 3 | Minimal 2 `struct` data inti | Tidak sesuai | Hanya ada `struct Obat` di awal file | Tambahkan `Transaksi` dan `User` untuk kelengkapan. |
| 4 | Modularisasi fungsi (minimal 8) | Tidak sesuai | Semua logika berada di `main()` tanpa fungsi terpisah | Perlu ekstraksi fungsi-fungsi (menu, tambah, cetak, validasi). |
| 5 | Menu awal: Login, Buat Akun, Keluar | Tidak sesuai | Tidak ada mekanisme akun atau menu awal | Wajib ditambahkan sesuai acuan. |
| 6 | Setelah login tampil menu pengelolaan data | Tidak sesuai | Tidak relevan (tidak ada login) | — |
| 7 | CRUD data utama | Tidak sesuai | Hanya create-like (menambah jumlah pembelian di array) dan tampil struk | Belum ada update/hapus atau persistensi data. |
| 8 | Validasi input dasar | Parsial | Validasi index menu, namun sedikit | Perlu validasi jumlah negatif, batasan kuantitas, input non-digit. |
| 9 | Pesan sukses/gagal jelas | Parsial | Ada pesan sederhana (Pilihan tidak valid) | Perlu pesan yang lebih informatif untuk setiap aksi. |
| 10 | Pencarian atau pengurutan data | Tidak sesuai | Tidak ada fitur pencarian/urutan | Harus ditambahkan jika diminta. |
| 11 | Ringkasan/statistik sederhana | Parsial | Menampilkan struk dan total | Tidak ada statistik agregat (penjualan per item, total transaksi). |
| 12 | Cetak/simpan laporan ke file .txt | Tidak sesuai | Tidak ada I/O file | Wajib ditambahkan (simpan struk/laporan). |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Tidak sesuai | Tidak ada ID transaksi atau ringkasan penyimpanan | Tambahkan ID transaksi dan cetak/rekam ke file. |

## Evaluasi Role (Admin/User)

| Aturan role dari acuan | Status | Bukti | Catatan |
|---|---|---|---|
| Role disimpan saat registrasi | Tidak sesuai | Tidak ada fungsi registrasi/login | Tambahkan `struct User` dan `save/load` untuk akun. |
| Menu menyesuaikan role | Tidak sesuai | Tidak ada login sehingga tidak ada menu per-role | Implementasikan menu berbeda untuk admin/user. |
| Setiap aksi cek hak akses | Tidak sesuai | Tidak ada pemeriksaan akses | Harus ditambahkan untuk operasi sensitif (mis. hapus data). |

## Kekurangan Utama
1. Tidak ada fitur registrasi/login dan model `role` — ketentuan wajib tidak terpenuhi.  
2. Semua logika ditulis di `main()` — kurang modular dan susah diuji/extend.  
3. Tidak ada penyimpanan file (persistensi) — data transaksi hilang saat program dihentikan.  
4. Validasi input masih minim (angka negatif, non-digit) dan tidak ada perlindungan terhadap buffer/masukan invalid.

## Kekurangan Teknis Tambahan
1. Tidak ada pembatas kapasitas array `beli[]` (walau 100 digunakan), tidak ada pengecekan overflow.  
2. Tidak ada format mata uang atau standardisasi output untuk memudahkan pembacaan laporan.  

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan `struct User { id, username, password, role }` dan fitur `buatAkun()` + `login()` beserta file CSV `users.csv`.  
2. Ekstrak fungsi-fungsi: `tampilkanMenu()`, `prosesPembelian()`, `cetakStruk()`, `simpanStrukKeFile()`, `validasiInput()` sehingga jumlah fungsi >= 8.  
3. Simpan riwayat transaksi ke file `transaksi.csv` dan tambahkan `cetakLaporan()` yang menulis ringkasan ke `.txt`.  
4. Perkuat validasi input (cek numeric, batas minimal/maksimal, sanitasi nama).  

## Kesimpulan
`Kelompok 3` memiliki implementasi minimal yang berjalan sebagai demo transaksi, namun masih jauh dari memenuhi seluruh persyaratan `tubes.md`. Dengan modulasi, penambahan model akun, dan persistensi file, program dapat ditingkatkan menjadi sesuai.

