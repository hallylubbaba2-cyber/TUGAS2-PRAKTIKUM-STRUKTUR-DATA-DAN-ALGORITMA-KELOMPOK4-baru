#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 10000
#define MAX_LEN 50
#define INT_DATA_SIZE 1000

// --- PROTOTIPE FUNGSI ---
void copyArrayInt(int src[], int dest[], int n);
void shuffleInt(int arr[], int n);
void printArrayInt(int arr[], int n, int limit);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);

void copyArrayStr(char src[][MAX_LEN], char dest[][MAX_LEN], int n);
void shuffleStr(char arr[][MAX_LEN], int n);
void printArrayStr(char arr[][MAX_LEN], int n, int limit);
void merge(char arr[][MAX_LEN], int l, int m, int r);
void mergeSort(char arr[][MAX_LEN], int l, int r);
int partition(char arr[][MAX_LEN], int low, int high);
void quickSort(char arr[][MAX_LEN], int low, int high);
void shellSort(char arr[][MAX_LEN], int n);

int readDataset(char arr[][MAX_LEN]);

// --- MAIN FUNCTION ---
int main() {
    srand(time(NULL)); // Seed untuk rand() agar acak asli tiap dijalankan
    int pilihanUtama, pilihanSub;
    
    // Alokasi memori array integer (Sorting Dasar)
    int masterInt[INT_DATA_SIZE];
    int tempInt[INT_DATA_SIZE];
    
    // Alokasi memori array string (Advance Sorting)
    // Menggunakan static atau dynamic allocation agar tidak stack overflow
    static char masterStr[MAX_WORDS][MAX_LEN];
    static char tempStr[MAX_WORDS][MAX_LEN];
    int totalWords = 0;

    // Generate data random awal untuk integer
    for(int i = 0; i < INT_DATA_SIZE; i++) {
        masterInt[i] = rand() % 10000; // Angka acak 0-9999
    }

    // Load dataset string untuk Advance Sorting
    totalWords = readDataset(masterStr);

    do {
        printf("\n==============================\n");
        printf("          MENU UTAMA          \n");
        printf("==============================\n");
        printf("1. Sorting Dasar (Integer)\n");
        printf("2. Advance Sorting (String)\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihanUtama);

        if (pilihanUtama == 1) {
            do {
                printf("\n==============================\n");
                printf("        SORTING DASAR         \n");
                printf("==============================\n");
                printf("1. Bubble Sort\n");
                printf("2. Insertion Sort\n");
                printf("3. Selection Sort\n");
                printf("4. Kembali\n");
                printf("Pilih metode: ");
                scanf("%d", &pilihanSub);

                if (pilihanSub >= 1 && pilihanSub <= 3) {
                    // Selalu gunakan data fresh yang di-shuffle sebelum disort
                    copyArrayInt(masterInt, tempInt, INT_DATA_SIZE);
                    shuffleInt(tempInt, INT_DATA_SIZE);

                    printf("\n--- Data SEBELUM Sorting (20 pertama) ---\n");
                    printArrayInt(tempInt, INT_DATA_SIZE, 20);

                    // Hitung waktu eksekusi
                    clock_t start = clock();
                    if (pilihanSub == 1) bubbleSort(tempInt, INT_DATA_SIZE);
                    else if (pilihanSub == 2) insertionSort(tempInt, INT_DATA_SIZE);
                    else if (pilihanSub == 3) selectionSort(tempInt, INT_DATA_SIZE);
                    clock_t end = clock();

                    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                    printf("\n--- Data SESUDAH Sorting (20 pertama) ---\n");
                    printArrayInt(tempInt, INT_DATA_SIZE, 20);

                    printf("\nWaktu proses sorting: %f detik\n", time_taken);
                }
            } while (pilihanSub != 4);

        } else if (pilihanUtama == 2) {
            if (totalWords == 0) {
                printf("[Error] Dataset string kosong atau file 'words.txt' tidak ditemukan!\n");
                continue;
            }
            do {
                printf("\n==============================\n");
                printf("       ADVANCE SORTING        \n");
                printf("==============================\n");
                printf("1. Merge Sort\n");
                printf("2. Quick Sort\n");
                printf("3. Shell Sort\n");
                printf("4. Kembali\n");
                printf("Pilih metode: ");
                scanf("%d", &pilihanSub);

                if (pilihanSub >= 1 && pilihanSub <= 3) {
                    copyArrayStr(masterStr, tempStr, totalWords);
                    shuffleStr(tempStr, totalWords);

                    printf("\n--- Data SEBELUM Sorting (20 pertama dari total %d kata) ---\n", totalWords);
                    printArrayStr(tempStr, totalWords, 20);

                    clock_t start = clock();
                    if (pilihanSub == 1) mergeSort(tempStr, 0, totalWords - 1);
                    else if (pilihanSub == 2) quickSort(tempStr, 0, totalWords - 1);
                    else if (pilihanSub == 3) shellSort(tempStr, totalWords);
                    clock_t end = clock();

                    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

                    printf("\n--- Data SESUDAH Sorting (20 pertama) ---\n");
                    printArrayStr(tempStr, totalWords, 20);

                    printf("\nWaktu proses sorting: %f detik\n", time_taken);
                }
            } while (pilihanSub != 4);
        }

    } while (pilihanUtama != 3);

    printf("\nProgram selesai. Terima kasih!\n");
    return 0;
}

// =========================================================
// UTILITY FUNCTIONS (FUNGSI PEMBANTU)
// =========================================================

void copyArrayInt(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

void shuffleInt(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void printArrayInt(int arr[], int n, int limit) {
    for (int i = 0; i < limit && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("... \n");
}

void copyArrayStr(char src[][MAX_LEN], char dest[][MAX_LEN], int n) {
    for (int i = 0; i < n; i++) strcpy(dest[i], src[i]);
}

void shuffleStr(char arr[][MAX_LEN], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_LEN];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void printArrayStr(char arr[][MAX_LEN], int n, int limit) {
    for (int i = 0; i < limit && i < n; i++) {
        printf("%s | ", arr[i]);
    }
    printf("... \n");
}

int readDataset(char arr[][MAX_LEN]) {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    while (count < MAX_WORDS && fscanf(file, "%49s", arr[count]) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

// =========================================================
// IMPLEMENTASI ALGORTIMA SORTING
// =========================================================

// 1. Bubble Sort (Ascending)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 2. Insertion Sort (Ascending)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}