#include "include/bitSequence.hpp"
#include "include/exceptions.cpp"
#include <cstring>


BitSequence::BitSequence() : data(nullptr), bitLength(0) {}

BitSequence::BitSequence(size_t size) : bitLength(size) {
    if (size > 0) {
        data = new unsigned char[byteCount()]();
    } else {
        data = nullptr;
    }
}

BitSequence::BitSequence(bool* bits, size_t count) : bitLength(count) {
    if (count > 0) {
        data = new unsigned char[byteCount()]();
        for (size_t i = 0; i < count; ++i) {
            if (bits[i]) SetBit(i, true);
        }
    } else {
        data = nullptr;
    }
}

BitSequence::BitSequence(const BitSequence& other) : bitLength(other.bitLength) {
    if (bitLength > 0) {
        data = new unsigned char[byteCount()];
        std::memcpy(data, other.data, byteCount());
    } else {
        data = nullptr;
    }
}

BitSequence::~BitSequence() {
    delete[] data;
}

void BitSequence::SetBit(size_t index, bool value) {
    if (index >= bitLength) {
        throw IndexOutOfRangeException("SetBit", bitLength, index);
    }
    size_t byteIdx = index / 8;
    size_t bitIdx = index % 8;
    if (value) {
        data[byteIdx] |= (1 << bitIdx);
    } else {
        data[byteIdx] &= ~(1 << bitIdx);
    }
}

bool BitSequence::GetBit(size_t index) const {
    if (index >= bitLength) {
        throw IndexOutOfRangeException("GetBit", bitLength, index);
    }
    size_t byteIdx = index / 8;
    size_t bitIdx = index % 8;
    return (data[byteIdx] & (1 << bitIdx)) != 0;
}

void BitSequence::RemoveBitAt(size_t index) {
    if (index >= bitLength) {
        throw IndexOutOfRangeException("RemoveBitAt", bitLength, index);
    }
    BitSequence newSeq(bitLength - 1);
    for (size_t i = 0; i < index; ++i) {
        newSeq.SetBit(i, GetBit(i));
    }
    for (size_t i = index + 1; i < bitLength; ++i) {
        newSeq.SetBit(i - 1, GetBit(i));
    }
    *this = newSeq;
}

void BitSequence::RemoveFirstBit() {
    if (bitLength == 0) throw EmptyCollectionException("RemoveFirstBit");
    RemoveBitAt(0);
}

void BitSequence::RemoveLastBit() {
    if (bitLength == 0) throw EmptyCollectionException("RemoveLastBit");
    RemoveBitAt(bitLength - 1);
}

void BitSequence::Resize(size_t newSize) {
    if (newSize == bitLength) return;
    
    BitSequence newSeq(newSize);
    size_t copyLen = (newSize < bitLength) ? newSize : bitLength;
    for (size_t i = 0; i < copyLen; ++i) {
        newSeq.SetBit(i, GetBit(i));
    }
    *this = newSeq;
}

void BitSequence::Clear() {
    delete[] data;
    data = nullptr;
    bitLength = 0;
}

bool BitSequence::GetFirst() {
    if (bitLength == 0) throw EmptyCollectionException("GetFirst");
    return GetBit(0);
}

bool BitSequence::GetLast() {
    if (bitLength == 0) throw EmptyCollectionException("GetLast");
    return GetBit(bitLength - 1);
}

bool BitSequence::Get(size_t index) {
    return GetBit(index);
}

size_t BitSequence::GetLength() {
    return bitLength;
}

Sequence<bool>* BitSequence::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex) {
        throw InvalidArgumentException("GetSubsequence", "начальный индекс больше конечного");
    }
    if (endIndex >= bitLength) {
        throw IndexOutOfRangeException("GetSubsequence", bitLength, endIndex);
    }
    size_t newLen = endIndex - startIndex + 1;
    BitSequence* result = new BitSequence(newLen);
    for (size_t i = 0; i < newLen; ++i) {
        result->SetBit(i, GetBit(startIndex + i));
    }
    return result;
}

Sequence<bool>* BitSequence::Append(bool item) {
    BitSequence* newSeq = new BitSequence(bitLength + 1);
    for (size_t i = 0; i < bitLength; ++i) {
        newSeq->SetBit(i, GetBit(i));
    }
    newSeq->SetBit(bitLength, item);
    
    delete[] data;
    data = newSeq->data;
    bitLength = newSeq->bitLength;
    newSeq->data = nullptr;
    delete newSeq;
    return this;
}

