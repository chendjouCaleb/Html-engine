//
// Created by HP on 26/03/2022.
//

#ifndef HTMLENGINE_SELECTOR_H
#define HTMLENGINE_SELECTOR_H

#include <string>
#include <vector>

enum SelectorType {
    SELECTOR_TAG, SELECTOR_CLASS, SELECTOR_ID, SELECTOR_ATTRIBUTE, SELECTOR_ALL
};
enum SelectorCombination {
    SELECTOR_COMBINATION_NONE,
    SELECTOR_COMBINATION_CHILD,
    SELECTOR_COMBINATION_NEXT,
    SELECTOR_COMBINATION_PARENT_NEXT,
    SELECTOR_COMBINATION_CHILDREN,
    SELECTOR_COMBINATION_DIRECT_CHILDREN
};

struct SelectorGroup {

};


class Selector {
public:
    Selector(std::wstring _value, SelectorType _type) {
        value = _value;
        type = _type;
    }

    std::wstring text;
    std::wstring value;

    SelectorType type;

    std::wstring state;
    std::wstring pseudoElement;

    SelectorCombination combination = SELECTOR_COMBINATION_NONE;

    std::vector<Selector*> constraints;

    std::wstring getText() {
        if(type == SELECTOR_TAG) {
            return value;
        }

        if(type == SELECTOR_CLASS) {
            return L"."+value;
        }
        if(type == SELECTOR_ID) {
            return L"#" + value;
        }

        if(type == SELECTOR_ALL) {
            return L"*";
        }


        return L"";
    }

    std::wstring combinationString() {
        if (combination == SELECTOR_COMBINATION_NONE) {
            return L"";
        }

        if (combination == SELECTOR_COMBINATION_NEXT) {
            return L"+";
        }

        if (combination == SELECTOR_COMBINATION_PARENT_NEXT) {
            return L"~";
        }

        if (combination == SELECTOR_COMBINATION_DIRECT_CHILDREN) {
            return L">";
        }

        if (combination == SELECTOR_COMBINATION_CHILDREN) {
            return L" ";
        }
        return L"";
    }

    virtual std::wstring toString() {
        std::wstring _value = combinationString() + getText();

        for (auto child:constraints) {
            _value += child -> toString();
        }

        if(!pseudoElement.empty()) {
            _value.append(L"::" + pseudoElement);
        }

        if(!state.empty()) {
            _value.append(L":" + state);
        }

        return _value;
    }
};

class AttributeSelector: public Selector {
public:
    std::wstring attributeValue;

    AttributeSelector(std::wstring name, std::wstring value) : Selector(name, SELECTOR_ATTRIBUTE) {
        attributeValue = value;
    }

    std::wstring toString() override {
        if (attributeValue.empty()) {
            return L"[" + value + L"]";
        }

        return L"[" + value + L"=" + L"\"" + attributeValue + L"\"" + L"]" ;
    }
};


struct Selectors {
    std::vector<Selector> groups;

    std::wstring toString() {
        std::wstring value;

        for (int i = 0; i < groups.size(); i++) {
            value.append(groups[i].toString());
            if (i < (groups.size() - 1)) {
                value.append(L", ");
            }
        }

        return value;
    }
};

#endif //HTMLENGINE_SELECTOR_H
