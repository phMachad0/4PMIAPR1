#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "swap.h"

// Function to heap a subtree rooted with node i
void heap(char *arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left = 2*i + 1
    int right = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (left < n && strcasecmp(arr[left], arr[largest]) > 0)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && strcasecmp(arr[right], arr[largest]) > 0)
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heap the affected sub-tree
        heap(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(char *arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // Call max heap on the reduced heap
        heap(arr, i, 0);
    }
}

// Function to print an array of strings
void printArray(char *arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s ", arr[i]);
    printf("\n");
}

int main() {
    char *arr[] = {"Longtemps", "je", "me", "suis", "couche", "de", "bonne", "heure", "Parfois", "a", "peine", "ma", "bougie", "eteinte"}; // Input array
    int n = sizeof(arr) / sizeof(arr[0]); // Calculate size of array

    printf("Original array:\n");
    printArray(arr, n); // Print original array

    heapSort(arr, n); // Sort the array

    printf("Sorted array:\n");
    printArray(arr, n); // Print sorted array

    return 0;
}