Sequence<bool>* BitSequence::Prepend(bool item) {
    return InsertAt(item, 0);
}

Sequence<bool>* BitSequence::InsertAt(bool item, size_t index) {
    if (index > bitLength) {
        throw IndexOutOfRangeException("InsertAt", bitLength, index);
    }
    BitSequence* newSeq = new BitSequence(bitLength + 1);
    for (size_t i = 0; i < index; ++i) {
        newSeq->SetBit(i, GetBit(i));
    }
    newSeq->SetBit(index, item);
    for (size_t i = index; i < bitLength; ++i) {
        newSeq->SetBit(i + 1, GetBit(i));
    }
    
    delete[] data;
    data = newSeq->data;
    bitLength = newSeq->bitLength;
    newSeq->data = nullptr;
    delete newSeq;
    return this;
}

Sequence<bool>* BitSequence::Concat(Sequence<bool>* list) {
    if (!list) throw NullPointerArgumentException("Concat", "list");
    size_t otherLen = list->GetLength();
    BitSequence* newSeq = new BitSequence(bitLength + otherLen);
    for (size_t i = 0; i < bitLength; ++i) {
        newSeq->SetBit(i, GetBit(i));
    }
    for (size_t i = 0; i < otherLen; ++i) {
        newSeq->SetBit(bitLength + i, list->Get(i));
    }
    
    delete[] data;
    data = newSeq->data;
    bitLength = newSeq->bitLength;
    newSeq->data = nullptr;
    delete newSeq;
    return this;
}

Sequence<bool>* BitSequence::Map() {
    BitSequence* result = new BitSequence(bitLength);
    for (size_t i = 0; i < bitLength; ++i) {
        result->SetBit(i, !GetBit(i));
    }
    return result;
}

Sequence<bool>* BitSequence::Where() {
    size_t trueCount = 0;
    for (size_t i = 0; i < bitLength; ++i) {
        if (GetBit(i)) trueCount++;
    }
    BitSequence* result = new BitSequence(trueCount);
    size_t idx = 0;
    for (size_t i = 0; i < bitLength; ++i) {
        if (GetBit(i)) {
            result->SetBit(idx++, true);
        }
    }
    return result;
}

bool BitSequence::Reduce() {
    if (bitLength == 0) return false;
    bool result = true;
    for (size_t i = 0; i < bitLength; ++i) {
        result = result && GetBit(i);
        if (!result) break;
    }
    return result;
}

Option<bool> BitSequence::Find() {
    for (size_t i = 0; i < bitLength; ++i) {
        if (GetBit(i)) {
            return Option<bool>(true);
        }
    }
    return Option<bool>();
}

BitSequence* BitSequence::And(const BitSequence& other) const {
    size_t minLen = (bitLength < other.bitLength) ? bitLength : other.bitLength;
    BitSequence* result = new BitSequence(minLen);
    for (size_t i = 0; i < minLen; ++i) {
        result->SetBit(i, GetBit(i) && other.GetBit(i));
    }
    return result;
}

BitSequence* BitSequence::Or(const BitSequence& other) const {
    size_t minLen = (bitLength < other.bitLength) ? bitLength : other.bitLength;
    BitSequence* result = new BitSequence(minLen);
    for (size_t i = 0; i < minLen; ++i) {
        result->SetBit(i, GetBit(i) || other.GetBit(i));
    }
    return result;
}

BitSequence* BitSequence::Xor(const BitSequence& other) const {
    size_t minLen = (bitLength < other.bitLength) ? bitLength : other.bitLength;
    BitSequence* result = new BitSequence(minLen);
    for (size_t i = 0; i < minLen; ++i) {
        result->SetBit(i, GetBit(i) != other.GetBit(i));
    }
    return result;
}

BitSequence* BitSequence::Not() const {
    BitSequence* result = new BitSequence(bitLength);
    for (size_t i = 0; i < bitLength; ++i) {
        result->SetBit(i, !GetBit(i));
    }
    return result;
}

BitSequence& BitSequence::operator=(const BitSequence& other) {
    if (this != &other) {
        delete[] data;
        bitLength = other.bitLength;
        if (bitLength > 0) {
            data = new unsigned char[byteCount()];
            std::memcpy(data, other.data, byteCount());
        } else {
            data = nullptr;
        }
    }
    return *this;
}

