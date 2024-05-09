#include <stdio.h>

int main() {
    int n;
    printf("Dizinin eleman sayisini girin: ");
    scanf("%d", &n);

    int dizi[n];
    int frekans[150] = {0};

    for (int i = 0; i < n; i++) {
        printf("%d. sayiyi girin: ", i + 1);
        scanf("%d", &dizi[i]);

        frekans[dizi[i]]++; //değerler tekrar sayısı hesaplama
    }

    for (int i = 0; i < n; i++) {
        int flag = 0;
        if (frekans[dizi[i]] > 1) {
            for (int q = i + 1; q < n; q++) {
                if (dizi[q] == dizi[i]) { // bu değerden dizimizde 1'den fazla hale var ise flag 0 yapacak
                    flag = 0 ;
                }
            }
            if (flag == 0) { //kaydırma işlem yapma(silme işlemi)
                for (int a = i; a < n; a++) {
                    dizi[a] = dizi[a + 1];
                }
                n--;
                i--;
            }
        }
        if (flag == 1) { //şimdiki indexin değeri dizimizde sıralayacak
            int temp;
            for (int j = 0; j < n - 1; j++) {
                if (dizi[i] < dizi[j]) {
                    temp = dizi[j];
                    dizi[j] = dizi[i];
                    dizi[i] = temp;
                }
            }
        }
    }

    printf("\nSirali benzersiz elemanlar: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", dizi[i]);
    }

    return 0;
}
