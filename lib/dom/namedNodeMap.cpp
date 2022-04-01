//
// Created by HP on 31/03/2022.
//

#include "dom.h"

NamedNodeMap::NamedNodeMap() {
    _values = new std::map<DOMString, Attr*>();
}

size_t NamedNodeMap::length() {
    return _values->size();
}