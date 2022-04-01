//
// Created by HP on 31/03/2022.
//

#include "dom.h"
#include "textIterator.h"
#include "iostream"

Text::Text(DOMString data) {
    DOMString value;
    TextIterator it= TextIterator(data);

    while (it.has()) {
        if(it.isWhiteSpace()) {
            value.append(L" ");
            it.skipWhiteSpace();
        }else {
            value.push_back(it.current_t());
            it.next();
        }
    }

    _nodeType = TEXT_NODE;
    _nodeName = L"TEXT";
    _data = value;
    //std::wcout << serialize(0) << std::endl;
}

DOMString Text::wholeText() {
    return _data;
}

DOMString Text::serialize(int depth) {
    return _data;
}

DOMString CharacterData::serialize(int depth) {
    return L"";
}