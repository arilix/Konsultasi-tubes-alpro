# Analisis Kesesuaian Kelompok 11

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 11/Kelompok11.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program antrean print dokumen (CLI) yang menyediakan registrasi/login, role, CRUD dokumen, pencarian, statistik, dan fungsi `cetakLaporan()` yang menghasilkan `laporan_dokumen.txt`. Fitur fungsional lengkap namun saat ini data disimpan in-memory; perlu penambahan persistensi agar data bertahan antar sesi. Estimasi kesesuaian **~85% (baik)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Aplikasi print/antrean dokumen | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `iostream`, menu teks | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | `Akun`, `Dokumen` | ✅ |
| 4 | Modularisasi fungsi (>=8) | Sesuai | Registrasi, login, CRUD, pencarian, statistik, cetakLaporan | ✅ |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Menu registrasi/login/keluar tersedia | ✅ |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Menu admin/user berbeda | ✅ |
| 7 | CRUD data utama | Sesuai | Tambah/Tampil/Update/Hapus dokumen | ✅ |
| 8 | Validasi input dasar | Parsial | Validasi ada tapi perlu diperkuat (panjang, format) | Tambahkan sanitasi input. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Notifikasi aksi tersedia | ✅ |
| 10 | Pencarian atau pengurutan data | Sesuai | Fungsi pencarian tersedia | ✅ |
| 11 | Ringkasan/statistik sederhana | Sesuai | Fungsi statistik menampilkan ringkasan | ✅ |
| 12 | Cetak/simpan laporan ke file .txt | Parsial | `cetakLaporan()` menulis `laporan_dokumen.txt` tetapi data sumber in-memory | Pastikan data persist agar laporan komprehensif. |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Parsial | Penambahan menampilkan info, ID mungkin tidak stabil antar sesi | Gunakan ID persisten bila disimpan ke file. |

## Evaluasi Role (Admin/User)

| Aturan role dari acuan | Status | Bukti | Catatan |
|---|---|---|---|
| Role disimpan saat registrasi | Tidak sesuai | Pembuatan akun hanya di memori | Simpan `users.csv` saat registrasi untuk persistensi. |
| Menu menyesuaikan role | Sesuai | Menu dirouting menurut role | ✅ |
| Setiap aksi cek hak akses | Parsial | Beberapa fungsi cek role lewat menu | Tambahkan guard eksplisit per-fungsi untuk keamanan. |

## Kekurangan Utama
1. Tidak ada persistensi pengguna/dokumen ke file — data hilang setelah program berakhir.  
2. Validasi input (panjang string, karakter illegal) dapat diperkuat.  
3. ID entitas tidak dipertahankan antar sesi karena tidak ada penyimpanan.

## Kekurangan Teknis Tambahan
1. Format laporan: pastikan encoding/format konsisten (UTF-8, newline).  
2. Untuk dataset besar, pertimbangkan struktur file yang efisien (CSV/JSON) atau DB sederhana.

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan fungsi `simpanUsers()` dan `simpanDokumen()` yang menulis ke `users.csv` dan `dokumen.csv`; muat pada startup.  
2. Terapkan guard akses di setiap fungsi sensitif dan tampilkan pesan `Akses ditolak` bila perlu.  
3. Standardisasikan format laporan dan tambahkan rekap agregat (dokumen per-hari, jumlah cetak).  
4. Tambahkan unit kecil untuk validasi input terpusat.

## Kesimpulan
Kelompok 11 sudah menyediakan fitur fungsional penting (registrasi/login, CRUD, pencarian, statistik, cetak laporan). Menambahkan persistensi file dan memperkuat validasi/akses akan membuat proyek sepenuhnya sesuai `tubes.md`.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 11/Kelompok11.cpp` dan perbandingan dengan `File acuan/tubes.md`.
