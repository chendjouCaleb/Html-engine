//
// Created by HP on 23/03/2022.
//

#ifndef HTMLENGINE_CSS_H
#define HTMLENGINE_CSS_H

#include <string>
#include <vector>
#include "textIterator.h"
#include "Iterator.h"

enum CssTokenType : short {
        CSS_TOKEN_SELECTOR,
        CSS_TOKEN_BLOCK_OPEN,
        CSS_TOKEN_BLOCK_CLOSE,
        CSS_TOKEN_PROPERTY,
        CSS_TOKEN_VALUE,
        CSS_TOKEN_COMMENT
};

struct CssToken {
    std::wstring value;
    TokenIndex index;
    CssTokenType type;


    std::wstring to_wstr() {
        std::wstring v = L"[ Value = " + value + L", Index = " + std::to_wstring(index.index) + L" ]";

        return v;
    }
};

class CssTokenizer {
private:
    std::wstring _text;
    TextIterator* _it;
    std::vector<CssToken> _tokens;

    CssToken takeSelector();
    CssToken takeBlockOpen();
    CssToken takeBlockClose();
    CssToken takeProperty();
    CssToken takeValue();
    CssToken takeComment();
    void takeBlockContent();
    char _c();

public:
    static CssTokenizer create(std::wstring text);
    std::vector<CssToken> tokenize();

    void skipWhiteSpace();
    std::vector<CssToken>* tokens();

    ~CssTokenizer();
};

struct CssSelector {
    std::wstring value;
};

struct CssDeclaration {
    std::wstring name;
    std::wstring value;
};

class CssSelectors {

};

class CssDeclarations {
private:
    std::vector<CssDeclaration> _declarations;

public:

    std::vector<CssDeclaration>* declarations();

    CssDeclaration add(std::wstring name, std::wstring value);
};

class CssRule {
private:
    std::wstring _selector;
    //CssSelector _selectors;
    CssDeclarations _declarations;

public:
    CssRule();
    CssRule(std::wstring _selector, CssDeclarations _declarations);

    CssDeclarations* declarations();
    std::wstring selector();
    void selector(std::wstring value);

    std::wstring toString();
};


class CssStyleSheet {
private:


public:
    std::vector<CssRule> _rules;
    std::vector<CssRule> rules();
    std::wstring toString();
};


class CssParser {
private:
    Iterator<CssToken>* _it;

public:
    CssParser(std::wstring);

    ~CssParser();

    CssStyleSheet parse();

    CssRule takeRule();

    CssDeclaration takeDeclaration();
};

#endif //HTMLENGINE_CSS_H
