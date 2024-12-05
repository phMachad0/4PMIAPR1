#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swap.h"

// Function to partition the array
int partition(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcasecmp(arr[j], pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Function to implement quicksort
void quickSort(char *arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to print an array of strings
void printArray(char *arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
}

int main() {
    char *arr[] = {"Longtemps", "je", "me", "suis", "couche", "de", "bonne", "heure", "Parfois", "a", "peine", "ma", "bougie", "eteinte"};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array of words:\n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("\nSorted array of words:\n");
    printArray(arr, n);

    return 0;
}