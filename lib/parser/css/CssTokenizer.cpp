//
// Created by HP on 23/03/2022.
//

#include <css.h>


CssToken CssTokenizer::takeSelector() {
    TokenIndex index = _it -> tokenIndex();

    std::wstring text;
    while (_it -> has() && !_it -> is('{')) {
        text += _it -> current();
        _it -> next();
    }
    CssToken token = {.value = text, .index = index, .type = CSS_TOKEN_SELECTOR};
    _tokens.push_back(token);
    return token;
}


CssToken CssTokenizer::takeBlockOpen() {
    if (_it -> is('{')) {
        CssToken token = {.value = L"{", .index = _it -> tokenIndex(), .type = CSS_TOKEN_BLOCK_OPEN};
        _tokens.push_back(token);
        _it -> next();
        return token;
    }
}

CssToken CssTokenizer::takeBlockClose() {
    if (_it -> is('}')) {
        CssToken token = {.value = L"}", .index = _it -> tokenIndex(), .type = CSS_TOKEN_BLOCK_CLOSE};
        _tokens.push_back(token);
        _it -> next();
        return token;
    }
}

CssToken CssTokenizer::takeProperty() {
    auto index = _it -> tokenIndex();
    std::wstring value;
    while (_it -> has() && !_it -> is(':')) {
        value += _it -> current();
        _it -> next();
    }
    CssToken token = {.value = value, .index = index, .type = CSS_TOKEN_PROPERTY};
    _tokens.push_back(token);
    return token;
}

CssToken CssTokenizer::takeValue() {
    auto index = _it -> tokenIndex();
    std::wstring value;
    while (_it -> has() && !_it -> is(';')) {
        value += _it -> current();
        _it -> next();
    }
    CssToken token = {.value = value, .index = index, .type = CSS_TOKEN_BLOCK_CLOSE};
    _tokens.push_back(token);
    return token;
}

CssToken CssTokenizer::takeComment() {}

void CssTokenizer::takeBlockContent() {
    while (_it -> has() && !_it -> is('}')) {
        takeProperty();
        skipWhiteSpace();

        if(_it -> is(':')) {
            _it -> next();
            skipWhiteSpace();
        }

        takeValue();
        if(_it -> is(';')) {
            _it -> next();
        }
        skipWhiteSpace();
    }
}

char CssTokenizer::_c() {
    return _it -> current();
}

CssTokenizer CssTokenizer::create(std::wstring text) {
    CssTokenizer tokenizer = CssTokenizer();

    tokenizer._text = text;
    tokenizer._it = new TextIterator(text);

    return tokenizer;
}


std::vector<CssToken> CssTokenizer::tokenize() {
    while (_it -> has()) {
        takeSelector();

       takeBlockOpen();
        skipWhiteSpace();
//
       takeBlockContent();
//
       skipWhiteSpace();
        takeBlockClose();
//        skipWhiteSpace();
    _it -> next();
    }
    return _tokens;
}

void CssTokenizer::skipWhiteSpace() {
    while (_it -> has() && _it -> isIn(L"\t\n\r\n\v ")) {
        _it -> next();
    }
}

std::vector<CssToken>* CssTokenizer::tokens() {
    return &_tokens;
}

CssTokenizer::~CssTokenizer() {
    //delete _it;
}