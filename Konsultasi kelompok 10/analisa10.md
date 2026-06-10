# Analisis Kesesuaian Kelompok 10

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 10/Kelompok10.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program peminjaman buku berbasis CLI yang menghitung durasi peminjaman, melakukan validasi tanggal, dan menyediakan opsi menyimpan invoice ke file `invoice_<nama>.txt`. Namun aplikasi tidak menyediakan registrasi/login, tidak menyimpan katalog buku, dan banyak logika masih di `main()`. Kesesuaian keseluruhan diperkirakan **~60% (parsial)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Aplikasi peminjaman buku CLI | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `iostream`, menu teks | ✅ |
| 3 | Minimal 2 `struct` data inti | Tidak sesuai | Tidak ada model `User`/`Buku` persisten | Tambahkan `Buku` dan `Peminjaman` struct. |
| 4 | Modularisasi fungsi (>=8) | Tidak sesuai | Banyak logika di `main()` | Ekstrak fungsi validasi, hitung durasi, simpan invoice. |
| 5 | Menu awal: Login, Buat Akun, Keluar | Tidak sesuai | Tidak ada registrasi/login | Perlu ditambah. |
| 6 | Setelah login tampil menu pengelolaan data | Tidak sesuai | Tidak ada konsep akun/role | — |
| 7 | CRUD data utama | Tidak sesuai | Hanya peminjaman ad-hoc tanpa katalog CRUD | Tambahkan CRUD katalog buku dan riwayat peminjaman. |
| 8 | Validasi input dasar | Sesuai | Validasi tanggal, telepon, email sederhana | ✅ tetapi perlu konsistensi. |
| 9 | Pesan sukses/gagal jelas | Parsial | Ada konfirmasi dan pesan error | Bisa diperbaiki untuk konsistensi. |
| 10 | Pencarian atau pengurutan data | Tidak sesuai | Tidak ada | Opsional namun direkomendasikan. |
| 11 | Ringkasan/statistik sederhana | Tidak sesuai | Hanya invoice per transaksi ada | Tambahkan laporan rekap. |
| 12 | Cetak/simpan laporan ke file .txt | Parsial | Invoice dapat disimpan (`invoice_<nama>.txt`) | Perlu sistem penyimpanan riwayat/pusat (mis. `riwayat.csv`). |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Tidak sesuai | Invoice ada tetapi tidak ada ID transaksi terpusat | Tambah ID transaksi dan simpan riwayat. |

## Evaluasi Role dan Akses

- Tidak ada mekanisme user/role; semua operasi dilakukan secara anonim — sesuai untuk demo, tetapi tidak memenuhi acuan per-role.

## Kekurangan Utama
1. Tidak ada registrasi/login dan model `User` — fitur wajib menurut acuan.  
2. Tidak ada katalog buku persistensi atau CRUD buku.  
3. Modularisasi minim; banyak logic di `main()` menyulitkan pengembangan lebih lanjut.

## Kekurangan Teknis Tambahan
1. Validasi tanggal sudah bagus, tetapi format input rentan per-locale; pertimbangkan format `YYYY-MM-DD`.  
2. Penyimpanan invoice per-nama bagus, namun riwayat pusat (CSV) lebih berguna untuk laporan.

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan `struct User` + `buatAkun()` + `login()` dan simpan akun ke `users.csv`.  
2. Tambahkan katalog buku (`buku.csv`) dan CRUD (admin).  
3. Ekstrak fungsi: `validasiTanggal()`, `hitungDurasi()`, `simpanInvoice()`, `simpanRiwayat()`.  
4. Simpan semua invoice ke `riwayat.csv` agar admin dapat membuat rekap/laporan.  

## Kesimpulan
Kelompok 10 sudah menunjukkan beberapa fitur teknis (validasi, simpan invoice), tetapi perlu model akun, CRUD katalog buku, dan persistensi riwayat untuk memenuhi `tubes.md` secara penuh.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 10/Kelompok10.cpp` dan perbandingan dengan `File acuan/tubes.md`.
