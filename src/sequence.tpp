#include "../include/sequence.hpp"

template<typename T> template<typename T2>
Sequence<T2>* Sequence<T>::Map(std::function<T2(T)> func) {
    return nullptr;
}

template<typename T>
Sequence<T>* Sequence<T>::Where(std::function<bool(T)> predicate) {
    return nullptr;
}

template<typename T> template<typename T2>
T2 Sequence<T>::Reduce(std::function<T2(T2, T)> func, T2 initial) {
    T2 res = initial;
    for (int i = 0; i < GetLength(); ++i) res = func(res, Get(i));
    return res;
}

template<typename T>
Option<T> Sequence<T>::Find(std::function<bool(T)> predicate) {
    for (int i = 0; i < GetLength(); ++i) {
        if (predicate(Get(i))) return Option<T>(Get(i));
    }
    return Option<T>();
}

