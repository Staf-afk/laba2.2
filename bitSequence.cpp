// bitSequence.cpp (в корне проекта)
#include "include/bitSequence.hpp"
#include "include/exceptions.hpp"
#include "include/dynamicArray.hpp"
#include "include/arraySequence.hpp"
#include <cstring>
#include <functional>

void BitSequence::SetBit(int i, bool v) {
    if (i < 0 || i >= bitLength) throw IndexOutOfRangeException();
    int b = i / 8, bit = i % 8;
    if (v) data[b] |= (1 << bit); else data[b] &= ~(1 << bit);
}

bool BitSequence::GetBit(int i) const {
    if (i < 0 || i >= bitLength) throw IndexOutOfRangeException();
    return (data[i / 8] & (1 << (i % 8))) != 0;
}

BitSequence::BitSequence() : data(nullptr), bitLength(0) {}

BitSequence::BitSequence(int size) : bitLength(size) {
    data = size > 0 ? new unsigned char[(size + 7) / 8]() : nullptr;
}

BitSequence::BitSequence(bool* bits, int count) : bitLength(count) {
    data = count > 0 ? new unsigned char[(count + 7) / 8]() : nullptr;
    for (int i = 0; i < count; ++i) SetBit(i, bits[i]);
}

BitSequence::BitSequence(const BitSequence& o) : bitLength(o.bitLength) {
    if (bitLength > 0) {
        int sz = (bitLength + 7) / 8;
        data = new unsigned char[sz];
        std::memcpy(data, o.data, sz);
    } else data = nullptr;
}

BitSequence::~BitSequence() { delete[] data; }

Bit BitSequence::GetFirst() const { 
    if (bitLength == 0) throw EmptyCollectionException();
    return Bit(GetBit(0)); 
}

Bit BitSequence::GetLast() const { 
    if (bitLength == 0) throw EmptyCollectionException();
    return Bit(GetBit(bitLength - 1)); 
}

Bit BitSequence::Get(int i) const { return Bit(GetBit(i)); }

int BitSequence::GetLength() const { return bitLength; }

BitSequence* BitSequence::GetSubsequence(int s, int e) const {
    if (s < 0 || e >= bitLength || s > e) throw IndexOutOfRangeException();
    BitSequence* r = new BitSequence(e - s + 1);
    for (int i = 0; i < r->bitLength; ++i) r->SetBit(i, GetBit(s + i));
    return r;
}

BitSequence* BitSequence::Append(Bit item) {
    BitSequence* r = new BitSequence(bitLength + 1);
    for (int i = 0; i < bitLength; ++i) r->SetBit(i, GetBit(i));
    r->SetBit(bitLength, item.GetValue());
    delete[] data; 
    data = r->data; 
    bitLength = r->bitLength; 
    r->data = nullptr; 
    delete r;
    return this;
}

BitSequence* BitSequence::Prepend(Bit item) { 
    return InsertAt(item, 0); 
}

BitSequence* BitSequence::InsertAt(Bit item, int idx) {
    if (idx < 0 || idx > bitLength) throw IndexOutOfRangeException();
    BitSequence* r = new BitSequence(bitLength + 1);
    for (int i = 0; i < idx; ++i) r->SetBit(i, GetBit(i));
    r->SetBit(idx, item.GetValue());
    for (int i = idx; i < bitLength; ++i) r->SetBit(i + 1, GetBit(i));
    delete[] data; 
    data = r->data; 
    bitLength = r->bitLength; 
    r->data = nullptr; 
    delete r;
    return this;
}

BitSequence* BitSequence::Concat(Sequence<Bit>* list) {
    if (!list) return new BitSequence(*this);
    BitSequence* r = new BitSequence(bitLength + list->GetLength());
    for (int i = 0; i < bitLength; ++i) r->SetBit(i, GetBit(i));
    for (int i = 0; i < list->GetLength(); ++i) r->SetBit(bitLength + i, list->Get(i).GetValue());
    delete[] data; 
    data = r->data; 
    bitLength = r->bitLength; 
    r->data = nullptr; 
    delete r;
    return this;
}

Sequence<Bit>* BitSequence::Where(std::function<bool(Bit)> pred) {
    DynamicArray<Bit>* filtered = new DynamicArray<Bit>();
    for (int i = 0; i < bitLength; ++i) {
        if (pred(Get(i))) {
            filtered->Resize(filtered->GetSize() + 1);
            filtered->Set(filtered->GetSize() - 1, Get(i));
        }
    }
    return new ArraySequence<Bit>(filtered);
}

Option<Bit> BitSequence::Find(std::function<bool(Bit)> pred) {
    for (int i = 0; i < bitLength; ++i) {
        if (pred(Get(i))) return Option<Bit>(Get(i));
    }
    return Option<Bit>();
}

BitSequence* BitSequence::And(const BitSequence& o) const {
    int m = (bitLength < o.bitLength) ? bitLength : o.bitLength;
    BitSequence* r = new BitSequence(m);
    for (int i = 0; i < m; ++i) r->SetBit(i, GetBit(i) && o.GetBit(i));
    return r;
}

BitSequence* BitSequence::Or(const BitSequence& o) const {
    int m = (bitLength < o.bitLength) ? bitLength : o.bitLength;
    BitSequence* r = new BitSequence(m);
    for (int i = 0; i < m; ++i) r->SetBit(i, GetBit(i) || o.GetBit(i));
    return r;
}

BitSequence* BitSequence::Xor(const BitSequence& o) const {
    int m = (bitLength < o.bitLength) ? bitLength : o.bitLength;
    BitSequence* r = new BitSequence(m);
    for (int i = 0; i < m; ++i) r->SetBit(i, GetBit(i) != o.GetBit(i));
    return r;
}

BitSequence* BitSequence::Not() const {
    BitSequence* r = new BitSequence(bitLength);
    for (int i = 0; i < bitLength; ++i) r->SetBit(i, !GetBit(i));
    return r;
}

IEnumerator<Bit>* BitSequence::GetEnumerator() { 
    return nullptr; 
}

BitSequence& BitSequence::operator=(const BitSequence& o) {
    if (this != &o) {
        delete[] data; 
        bitLength = o.bitLength;
        if (bitLength > 0) {
            int sz = (bitLength + 7) / 8;
            data = new unsigned char[sz];
            std::memcpy(data, o.data, sz);
        } else data = nullptr;
    }
    return *this;
}