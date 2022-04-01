//
// Created by HP on 29/03/2022.
//

#ifndef HTMLENGINE_DOCUMENT_HPP
#define HTMLENGINE_DOCUMENT_HPP

#include <string>

typedef std::wstring USVString;
typedef std::wstring DOMString;

struct DocumentCreateOptions {
    std::wstring filePath;
};

class Document {
private:
    USVString _URL;
    USVString _documentURI;
    DOMString _charset = L"utf-8";
    DOMString _contentType = L"text/html";


public:
    USVString URL() {
        return _URL;
    }

    /**
     * Get the document location as string.
     * Unlike HTML, document location in this scope should be the applications folder location.
     */
    USVString documentURI() {
        return _documentURI;
    }

    DOMString charset() {
        return _charset;
    }

    /**
     * Get the content-type of document. text/html is the only content-type available.
     */
    DOMString contentType() {
        return _contentType;
    }



};

#endif //HTMLENGINE_DOCUMENT_HPP
