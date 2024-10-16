#include <iostream>
using namespace std;

// Структура для массива
struct Array {
    int* data;       // Указатель на массив
    int size;        // Текущий размер массива
    int capacity;    // Максимальная вместимость массива
};


void Ainit(Array& arr, int cap);
void Adestroy(Array& arr);
void Aappend(Array& arr, int value);
void Ainsert(Array& arr, int index, int value);
int Aget(const Array& arr, int index);
void Aremove(Array& arr, int index);
void Areplace(Array& arr, int index, int value);
int Alength(const Array& arr);
void printArray(const Array& arr);
