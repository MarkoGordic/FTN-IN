#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int arr[], int n) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] < arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

float calculate_profit(int *zahtevi, int *radnici, int br_zahteva, int br_radnika) {
    bubble_sort(zahtevi, br_zahteva);
    bubble_sort(radnici, br_radnika);

    int zah_index = 0, rad_index = 0;
    float profit = 0.0;

    for(;zah_index < br_zahteva && rad_index < br_radnika;rad_index++){
        if(zahtevi[zah_index] >= radnici[rad_index]) {
            if(radnici[rad_index] >= 0 && radnici[rad_index] <= 10)
                profit += radnici[rad_index] * 0.25;
            else if(radnici[rad_index] <= 20)
                profit += radnici[rad_index] * 0.20;
            else
                profit += radnici[rad_index] * 0.15;

            printf("{%d, %d} ", zahtevi[zah_index], radnici[rad_index]);
            zah_index++;

        }
    }

    return profit;
}

int main() {
    int zahtevi[] = {5, 22, 12};
    int radnici[] = {3, 12, 27, 21, 9, 18};
    int n_zahtevi = sizeof(zahtevi) / sizeof(zahtevi[0]);
    int n_radnici = sizeof(radnici) / sizeof(radnici[0]);

    float profit = calculate_profit(zahtevi, radnici, n_zahtevi, n_radnici);
    printf("\nFirma po satu zaradi: %.2f\n", profit);

    return 0;
}
