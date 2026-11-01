#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "data.h"

// Menghapus newline dan spasi di awal/akhir input. 
static void rapikanInput(char *teks) {
    char *awal = teks;
    char *akhir;

    while (isspace((unsigned char)*awal)) {
        awal++;
    }

    if (awal != teks) {
        memmove(teks, awal, strlen(awal) + 1);
    }

    akhir = teks + strlen(teks);
    while (akhir > teks && isspace((unsigned char)akhir[-1])) {
        *--akhir = '\0';
    }
}

// Membaca input teks dengan aman. Mengembalikan 0 jika EOF/error. 
static int bacaInput(char *buffer, size_t ukuran) {
    if (fgets(buffer, (int)ukuran, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int karakter;
        while ((karakter = getchar()) != '\n' && karakter != EOF) {
        }
        return -1;
    }

    rapikanInput(buffer);
    return 1;
}

// Mencari buku berdasarkan kode yang dimasukkan pengguna. 
static int cariBuku(const char *kode) {
    int i;

    for (i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].kode, kode) == 0) {
            return i;
        }
    }

    return -1;
}

// Menu 7 - Input transaksi penjualan.
void inputTransaksi(void) {
    char kode[32];
    char inputJumlah[64];
    char *akhir;
    long jumlah;
    int status;
    int indexBuku;
    double totalHarga;
    History transaksi;

    printf("\n=== Input Transaksi Penjualan ===\n");

    if (jumlahBuku == 0) {
        printf("Belum ada data buku. Silakan input data buku terlebih dahulu.\n");
        return;
    }

    if (jumlahHistory >= MAX_HISTORY) {
        printf("Data histori transaksi sudah penuh. Transaksi tidak dapat ditambahkan.\n");
        return;
    }

    // Meminta kode buku dan menormalkan huruf menjadi kapital.
    do {
        printf("Masukkan Kode Buku       : ");
        status = bacaInput(kode, sizeof(kode));

        if (status == 0) {
            printf("\nInput dibatalkan.\n");
            return;
        }
        if (status == -1 || kode[0] == '\0') {
            printf("Kode buku tidak valid atau terlalu panjang.\n");
            continue;
        }

        {
            size_t i;
            for (i = 0; kode[i] != '\0'; i++) {
                kode[i] = (char)toupper((unsigned char)kode[i]);
            }
        }

        indexBuku = cariBuku(kode);
        if (indexBuku == -1) {
            printf("Kode buku tidak ditemukan. Periksa kembali kode buku.\n");
        }
    } while (status != 1 || kode[0] == '\0' || indexBuku == -1);

    // Meminta jumlah terjual berupa bilangan bulat positif.
    do {
        printf("Masukkan Jumlah Terjual  : ");
        status = bacaInput(inputJumlah, sizeof(inputJumlah));

        if (status == 0) {
            printf("\nInput dibatalkan.\n");
            return;
        }
        if (status == -1 || inputJumlah[0] == '\0') {
            printf("Jumlah terjual harus berupa bilangan bulat positif.\n");
            continue;
        }

        errno = 0;
        jumlah = strtol(inputJumlah, &akhir, 10);

        if (errno == ERANGE || akhir == inputJumlah || *akhir != '\0' ||
            jumlah <= 0 || jumlah > INT_MAX) {
            printf("Jumlah terjual harus berupa bilangan bulat positif.\n");
            status = -1;
        } else {
            status = 1;
        }
    } while (status != 1);

    totalHarga = daftarBuku[indexBuku].harga * (double)jumlah;
    if (!isfinite(totalHarga)) {
        printf("Total harga terlalu besar. Transaksi tidak dapat diproses.\n");
        return;
    }

    // Menambahkan transaksi ke array histori global 
    strcpy(transaksi.kodeBuku, daftarBuku[indexBuku].kode);
    transaksi.jumlahTerjual = (int)jumlah;
    transaksi.totalHarga = totalHarga;

    daftarHistory[jumlahHistory] = transaksi;
    jumlahHistory++;

    // Simpan histori agar transaksi langsung tercatat di history.txt.
    simpanHistory();

    //output
    printf("\nTransaksi berhasil dicatat.\n");
    printf("Kode Buku      : %s\n", transaksi.kodeBuku);
    printf("Nama Buku      : %s\n", daftarBuku[indexBuku].nama);
    printf("Harga Satuan   : Rp %.2f\n", daftarBuku[indexBuku].harga);
    printf("Jumlah Terjual : %d\n", transaksi.jumlahTerjual);
    printf("Total Harga    : Rp %.2f\n", transaksi.totalHarga);
}
