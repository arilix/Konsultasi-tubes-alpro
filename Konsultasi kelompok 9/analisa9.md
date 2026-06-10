# Analisis Kesesuaian Kelompok 9

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 9/Kelompok9.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program rental game (PS/Nintendo) yang sudah menerapkan registrasi/login, role, dan penyimpanan file (`users.txt`, `rental.txt`, `games.txt`). Fitur order, pembatalan, reprint invoice, dan manajemen admin tersedia. Implementasi file I/O cukup memadai dan konsisten sehingga tingkat kesesuaian diperkirakan **~90% (sangat sesuai)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Rental game CLI | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `fstream`/`iostream` digunakan | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | Ada `User`, `Rental`, dan `Game` (representasi struktur/file) | ✅ |
| 4 | Modularisasi fungsi (>=8) | Parsial | Beberapa fungsi I/O dan operasi tersedia | Lengkapi dengan helper validasi dan pencarian untuk kesetaraan fungsional. |
| 5 | Menu awal: Login, Buat Akun, Keluar | Sesuai | Ada registrasi/login dan keluar | ✅ |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Menu admin/user dipisah | ✅ |
| 7 | CRUD data utama | Parsial/Sesuai | Admin dapat manage games; rental diappend ke file; ada pembatalan (delete) | Perlu konsistensi update file (rewrite) saat delete. |
| 8 | Validasi input dasar | Parsial | Validasi slot/durasi ada | Perlu validasi username/format lebih ketat. |
| 9 | Pesan sukses/gagal jelas | Sesuai | Ada konfirmasi transaksi dan error | ✅ |
| 10 | Pencarian atau pengurutan data | Tidak jelas | Tidak ada menu pencarian/urut eksplisit | Opsional namun direkomendasikan. |
| 11 | Ringkasan/statistik sederhana | Parsial | Invoice per-order tersedia, reprint memungkinkan | Tambahkan laporan agregat (pendapatan total). |
| 12 | Cetak/simpan laporan ke file .txt | Sesuai | `rental.txt`, `users.txt`, `games.txt` digunakan; invoices disimpan | ✅ |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Parsial | Invoice memiliki ID/format; tambah game menunjukkan hasil | Tingkat tampilan ID perlu konsisten. |

## Evaluasi Role dan Keamanan

- Akun disimpan di `users.txt` dengan format `username#password#role` — sesuai kebutuhan persistensi.  
- Password disimpan plain text dalam file — pertimbangkan hashing jika butuh keamanan lebih tinggi.  
- Akses admin dibedakan lewat role field; pastikan validasi role tidak mudah dimanipulasi saat file diedit manual.

## Kekurangan Utama
1. Penggunaan `system("pause")/cls` di beberapa bagian tidak portabel.  
2. Password disimpan plain text di file — risiko keamanan untuk data riil.  
3. Belum ada laporan agregat yang menghitung total pendapatan / product popularity.

## Kekurangan Teknis Tambahan
1. Hapus/rewrite file dilakukan dengan membuka file baru dan menulis ulang — implementasi harus tangani error I/O.  
2. Kurang helper pencarian/filter untuk game; UX bisa dipermudah dengan search.  

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Jangan gunakan `system("pause")/cls`; gunakan fungsi portable atau beri opsi `press enter to continue`.  
2. Simpan password dalam bentuk hash, atau setidaknya dokumentasikan bahwa ini prototype edukasional.  
3. Tambahkan `laporan.txt` yang menyediakan ringkasan pendapatan total per-range waktu.  
4. Tambahkan fitur pencarian/penyortiran game (judul/genre) dan perbaiki validasi input.  

## Kesimpulan
Kelompok 9 telah memenuhi sebagian besar ketentuan acuan termasuk persistensi file, registrasi/login, CRUD/pembatalan, dan reprint invoice. Dengan perbaikan portabilitas dan perbaikan keamanan sederhana, proyek ini akan menjadi kuat dan sesuai acuan.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 9/Kelompok9.cpp` dan perbandingan dengan `File acuan/tubes.md`.
