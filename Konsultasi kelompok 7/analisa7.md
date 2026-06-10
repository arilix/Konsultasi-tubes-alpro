# Analisis Kesesuaian Kelompok 7

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 7/Kelompok7.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program tiket berbasis CLI yang menyediakan registrasi/login, role admin/user, CRUD tiket, statistik sederhana, dan kemampuan menulis laporan ke `laporan.txt`. Secara fungsional fitur inti sudah lengkap dan terorganisir; kekurangan utama adalah ketiadaan persistensi akun/tiket (in-memory) dan beberapa validasi yang bisa diperkuat. Estimasi kesesuaian **~80% (baik)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Aplikasi tiket CLI | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `iostream` + menu teks | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | `Akun`, `Tiket` struct ada | ✅ |
| 4 | Modularisasi fungsi (>=8) | Sesuai | Fungsi register/login, tambah, tampil, update, hapus, statistik, cetakLaporan | ✅ |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Ada menu registrasi/login/keluar | ✅ |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Menu admin/user berbeda | ✅ |
| 7 | CRUD data utama | Sesuai | Tambah/Tampil/Update/Hapus tiket tersedia | ✅ |
| 8 | Validasi input dasar | Parsial | Validasi jenis data ada namun tidak konsisten | Perkuat validasi panjang string, nilai numerik. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Notifikasi di tiap aksi | ✅ |
| 10 | Pencarian atau pengurutan data | Tidak sesuai | Tidak ada menu pencarian eksplisit | Tambahkan search/filter untuk tiket. |
| 11 | Ringkasan/statistik sederhana | Sesuai | Fungsi `statistik()` menyediakan ringkasan | ✅ |
| 12 | Cetak/simpan laporan ke file .txt | Sesuai | `cetakLaporan()` menulis ke `laporan.txt` | ✅ |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Sesuai | Tambah tiket menampilkan ID | ✅ |

## Evaluasi Role (Admin/User)

| Aturan role dari acuan | Status | Bukti | Catatan |
|---|---|---|---|
| Role disimpan saat registrasi | Tidak sesuai | Akun dibuat di memori, tidak dipersist | Simpan `users.csv` untuk konsistensi antar sesi. |
| Menu menyesuaikan role | Sesuai | Routing menu berdasarkan role | ✅ |
| Setiap aksi cek hak akses | Parsial | Akses dibatasi lewat menu; belum ada guard per-fungsi | Tambahkan pemeriksaan `if(!isAdmin) return;` di fungsi sensitif. |

## Kekurangan Utama
1. Tidak ada persistensi akun dan tiket (hanya in-memory), sehingga data hilang setelah keluar.  
2. Tidak ada fitur pencarian/pengurutan tiket (opsional tapi direkomendasikan).  
3. Validasi input (panjang, batas, sanitasi) dapat ditingkatkan.

## Kekurangan Teknis Tambahan
1. Tidak ada sanitasi input untuk mencegah injection karakter khusus di nama/ID.  
2. Tidak ada perlindungan terhadap overflow array/vektor jika jumlah tiket sangat besar.

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Tambahkan fungsi `simpanAkun()` dan `simpanTiket()` yang menulis ke file CSV dan `muat()` pada startup.  
2. Tambahkan fitur pencarian dan filter (berdasarkan tujuan, tanggal, harga).  
3. Konsolidasikan validasi pada helper `validasiInput()` dan terapkan pada semua input.  
4. Tambahkan pemeriksaan hak akses eksplisit di level fungsi, dan pesan `Akses ditolak` jika diperlukan.

## Kesimpulan
Kelompok 7 telah mengimplementasikan sebagian besar fitur inti sesuai acuan: akun, CRUD tiket, statistik, dan cetak laporan. Dengan penambahan persistensi file dan beberapa perbaikan validasi/akses, proyek ini akan memenuhi acuan secara penuh.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 7/Kelompok7.cpp` dan perbandingan dengan `File acuan/tubes.md`.
