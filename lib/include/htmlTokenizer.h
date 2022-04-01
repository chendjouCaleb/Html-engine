//
// Created by HP on 12/03/2022.
//

#ifndef HTMLENGINE_HTMLTOKENIZER_H
#define HTMLENGINE_HTMLTOKENIZER_H

#include <string>
#include <vector>
#include "textIterator.h"

enum HtmlTokenType {HTML_TOKEN_ELEMENT_OPEN,
        HTML_TOKEN_TAG_CLOSE,
        HTML_TOKEN_ELEMENT_CLOSE, HTML_TOKEN_TEXT,
        HTML_TOKEN_ATTR_NAME, HTML_TOKEN_ATTR_VALUE};

struct HtmlToken {
    std::wstring value;
    HtmlTokenType type;
};

class HtmlTokenizer {
private:
    std::wstring _input;
    TextIterator* _it;
    std::vector<HtmlToken*> _tokens;

    HtmlToken* takeTextToken();
    void takeElementOpen();
    HtmlToken* takeTagClose();
    HtmlToken* takeElementClose();
    void takeElement();

    void takeAttrs();
    void takeAttr();
    HtmlToken* takeAttrName();
    void skipAttrEqual();
    HtmlToken* takeAttrValue();
    HtmlToken* takeAttrUnquotedValue();
    HtmlToken* takeAttrSingleQuotedValue();
    HtmlToken* takeAttrQuotedValue();
    char _c();

public:
    ~HtmlTokenizer();
    static HtmlTokenizer create(std::wstring text);
    std::vector<HtmlToken*> tokenize();

    void skipWhiteSpace();
    std::vector<HtmlToken*> tokens();

};

#endif //HTMLENGINE_HTMLTOKENIZER_H
