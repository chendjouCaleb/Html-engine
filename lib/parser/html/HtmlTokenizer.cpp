//
// Created by HP on 12/03/2022.
//

#include "htmlTokenizer.h"
#include <iostream>

HtmlTokenizer HtmlTokenizer::create(const std::wstring text) {
    HtmlTokenizer tokenizer = HtmlTokenizer();

    tokenizer._input = text;
    tokenizer._it = new TextIterator(text);

    return tokenizer;
}

char HtmlTokenizer::_c() {
    return _it->current();
}

std::vector<HtmlToken*> HtmlTokenizer::tokenize() {
    _tokens = std::vector<HtmlToken>();

    while (_it->has()) {
        if (_it->current() == '<') {
            takeElement();
            // _tokens.push_back(takeElement());
        } else {
            takeTextToken();
            //_tokens.push_back(takeTextToken());
        }
    }
    return _tokens;
}

void HtmlTokenizer::takeElement() {
    if (_it->current() == '<') {
        _it->next();

        if (_it->current() == '/') {
            _it->next();
            takeElementClose();
        } else {
            takeElementOpen();
        }

    } else {
        throw "Unknown element open token";
    }

}

void HtmlTokenizer::takeElementOpen() {
    std::wstring text = L"";
    HtmlToken token = HtmlToken();
    token.type = HTML_TOKEN_ELEMENT_OPEN;

    while (_it->isLetter() || _it->isDigit()) {
        text += _it->current();
        _it->next();
    }
    skipWhiteSpace();

    token.value = text;

    _tokens.push_back(token);

    takeAttrs();

    takeTagClose();
    std::wcout << _it->current() << std::endl;
}

HtmlToken* HtmlTokenizer::takeTagClose() {
    if (_it->is('>')) {
        HtmlToken* token = new HtmlToken{L">", HTML_TOKEN_TAG_CLOSE};
        _it->next();
        _tokens.push_back(token);
        return token;
    }
    return HtmlToken {};
}


HtmlToken HtmlTokenizer::takeElementClose() {
    std::wstring text = L"";
    HtmlToken token = HtmlToken();
    token.type = HTML_TOKEN_ELEMENT_CLOSE;

    while (_it->isLetter() || _it->isDigit()) {
        text += _it->current();
        _it->next();
    }
    // Skip '>'
    _it->next();
    // text += '>';

    token.value = text;
    //std::cout << text << std::endl;
    _tokens.push_back(token);
    return token;
}

std::vector<HtmlToken> HtmlTokenizer::tokens() {
    return _tokens;
}

HtmlToken HtmlTokenizer::takeTextToken() {

    HtmlToken token = HtmlToken();
    token.type = HTML_TOKEN_TEXT;
    token.value = L"";

    while (_it->has() && _it->current() != '<') {
        token.value += _it->current();
        _it->next();
    }
    //std::cout << "Text: " << token.value << std::endl;
    _tokens.push_back(token);
    return token;
}

void HtmlTokenizer::takeAttrs() {
    skipWhiteSpace();
    while (_it->has() && !_it->is('>') && !_it->is('/')) {
        takeAttr();
    }
}

void HtmlTokenizer::takeAttr() {
    skipWhiteSpace();
    takeAttrName();

    skipAttrEqual();

    takeAttrValue();
}


HtmlToken HtmlTokenizer::takeAttrName() {
    std::wstring value;
    while (_it->has() && !_it->is('=') && !_it->is('/') && !_it->is('>') && !_it->isWhiteSpace()) {
        value.push_back(_it->current_t());
        _it->next();
    }

    if (!value.empty()) {
        HtmlToken token;
        token.type = HTML_TOKEN_ATTR_NAME;
        token.value = value;
        _tokens.push_back(token);
        return token;
    }
    return HtmlToken{};
}


HtmlToken HtmlTokenizer::takeAttrValue() {
    if(_it->is('"')) {
        return takeAttrQuotedValue();
    }else if(_it->is('\'')) {
        return takeAttrSingleQuotedValue();
    } else {
        return takeAttrUnquotedValue();
    }
}

HtmlToken HtmlTokenizer::takeAttrUnquotedValue() {
    std::wstring value;
    std::wcout <<"value: " << value << std::endl;
    while (_it->has() && !_it->isWhiteSpace() && !_it->is('>') && !_it->is('/')) {
        value.push_back(_it->current());
        _it->next();
    }
    auto token = HtmlToken { value, HTML_TOKEN_ATTR_VALUE};
    _tokens.push_back(token);
    return token;
}

HtmlToken HtmlTokenizer::takeAttrSingleQuotedValue() {
    _it->skipIfIs('\'');
    std::wstring value;
    while (_it->has() && !_it->is_t(L'\'') ) {
        value.push_back(_it->current());
        _it->next();
    }
    _it->skipIfIs('\'');
    auto token = HtmlToken { value, HTML_TOKEN_ATTR_VALUE};
    _tokens.push_back(token);
    return token;
}

HtmlToken HtmlTokenizer::takeAttrQuotedValue() {
    _it->skipIfIs('"');
    std::wstring value;
    while (_it->has() &&  !_it->is_t(L'"') ) {
        value.push_back(_it->current());
        _it->next();
    }
    _it->skipIfIs('"');
    auto token = HtmlToken { value, HTML_TOKEN_ATTR_VALUE};
    _tokens.push_back(token);
    return token;
}


void HtmlTokenizer::skipAttrEqual() {
    skipWhiteSpace();
    if (_it->is('=')) {
        _it->next();
        skipWhiteSpace();
    }
}

void HtmlTokenizer::skipWhiteSpace() {
    while (_it->has() && _it->isWhiteSpace()) {
        _it->next();
    }
}

HtmlTokenizer::~HtmlTokenizer() {
    //delete _it;
}
