// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &other) : BitField(other.MaxPower)
{
    MaxPower = other.MaxPower;
    for (int i = 0; i < MaxPower; i++) {
        if (other.BitField.GetBit(i) == 0) {
            BitField.ClrBit(i);
        } else {
            BitField.SetBit(i);
        }
    }
}


TSet::operator TBitField()
{
    return FAKE_BITFIELD;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) = default; // присваивание

int TSet::operator==(const TSet &other) const // сравнение
{
    if (MaxPower != other.MaxPower) {
        return false;
    }
    if (BitField == other.BitField) {
        return true;
    }
    return false;
}

int TSet::operator!=(const TSet &other) const // сравнение
{
    return !(*this == other);
}

TSet TSet::operator+(const TSet &other) // объединение
{
    if (MaxPower < other.MaxPower) {
        MaxPower = other.MaxPower;
    }
    TSet result(MaxPower);
    result.BitField = BitField | other.BitField;
    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem > MaxPower) {
        throw "Can't insert out of range!";
    }
    this->BitField.SetBit(Elem);
    return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem > MaxPower) {
        throw "Can't insert out of range!";
    }
    this->BitField.ClrBit(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &other) {
    TSet result(MaxPower > other.MaxPower ? MaxPower : other.MaxPower);
    result.BitField = BitField & other.BitField;
    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(MaxPower);
    result.BitField = ~this->BitField;
    return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &os, const TSet &set) // вывод
{
    os << set.BitField;
    return os;
}
