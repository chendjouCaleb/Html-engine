//
// Created by HP on 12/03/2022.
//

#ifndef HTMLENGINE_DOM_H
#define HTMLENGINE_DOM_H

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <ctime>
#include <iterator>
#include <type_traits>

enum NodeType {

    /// <summary>
    /// Element node like <p> or <div>.
    /// </summary>
    ELEMENT_NODE = 1,

    /// <summary>
    /// The text of the current node.
    /// </summary>
    TEXT_NODE = 3,

    /** Comment node. */
    COMMENT_NODE = 8,

    /** Entire document node. */
    DOCUMENT_NODE = 9,

    /** Document type, like <!DOCTYPE html> */
    DOCUMENT_TYPE_NODE = 10,

    /** Fragment of document. Like injected html content. */
    DOCUMENT_FRAGMENT_NODE = 11
};


typedef std::wstring DOMString;
typedef std::wstring USVString;


class Document;
class Text;
class Element;
typedef Text TextNode;
class Comment;
class Attr;

class HTMLCollection;
class NodeIterator;
class NamedNodeMap;
class DOMTokenList;
class NodeList;

typedef std::clock_t DOMHighResTimeStamp;

typedef struct ElementCreationOptions {
    DOMString is;
} ElementCreationOptions;



class Node {
protected:
    NodeType _nodeType;
    DOMString _nodeName;

public:
    NodeType nodeType();

    DOMString nodeTypeAsString();

    DOMString nodeName();


    /**
     * The read-only baseURI property of the Node interface returns the absolute base URL of the document containing the node.
     *
     * The base URL is determined as follows:
     * 1. By default, the base URL is the location of the document (as determined by window.location).
     * 2. If it is an HTML Document and there is a <base> element in the document,
     *    the hrefvalue of the first Base element with such an attribute is used instead.
     */
    USVString baseURI();

    bool isConnected();

    Document* ownerDocument();

    Node* getRootNode();

    Node* parentNode();

    Element* parentElement();

    bool hasChildNodes();

    NodeList childNodes();

    Node* firstChild();

    Node* lastChild();

    Node* previousSibling();

    Node* nextSibling();

    DOMString nodeValue();

    DOMString textContent();

    void normalize();

    Node *cloneNode();

    Node *cloneNode(bool deep);

    bool isEqualNode(Node *node);

    bool isSameNode(Node *node);

    bool contains(Node *node);

    Node *insertBefore(Node *node, Node *child);

    Node *appendChild(Node *node);

    Node *replaceChild(Node *node, Node *child);

    Node *removeChild(Node *child);


    std::vector<Node*>* children;
    NodeType type;

    virtual DOMString serialize(int depth);
};


class NodeIterator {
public:
    const Node *root;

    Node* currentNode();

    Node *nextNode();

    Node *previousNode();
};

class TreeWalker {
    Node *root;
    Node *currentNode;

    Node *parentNode();

    Node *firstChild();

    Node *lastChild();

    Node *previousSibling();

    Node *nextSibling();

    Node *previousNode();

    Node *nextNode();
};


class Element : public Node {
protected:
    DOMString _tagName;
    NamedNodeMap* _attributes;

public:
    Element(DOMString tagName);
    DOMString tagName();

    DOMString getId();

    void setId(DOMString id);

    DOMString getClassName();

    void setClassName(DOMString className);


    DOMTokenList classList();

    NamedNodeMap* attributes();

    std::vector<DOMString> getAttributeNames();

    DOMString getAttribute(DOMString qualifiedName);

    DOMString getAttributeNS(DOMString _namespace, DOMString localName);

    void setAttribute(DOMString qualifiedName, DOMString value);

    void setAttributeNS(DOMString _namespace, DOMString qualifiedName, DOMString value);

    void removeAttribute(DOMString qualifiedName);

    void removeAttributeNS(DOMString _namespace, DOMString localName);

    bool toggleAttribute(DOMString qualifiedName, bool force);

    bool toggleAttribute(DOMString qualifiedName);

    bool hasAttribute(DOMString qualifiedName);

    bool hasAttributeNS(DOMString _namespace, DOMString localName);

    Element closest(DOMString selectors);

    bool matches(DOMString selectors);

    HTMLCollection getElementsByTagName(DOMString qualifiedName);

    HTMLCollection getElementsByTagNameNS(DOMString _namespace, DOMString localName);

    HTMLCollection getElementsByClassName(DOMString classNames);

    DOMString serialize(int depth) override;
};


class CharacterData: public Node {
protected:
    DOMString _data;
public:
    DOMString data();

    /**
     * Get data content length.
     * @return
     */
    size_t length();
    Document& ownerDocument();
    void appendData(DOMString data);
    void deleteData(size_t offset, size_t count);
    void insertData(size_t offset, DOMString data);
    void replaceData(size_t offset, size_t count, DOMString data);
    DOMString substring(size_t number, size_t count);

    DOMString serialize(int depth) override;
};

class Text: public CharacterData {
private:

public:
    Text(DOMString data);
    DOMString wholeText();
    Text splitText(unsigned int offset);

    DOMString serialize(int depth) override;
};


class Document {
public:

    Element documentElement;

    HTMLCollection getElementsByTagName(DOMString qualifiedName);

    HTMLCollection getElementsByClassName(DOMString classNames);

    Element createElement(DOMString localName, ElementCreationOptions options);

    Element createElement(DOMString localName, DOMString options);

    Text createTextNode(DOMString data);


    Node adoptNode(Node node);

    Attr createAttribute(DOMString localName);

};


typedef std::list<DOMString> DOMStringArray;

class DOMTokenList {
    unsigned long length;

    DOMString item(unsigned long index);

    bool contains(DOMString token);

    void add(DOMStringArray tokens);

    void remove(DOMStringArray tokens);

    bool toggle(DOMString token, bool force);

    bool toggle(DOMString token);

    bool replace(DOMString token, DOMString newToken);

    bool supports(DOMString token);

    DOMString value;
    std::vector<DOMString>::iterator iterable;
};

class HTMLCollection {
    unsigned long length;

    Element *item(unsigned long index);

    Element *namedItem(DOMString name);
};

class Attr: public Node {
private:
    DOMString _name;
    DOMString _value;
    Element* _ownerElement;
    Document* _document;

public:
    Attr(Element* element, DOMString name, DOMString value);
    Attr(Element* element, DOMString name);
    Attr(DOMString name, DOMString value);
    Attr(DOMString name);
    DOMString name();
    DOMString value();
    Element *ownerElement();
    Document* document();
    DOMString serialize(int depth) override;
};

/** A collection of Attr objects. Objects inside a NamedNodeMap are not in any particular order,
 * unlike NodeList, although they may be accessed by an index as in an array. */
class NamedNodeMap {
private:
    std::map<DOMString, Attr*>* _values;

public:
    NamedNodeMap();
    size_t length();
    Attr* getNamedItem(DOMString qualifiedName);
    Attr* item(size_t index);
    Attr* removeNamedItem(DOMString qualifiedName);
    Attr* setNamedItem(DOMString qualifiedName);
};

class NodeList {
public:
    Node getItem(unsigned long index);
    unsigned long length();
};

#endif //HTMLENGINE_DOM_H