#include "tri.h"
#include "../td6/swap.h"
#include "../td6/heap.h"

void fusion(vect_t tab, vect_t tmp, size_t gauche, size_t droit) {
    int milieu = gauche + (droit - gauche) / 2;
    int i, j, k;
    int n1 = milieu - gauche + 1;
    int n2 = droit - milieu;

    for (i = 0; i < n1; i++)
        tmp->data[i] = tab->data[gauche + i];
    for (j = 0; j < n2; j++)
        tmp->data[n1 + j] = tab->data[milieu + 1 + j];

    i = 0;
    j = n1;
    k = gauche;
    while (i < n1 && j < n1 + n2) {
        if (tab->equal_data(tmp->data[i], tmp->data[j]) < 0) {
            tab->data[k] = tmp->data[i];
            i++;
        }
        else {
            tab->data[k] = tmp->data[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tab->data[k] = tmp->data[i];
        i++;
        k++;
    }

    while (j < n1 + n2) {
        tab->data[k] = tmp->data[j];
        j++;
        k++;
    }
}

void _trifusionrec(vect_t tab, vect_t tmp, size_t gauche, size_t droit) {
    if (gauche < droit) {
        int milieu = gauche + (droit - gauche) / 2;
        _trifusionrec(tab, tmp, gauche, milieu);
        _trifusionrec(tab, tmp, milieu + 1, droit);
        fusion(tab, tmp, gauche, droit);
    }
}

void mergesort(vect_t tab) {
    vect_t tmp = vect_new(tab->actual_size, tab->fprint_data, tab->delete_data, tab->equal_data);
    _trifusionrec(tab, tmp, 0, tab->actual_size - 1);
    vect_delete(tmp);
}

int partitionner(vect_t tab, int gauche, int droit) {
    int i = (gauche - 1);

    for (int j = gauche; j <= droit - 1; j++) {
        if (tab->equal_data(tab->data[j], tab->data[droit]) < 0) {
            i++;
            swap(&tab->data[i], &tab->data[j]);
        }
    }

    swap(&tab->data[i + 1], &tab->data[droit]);
    return (i + 1);
}

void quick_sortrec(vect_t tab, int gauche, int droit) {
    if (gauche < droit) {
        int pi = partitionner(tab, gauche, droit);

        quick_sortrec(tab, gauche, pi - 1);
        quick_sortrec(tab, pi + 1, droit);
    }
}

void quicksort(vect_t tab) {
    quick_sortrec(tab, 0, tab->actual_size - 1);
}

void heapsort(vect_t tab) {
    heap_t tas = heap_new(tab->actual_size, tab->fprint_data, tab->delete_data, tab->equal_data);

    for (int i = 0; i < tab->actual_size; i++) {
        heap_add(tab->data[i], tas);
    }

    for (int i = 0; i < tab->actual_size; i++) {
        tab->data[i] = heap_get_extrema(tas);
        heap_delete_extrema(tas);
    }

    tas = heap_delete(tas);
}

int binary_search(vect_t tab, void* element) {
    int left = 0;
    int right = tab->actual_size - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (tab->equal_data(tab->data[middle], element) == 0) {
            return middle;
        }

        if (tab->equal_data(tab->data[middle], element) < 0) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}