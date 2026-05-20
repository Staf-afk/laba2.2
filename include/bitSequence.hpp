#pragma once
#include "sequence.hpp"
#include "dynamicArray.hpp"
#include "arraySequence.hpp"

class Bit {
    bool value;
public:
    Bit(bool val = false) : value(val) {}
    bool GetValue() const { return value; }
    void SetValue(bool val) { value = val; }
    Bit operator&(const Bit& o) const { return Bit(value && o.value); }
    Bit operator|(const Bit& o) const { return Bit(value || o.value); }
    Bit operator^(const Bit& o) const { return Bit(value != o.value); }
    Bit operator~() const { return Bit(!value); }
    Bit& operator=(bool val) { value = val; return *this; }
    operator bool() const { return value; }
};

class BitSequence : public Sequence<Bit> {
    unsigned char* data;
    int bitLength;
    
public:
    BitSequence();
    explicit BitSequence(int size);
    BitSequence(bool* bits, int count);
    BitSequence(const BitSequence& other);
    ~BitSequence();
    
    void SetBit(int index, bool value);
    bool GetBit(int index) const;
    
    Bit GetFirst() const override;
    Bit GetLast() const override;
    Bit Get(int index) const override;
    BitSequence* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    
    BitSequence* Append(Bit item) override;
    BitSequence* Prepend(Bit item) override;
    BitSequence* InsertAt(Bit item, int index) override;
    BitSequence* Concat(Sequence<Bit>* list) override;
    
    template<typename T2> Sequence<T2>* Map(std::function<T2(Bit)> func);
    Sequence<Bit>* Where(std::function<bool(Bit)> predicate);
    template<typename T2> T2 Reduce(std::function<T2(T2, Bit)> func, T2 initial);
    Option<Bit> Find(std::function<bool(Bit)> predicate);
    
    BitSequence* And(const BitSequence& other) const;
    BitSequence* Or(const BitSequence& other) const;
    BitSequence* Xor(const BitSequence& other) const;
    BitSequence* Not() const;
    
    BitSequence& operator=(const BitSequence& other);
};
template<typename T2> 
Sequence<T2>* BitSequence::Map(std::function<T2(Bit)> func) {
    T2* result = new T2[bitLength];
    for (int i = 0; i < bitLength; ++i) {
        result[i] = func(Get(i));
    }
    auto* seq = new ArraySequence<T2>(result, bitLength);
    delete[] result;
    return seq;
}

template<typename T2> 
T2 BitSequence::Reduce(std::function<T2(T2, Bit)> func, T2 initial) {
    T2 res = initial;
    for (int i = 0; i < bitLength; ++i) res = func(res, Get(i));
    return res;
}