//
// Created by HP on 24/03/2022.
//

#include <css.h>
#include <vector>
#include <iostream>

std::vector<CssDeclaration>* CssDeclarations::declarations() {
    return &_declarations;
}

CssDeclaration CssDeclarations::add(std::wstring name, std::wstring value) {
    CssDeclaration declaration = { .name = name, .value = value };
    _declarations.push_back(declaration);

    return declaration;
}

CssRule::CssRule() = default;

CssDeclarations* CssRule::declarations() {
    return &_declarations;
}
std::wstring CssRule::selector() {
    return _selector;
}

void CssRule::selector(std::wstring value) {
    _selector = value;
}

std::wstring CssRule::toString() {
    std::wstring value;
    value += _selector;
    value += L" {\n";

    for (int i = 0; i < _declarations.declarations() -> size(); ++i) {
        auto declaration = (*_declarations.declarations())[i];
        value += L"    ";
        value += declaration.name;
        value += L" : ";
        value += declaration.value;
        value += L";\n";
    }
    value += L"}\n";

    return value;
}

std::vector<CssRule> CssStyleSheet::rules() {
    return _rules;
}

std::wstring CssStyleSheet::toString() {
    std::wstring value;
    std::cout << _rules.size() << std::endl;
    for (auto & _rule : _rules) {
        value += _rule.toString();
        value += L"\n\n";
    }
    return value;
}