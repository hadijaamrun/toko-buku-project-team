#include <stdio.h>
#include <string.h>
#include "data.h"

//Membuang sisa input (termasuk enter) setelah scanf
static void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

//Membuat kode buku otomatis BK001, BK002, dst
//Nomor diambil dari kode terbesar + 1 agar tidak bentrok setelah ada buku yang dihapus
static void buatKodeBuku(char *kode) {
    int i, nomor, terbesar;

    terbesar = 0;
    for (i = 0; i < jumlahBuku; i++) {
        if (sscanf(daftarBuku[i].kode, "BK%d", &nomor) == 1 && nomor > terbesar) {
            terbesar = nomor;
        }
    }

    sprintf(kode, "BK%03d", terbesar + 1);
}

//Menu 1 - Input data buku baru
void inputBuku() {
    Buku b;
    int valid;

    if (jumlahBuku >= MAX_BUKU) {
        printf("\nData buku sudah penuh.\n");
        return;
    }

    printf("\n=== Input Data Buku Baru ===\n");

    //Input nama buku, tidak boleh ada karakter '|' karena dipakai sebagai pemisah di file
    do {
        printf("Nama Buku  : ");
        valid = scanf(" %99[^\n]", b.nama);
        bersihkanBuffer();
        if (valid == EOF) {
            return;
        }
        if (strchr(b.nama, '|') != NULL) {
            printf("Nama buku tidak boleh mengandung karakter '|'.\n");
            valid = 0;
        }
    } while (valid != 1);

    //Input jenis buku
    do {
        printf("Jenis Buku : ");
        valid = scanf(" %49[^\n]", b.jenis);
        bersihkanBuffer();
        if (valid == EOF) {
            return;
        }
        if (strchr(b.jenis, '|') != NULL) {
            printf("Jenis buku tidak boleh mengandung karakter '|'.\n");
            valid = 0;
        }
    } while (valid != 1);

    //Input harga, harus angka dan lebih dari 0
    do {
        printf("Harga Buku : ");
        valid = scanf("%lf", &b.harga);
        bersihkanBuffer();
        if (valid == EOF) {
            return;
        }
        if (valid != 1 || b.harga <= 0) {
            printf("Harga harus berupa angka dan lebih dari 0.\n");
            valid = 0;
        }
    } while (valid != 1);

    //Kode buku dibuat otomatis
    buatKodeBuku(b.kode);

    daftarBuku[jumlahBuku] = b;
    jumlahBuku++;

    printf("\nBuku berhasil ditambahkan dengan kode %s\n", b.kode);
}

//Menampilkan tabel buku (dipakai juga oleh sorting.c untuk hasil pengurutan)
void tampilTabelBuku(Buku data[], int jumlah) {
    int i;

    printf("-------------------------------------------------------------------------------------\n");
    printf("%-4s %-7s %-32s %-20s %15s\n", "No", "Kode", "Nama Buku", "Jenis Buku", "Harga (Rp)");
    printf("-------------------------------------------------------------------------------------\n");
    for (i = 0; i < jumlah; i++) {
        printf("%-4d %-7s %-32.32s %-20.20s %15.2f\n", i + 1, data[i].kode, data[i].nama,
               data[i].jenis, data[i].harga);
    }
    printf("-------------------------------------------------------------------------------------\n");
}

//Menu 3 - Menampilkan seluruh data buku
void tampilBuku() {
    printf("\n=== Daftar Buku ===\n");

    if (jumlahBuku == 0) {
        printf("Belum ada data buku.\n");
        return;
    }

    tampilTabelBuku(daftarBuku, jumlahBuku);
}

//Menu 5 - Menghapus data buku berdasarkan index
void hapusBuku() {
    int index, i, valid;

    tampilBuku();
    if (jumlahBuku == 0) {
        return;
    }

    //Validasi index minimal 1 dan maksimal jumlah data
    do {
        printf("Masukkan index buku yang akan dihapus (1-%d): ", jumlahBuku);
        valid = scanf("%d", &index);
        bersihkanBuffer();
        if (valid == EOF) {
            return;
        }
        if (valid != 1 || index < 1 || index > jumlahBuku) {
            printf("Index tidak valid.\n");
            valid = 0;
        }
    } while (valid != 1);

    //Geser data setelah index ke kiri
    for (i = index - 1; i < jumlahBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
    }
    jumlahBuku--;

    printf("Data Successfully delete..\n");
}
