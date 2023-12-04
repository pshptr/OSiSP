#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
unsigned int notes[] = { 329, 329, 329, 415, 523, 659, 587, 523, 330 };
unsigned int note_delays[] = { 200, 100, 200, 400, 200, 200, 400, 200, 400 };

void playSound();
void printStates();
void CharToBin(unsigned char state, char* str);
void TurnOnSpeaker();
void TurnOffSpeaker();
void SetCount(int iDivider);
void menu();

int main()
{
    menu();
    return 0;
}

void menu()
{
    int choice = 0;
    while (1)
    {
        printf("0 - exit\n");
        printf("1 - play sound\n");
        printf("2 - print channels state words and counters\n");
        scanf("%d", &choice);
        if (choice >= 0 && choice <= 2)
        {
            switch (choice)
            {
                case 0:
                    return;
                case 1:
                    playSound();
                    break;
                case 2:
                    printStates();
                    printf("\n\nPress any key to continue: ");
                    scanf("%d", &choice);
                    break;
            }
        }
    }
}

//функция считывающая слова состояния каналов
void printStates()
{
    char* bin_state;
    unsigned char state;
    unsigned char counter;
    bin_state = (char*)calloc(9, sizeof(char));
    if (!bin_state)
    {
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    outp(0x43, 0xE2);  //заносим управляющее слово, которое соответствует RBC (Чтение состояния канала) в УР и номеру канала 2
    state = inp(0x40); //чтение слова состояния канала 0
    CharToBin(state, bin_state);
    outp(0x43, 0xD2);		// 0xD2 == 1101 0010 (11 - режим чтения, 01 - регистр счетчика, 001 - 0 порт, 0 - bcd или binary)
    counter = inp(0x40);
    printf("0x40\tword: %s\tcounter: 0x%02X\n", bin_state, counter);
    *bin_state = '\0';
    outp(0x43, 0xE4);  //заносим управляющее слово, которое соответствует RBC (Чтение состояния канала) в УР и номеру канала 1
    state = inp(0x41); //чтение слова состояния канала 1
    CharToBin(state, bin_state);
    outp(0x43, 0xD2);
    counter = inp(0x41);
    printf("0x41\tword: %s\tcounter: 0x%02X\n", bin_state, counter);
    *bin_state = '\0';
    outp(0x43, 0xE8);  //заносим управляющее слово, которое соответствует RBC (Чтение состояния канала) в УР и номеру канала 2
    state = inp(0x42); //чтение слова состояния канала 2
    CharToBin(state, bin_state);
    outp(0x43, 0xD2);
    counter = inp(0x42);
    printf("0x43\tword: %s\tcounter: 0x%02X\n", bin_state, counter);
    free(bin_state);
    return;
}

//функция перевода в двоичный код
void CharToBin(unsigned char state, char* str)
{
    char temp;
    for (int i = 7; i >= 0; i--)
    {
        temp = state % 2;
        state /= 2;
        str[i] = temp + '0';
    }
    str[8] = '\0';
}

//функция установки значения счетчика
void SetCount(int iDivider)
{
    long base = 1193180;		//максимальная частота
    long kd;
    outp(0x43, 0xB6);			//10110110 - канал 2, операция 4, режим 3, формат 0
    kd = base / iDivider;
    outp(0x42, kd % 256);		// младший байт делителя частоты
    kd /= 256;
    outp(0x42, kd);				//старший байт делителя частоты
}

//функция работы с громкоговорителем
void TurnOffSpeaker()
{
    outp(0x61, inp(0x61) & 0xFC);	//устанавливаем 2 младших бита в 00, чтобы выключить динамик
}

void TurnOnSpeaker()
{
    outp(0x61, inp(0x61) | 0x03);	//устанавливаем 2 младших бита в 11, чтобы разрешить работу динамика и включить его
}

//функция воспроизведения песни
void playSound()
{
    for (int i = 0; i < 9; i++)
    {
        SetCount(notes[i]);
        TurnOnSpeaker();		//включаем динамик
        delay(note_delays[i]);  //устанавливаем длительность мс
        TurnOffSpeaker();		//выключаем динамик
    }
}