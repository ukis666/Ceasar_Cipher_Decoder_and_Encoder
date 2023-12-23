#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>  // _getch fonksiyonu için
#define MAX_UZUNLUK 2000

int can_file_open(FILE* input_file, FILE* output_file) {
    if (input_file == NULL || output_file == NULL) {
        printf("FILE ERROR\n");
        return perror;
    }
}

void Kucuk_Harf_Dizi(char dizi[], FILE* input_file) {
    int i = 0, ch;
    while ((ch = fgetc(input_file)) != EOF && i < MAX_UZUNLUK - 1) {
        dizi[i] = tolower((unsigned char)ch);
        i++;
    }
    dizi[i] = '\0';
}

void sifreleyici(int kaydirma, char kucultulmus_dizi[], FILE* output_file) {
    char sifrelenmis_dizi[MAX_UZUNLUK] = { 0 };
    int index = 0;

    for (int i = 0; i < strlen(kucultulmus_dizi); i++) {
        char anlik_karakter = kucultulmus_dizi[i];
        if (isalpha(anlik_karakter)) {
            char sifrelenmis_karakter = 'a' + (anlik_karakter - 'a' + kaydirma) % 26;
            sifrelenmis_dizi[index++] = sifrelenmis_karakter;
        }
        else {
            sifrelenmis_dizi[index++] = anlik_karakter;
        }
    }

    sifrelenmis_dizi[index] = '\0';
    fprintf(output_file, "%s", sifrelenmis_dizi);
}

void sifre_Coz(char dizi[MAX_UZUNLUK], FILE* outputFile) {
    char cozulmus_var[2 * MAX_UZUNLUK] = { 0 };

    for (int kaydirma = 0; kaydirma <= 255; kaydirma++) {
        int varIndex = 0;

        for (int i = 0; i < strlen(dizi); i++) {
            char anlik_karakter = dizi[i];

            if (isalpha(anlik_karakter)) {
                char cozulmus_karakter = 'a' + ((anlik_karakter - 'a' - kaydirma + 26) % 26);
                cozulmus_var[varIndex++] = cozulmus_karakter;
            }
            else {
                cozulmus_var[varIndex++] = anlik_karakter;
            }
        }

        cozulmus_var[varIndex] = '\0';

        fprintf(outputFile, "\n*************************\n");
        fprintf(outputFile, "VARIANT  %d: %s", kaydirma, cozulmus_var);
        fprintf(outputFile, "\n");
        fprintf(outputFile, "\n*************************\n");
    }
}

int main() {
    int secim = 0;
    ana_menu:
    printf("Hello, what do you want to do?\n1 DECODE\n2 ENCODE\n->");
    scanf_s("%d", &secim);

    if (secim == 2) {
        char kucultulmus_dizi[MAX_UZUNLUK];
        int kaydirma = 0;

        FILE* input_file = fopen("sifreli_text.txt", "w");
        FILE* output_file = fopen("sifresiz_text.txt", "r");
        can_file_open(output_file, input_file);
        system("cls");
        printf("DON'T FORGET TO SAVE\n");
        system("sifresiz_text.txt");
        system("cls");

        printf("Enter how many shifts you want (enter -1 to see the encryption table): ");
        scanf_s("%d", &kaydirma);

        if (kaydirma == -1) {
            system("cls");
            printf("1- A->B  2- A->C  3- A->D  4- A->E  5- A->E  6- A->F  7- A->G  8- A->H  9- A->J\n\n\n10- A->K  11- A->L  12- A->M  13- A->N  14- A->O  15- A->P  16- A->Q  17- A->R  18- A->S  19- A->T\n\n\n20- A->U  21- A->V  22- A->W  23- A->X  24- A->Y  25- A->Z\n\n\n\n\n\n");
                        system("cls");
            goto ana_menu;
        }

        Kucuk_Harf_Dizi(kucultulmus_dizi, output_file);
        sifreleyici(kaydirma, kucultulmus_dizi, input_file);
        fclose(input_file);
        FILE* bakma = fopen("sifreli_text.txt", "r");
        system("cls");
        printf("ENCRYPTED FILE\n");
        system("sifreli_text.txt");
        fclose(bakma);
        fclose(output_file);
        system("cls");

        // Dosyaları kapat ve sıfırlamak için tekrar aç.
        FILE* input_file_silme = fopen("sifreli_text.txt", "w");
        FILE* output_file_silme = fopen("sifresiz_text.txt", "w");
        fprintf(input_file_silme, " ");
        fprintf(output_file_silme, " ");
        fclose(input_file_silme);
        fclose(output_file_silme);

        goto ana_menu;
    }

    if (secim == 1) {
        char kucultulmus_dizi[MAX_UZUNLUK];
        FILE* input_file = fopen("sifreli_text.txt", "r");
        FILE* output_file = fopen("sifresiz_text.txt", "w");
        system("cls");
        printf("DON'T FORGET TO SAVE\n");
        system("sifreli_text.txt");
        Kucuk_Harf_Dizi(kucultulmus_dizi, input_file);
        sifre_Coz(kucultulmus_dizi, output_file);
        fclose(output_file);
        system("cls");
        printf("CRACKED TEXT\n");
        system("sifresiz_text.txt");
        fclose(input_file);
        fclose(output_file);
        system("cls");

        // Dosyaları kapat ve sıfırlamak için tekrar aç.
        FILE* input_file_silme = fopen("sifreli_text.txt", "w");
        FILE* output_file_silme = fopen("sifresiz_text.txt", "w");
        fprintf(input_file_silme, " ");
        fprintf(output_file_silme, " ");
        fclose(input_file_silme);
        fclose(output_file_silme);

        goto ana_menu;
    }

    return 0;
}
