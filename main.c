
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "data.h"

/* Menampilkan menu utama */
void tampilkanMenu(void) {
    printf("\n");
    printf("========================================\n");
    printf("       TOKO BUKU LITERASI NUSANTARA     \n");
    printf("========================================\n");
    printf("1. Input Data Buku Baru\n");
    printf("2. View History Transaksi Penjualan\n");
    printf("3. View Buku\n");
    printf("4. Delete History\n");
    printf("5. Delete Buku\n");
    printf("6. Exit\n");
    printf("7. Input Transaksi Penjualan\n");
    printf("8. Sort Buku\n");
    printf("========================================\n");
}

/* Membaca pilihan menu dan memvalidasi input */
static int bacaPilihanMenu(int *pilihan) {
    char baris[128];
    char *akhir;
    long nilai;

    if (fgets(baris, sizeof(baris), stdin) == NULL) {
        return 0; /* Input berakhir */
    }

    /* Memeriksa apakah input terlalu panjang */
    if (strchr(baris, '\n') == NULL && !feof(stdin)) {
        int karakter;
        while ((karakter = getchar()) != '\n' &&
               karakter != EOF) {
        }
        return -1;
    }

    errno = 0;
    nilai = strtol(baris, &akhir, 10);

    /* Memeriksa input bukan angka */
    if (akhir == baris || errno == ERANGE) {
        return -1;
    }

    /* Memeriksa karakter tambahan */
    while (isspace((unsigned char)*akhir)) {
        akhir++;
    }

    if (*akhir != '\0' || nilai < 1 || nilai > 8) {
        return -1;
    }

    *pilihan = (int)nilai;
    return 1;
}

/* Fungsi utama program */
int main(void) {

    int pilihan;
    int status;

    /* Membaca data buku dan history dari file */
    muatData();

    printf("\nSelamat datang di Toko Buku Literasi Nusantara!\n");

    while (1) {

        tampilkanMenu();

        printf("Masukkan pilihan menu: ");

        status = bacaPilihanMenu(&pilihan);

        if (status == 0) {
            printf("\nInput berakhir. Menyimpan data...\n");
            simpanSemua();
            break;
        }

        if (status == -1) {
            printf("\nInput tidak valid! Pilih angka 1-8.\n");
            continue;
        }

        switch (pilihan) {

            case 1:
                inputBuku();
                break;

            case 2:
                tampilHistory();
                break;

            case 3:
                tampilBuku();
                break;

            case 4:
                hapusHistory();
                break;

            case 5:
                hapusBuku();
                break;

            case 6:
                simpanSemua();
                printf("\nData berhasil disimpan.\n");
                printf("Terima kasih telah menggunakan program!\n");
                return 0;

            case 7:
                inputTransaksi();
                break;

            case 8:
                menuSorting();
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}
