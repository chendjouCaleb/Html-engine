//
// Created by HP on 23/03/2022.
//

#ifndef HTMLENGINE_TEXTITERATOR_H
#define HTMLENGINE_TEXTITERATOR_H

#include <string>
#include "token.h"

class TextIterator {
private:
    std::wstring _text;
    size_t _index;
    size_t _line;
    size_t _lineIndex;

public:
    static TextIterator create(const std::wstring value);

    TextIterator(std::wstring value);

    std::wstring text();

    size_t index();
    size_t line();
    size_t lineIndex();

    void next();

    bool isDigit();

    bool isLetter();

    bool isWhiteSpace();

    void skipWhiteSpace();

    char current();
    wchar_t current_t();
    wchar_t t();

    bool has();

    bool is(char c);
    bool is_t(wchar_t t);
    bool isNot(char c);

    void skipIfIs(wchar_t t);

    TokenIndex tokenIndex();

    bool isIn(std::wstring c);


    bool isInAsciiRange(wchar_t t1, wchar_t t2);

    /**
     * An ASCII code point is a code point in the range U+0000 NULL to U+007F DELETE, inclusive.
     */
    bool isAsciiCodePoint();


    /**
     * A surrogate is a code point that is in the range U+D800 to U+DFFF, inclusive.
     */
    bool isSurrogateCodePoint();


    /**
     * A scalar value is a code point that is not a surrogate.
     */
    bool  isScalarValue();


    /**
     * A noncharacter is a code point that is in the range U+FDD0 to U+FDEF, inclusive, or
     * U+FFFE, U+FFFF, U+1FFFE, U+1FFFF, U+2FFFE, U+2FFFF, U+3FFFE, U+3FFFF, U+4FFFE,
     * U+4FFFF, U+5FFFE, U+5FFFF, U+6FFFE, U+6FFFF, U+7FFFE, U+7FFFF, U+8FFFE, U+8FFFF,
     * U+9FFFE, U+9FFFF, U+AFFFE, U+AFFFF, U+BFFFE, U+BFFFF,
     * U+CFFFE, U+CFFFF, U+DFFFE, U+DFFFF, U+EFFFE, U+EFFFF, U+FFFFE, U+FFFFF, U+10FFFE, or U+10FFFF.
     */
    bool isNonCharacter();


    /**
     * An ASCII tab or newline is U+0009 TAB, U+000A LF, or U+000D CR.
     */
    bool isAsciiTabOrNewline();


    /**
     * ASCII whitespace is U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or U+0020 SPACE.
     */
    bool isAsciiWhiteSpace();

    /**
     * A C0 control is a code point in the range U+0000 NULL to U+001F INFORMATION SEPARATOR ONE, inclusive.
     */
    bool isC0_Control();

    /**
     * A C0 control or space is a C0 control or U+0020 SPACE.
     */
    bool isC0_ControlOrSpace();

    /**
     * A control is a C0 control or a code point in the range U+007F DELETE to U+009F APPLICATION PROGRAM COMMAND, inclusive.
     */
    bool isControl();

    /**
     * An ASCII digit is a code point in the range U+0030 (0) to U+0039 (9), inclusive.
     */
    bool isAsciiDigits();

    /**
     * An ASCII upper hex alpha is a code point in the range U+0041 (A) to U+0046 (F), inclusive.
     */
    bool isAsciiUpperHexAlpha();

    /**
     * An ASCII lower hex alpha is a code point in the range U+0061 (a) to U+0066 (f), inclusive.
     */
    bool isAsciiLowerHexAlpha();

    /**
     * An ASCII hex alpha is a lower hex alpha or upper hex alpha.
     */
    bool isAsciiHexAlpha();

    /**
     * An ASCII upper hex digit is an ASCII digit or a code point in the range U+0041 (A) to U+0046 (F), inclusive.
     */
    bool isAsciiUpperHexDigit();

    /**
     * An ASCII lower hex digit is an ASCII digit or a code point in the range U+0061 (a) to U+0066 (f), inclusive.
     */
    bool isAsciiLowerHexDigit();

    /**
     * An ASCII hex digit is an ASCII upper hex digit or ASCII lower hex digit.
     */
    bool isAsciiHexDigit();

    /**
     * An ASCII upper alpha is a code point in the range U+0041 (A) to U+005A (Z), inclusive.
     */
    bool isAsciiUpperAlpha();

    /**
     * An ASCII lower alpha is a code point in the range U+0061 (a) to U+007A (z), inclusive.
     */
    bool isAsciiLowerAlpha();

    /**
     * An ASCII alpha is an ASCII upper alpha or ASCII lower alpha.
     */
    bool isAsciiAlpha();

    /**
     * An ASCII alphanumeric is an ASCII digit or ASCII alpha.
     */
    bool isAsciiAlphaNumeric();


};

#endif //HTMLENGINE_TEXTITERATOR_H
