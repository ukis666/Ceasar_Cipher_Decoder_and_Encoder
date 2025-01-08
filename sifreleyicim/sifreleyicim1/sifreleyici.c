#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_UZUNLUK 2000

int can_file_open(FILE* input_file, FILE* output_file) {
    if (input_file == NULL || output_file == NULL) {
        perror("FILE ERROR");

        return 1; // hata kodu döndür
    }
    return 0; // başarı
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
    char sifrelenmis_dizi[MAX_UZUNLUK] = {0};
    int index = 0;

    for (int i = 0; i < (int)strlen(kucultulmus_dizi); i++) {
        char anlik_karakter = kucultulmus_dizi[i];
        if (isalpha(anlik_karakter)) {
            char sifrelenmis_karakter = 'a' + (anlik_karakter - 'a' + kaydirma) % 26;
            sifrelenmis_dizi[index++] = sifrelenmis_karakter;
        } else {
            sifrelenmis_dizi[index++] = anlik_karakter;
        }
    }

    sifrelenmis_dizi[index] = '\0';
    fprintf(output_file, "%s", sifrelenmis_dizi);
}

void sifre_Coz(char dizi[MAX_UZUNLUK], FILE* outputFile) {
    char cozulmus_var[2 * MAX_UZUNLUK] = {0};

    for (int kaydirma = 0; kaydirma <= 255; kaydirma++) {
        int varIndex = 0;

        for (int i = 0; i < (int)strlen(dizi); i++) {
            char anlik_karakter = dizi[i];

            if (isalpha(anlik_karakter)) {
                char cozulmus_karakter = 'a' + ((anlik_karakter - 'a' - kaydirma + 26) % 26);
                cozulmus_var[varIndex++] = cozulmus_karakter;
            } else {
                cozulmus_var[varIndex++] = anlik_karakter;
            }
        }

        cozulmus_var[varIndex] = '\0';

        fprintf(outputFile, "\n*************************\n");
        fprintf(outputFile, "VARIANT  %d: %s", kaydirma, cozulmus_var);
        fprintf(outputFile, "\n*************************\n");
    }
}

int main() {
    int secim = 0;

ana_menu:
    printf("Hello, what do you want to do?\n1) DECODE\n2) ENCODE\n-> ");
    scanf("%d", &secim);

    if (secim == 2) {
        char kucultulmus_dizi[MAX_UZUNLUK];
        int kaydirma = 0;

        FILE* input_file = fopen("sifreli_text.txt", "w");
        FILE* output_file = fopen("sifresiz_text.txt", "r");
        if (can_file_open(output_file, input_file)) {
            // Dosya açılamadıysa programı sonlandırıyoruz
            return 1;
        }

        system("clear"); // Linux'ta ekran temizleme
        printf("DON'T FORGET TO SAVE\n");

        // Linux'ta metin dosyası açmak için (Varsayılan program) xdg-open kullanabilirsiniz:
        system("xdg-open sifresiz_text.txt");

        system("clear");
        printf("Enter how many shifts you want (enter -1 to see the encryption table): ");
        scanf("%d", &kaydirma);

        if (kaydirma == -1) {
            system("clear");
            // Örnek tablo
            printf("1- A->B  2- A->C  3- A->D  4- A->E  5- A->F  6- A->G\n");
            printf("...\n25- A->Z\n\n\n");
            goto ana_menu;
        }

        Kucuk_Harf_Dizi(kucultulmus_dizi, output_file);
        sifreleyici(kaydirma, kucultulmus_dizi, input_file);
        fclose(input_file);

        FILE* bakma = fopen("sifreli_text.txt", "r");
        system("clear");
        printf("ENCRYPTED FILE\n");
        system("xdg-open sifreli_text.txt");
        if (bakma) fclose(bakma);
        fclose(output_file);
        system("clear");

        // Dosyaları kapatıp sıfırlamak için tekrar aç
        FILE* input_file_silme = fopen("sifreli_text.txt", "w");
        FILE* output_file_silme = fopen("sifresiz_text.txt", "w");
        if (input_file_silme) {
            fprintf(input_file_silme, " ");
            fclose(input_file_silme);
        }
        if (output_file_silme) {
            fprintf(output_file_silme, " ");
            fclose(output_file_silme);
        }

        goto ana_menu;
    }
    else if (secim == 1) {
        char kucultulmus_dizi[MAX_UZUNLUK];
        FILE* input_file = fopen("sifreli_text.txt", "r");
        FILE* output_file = fopen("sifresiz_text.txt", "w");
        if (can_file_open(input_file, output_file)) {
            return 1;
        }

        system("clear");
        printf("DON'T FORGET TO SAVE\n");
        system("xdg-open sifreli_text.txt");

        Kucuk_Harf_Dizi(kucultulmus_dizi, input_file);
        sifre_Coz(kucultulmus_dizi, output_file);
        fclose(output_file);

        system("clear");
        printf("CRACKED TEXT\n");
        system("xdg-open sifresiz_text.txt");

        fclose(input_file);

        system("clear");

        // Dosyaları kapatıp sıfırlamak için tekrar aç
        FILE* input_file_silme = fopen("sifreli_text.txt", "w");
        FILE* output_file_silme = fopen("sifresiz_text.txt", "w");
        if (input_file_silme) {
            fprintf(input_file_silme, " ");
            fclose(input_file_silme);
        }
        if (output_file_silme) {
            fprintf(output_file_silme, " ");
            fclose(output_file_silme);
        }

        goto ana_menu;
    }

    return 0;
}
