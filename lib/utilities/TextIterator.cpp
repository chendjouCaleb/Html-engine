//
// Created by HP on 23/03/2022.
//

#include "textIterator.h"

TextIterator TextIterator::create(const std::wstring value) {
    TextIterator it = TextIterator(value);
    return it;
}

std::wstring TextIterator::text() {
    return _text;
}

TextIterator::TextIterator(std::wstring value) {
    _text = value;
    _index = 0;
    _lineIndex = 0;
    _index = 0;
}

void TextIterator::next() {
    if (!has()) {
        return;
    }
    if (current() == '\n') {
        _line += 1;
        _lineIndex = 0;
    } else {
        _lineIndex += 1;
    }
    _index++;
}

bool TextIterator::has() {
    return _index <= _text.length() - 1;
}

bool TextIterator::is(char c) {
    return has() && current() == c;
}

bool TextIterator::is_t(wchar_t t) {
    return current_t() == t;
}

bool TextIterator::isNot(char c) {
    return has() && current() != c;
}

void TextIterator::skipIfIs(wchar_t t) {
    if(is_t(t)) {
        next();
    }
}

/**
 * Checks if the current char is in the provided string.
 * @param text The provided string.
 * @return True if the current is in the provided string.
 */
bool TextIterator::isIn(std::wstring text) {
    return has() && text.find(current()) < text.length();
}


/**
 * Checks if the current char is a digits.
 * @return
 */
bool TextIterator::isDigit() {
    return has() && current() >= '0' && current() <= '9';
}


/**
 * Checks if the current char is a letter.
 * @return
 */
bool TextIterator::isLetter() {
    char _char = current();
    return has() && ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z'));
}

/**
 * Gets the current char.
 * @return
 */
char TextIterator::current() {
    if (has()) {
        return _text[_index];
    }
    return '\0';
}

wchar_t TextIterator::current_t() {
    if (has()) {
        return _text[_index];
    }
    return '\0';
}

wchar_t TextIterator::t() {
    return current_t();
}


/**
 * Get is the current char is a whitespace.
 * Whitespace is a
 * @return
 */
bool TextIterator::isWhiteSpace() {
    std::wstring text = L"\u0009\u000A\u000C\u000D\u0020";
    return has() && text.find(current()) < text.length();
}

void TextIterator::skipWhiteSpace() {
    while (isWhiteSpace()) {
        next();
    }
}

size_t TextIterator::index() {
    return _index;
}

size_t TextIterator::line() {
    return _line;
}


size_t TextIterator::lineIndex() {
    return _lineIndex;
}

TokenIndex TextIterator::tokenIndex() {
    return {.index = _index, .line = _line, .lineIndex = _lineIndex};
}

bool TextIterator::isInAsciiRange(wchar_t t1, wchar_t t2) {
    return t() >= t1 && t() <= t2;
}


bool TextIterator::isAsciiCodePoint() {
    return isInAsciiRange('\u0000', '\u007F');
}


bool TextIterator::isSurrogateCodePoint() {
    return false;
}


bool TextIterator::isScalarValue() {
    return false;
}


bool TextIterator::isAsciiTabOrNewline() {
    return t() == '\u0009' || t() == '\u000A' || t() == '\u000D';
}

bool TextIterator::isAsciiWhiteSpace() {
    return is_t('\u0009') || is_t('\u000A') || is_t('\u000C') || is_t('\u000D') || is_t('\u0020');
}


bool TextIterator::isC0_Control() {
    return has() && (t() > '\u0000' && t() <= '\u001f');
}


bool TextIterator::isC0_ControlOrSpace() {
    return isC0_Control() || t() > '\u0020';
}

bool TextIterator::isControl() {
    return isC0_Control() || (t() >= L'\u007f' && t() <= L'\u009f');
}

bool TextIterator::isAsciiDigits() {
    return has() && (t() >= '\u0030' && t() <= '\u0039');
}

bool TextIterator::isAsciiUpperHexAlpha() {
    return t() >= '\u0041' && t() <= '\u0046';
}


bool TextIterator::isAsciiLowerHexAlpha() {
    return t() >= '\u0061' && t() <= '\u0066';
}


bool TextIterator::isAsciiHexAlpha() {
    return isAsciiUpperHexAlpha() || isAsciiLowerHexAlpha();
}

bool TextIterator::isAsciiUpperHexDigit() {
    return isAsciiDigits() || isAsciiUpperHexAlpha();
}

bool TextIterator::isAsciiLowerHexDigit() {
    return isAsciiDigits() || isAsciiLowerHexAlpha();
}

bool TextIterator::isAsciiHexDigit() {
    return isAsciiDigits() || isAsciiHexAlpha();
}

bool TextIterator::isAsciiUpperAlpha() {
    return t() >= '\u0041' && t() <= '\u005A';
}

bool TextIterator::isAsciiLowerAlpha() {
    return t() >= '\u0061' && t() <= '\u007A';
}

bool TextIterator::isAsciiAlpha() {
    return isAsciiLowerAlpha() || isAsciiUpperAlpha();
}

bool TextIterator::isAsciiAlphaNumeric() {
    return isAsciiDigits() || isAsciiAlpha();
}