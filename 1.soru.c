#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 150

struct kuyruk {
    int bas;
    int son;
    int deger[MAX_SIZE];
};

struct linkedliste{
    int data;
    struct linkedliste *next;
};

struct stack{
    int count;
    int top;
    int deger1[150];
};

struct linkedliste *head = NULL;
struct stack *sta = NULL;
struct kuyruk *ptr = NULL;
int rakamSayisi = 0;
int tekrarMedyan;

void ikiliSayiHesaplama(int n) {
    // Ptr'nin NULL olup olmadığını kontrol etme veya dinamik olarak başlatma
    if (ptr == NULL) {
        ptr = (struct kuyruk *)malloc(sizeof(struct kuyruk));
        ptr->bas = 0;
        ptr->son = -1;
    }

    //1'den N'e kadar kuyruğa ekleme
    for (int i = 1; i <= n; i++) {
        ptr->son++;
        if (ptr->son < MAX_SIZE) {
            ptr->deger[ptr->son] = i; // Yapının üyesini kullanarak deger dizisine erişme
        } else {
            printf("Queue is full.\n");
            break;
        }
    }

    //Kuyruktaki ilk beş elemanın toplamı aynı kuyruğa eklenmesi aynı zamanda bu beş eleman kuyruktan silinmesi.
    int toplam = 0;
    for(int i = 0; i < 5; i++){
        int x = ptr->deger[ptr->bas];
            for(int j=1;j<=ptr->son;j++)
                ptr->deger[j-1] = ptr->deger[j];
            ptr->son--;
            toplam+=x;
    }
    ptr->son++;
    ptr->deger[ptr->son] = toplam;

    //Kuyruğun son halindeki ilk on elemanın ortalaması ve yine aynı kuyruğa eklenmesi aynı zamanda bu on eleman kuyruktan çıkarması.
    int ilk10ortalama = 0;
    for(int i = 0; i < 10; i++){
        int x = ptr->deger[ptr->bas];
            for(int j=1;j<=ptr->son;j++)
                ptr->deger[j-1] = ptr->deger[j];
            ptr->son--;
            ilk10ortalama+=x;
    }
    ptr->son++;
    ptr->deger[ptr->son] = ilk10ortalama/10;

    //Kuyruğun son halindeki değerlerinin max ve min değerlerinin farkı ve kuyruğa eklenmesi ve min ve max değerler kuyruktan çıkarması
    int min = 150;
    int max = 0;
    int indexMin;
    int indexMax;

    for(int i = 0; i <= ptr->son; i++){
        if(min > ptr->deger[i]){
            min = ptr->deger[i];
            indexMin = i;
        }
        if(max < ptr->deger[i]){
            max = ptr->deger[i];
            indexMax = i;
        }
    }

    int fark = max - min;

    for(int i = indexMin; i<= ptr->son; i++){
        ptr->deger[i] = ptr->deger[i+1];
    }
    ptr->son--;
    // Max değerin indexi kaymadıysa if içine girecek
    if(ptr->deger[indexMax] == max){
        for(int i = indexMax; i<= ptr->son; i++){
            ptr->deger[i] = ptr->deger[i+1];
        }
    }
    else{
        for(int i = indexMax-1; i<= ptr->son; i++){
            ptr->deger[i] = ptr->deger[i+1];
        }
    }
    ptr->deger[ptr->son] = fark;

    //kuyruktan bir bağlı listelere aktarma
    for(int i = 0; i <= ptr->son; i++) {
        struct linkedliste *gecici = (struct linkedliste *)malloc(sizeof(struct linkedliste));
        gecici->data = ptr->deger[i];
        gecici->next = NULL;

        if (head == NULL) {
            head = gecici;
        } else {
            struct linkedliste *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = gecici;
        }
    }

    if (sta == NULL) {
        sta = (struct stack *)malloc(sizeof(struct stack));
        sta->count = 0;
        sta->top = -1;
    }

    struct linkedliste *temp = head;

    // Bağlı listedeki verileri sırayla yığına aktarma
    while (temp != NULL) {
        sta->top++; // Yığın indeksi artırılıyor
        if (sta->top < MAX_SIZE) {
            sta->deger1[sta->top] = temp->data; // Yığına veri ekleniyor
            sta->count++; // Eleman sayısı artırılıyor
            temp = temp->next;
        } else {
            printf("Stack is full.\n");
            break;
        }
    }

    // Yığındaki elemanları tersine çevirme (opsiyonel)
    int start = 0;
    int end = sta->top;

    while (start < end) {
        // Elemanları yer değiştirme
        int tempData = sta->deger1[start];
        sta->deger1[start] = sta->deger1[end];
        sta->deger1[end] = tempData;

        // İndisleri güncelleme
        start++;
        end--;
    }

    int frekans[150] = {0};
    int flag = 0;
    int ikiliSayi;

    //frekans hesaplama
    for(int i=0; i<sta->count; i++){
        frekans[sta->deger1[i]]++;
    }

     //tekrar eden sayı varsa ikili sayı değişekninde tutma
    for(int i=0; i<sta->count; i++){
        if(frekans[sta->deger1[i]]>1){
            ikiliSayi = sta->deger1[i];
            flag = 1;
            break;
         }
       }

    //tekrar eden sayı yok ise dizi sırlama
    if(flag == 0){
        for(int i=0; i<sta->count-1; i++){
            for(int j=0; j<sta->count-1-i; j++){
                if(sta->deger1[j] > sta->deger1[j+1]){
                    int temp = sta->deger1[j+1];
                    sta->deger1[j+1] = sta->deger1[j];
                    sta->deger1[j] = temp;
                }
            }
        }
        //medyan hesaplama
        if(sta->count % 2 == 1)
           ikiliSayi=sta->deger1[(sta->count/2)];
        else
           ikiliSayi=(sta->deger1[(sta->count/2)]+sta->deger1[(sta->count/2)-1])/2;
    }

    int sta_top = sta->top;
    tekrarMedyan = ikiliSayi;
    //medyan yada tekrar edilmiş sayı ikili sayı sistemine çevirme
    while(ikiliSayi > 0){
        sta->top++;
        sta->deger1[sta->top] = ikiliSayi%2;
        ikiliSayi /= 2;
        sta->count++;
        rakamSayisi++;
    }
}

