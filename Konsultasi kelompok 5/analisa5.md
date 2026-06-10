# Analisis Kesesuaian Kelompok 5

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 5/Kelompok5.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program bioskop berbasis CLI yang menyediakan registrasi/login, role `admin/user`, manajemen jadwal/film, pemesanan tiket, dan pemetaan kursi. Implementasi sudah relatif lengkap secara fungsional tetapi menyimpan data hanya di memori (vektor) sehingga tidak persisten antar sesi. Tingkat kesesuaian diperkirakan **~72% (parsial baik)** — memenuhi mayoritas fitur interaktif, tetapi perlu persistensi dan laporan untuk memenuhi acuan sepenuhnya.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Aplikasi bioskop CLI | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `cout/cin` pada fungsi utama dan modul | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | `Akun`, `Film`, `Tiket`/`Booking` | ✅ |
| 4 | Modularisasi fungsi (>=8) | Parsial | Beberapa fungsi terpisah (register, login, tambah film, booking) | Perlu ekstra utilitas (load/save, laporan, search). |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Ada menu awal dan registrasi/login | ✅ |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | `menuAdmin()` dan `menuUser()` | ✅ |
| 7 | CRUD data utama | Parsial | Admin dapat menambah dan menampilkan film; update/hapus tidak konsisten | Tambahkan Update/Delete penuh untuk film/jadwal. |
| 8 | Validasi input dasar | Parsial | Validasi kursi/jadwal sebagian | Perkuat validasi username/password/angka. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Pesan registrasi, login, pembelian, kesalahan kursi | ✅ |
| 10 | Pencarian atau pengurutan data | Tidak sesuai | Tidak ada fitur pencarian/urut film | Disarankan menambahkan pencarian judul/genre. |
| 11 | Ringkasan/statistik sederhana | Tidak sesuai | Hanya struk per transaksi tanpa agregat | Tambahkan laporan penjualan per-film/hari. |
| 12 | Cetak/simpan laporan ke file .txt | Tidak sesuai | Data hanya in-memory | Perlu I/O file: `users.csv`, `bookings.csv`, `laporan.txt`. |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Parsial | ID dibuat tetapi tampil tidak konsisten | Tampilkan ID transaksi/film saat sukses tambah. |

## Evaluasi Role dan Keamanan

- Implementasi akun & menu role sudah ada: ada alur registrasi dan login serta menu berbeda untuk admin dan user.  
- Kekurangan keamanan: password disimpan plain di memori (belum disimpan ke file), tidak ada hashing.  
- Karena tidak ada persistensi, tidak ada proteksi double-booking setelah restart.

## Kekurangan Utama
1. Tidak ada persistensi file untuk akun dan booking → semua data hilang saat program keluar.  
2. CRUD film/jadwal belum lengkap (update/hapus harus ditambah dan diuji).  
3. Tidak ada laporan agregat (penjualan per-film, pendapatan harian) yang diekspor.  
4. Validasi input perlu diperkuat (duplikasi username, panjang password, input non-digit).

## Kekurangan Teknis Tambahan
1. Penggunaan struktur data in-memory membuat integrasi multi-run sulit.  
2. Tidak ada format ekspor standar (CSV/JSON) — menggunakan simple text akan mempermudah grading.  
3. UI konsistensi: beberapa pesan/konfirmasi tidak menampilkan ID hasil operasi.

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan file I/O: `users.csv` (username,password,role), `bookings.csv` (id,user,film,jadwal,kursi,total), dan `laporan.txt`.  
2. Lengkapi CRUD film/jadwal (Create, Read, Update, Delete) dan tampilkan ID baru setelah tambah.  
3. Ekstrak utilitas: `simpan()`, `muat()`, `validasiInput()`, `cetakLaporan()` sehingga kode lebih modular.  
4. Tambahkan fitur pencarian film (judul/genre) dan laporan agregat untuk admin.  
5. Terapkan hashing password sederhana (mis. SHA-256 library) jika diperlukan untuk keamanan.

## Kesimpulan
Kelompok 5 memiliki fondasi aplikasi yang kuat (akun, role, pemesanan tiket, denah kursi). Untuk memenuhi sepenuhnya `tubes.md`, tim perlu menambahkan persistensi file, laporan agregat, validasi lebih ketat, dan penyempurnaan CRUD.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 5/Kelompok5.cpp` dan perbandingan dengan `File acuan/tubes.md`.
