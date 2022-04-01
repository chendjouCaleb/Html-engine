//
// Created by HP on 24/03/2022.
//

#ifndef HTMLENGINE_ITERATOR_H
#define HTMLENGINE_ITERATOR_H

#include <vector>

template <typename T>
class Iterator {
private:
    std::vector<T>* _items;
    size_t _index;

public:
    Iterator(std::vector<T>* items) {
        _items = items;
        _index = 0;
    }

    T& current() {
        return _items->at(_index);
    }

    size_t index() {
        return _index;
    }

    bool has() {
       return _index <= _items -> size() - 1;
    }

    void next() {
        _index += 1;
    }
};

#endif //HTMLENGINE_ITERATOR_H
