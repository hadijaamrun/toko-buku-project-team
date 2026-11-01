
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "data.h"

/* Definisi variabel global: hanya didefinisikan satu kali di file.c. */
Buku daftarBuku[MAX_BUKU];
int jumlahBuku = 0;

History daftarHistory[MAX_HISTORY];
int jumlahHistory = 0;

/* Menghapus spasi dan karakter akhir baris di awal/akhir teks. */
static char *rapikanTeks(char *teks) {
    char *akhir;

    while (isspace((unsigned char)*teks)) {
        teks++;
    }

    akhir = teks + strlen(teks);
    while (akhir > teks && isspace((unsigned char)akhir[-1])) {
        *--akhir = '\0';
    }

    return teks;
}

/* Memisahkan satu baris menjadi sejumlah kolom dengan delimiter '|'. */
static int pisahkanKolom(char *baris, char *kolom[], int banyakKolom) {
    int i;

    for (i = 0; i < banyakKolom - 1; i++) {
        char *pemisah = strchr(baris, '|');
        if (pemisah == NULL) {
            return 0;
        }
        *pemisah = '\0';
        kolom[i] = rapikanTeks(baris);
        baris = pemisah + 1;
    }

    if (strchr(baris, '|') != NULL) {
        return 0;
    }
    kolom[banyakKolom - 1] = rapikanTeks(baris);

    for (i = 0; i < banyakKolom; i++) {
        if (kolom[i][0] == '\0') {
            return 0;
        }
    }
    return 1;
}

/* Mengubah teks menjadi double dan menolak angka tidak valid. */
static int bacaDouble(const char *teks, double *hasil) {
    char *akhir;
    double nilai;

    errno = 0;
    nilai = strtod(teks, &akhir);
    if (akhir == teks || *akhir != '\0' || errno == ERANGE ||
        !isfinite(nilai) || nilai < 0) {
        return 0;
    }

    *hasil = nilai;
    return 1;
}

/* Mengubah teks menjadi integer positif. */
static int bacaJumlah(const char *teks, int *hasil) {
    char *akhir;
    long nilai;

    errno = 0;
    nilai = strtol(teks, &akhir, 10);
    if (akhir == teks || *akhir != '\0' || errno == ERANGE ||
        nilai <= 0 || nilai > INT_MAX) {
        return 0;
    }

    *hasil = (int)nilai;
    return 1;
}

/* Membaca satu record buku sesuai format Kode|Nama|Jenis|Harga. */
static int bacaBarisBuku(char *baris, Buku *buku) {
    char *kolom[4];

    if (!pisahkanKolom(baris, kolom, 4) ||
        strlen(kolom[0]) >= sizeof(buku->kode) ||
        strlen(kolom[1]) >= sizeof(buku->nama) ||
        strlen(kolom[2]) >= sizeof(buku->jenis) ||
        !bacaDouble(kolom[3], &buku->harga)) {
        return 0;
    }

    strcpy(buku->kode, kolom[0]);
    strcpy(buku->nama, kolom[1]);
    strcpy(buku->jenis, kolom[2]);
    return 1;
}

/* Membaca satu record history sesuai format Kode|Jumlah|Total. */
static int bacaBarisHistory(char *baris, History *history) {
    char *kolom[3];

    if (!pisahkanKolom(baris, kolom, 3) ||
        strlen(kolom[0]) >= sizeof(history->kodeBuku) ||
        !bacaJumlah(kolom[1], &history->jumlahTerjual) ||
        !bacaDouble(kolom[2], &history->totalHarga)) {
        return 0;
    }

    strcpy(history->kodeBuku, kolom[0]);
    return 1;
}

