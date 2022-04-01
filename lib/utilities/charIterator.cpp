//
// Created by HP on 12/03/2022.
//

#include "charItertor.h"

CharIterator CharIterator::create(const std::string value) {
    CharIterator it = CharIterator();
    it._text = value;
    it._index = 0;

    return it;
}

void CharIterator::next() {
    _index++;
    _current = current();
}

bool CharIterator::has() {
    return _index <= _text.length() - 1;
}

bool CharIterator::is(char c) {
    return has() && current() == c;
}

bool CharIterator::isDigit() {
    return has() && current() >= '0' && current() <= '9';
}

bool CharIterator::isLetter() {
    char _char = current();
    return has() && ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z'));
}

char CharIterator::current() {
    if(has()) {
        return _text[_index];
    }
    return '\0';
}


bool CharIterator::isWhiteSpace() {
    char c = current();

    return has() && (c == '\t' || c == ' ' || c == '\r' || c == '\n');
}

int CharIterator::index() {
    return _index;
}