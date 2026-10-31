
#ifndef DATA_H
#define DATA_H

/* Kapasitas maksimum data */
#define MAX_BUKU 500
#define MAX_HISTORY 1000

/* Struktur data buku */
typedef struct {
    char kode[10];
    char nama[100];
    char jenis[50];
    double harga;
} Buku;

/* Struktur data histori transaksi */
typedef struct {
    char kodeBuku[10];
    int jumlahTerjual;
    double totalHarga;
} History;

/* Deklarasi variabel global */
extern Buku daftarBuku[MAX_BUKU];
extern int jumlahBuku;

extern History daftarHistory[MAX_HISTORY];
extern int jumlahHistory;

/* FUNGSI FILE HANDLING - file.c*/
void muatData(void);
void simpanBuku(void);
void simpanHistory(void);
void simpanSemua(void);

/* FUNGSI PENGELOLAAN BUKU - buku.c*/
void inputBuku(void);
void tampilBuku(void);
void hapusBuku(void);

/* FUNGSI TRANSAKSI - transaksi.c*/
void inputTransaksi(void);

/* FUNGSI HISTORY - history.c*/
void tampilHistory(void);
void hapusHistory(void);

/* FUNGSI SORTING - sorting.c*/
void menuSorting(void);

#endif