void sifreUretma(){
    printf("\nRepeated or median value in the stack: %d",tekrarMedyan);
    printf("\niste sifremiz: ");

    printf("%c",(rand()%26) + 'A');
    printf("%c",(rand()%15) + 33);
    printf("%c",(rand()%26) + 'a');
    printf("%c",(rand()%15) + 33);

    for(int i=0; i<rakamSayisi; i++){
        printf("%d",sta->deger1[sta->top]);
        sta->top--;
    }

}

void LinkedListele(){
    if (head == NULL){
        printf("Liste bos.\n");
        return head;
    }
    struct linkedliste * gecici;
    gecici = head;
    printf("->Elements in the linked:\n");
    while (1){
        printf("%d ",gecici->data);
        if (gecici->next == NULL) break;
        else gecici = gecici->next;
    }
    return gecici;
}

void queueListele(){
    if (ptr != NULL) {
        printf("->Elements in the queue:\n");
        for (int i = ptr->bas; i <= ptr->son; i++) {
            printf("%d ", ptr->deger[i]);
        }
        printf("\n");
    }
}

void stackListele(){
    if(sta != NULL){
        printf("\n->Elements in the stack:\n");
        for(int i=0; i<sta->count  - rakamSayisi ; i++){
            printf("\%d ",sta->deger1[i]);
        }
    }
}


int main() {
    srand(time(NULL));
    int sayi;
    printf("Sifre Belirleme Programina hosgeldiniz.\n");
    printf("Lutfen bir sayi girin: ");
    scanf("%d",&sayi);

    ikiliSayiHesaplama(sayi);
    queueListele();
    LinkedListele();
    stackListele();
    sifreUretma();




    return 0;
}
