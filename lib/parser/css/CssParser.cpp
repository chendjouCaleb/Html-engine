//
// Created by HP on 24/03/2022.
//

#include "css.h"
#include <iostream>

CssParser::CssParser(std::wstring text)  {
    auto tokenizer = CssTokenizer::create(text);
    tokenizer.tokenize();
    _it = new Iterator((&tokenizer)->tokens());
}

CssStyleSheet CssParser::parse() {
    CssStyleSheet styleSheet;
    while (_it->has()) {
        if(_it -> current().type == CSS_TOKEN_SELECTOR ) {
            auto rule = takeRule();
            styleSheet._rules.push_back(rule);
        }
    }

    return styleSheet;
}

CssRule CssParser::takeRule() {
    CssRule rule = CssRule();
    auto selector = _it->current().value;
    rule.selector(selector);
    _it->next();

    if(_it->has() && _it->current().type == CSS_TOKEN_BLOCK_OPEN) {
        _it->next();
    }

    while (_it->has() && _it->current().type != CSS_TOKEN_BLOCK_CLOSE) {
        rule.declarations() -> declarations()-> push_back(takeDeclaration());
    }

    if(_it->has() && _it->current().type == CSS_TOKEN_BLOCK_CLOSE) {
        _it->next();
    }
    return rule;
}


CssDeclaration CssParser::takeDeclaration() {
    CssDeclaration declaration;
    declaration.name = _it->current().value;
    _it->next();

    declaration.value = _it->current().value;
    _it->next();

    return declaration;
}

CssParser::~CssParser() {
    delete(_it);
}