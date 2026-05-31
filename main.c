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
// 3. Selection Sort (Ascending)
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// 4. Merge Sort (String Ascending)
void merge(char arr[][MAX_LEN], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Alokasi temporary array dinamis agar tidak overflow di stack
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char *)malloc(n2 * sizeof(char *));
    for (int i = 0; i < n1; i++) L[i] = (char *)malloc(MAX_LEN * sizeof(char));
    for (int j = 0; j < n2; j++) R[j] = (char *)malloc(MAX_LEN * sizeof(char));

    for (int i = 0; i < n1; i++) strcpy(L[i], arr[l + i]);
    for (int j = 0; j < n2; j++) strcpy(R[j], arr[m + 1 + j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }
    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }

    // Free memory temp array
    for (int i = 0; i < n1; i++) free(L[i]);
    for (int j = 0; j < n2; j++) free(R[j]);
    free(L); free(R);
}

void mergeSort(char arr[][MAX_LEN], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 5. Quick Sort (String Ascending)
int partition(char arr[][MAX_LEN], int low, int high) {
    char pivot[MAX_LEN];
    strcpy(pivot, arr[high]);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            char temp[MAX_LEN];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }
    char temp[MAX_LEN];
    strcpy(temp, arr[i + 1]);
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);
    return (i + 1);
}

void quickSort(char arr[][MAX_LEN], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Shell Sort (String Ascending)
void shellSort(char arr[][MAX_LEN], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            char temp[MAX_LEN];
            strcpy(temp, arr[i]);
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                strcpy(arr[j], arr[j - gap]);
            }
            strcpy(arr[j], temp);
        }
    }
}