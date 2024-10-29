// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests

TBitField::TBitField(int len):BitLen(len)
{
    std::cout << "Конструктор TBitField вызывается с len: " << len << std::endl;
    if (len < 0) {
        throw std::invalid_argument("len не должен быть отрицательным");
    }

    MemLen = (len + 31) / 32;
    pMem = new unsigned int[MemLen];

    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    pMem = new unsigned int[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr) {
        delete[] pMem;
        pMem = nullptr;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % 32);;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) {
        throw std::invalid_argument("Индекс не должен быть отрицательным");
    }

    if (n >= BitLen) {
        throw std::out_of_range("Индекс превышает длину битового поля");
    }

    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) {
        throw std::invalid_argument("Индекс не должен быть отрицательным");
    }
    if (n >= BitLen) {
        throw std::out_of_range("Индекс превышает длину битового поля");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);

}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) {
        throw std::invalid_argument("Индекс не должен быть отрицательным");
    }

    if (n >= BitLen) {
        throw std::out_of_range("Индекс превышает длину битового поля");
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf)
{
    if (this != &bf) {
        delete[] pMem; // Освобождаем старую память

        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new unsigned int[MemLen]; // Выделяем новую память
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i]; // Копируем данные
        }
    }
    return *this; // Возвращаем ссылку на текущий объект
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return false;
        }
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int maxLength = std::max(BitLen, bf.BitLen);
    TBitField result(maxLength);

    // Выполнение операции "или" по каждому элементу памяти
    for (int i = 0; i < result.MemLen; i++) {
        // Если одно из полей меньше, используйте только его длину
        unsigned int leftValue = (i < MemLen) ? pMem[i] : 0;
        unsigned int rightValue = (i < bf.MemLen) ? bf.pMem[i] : 0;
        result.pMem[i] = leftValue | rightValue;
    }
    return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return result;
}

TBitField TBitField::operator~()  // оператор инверсии
{
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i];
    }
    unsigned int mask = (1U << (BitLen % 32)) - 1;
    result.pMem[MemLen - 1] &= mask;
    return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.BitLen; i++) {
        bool bit;
        istr >> bit;
        if (bit) {
            bf.SetBit(i);
        } else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
