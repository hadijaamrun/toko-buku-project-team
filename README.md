untuk memudahkan integrasi program, aku sudah menyiapkan rancangan data.h sebagai header utama yang akan digunakan oleh semua file .c.

Mohon setiap anggota menyesuaikan nama fungsi dengan kesepakatan berikut:

*Anggota 2 — file.c*
- muatData()
- simpanBuku()
- simpanHistory()
- simpanSemua()

Anggota 2 juga bertanggung jawab mendefinisikan array global:
- daftarBuku
- jumlahBuku
- daftarHistory
- jumlahHistory

*Anggota 3 — buku.c dan sorting.c*
- inputBuku()
- tampilBuku()
- hapusBuku()
- menuSorting()

*Anggota 4 — transaksi.c*
- inputTransaksi()

*Anggota 5 — history.c*
- tampilHistory()
- hapusHistory()

Semua fungsi tersebut harus menggunakan nama dan parameter yang sama dengan deklarasi di data.h.

Gunakan #include "data.h" pada setiap file .c yang membutuhkan struktur data atau deklarasi fungsi.

Jangan mendefinisikan ulang array global di masing-masing file karena dapat menyebabkan error saat proses kompilasi.

Kalau ada perubahan nama fungsi atau struktur data, mohon informasikan terlebih dahulu agar header dan main.c bisa disesuaikan.
