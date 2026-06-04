# Analisis Kesesuaian Kelompok 1

Tanggal analisis: 04 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 1/Konsultasi kelompok 1.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program `Konsultasi kelompok 1.cpp` adalah aplikasi pemesanan makanan berbasis CLI yang berfungsi sebagai prototipe sistem order (menu, keranjang, ongkir, metode bayar, dan invoice). Program sudah menjalankan alur pemesanan dan mencetak invoice namun **belum memenuhi banyak ketentuan wajib** dalam `tubes.md` sehingga tingkat kesesuaian adalah **parsial (sekitar 35-45%)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Topik: aplikasi pemesanan makanan (CLI) | Topik diperbolehkan oleh acuan. |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `Konsultasi kelompok 1.cpp` menggunakan `cout/cin` | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | Ada `Menu` dan `Pesanan` | ✅ |
| 4 | Modularisasi fungsi (minimal 8 fungsi) | Tidak sesuai | Hanya `getWaktuSekarang()` + `main()` | Hanya 1 fungsi bantuan; harus dipisah ke fitur (login, register, tambah, tampil, update, hapus, statistik, cetakLaporan, dsb.). |
| 5 | Menu awal: Login, Buat Akun, Keluar | Tidak sesuai | Tidak ada mekanisme login/registrasi | Alur tidak memenuhi ketentuan awal. |
| 6 | Setelah login tampil menu pengelolaan data | Tidak sesuai | Tidak ada konsep akun/role | Tidak ada pembeda akses admin/user. |
| 7 | CRUD data utama | Parsial | Ada proses tambah pesanan (create) dan menampilkan invoice (read) | Tidak ada fitur update/hapus pesanan atau CRUD untuk katalog/menu yang persistent. |
| 8 | Validasi input dasar | Parsial | Validasi pilihan menu dan jumlah, validasi uang tunai minimal | Masih banyak input yang belum tervalidasi (format nama, alamat kosong, pilihan ongkir/metode invalid). |
| 9 | Pesan sukses/gagal jelas | Sesuai | Ada pesan sukses pada beberapa titik (tambah pesanan, checkout) | ✅ |
| 10 | Pencarian atau pengurutan data | Tidak sesuai | Tidak ada fitur pencarian/urut | Fitur wajib ini belum ada. |
| 11 | Ringkasan/statistik sederhana | Parsial | Invoice per-pesanan tersedia | Tidak ada statistik agregat (total transaksi, item terpopuler). |
| 12 | Cetak/simpan laporan ke file .txt | Tidak sesuai | Tidak ada I/O file | Fitur wajib laporan ke file belum diimplementasikan. |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Tidak sesuai | Invoice tampil, tetapi tidak ada ID data atau ringkasan penyimpanan | Perlu ID transaksi dan penulisan ringkasan ke file. |

## Evaluasi Role (Admin/User)

| Aturan role dari acuan | Status | Bukti | Catatan |
|---|---|---|---|
| Role disimpan saat registrasi | Tidak sesuai | Tidak ada registrasi/user model | Hanya input nama pemesan; tidak ada akun/role. |
| Menu menyesuaikan role | Tidak sesuai | Tidak ada mekanisme login | — |
| Setiap aksi cek hak akses | Tidak sesuai | Tidak ada pengecekan hak akses | — |

## Kekurangan Utama (Prioritas Tinggi)
1. Tidak ada fitur `registrasi` dan `login` (wajib menurut acuan).
2. Tidak ada model `role` (admin/user) dan kontrol akses per-fitur.
3. Tidak ada operasi CRUD lengkap untuk data utama (update, delete, persistensi data).
4. Tidak ada fitur pencarian/penyortiran data sebagai menu terpisah.
5. Tidak ada penyimpanan / pencetakan laporan ke file `.txt`.
6. Hanya satu helper function — kebutuhan modular minimal (>=8 fungsi) tidak terpenuhi.

## Kekurangan Teknis Tambahan
1. Tidak ada penanganan batas kapasitas keranjang atau validasi input panjang/format.
2. Tidak ada penyimpanan file (semua data hanya di memori selama runtime).
3. Tidak ada pemisahan kode menjadi fungsi-fungsi terpisah untuk tiap fitur (menyulitkan pengujian dan pemeliharaan).
4. Format mata uang/locale tidak distandarkan (angka ditampilkan mentah tanpa format ribuan).

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan `struct User { id, username, password, role }` dan fitur `buatAkun()` + `login()`.
2. Pisahkan alur menu menjadi `admin` dan `user` setelah login; tambahkan pemeriksaan hak akses tiap fitur.
3. Implementasikan CRUD lengkap untuk katalog/menu dan transaksi (Create, Read, Update, Delete).
4. Tambahkan penyimpanan sederhana menggunakan file CSV atau TXT untuk data katalog, akun, dan riwayat transaksi.
5. Tambahkan fitur `cetakLaporan()` yang menulis ringkasan/riwayat ke file `.txt`.
6. Tambahkan minimal 6 fungsi lain (search, sort, statistik, cetak, simpan, load) sehingga jumlah fungsi total >= 8.
7. Perbaiki validasi input (cek kosong, tipe data, batas angka, duplikasi ID/nama).
8. Ganti `system("cls")/pause` dengan pendekatan portabel jika diperlukan (atau gunakan guard platform).

## Kesimpulan
`Konsultasi kelompok 1.cpp` memberikan prototipe pemesanan makanan yang dapat berjalan di terminal, namun **belum memenuhi banyak persyaratan wajib** dalam `tubes.md` (terutama login/registrasi, CRUD penuh, pencarian, dan penyimpanan laporan ke file). Dengan tambahan modulasi fungsi, model akun/role, dan penyimpanan file, program ini bisa ditingkatkan menjadi sesuai.

---
Laporan ini dibuat berdasarkan pembacaan kode pada `Konsultasi kelompok 1/Konsultasi kelompok 1.cpp` dan perbandingan dengan `File acuan/tubes.md`.
