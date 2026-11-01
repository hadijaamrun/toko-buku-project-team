#include <stdio.h>
#include <ctype.h>
#include "data.h"

//Fungsi dari buku.c untuk menampilkan tabel buku
void tampilTabelBuku(Buku data[], int jumlah);

//Membuang sisa input (termasuk enter) setelah scanf
static void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

//Membandingkan dua nama tanpa membedakan huruf besar dan kecil
static int bandingNama(char a[], char b[]) {
    int i = 0;

    while (a[i] != '\0' && tolower((unsigned char) a[i]) == tolower((unsigned char) b[i])) {
        i++;
    }
    return tolower((unsigned char) a[i]) - tolower((unsigned char) b[i]);
}

//Bubble sort - urutkan berdasarkan nama buku (ascending)
void bubbleSortNama(Buku data[], int jumlah) {
    int i, j;
    Buku temp;

    for (i = 0; i < jumlah - 1; i++) {
        for (j = 0; j < jumlah - 1 - i; j++) {
            //Tukar jika nama sebelah kiri lebih besar dari kanan
            if (bandingNama(data[j].nama, data[j + 1].nama) > 0) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

//Selection sort - urutkan berdasarkan harga buku (descending)
void selectionSortHarga(Buku data[], int jumlah) {
    int i, j, idxMaks;
    Buku temp;

    for (i = 0; i < jumlah - 1; i++) {
        //Cari harga tertinggi dari sisa data
        idxMaks = i;
        for (j = i + 1; j < jumlah; j++) {
            if (data[j].harga > data[idxMaks].harga) {
                idxMaks = j;
            }
        }

        //Tukar ke posisi i
        if (idxMaks != i) {
            temp = data[i];
            data[i] = data[idxMaks];
            data[idxMaks] = temp;
        }
    }
}

//Menu 8 - Sub-menu sorting buku
//Sorting dilakukan pada salinan array agar urutan data asli tidak berubah
void menuSorting() {
    static Buku salinan[MAX_BUKU];
    char pilihan;
    int i, valid;

    do {
        printf("\n=== Sort Buku ===\n");
        printf("a. Urutkan berdasarkan nama buku (ascending, bubble sort)\n");
        printf("b. Urutkan berdasarkan harga buku (descending, selection sort)\n");
        printf("c. Kembali ke menu utama\n");
        printf("Pilihan: ");

        valid = scanf(" %c", &pilihan);
        bersihkanBuffer();
        if (valid == EOF) {
            return;
        }
        pilihan = (char) tolower((unsigned char) pilihan);

        switch (pilihan) {
            case 'a':
            case 'b':
                //Validasi data buku kosong
                if (jumlahBuku == 0) {
                    printf("Tidak ada data buku untuk diurutkan.\n");
                    break;
                }

                //Salin data buku
                for (i = 0; i < jumlahBuku; i++) {
                    salinan[i] = daftarBuku[i];
                }

                if (pilihan == 'a') {
                    bubbleSortNama(salinan, jumlahBuku);
                    printf("\nHasil urut berdasarkan nama buku (A-Z):\n");
                } else {
                    selectionSortHarga(salinan, jumlahBuku);
                    printf("\nHasil urut berdasarkan harga buku (tertinggi - terendah):\n");
                }

                tampilTabelBuku(salinan, jumlahBuku);
                break;
            case 'c':
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 'c');
}
