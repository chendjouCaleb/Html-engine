//
// Created by HP on 31/03/2022.
//

#include "dom.h"


Attr::Attr(Element* element, DOMString name, DOMString value) {
    _ownerElement = element;
    _name = name;
    _value = value;
}
Attr::Attr(Element* element, DOMString name) {
    _ownerElement = element;
    _name = name;
}

Attr::Attr(DOMString name, DOMString value) {
    _name = name;
    _value = value;
}

Attr::Attr(DOMString name) {
    _name = name;
}


DOMString Attr::name() {
    _name;
}

DOMString Attr::value() {
    return _value;
}

Element* Attr::ownerElement() {
    return _ownerElement;
}


Document* Attr::document() {
    return _document;
}


DOMString Attr::serialize(int depth) {
    if(_value.length() == 0) {
        return name();
    }

    return name() + L"=" + value();
}