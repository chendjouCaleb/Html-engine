//
// Created by HP on 12/03/2022.
//

#ifndef HTMLENGINE_PARSER_H
#define HTMLENGINE_PARSER_H


#include <string>
#include <vector>
#include "charItertor.h"
#include "htmlTokenizer.h"
#include "dom.h"

class HtmlParser {
private:
    std::wstring input;
    size_t index = 0;
    HtmlTokenizer tokenizer;

public:
    static HtmlParser create(std::wstring input);
    static HtmlParser createFromFile(std::string filePath);

    std::vector<Node*> parseNodes();
    Node* parseTree();
    std::vector<Node*>* getChildren(Node* node);
    Node* getNode();

    std::vector<HtmlToken> tokens();

    void next();
    bool hasMore();
    HtmlToken current();
};

#endif //HTMLENGINE_PARSER_H
