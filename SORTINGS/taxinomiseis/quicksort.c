#include <stdio.h>
//O(nlogn)  O(n^2) worst //// O(n) worst case , O(logn) best case 
// Συνάρτηση για την εναλλαγή δύο στοιχείων
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Συνάρτηση QuickSort
void quicksort(int *x, int lower, int upper) {
    if (lower < upper) {
        int pivot = x[(lower + upper) / 2]; // Επιλογή pivot
        int i = lower;
        int j = upper;

        // Κατανομή των στοιχείων γύρω από το pivot
        while (i <= j) {
            while (x[i] < pivot) i++;
            while (x[j] > pivot) j--;
            if (i <= j) {
                swap(&x[i], &x[j]);
                i++;
                j--;
            }
        }

        // Αναδρομική ταξινόμηση των υποσυνόλων
        if (lower < j) quicksort(x, lower, j);
        if (i < upper) quicksort(x, i, upper);
    }
}

// Κύρια συνάρτηση
int main() {
    int x[9] = {1, 2, 5, 7, 3, 4, 8, 1, 2};
    int n = sizeof(x) / sizeof(x[0]);

    quicksort(x, 0, n - 1);

    // Εκτύπωση του ταξινομημένου πίνακα
    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    return 0;
}

