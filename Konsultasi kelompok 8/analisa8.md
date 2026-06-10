# Analisis Kesesuaian Kelompok 8

Tanggal analisis: 10 Juni 2026
Objek analisis:
- Kode: Konsultasi kelompok 8/Kelompok8.cpp
- Acuan: File acuan/tubes.md

## Ringkasan Eksekutif
Program reservasi restoran yang relatif matang: model data `Meja`/`Reservasi`, validasi input kuat (tanggal, jam, nama, kontak), dan implementasi persistensi ke file `reservasi.txt` (fungsi load/save tersedia). Ada menu admin dan customer (admin login hardcoded). Fitur pencarian, ubah, batal, dan cetak nota/struk juga ada. Tingkat kesesuaian diperkirakan **~92% (sangat sesuai)**.

## Matriks Kesesuaian terhadap Acuan

| No | Ketentuan Acuan | Status | Bukti pada Kode | Catatan |
|---|---|---|---|---|
| 1 | Topik umum, di luar kampus | Sesuai | Reservasi restoran (CLI) | ✅ |
| 2 | Bahasa C++ dan terminal/CLI | Sesuai | `iostream`, menu teks | ✅ |
| 3 | Minimal 2 `struct` data inti | Sesuai | `Meja`, `Reservasi` | ✅ |
| 4 | Modularisasi fungsi (>=8) | Sesuai | `muatReservasiDariFile`, `simpanSemuaDataKeFile`, validasi, CRUD, dll. | ✅ |
| 5 | Menu awal: Login, Buat Akun, Keluar | Parsial | Admin login hardcoded; customer tidak perlu akun | Idealnya tambahkan manajemen akun jika ingin lengkap. |
| 6 | Setelah login tampil menu pengelolaan data | Sesuai | Menu admin untuk manajemen, customer dapat reservasi | ✅ |
| 7 | CRUD data utama | Sesuai | Tambah/tampil/ubah/batal reservasi tersedia | ✅ |
| 8 | Validasi input dasar | Sesuai | Validasi tanggal, jam, nama, kontak | ✅ |
| 9 | Pesan sukses/gagal jelas | Sesuai | Tersedia konfirmasi dan pesan error | ✅ |
| 10 | Pencarian atau pengurutan data | Parsial | Ada pencarian berdasarkan nama/nomor telepon | Cukup memadai; bisa ditambah filter tanggal. |
| 11 | Ringkasan/statistik sederhana | Parsial | Belum ada rekap pendapatan per hari | Tambahkan laporan agregat jika diminta. |
| 12 | Cetak/simpan laporan ke file .txt | Sesuai | Fungsi menyimpan `reservasi.txt` dan mencetak struk | ✅ |
| 13 | Setiap tambah data menampilkan ringkasan + ID | Sesuai | Reservasi menghasilkan ID dan menampilkan ringkasan | ✅ |

## Evaluasi Role dan Keamanan

- Role admin ada tetapi hardcoded: aman untuk demo tetapi tidak ideal untuk produksi.  
- Customer tidak memerlukan akun, yang sesuai untuk use-case reservasi sederhana.  
- Karena ada file I/O untuk reservasi, data bertahan antar sesi.

## Kekurangan Utama
1. Login admin masih hardcoded — tidak ada `users.txt` untuk manajemen akun.  
2. Belum ada laporan agregat (pendapatan, jumlah reservasi per-hari) yang diekspor untuk analisis.  
3. Konsistensi format file: gunakan CSV atau JSON untuk interoperabilitas.

## Kekurangan Teknis Tambahan
1. Saat skala besar, format `reservasi.txt` harus distandarisasi agar parsing robust.  
2. Perlu proteksi terhadap format tanggal yang tidak standar lintas locale.

## Rekomendasi Perbaikan (Urutan Prioritas)
1. Implementasikan manajemen akun admin (`users.csv`) alih-alih hardcoded; tambahkan hashing sederhana untuk password jika diperlukan.  
2. Tambahkan `laporan.txt` rekap (pendapatan per-hari, jumlah reservasi per-hari) untuk admin.  
3. Konversi format penyimpanan ke CSV/JSON demi kemudahan parsing dan integrasi.  
4. Tambahkan filter pencarian berdasarkan rentang tanggal untuk laporan.

## Kesimpulan
Kelompok 8 hampir sepenuhnya memenuhi ketentuan `tubes.md`: modular, validasi kuat, CRUD reservasi, dan persistensi file. Dengan sedikit perbaikan pada manajemen akun dan penambahan laporan agregat, proyek ini akan sepenuhnya sesuai.

---
Laporan ini dibuat berdasarkan pembacaan `Konsultasi kelompok 8/Kelompok8.cpp` dan perbandingan dengan `File acuan/tubes.md`.