/* Membaca isi databuku.txt ke array daftarBuku. */
static void muatBuku(void) {
    FILE *file = fopen("databuku.txt", "r");
    char baris[512];
    int nomorBaris = 0;

    if (file == NULL) {
        if (errno == ENOENT) {
            printf("databuku.txt belum ada. Data buku dimulai kosong.\n");
        } else {
            perror("Gagal membuka databuku.txt");
        }
        return;
    }

    while (fgets(baris, sizeof(baris), file) != NULL) {
        Buku buku;
        nomorBaris++;

        if (strchr(baris, '\n') == NULL && !feof(file)) {
            int karakter;
            while ((karakter = fgetc(file)) != '\n' && karakter != EOF) {
            }
            fprintf(stderr, "databuku.txt baris %d terlalu panjang, dilewati.\n", nomorBaris);
            continue;
        }

        if (*rapikanTeks(baris) == '\0') {
            continue;
        }

        if (jumlahBuku >= MAX_BUKU) {
            fprintf(stderr, "Kapasitas buku penuh (maksimum %d).\n", MAX_BUKU);
            break;
        }

        if (bacaBarisBuku(baris, &buku)) {
            daftarBuku[jumlahBuku++] = buku;
        } else {
            fprintf(stderr, "databuku.txt baris %d tidak valid, dilewati.\n", nomorBaris);
        }
    }

    if (ferror(file)) {
        perror("Kesalahan membaca databuku.txt");
    }
    fclose(file);
    printf("Berhasil memuat %d buku.\n", jumlahBuku);
}

/* Membaca isi history.txt ke array daftarHistory. */
static void muatHistory(void) {
    FILE *file = fopen("history.txt", "r");
    char baris[512];
    int nomorBaris = 0;

    if (file == NULL) {
        if (errno == ENOENT) {
            printf("history.txt belum ada. Histori dimulai kosong.\n");
        } else {
            perror("Gagal membuka history.txt");
        }
        return;
    }

    while (fgets(baris, sizeof(baris), file) != NULL) {
        History history;
        nomorBaris++;

        if (strchr(baris, '\n') == NULL && !feof(file)) {
            int karakter;
            while ((karakter = fgetc(file)) != '\n' && karakter != EOF) {
            }
            fprintf(stderr, "history.txt baris %d terlalu panjang, dilewati.\n", nomorBaris);
            continue;
        }

        if (*rapikanTeks(baris) == '\0') {
            continue;
        }

        if (jumlahHistory >= MAX_HISTORY) {
            fprintf(stderr, "Kapasitas history penuh (maksimum %d).\n", MAX_HISTORY);
            break;
        }

        if (bacaBarisHistory(baris, &history)) {
            daftarHistory[jumlahHistory++] = history;
        } else {
            fprintf(stderr, "history.txt baris %d tidak valid, dilewati.\n", nomorBaris);
        }
    }

    if (ferror(file)) {
        perror("Kesalahan membaca history.txt");
    }
    fclose(file);
    printf("Berhasil memuat %d histori transaksi.\n", jumlahHistory);
}

/* Dipanggil satu kali ketika program mulai dijalankan. */
void muatData(void) {
    jumlahBuku = 0;
    jumlahHistory = 0;
    muatBuku();
    muatHistory();
}

/* Menyimpan array buku ke databuku.txt dengan delimiter '|'. */
void simpanBuku(void) {
    FILE *file = fopen("databuku.txt", "w");
    int i;
    int gagal = 0;

    if (file == NULL) {
        perror("Gagal membuat/menulis databuku.txt");
        return;
    }

    for (i = 0; i < jumlahBuku; i++) {
        Buku *buku = &daftarBuku[i];
        if (fprintf(file, "%s|%s|%s|%.15g\n",
                    buku->kode, buku->nama, buku->jenis, buku->harga) < 0) {
            gagal = 1;
            break;
        }
    }

    if (fclose(file) == EOF) {
        gagal = 1;
    }
    if (gagal) {
        fprintf(stderr, "Gagal menyimpan seluruh data ke databuku.txt.\n");
    }
}

/* Menyimpan array transaksi ke history.txt dengan delimiter '|'. */
void simpanHistory(void) {
    FILE *file = fopen("history.txt", "w");
    int i;
    int gagal = 0;

    if (file == NULL) {
        perror("Gagal membuat/menulis history.txt");
        return;
    }

    for (i = 0; i < jumlahHistory; i++) {
        History *history = &daftarHistory[i];
        if (fprintf(file, "%s|%d|%.15g\n",
                    history->kodeBuku, history->jumlahTerjual,
                    history->totalHarga) < 0) {
            gagal = 1;
            break;
        }
    }

    if (fclose(file) == EOF) {
        gagal = 1;
    }
    if (gagal) {
        fprintf(stderr, "Gagal menyimpan seluruh data ke history.txt.\n");
    }
}

/* Dipanggil dari menu Exit untuk menyimpan kedua file. */
void simpanSemua(void) {
    simpanBuku();
    simpanHistory();
}
