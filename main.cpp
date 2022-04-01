#include <iostream>
#include "charItertor.h"
#include "iterator"
#include "parser.h"
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <css.h>
#include <selector.h>
#include "htmlTokenizer.h"


int main() {
    _setmode(_fileno(stdout), _O_WTEXT);
    std::wcout << L"bonjour à vous "<< std::endl;
    auto fn = [](int n) -> void { std::cout << n * n << std::endl; };

    //fn(5);

    //std::wcout << L"e\u0009e\u000Ae\u000Ce\u000De\u0020e" << std::endl;


    std::wstring str = L"Bonjour à tous pour l'élection éà-è";

    auto filePath = "E:/Lab/HTML/Dom/document.html";
    std::wstring html = L"<html></html>";

    //HtmlParser parser = HtmlParser::createFromFile("E:/Lab/HTML/Dom/document.html");

    std::wifstream inputFile(filePath, std::ios::binary);
    std::wstring content((std::istreambuf_iterator<wchar_t>(inputFile)), {});

    HtmlTokenizer tokenizer = HtmlTokenizer::create(content);
    tokenizer.tokenize();

   // Node *tree = parser.parseTree();

    auto tokens = tokenizer.tokens();
    Iterator<HtmlToken> it = Iterator(&tokens);

    while (it.has()) {
        auto token = it.current();
        std::wcout << token.value ;
        it.next();
    }

    //std::wcout << tree -> serialize(0) << std::endl;


//    std::wifstream input1("E:/Lab/HTML/Dom/index.css", std::ios::binary);
//
//    std::wstring content((std::istreambuf_iterator<wchar_t>(input1)), {});
//    //std::wcout << content << std::endl;
//
//    CssTokenizer cssTokenizer = CssTokenizer::create(content);
//    auto tokens = cssTokenizer.tokenize();
//
//    for (auto &token : tokens) {
//        //  std::wcout << token.to_wstr() << std::endl;
//    }
//
//    CssParser cssParser = CssParser(content);
//    CssStyleSheet styleSheet = cssParser.parse();

    //std::wcout << "style: " << styleSheet.serialize() << std::endl;

    //std::cout << tree.serialize(0) << std::endl;
//
////    std::cout << "Size: " << parser.tokens().size() << std::endl;
////
////    while (parser.hasMore()) {
////        auto token = parser.current();
////        std::cout << token.value << std::endl;
////        parser.next();
////    }


//    Selectors selectors;
//
//    Selector first = Selector(L"input", SELECTOR_TAG);
//    Selector firstClassName = Selector(L"material", SELECTOR_CLASS);
//    AttributeSelector firstAttribute = AttributeSelector(L"type", L"text");
//
//    first.constraints.push_back(&firstClassName);
//    first.constraints.push_back(&firstAttribute);
//
//    Selector div = Selector(L"red", SELECTOR_ID);
//    div.state = L"hover";
//    div.combination = SELECTOR_COMBINATION_NEXT;
//
//    Selector divClassName = Selector(L"glass", SELECTOR_CLASS);
//    AttributeSelector divAttribute = AttributeSelector(L"color", L"red");
//
//    div.constraints.push_back(&divClassName);
//    div.constraints.push_back(&divAttribute);
//
//    selectors.groups.push_back(first);
//    selectors.groups.push_back(div);
//
//    std::wcout << selectors.serialize() << std::endl;

    return 0;
}
