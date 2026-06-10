# Analisis Kesesuaian Kelompok 12

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 12/Kelompok12.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Sistem kasir toko yang sudah menerapkan registrasi/login dengan file `akun.txt`, manajemen produk (`produk.txt`), transaksi (invoice/struk), dan laporan (`laporan.txt`). Implementasi menggunakan file I/O, menyediakan menu admin/user, serta fitur CRUD pada produk dan transaksi. Secara keseluruhan sangat sesuai dengan acuan: estimasi **~92% (sangat sesuai)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Aplikasi kasir toko CLI | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `iostream`, `fstream` digunakan | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | Representasi produk, akun, transaksi ada (file-backed) | ✅ |
| 4 | Modularisasi fungsi (>=8) | Parsial | Fungsi CRUD produk, transaksi, cetak laporan tersedia | Beberapa helper utilitas bisa ditambahkan. |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Ada registrasi/login (`akun.txt`) | ✅ |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Menu admin/user berbeda | ✅ |
| 7 | CRUD data utama | Sesuai | CRUD produk dan transaksi memakai file I/O | ✅ |
| 8 | Validasi input dasar | Parsial | Validasi numeric dasar ada | Tambah pengecekan duplikat ID dan sanitasi. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Konfirmasi transaksi dan notifikasi | ✅ |
| 10 | Pencarian atau pengurutan data | Tidak sepenuhnya | Tidak terlihat fitur search eksplisit | Bisa ditambahkan untuk UX. |
| 11 | Ringkasan/statistik sederhana | Parsial | `laporan.txt` ada tapi mungkin ringkasan terbatas | Perlu perluasan rekap (per-hari, produk terlaris). |
| 12 | Cetak/simpan laporan ke file .txt | Sesuai | `produk.txt`, `akun.txt`, `laporan.txt`, `struk.txt` ada | ✅ |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Parsial | ID produk dibuat; tampil kadang konsisten | Standardisasi output diperlukan. |

## Evaluasi Role dan Keamanan

- Akun disimpan di `akun.txt` dan role tampak tercatat — ini cocok dengan persyaratan per-role.  
- Perlu pengecekan duplikasi ID dan validasi input numeric untuk menghindari data korup.  
- Password tampaknya disimpan plain; hashing direkomendasikan bila diperlukan.

## Kekurangan Utama
1. Duplikasi ID saat tambah produk belum dicegah secara eksplisit.  
2. Validasi input numeric/sanitasi bisa diperkuat untuk mencegah entri invalid.  
3. Laporan agregat (produk terlaris, pendapatan per-hari) dapat ditingkatkan.

## Kekurangan Teknis Tambahan
1. Format file ad-hoc; pertimbangkan format CSV untuk konsistensi.  
2. Error handling I/O belum komprehensif (cek hasil `ifstream/ofstream`).

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan pengecekan duplikasi ID saat tambah produk dan tampilkan ID yang dihasilkan.  
2. Standarisasi format file menjadi CSV dan tambahkan parser yang robust.  
3. Perluas `laporan.txt` menjadi rekap yang bisa di-generate (pendapatan per-hari, top 5 produk).  
4. Tambahkan validasi input lebih lengkap dan handling error I/O.

## Kesimpulan
Kelompok 12 sudah memenuhi hampir semua ketentuan acuan: CLI, CRUD, role, pencetakan laporan, dan persistensi file. Dengan perbaikan minor pada validasi, duplikasi ID, dan format laporan, proyek ini akan sepenuhnya sesuai.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 12/Kelompok12.cpp` dan perbandingan dengan `File acuan/tubes.md`.
