//
// Created by HP on 12/03/2022.
//

#include <string>
#include <iostream>
#include <fstream>
#include <ios>
#include "parser.h"

HtmlParser HtmlParser::create(const std::wstring input) {
    HtmlParser parser = HtmlParser();
    parser.index = 0;
    parser.input = input;
    parser.tokenizer = HtmlTokenizer::create(input);

    return parser;
}

HtmlParser HtmlParser::createFromFile(std::string filePath) {
    std::wifstream inputFile(filePath, std::ios::binary);
    std::wstring content((std::istreambuf_iterator<wchar_t>(inputFile)), {});
    HtmlParser parser = HtmlParser::create(content);
    return parser;
}

Node* HtmlParser::parseTree() {
    auto tokens = tokenizer.tokenize();
    Node* node = new Element(L"document");

    while (hasMore() && current().type != HTML_TOKEN_ELEMENT_CLOSE) {
        node -> children -> push_back(getNode());
    }

    return node;
}

std::vector<Node*> HtmlParser::parseNodes() {
    auto nodes = std::vector<Node*>();

    while (hasMore() && current().type == HTML_TOKEN_ELEMENT_OPEN) {
        Node* node = new Element(current().value);
        node -> children = getChildren(node);
    }

    return nodes;
}

Node* HtmlParser::getNode() {
    if(current().type == HTML_TOKEN_TEXT) {
        Node* node = new Text(current().value);
        next();
        return node;
    }

   Element* node = new Element(current().value);
    next();

    while (hasMore() && !(current().type == HTML_TOKEN_ELEMENT_CLOSE && current().value == node -> tagName())) {
        node -> children -> push_back(getNode());
    }
    if((current().type == HTML_TOKEN_ELEMENT_CLOSE && current().value == node -> tagName())) {
        next();
    }

    return node;
}

std::vector<Node*>* HtmlParser::getChildren(Node* node) {
    auto nodes = new std::vector<Node*>();
    return nodes;
}

void HtmlParser::next() {
    if(hasMore()) {
        index++;
    }
}

bool HtmlParser::hasMore() {
    return index < tokenizer.tokens().size() - 1;
}

HtmlToken HtmlParser::current() {
    return tokenizer.tokens()[index];
}

std::vector<HtmlToken> HtmlParser::tokens() {
    return tokenizer.tokens();
}