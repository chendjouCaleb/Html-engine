#include "dom.h"

DOMString CharacterData::data() {
    return _data;
}

size_t CharacterData::length() {
    return _data.length();
}

