//
// Created by HP on 31/03/2022.
//

#include "dom.h"

Element::Element(DOMString name) {
    _tagName = name;
    _nodeName = _tagName;
    children = new std::vector<Node*>();
}

DOMString Element::tagName() {
    return _tagName;
}


std::wstring getDepth(int n);


DOMString Element::serialize(int depth){
    std::wstring tree_text = L"\n";

    tree_text += getDepth(depth);
    tree_text += L"<" + tagName() + L">";


    if(children -> size() > 0) {
        for(Node* child : *children) {
            //tree_text += L"\n";
            tree_text += child -> serialize(depth + 1);
        }
        tree_text += L"\n" + getDepth(depth);
    }

    tree_text += L"</" + tagName() + L">";


    return tree_text;

    return _tagName;
}

std::wstring getDepth(int n) {
    std::wstring space = L"";
    for(int i = 0; i < n ; i++) {
        space += L"    ";
    }
    return space;
}