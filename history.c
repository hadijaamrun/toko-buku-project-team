// Dibuat Oleh
// Nama : Muhammad Naufal Al Fadhil
// NIM  : 3002926731

#include <stdio.h>
#include "data.h"

static void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void tampilTabelHistory(History data[], int jumlah) {
    int i;

    printf("-----------------------------------------------------\n");
    printf("%-4s %-7s %-20s %15s\n", "No", "Kode", "Jumlah Terjual", "Total Harga (Rp)");
    printf("------------------------------------------------------\n");
    for (i = 0; i < jumlah; i++) {
        printf("%-4d %-7s %-20d %15.2f\n", i + 1, data[i].kodeBuku, data[i].jumlahTerjual,
               data[i].totalHarga);
    }
    printf("------------------------------------------------------\n");
}

// Menu 2 - Menampilkan history transaksi
void tampilHistory() {
    if (jumlahHistory == 0) {
        printf("Belum ada history transaksi.\n");
        return;
    }

    tampilTabelHistory(daftarHistory, jumlahHistory);
}

// Menu 4 - Menghapus data history berdasarkan index
void hapusHistory() {
    if (jumlahHistory == 0) {
        printf("Belum ada history transaksi.\n");
        return;
    }

    int index, i, valid;

    tampilHistory();
    printf("Masukkan nomor history yang ingin dihapus: ");
    valid = scanf("%d", &index);
    if (valid != 1 || index < 1 || index > jumlahHistory) {
        printf("Nomor history tidak valid.\n");
        bersihkanBuffer();
        return;
    }

    for (i = index - 1; i < jumlahHistory - 1; i++) {
        daftarHistory[i] = daftarHistory[i + 1];  
    }
    jumlahHistory--;

    printf("History transaksi berhasil dihapus.\n");
}