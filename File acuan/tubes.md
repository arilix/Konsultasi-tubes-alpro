Laboratorium Teknik Komputer

# TUGAS BESAR
# PERTEMUAN KE-5 (C++ ONLY)

## Ketentuan Topik (Wajib)
Contoh Sistem Manajemen Tiket Kereta Api pada foto hanya referensi alur, dan tidak boleh dipakai kembali sebagai topik tugas besar.

Setiap mahasiswa wajib membuat sistem pengelolaan data lain yang:
- Bersifat umum.
- Berada di luar konteks kampus.
- Topiknya bebas sesuai minat mahasiswa.

Topik bertema data kampus tidak diperbolehkan, misalnya:
- Data mahasiswa/dosen.
- Mata kuliah, KRS/KHS, nilai, absensi kuliah.
- Administrasi organisasi kampus.

## Deskripsi Umum
Mahasiswa diminta membuat program C++ berbasis menu (terminal/CLI) untuk sistem pengelolaan data sesuai topik bebas yang dipilih. Program harus menunjukkan alur manajemen data yang lengkap: input, simpan, tampil, ubah, hapus, dan laporan/rekap.

Fokus tugas ini adalah penerapan materi C++ secara terintegrasi: percabangan, perulangan, fungsi/prosedur, string, array/struct, validasi input, dan pengolahan data.

## Penjelasan Tugas dari Foto (Sebagai Pola, Bukan Tema)
Foto dipakai sebagai contoh pola alur aplikasi, bukan tema yang harus diikuti. Implementasi minimal mengikuti pola berikut:

1. Halaman awal menampilkan menu minimal:
   - Login
   - Buat Akun
   - Keluar
2. Setelah login, tampilkan menu fitur pengelolaan data.
3. Program memiliki fitur CRUD (Tambah, Tampil, Update, Hapus).
4. Setiap proses tambah data menampilkan ringkasan hasil dan ID data.
5. Program menyediakan fitur cetak/simpan laporan ke file .txt.

Catatan:
- Penggunaan role admin/user diperbolehkan dan direkomendasikan.
- Jika tidak memakai role, pastikan alur menu tetap jelas dan lengkap.

## Penjelasan Role 
Jika mahasiswa menerapkan multi-role, gunakan minimal 2 role berikut:

1. Admin
   - Akses penuh ke seluruh data utama.
   - Dapat tambah, lihat, update, dan hapus semua data.
   - Dapat melihat ringkasan/statistik global.
   - Dapat mencetak laporan keseluruhan data.
   - Dapat mengelola akun user (opsional).

2. User/Operator
   - Dapat login dan mengakses menu operasional.
   - Dapat tambah data sesuai kebutuhan topik.
   - Dapat melihat data miliknya atau data sesuai batasan yang ditentukan program.
   - Dapat update/hapus data yang menjadi hak aksesnya.
   - Dapat mencetak laporan terbatas (data milik sendiri/unit sendiri).

Aturan akses role yang disarankan:
1. Role disimpan pada data akun saat registrasi.
2. Setelah login, menu yang tampil harus menyesuaikan role.
3. Setiap aksi (CRUD/laporan/statistik) wajib dicek hak aksesnya.
4. Jika akses tidak sesuai role, tampilkan pesan "Akses ditolak".
5. Jika tidak menggunakan multi-role, jelaskan alasan pada laporan.

## Aturan Umum Pengerjaan
1. Bahasa pemrograman wajib C++ (tanpa framework bahasa lain).
2. Program dijalankan di terminal/console (bukan GUI).
3. Gunakan modularisasi (fungsi/prosedur) untuk tiap fitur utama.
4. Wajib menggunakan struct untuk data inti (minimal 2 struct sesuai topik).
5. Program harus memiliki validasi input dasar:
   - Menu hanya menerima pilihan yang tersedia.
   - ID yang dipilih harus valid.
   - Nilai angka tidak boleh negatif (jika relevan).
   - Data wajib tidak boleh kosong.
6. Data utama minimal mendukung operasi CRUD:
   - Create (Tambah)
   - Read (Tampil)
   - Update
   - Delete
7. Wajib ada fitur pencarian atau pengurutan data (pilih salah satu, boleh keduanya).
8. Wajib ada ringkasan/statistik sederhana sesuai topik.
9. Program harus menampilkan pesan sukses/gagal yang jelas untuk setiap aksi.
10. Dilarang menyalin penuh dari internet/teman tanpa memahami logikanya.
11. Dilarang menggunakan topik Sistem Manajemen Tiket Kereta Api.

## Fitur Wajib
1. Registrasi akun dan login.
2. Tambah data utama.
3. Tampilkan data utama.
4. Update data utama.
5. Hapus data utama.
6. Pencarian atau pengurutan data.
7. Ringkasan/statistik sederhana.
8. Cetak/simpan laporan ke file .txt.

Contoh topik yang diperbolehkan:
- Manajemen data laundry.
- Manajemen data rental kendaraan.
- Manajemen data bengkel.
- Manajemen data klinik hewan.
- Manajemen data toko/UMKM.
- Topik umum lain di luar kampus.

## Ketentuan Teknis Minimal
1. Gunakan minimal 8 fungsi terpisah (contoh: login, register, tambah, tampil, update, hapus, statistik, cetakLaporan).
2. Gunakan perulangan untuk menu agar program berjalan sampai user memilih keluar.
3. Gunakan format output rapi dan mudah dibaca.
4. Rumus/perhitungan inti (jika ada) harus konsisten dan dijelaskan di komentar/laporan.
5. Nama variabel/fungsi harus relevan dengan topik yang dipilih.

## Kriteria Penilaian (Saran)
- Kesesuaian topik (bebas, umum, di luar kampus): 20%
- Kelengkapan fitur: 30%
- Kebenaran logika program: 20%
- Struktur kode dan modularisasi: 15%
- Validasi input dan handling error: 15%

## Catatan Asisten
- Deadline, cara pengumpulan, dan ketentuan tambahan dapat disesuaikan oleh masing-masing asisten kelas.
- Jika diperlukan, asisten dapat menambahkan fitur bonus (misalnya simpan/muat data dari file).

---

Praktikum Pemrograman