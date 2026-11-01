# Literasi Nusantara Jaya
### Aplikasi Pemantauan Transaksi Toko Buku Berbasis Bahasa C

## Deskripsi Proyek

**Literasi Nusantara Jaya** merupakan aplikasi berbasis terminal yang dibuat menggunakan bahasa pemrograman C untuk membantu pengelolaan data buku dan transaksi penjualan pada toko buku.

Program ini dikembangkan sebagai bagian dari tugas praktikum mata kuliah Algoritma dan Pemrograman. Aplikasi menerapkan konsep dasar pemrograman C, seperti `struct`, array, fungsi, percabangan, perulangan, pengolahan file, serta algoritma pengurutan data.

## Fitur Utama

Program memiliki beberapa fitur berikut:

1. **Input Buku Baru**  
   Menambahkan data buku berupa nama, jenis, dan harga. Kode buku dibuat secara otomatis dengan format BK001, BK002, dan seterusnya.

2. **Melihat Riwayat Transaksi**  
   Menampilkan daftar transaksi penjualan yang telah dicatat.

3. **Melihat Daftar Buku**  
   Menampilkan seluruh data buku yang tersimpan.

4. **Menghapus Riwayat Transaksi**  
   Menghapus riwayat transaksi berdasarkan nomor urut yang dipilih.

5. **Menghapus Data Buku**  
   Menghapus data buku berdasarkan nomor urut yang dipilih.

6. **Keluar dan Menyimpan Data**  
   Menyimpan data buku dan riwayat transaksi sebelum program ditutup.

7. **Input Transaksi Penjualan**  
   Mencatat transaksi berdasarkan kode buku dan jumlah pembelian serta menghitung total harga secara otomatis.

8. **Pengurutan Data Buku**
   - Bubble Sort: mengurutkan nama buku secara alfabetis dari A sampai Z.
   - Selection Sort: mengurutkan harga buku dari tertinggi ke terendah.

## Struktur Proyek

```text
toko-buku-project-team/
│
├── main.c
├── data.h
├── file.c
├── buku.c
├── transaksi.c
├── history.c
├── sorting.c
│
├── databuku.txt
├── history.txt
│
└── README.md
```

### Keterangan File

| File | Keterangan |
|---|---|
| `main.c` | Program utama dan menu aplikasi. |
| `data.h` | Deklarasi struct, variabel, dan prototype fungsi. |
| `file.c` | Membaca dan menyimpan data ke file. |
| `buku.c` | Mengelola data buku. |
| `transaksi.c` | Mengelola transaksi penjualan. |
| `history.c` | Mengelola riwayat transaksi. |
| `sorting.c` | Mengimplementasikan algoritma Bubble Sort dan Selection Sort. |
| `databuku.txt` | File penyimpanan data buku. |
| `history.txt` | File penyimpanan riwayat transaksi. |

## Penyimpanan Data

Program menggunakan dua file teks untuk menyimpan informasi:

- `databuku.txt`: menyimpan data buku.
- `history.txt`: menyimpan riwayat transaksi.

Data dibaca ketika program dijalankan dan disimpan kembali ketika pengguna memilih menu keluar.

Apabila file penyimpanan belum tersedia, program dirancang untuk tetap dapat dijalankan dengan kondisi data awal kosong.

