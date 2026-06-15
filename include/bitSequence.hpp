#pragma once
#include "sequence.hpp"
#include <cstring>

class BitSequence : public Sequence<bool> {
private:
    unsigned char* data;
    size_t bitLength;
    size_t byteCount() const { return (bitLength + 7) / 8; }
    
public:
    BitSequence();
    explicit BitSequence(size_t size);
    BitSequence(bool* bits, size_t count);
    BitSequence(const BitSequence& other);
    ~BitSequence();
    
    void SetBit(size_t index, bool value);
    bool GetBit(size_t index) const;
    
    bool GetFirst() override;
    bool GetLast() override;
    bool Get(size_t index) override;
    Sequence<bool>* GetSubsequence(size_t startIndex, size_t endIndex) const override;  // const!!!
    size_t GetLength() override;
    
    Sequence<bool>* Append(bool item) override;
    Sequence<bool>* Prepend(bool item) override;
    Sequence<bool>* InsertAt(bool item, size_t index) override;
    Sequence<bool>* Concat(Sequence<bool>* list) override;
    
    Sequence<bool>* Map() override;
    Sequence<bool>* Where() override;
    bool Reduce() override;
    Option<bool> Find() override;
    
    BitSequence* And(const BitSequence& other) const;
    BitSequence* Or(const BitSequence& other) const;
    BitSequence* Xor(const BitSequence& other) const;
    BitSequence* Not() const;
    
    bool operator[](size_t index) const { return GetBit(index); }
    BitSequence& operator=(const BitSequence& other);
    
    void RemoveBitAt(size_t index);
    void RemoveFirstBit();
    void RemoveLastBit();
    void Resize(size_t newSize);
    void Clear();
};