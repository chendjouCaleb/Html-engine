//
// Created by HP on 12/03/2022.
//

#ifndef HTMLENGINE_CHARITERTOR_H
#define HTMLENGINE_CHARITERTOR_H

#include <string>

class CharIterator {
private:
    std::string _text;
    size_t _index;
    char _current;

public:
    static CharIterator create(const std::string value);

    int index();

    void next();

    bool isDigit();

    bool isLetter();

    bool isWhiteSpace();

    char current();

    bool has();

    bool is(char c);

};

#endif //HTMLENGINE_CHARITERTOR_H
