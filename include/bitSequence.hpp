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
    size_t bitLength;
    
public:
    BitSequence();
    BitSequence(size_t size);
    BitSequence(bool* bits, size_t count);
    BitSequence(const BitSequence& other);
    ~BitSequence();
    
    void SetBit(size_t index, bool value);
    bool GetBit(size_t index) const;
    
    Bit GetFirst() override;
    Bit GetLast() override;
    Bit Get(size_t index) override;
    BitSequence* GetSubsequence(size_t startIndex, size_t endIndex) const override;
    size_t GetLength() override;
    
    BitSequence* Append(Bit item) override;
    BitSequence* Prepend(Bit item) override;
    BitSequence* InsertAt(Bit item, size_t index) override;
    BitSequence* Concat(Sequence<Bit>* list) override;
    
    BitSequence* Map() override;
    BitSequence* Where() override;
    Bit Reduce() override;
    Option<Bit> Find() override;
    
    BitSequence* And(const BitSequence& other) const;
    BitSequence* Or(const BitSequence& other) const;
    BitSequence* Xor(const BitSequence& other) const;
    BitSequence* Not() const;
    
    BitSequence& operator=(const BitSequence& other);
};
