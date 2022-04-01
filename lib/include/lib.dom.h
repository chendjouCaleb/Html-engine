//
// Created by HP on 23/03/2022.
//

#ifndef HTMLENGINE_LIB_DOM_H
#define HTMLENGINE_LIB_DOM_H

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

enum DOCUMENT_POSITION : unsigned short {
    DOCUMENT_POSITION_DISCONNECTED = 0x01,
    DOCUMENT_POSITION_PRECEDING = 0x02,
    DOCUMENT_POSITION_FOLLOWING = 0x04,
    DOCUMENT_POSITION_CONTAINS = 0x08,
    DOCUMENT_POSITION_CONTAINED_BY = 0x10,
    DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20
};

enum EventPhase : unsigned short {
    EVENT_PHASE_NONE = 0,
    EVENT_PHASE_CAPTURING_PHASE = 1,
    EVENT_PHASE_AT_TARGET = 2,
    EVENT_PHASE_BUBBLING_PHASE = 3
};

enum AcceptNode : short {
    ACCEPT_NODE_FILTER_ACCEPT = 1,
    ACCEPT_NODE_FILTER_REJECT = 2,
    ACCEPT_NODE_FILTER_SKIP = 3
};

enum WhatToShow : unsigned long {
    SHOW_ALL = 0xFFFFFFFF,
    SHOW_ELEMENT = 0x00000001,
    SHOW_ATTRIBUTE = 0x00000002,
    SHOW_TEXT = 0x00000004,
    SHOW_CDATA_SECTION = 0x00000008,
    SHOW_ENTITY_REFERENCE = 0x00000010,
    SHOW_ENTITY = 0x00000020,
    SHOW_PROCESSING_INSTRUCTION = 0x00000040,
    SHOW_COMMENT = 0x00000080,
    SHOW_DOCUMENT = 0x00000100,
    SHOW_DOCUMENT_TYPE = 0x00000200,
    SHOW_DOCUMENT_FRAGMENT = 0x00000400,
    SHOW_NOTATION = 0x00000800
};



using nodeAttrs = std::map<std::string, std::string>;

typedef std::u16string DOMString;
typedef std::string USVString;

class DOMTokenList;

class NamedNodeMap;

struct EventInit;
struct KeyboardEventInit;
struct ElementCreationOptions;
struct ClientRect;
struct DOMRectInit;
struct DoubleRange;

class EventTarget;

class Event;

class Document;

class Attr;

class HTMLCollection;

class DOMImplementation;

class DocumentType;

class DocumentFragment;

class CDATASection;

class Text;

class Comment;

class ProcessingInstruction;

class Range;

class NodeIterator;

class NodeList;

class TreeWalker;

class NodeFilter;

class Element;


typedef std::clock_t DOMHighResTimeStamp;

typedef struct ElementCreationOptions {
    DOMString is;
} ElementCreationOptions;

typedef struct EventInit {
    bool bubbles = false;
    bool cancelable = false;
    bool composed = false;
} EventInit;

typedef struct KeyboardEventInit {
    DOMString code;
    bool isComposing;
    DOMString key;
    int location;
    bool repeat;
} KeyboardEventInit;

struct MouseEventInit {
    int button;
    int buttons;
    float clientX;
    float clientY;
    float movementX;
    float movementY;
    EventTarget relatedTarget;
    float screenX;
    float screenY;
};


struct MutationObserverInit {
    /**
     * Set to a list of attribute local names (without namespace) if not all attribute mutations need to be observed and attributes is true or omitted.
     */
    std::vector<DOMString> attributeFilter;

    /**
     * Set to true if attributes is true or omitted and target's attribute value before the mutation needs to be recorded.
     */
    bool attributeOldValue;

    /**
     * Set to true if mutations to target's attributes are to be observed. Can be omitted if attributeOldValue or attributeFilter is specified.
     */
    bool attributes;

    /**
     * Set to true if mutations to target's data are to be observed. Can be omitted if characterDataOldValue is specified.
     */
    bool characterData;

    /**
     * Set to true if characterData is set to true or omitted and target's data before the mutation needs to be recorded.
     */
    bool characterDataOldValue;

    /** Set to true if mutations to target's children are to be observed. */
    bool childList;

    /**  Set to true if mutations to not just target, but also target's descendants are to be observed. */
    bool subtree;
}

struct EventListenerOptions {
    bool capture = false;
};

struct AddEventListenerOptions : public EventListenerOptions {
    bool passive = false;
    bool once = false;
};

class EventListener {
public:
    void handleEvent(Event event);
};

class Event {
public:
    Event(DOMString type, EventInit options);

    DOMString type();

    EventTarget target();

    EventTarget srcElement();

    EventTarget currentTarget();

    EventPhase eventPhase();

    void stopPropagation();

    bool cancelBubble();

    void stopImmediatePropagation();

    bool bubbles();

    bool cancellable();

    bool returnValues();

    void preventDefault();

    bool composed();

    bool isTrusted();


    DOMHighResTimeStamp timeStamp;

    void initEvent(DOMString type, bool bubbles, bool cancelable);

    virtual ~Event();
};

class EventTarget {
public:
    virtual void addEventListener(DOMString type, EventListener callback, EventListenerOptions options);

    virtual void removeEventListener(DOMString type, EventListener callback, EventListenerOptions options);

    virtual bool dispatchEvent(Event event);
};


struct GetRootNodeOptions {
    bool composed = false;
};

class Node {
private:
    NodeType _nodeType;
    DOMString _nodeName;

    USVString _baseURI;

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

    Document ownerDocument();

    Node getRootNode(GetRootNodeOptions options);

    Node getRootNode();

    Node parentNode();

    Element parentElement();

    bool hasChildNodes();

    NodeList childNodes();

    Node firstChild();

    Node lastChild();

    Node previousSibling();

    Node nextSibling();

    DOMString nodeValue();

    DOMString textContent();

    void normalize();

    Node *cloneNode();

    Node *cloneNode(bool deep);

    bool isEqualNode(Node *node);

    bool isSameNode(Node *node);

    DOCUMENT_POSITION compareDocumentPosition(Node *other);

    bool contains(Node *node);

    DOMString lookpPrefix(DOMString _namespace);

    DOMString lookupNamespaceURI(DOMString prefix);

    bool isDefaultNamespace(DOMString _namespace);

    Node *insertBefore(Node *node, Node *child);

    Node *appendChild(Node *node);

    Node *replaceChild(Node *node, Node *child);

    Node *removeChild(Node *child);


    std::vector<Node> children;
    NodeType type;
    std::string tagname;
    std::string text;
    nodeAttrs attributes;

    std::string serialize(int depth);

    static Node create(NodeType type);

    static Node createTextNode(std::string);

    static Node createElement(std::string name);
};


class NodeIterator {
public:
    const Node *root;
    Node *referenceNode;
    bool pointerBeforeReferenceNode;
    WhatToShow whatToShow;
    NodeFilter filter;

    Node *nextNode();

    Node *previousNode();

    void detach();
};

class TreeWalker {
    Node *root;
    WhatToShow whatToShow;
    NodeFilter filter;
    Node *currentNode;

    Node *parentNode();

    Node *firstChild();

    Node *lastChild();

    Node *previousSibling();

    Node *nextSibling();

    Node *previousNode();

    Node *nextNode();
};


class NodeFilter {
public:
    AcceptNode acceptNode(Node *node);
};


class Element {
public:
    DOMString namespaceURI();

    DOMString prefix();

    DOMString localName();

    DOMString tagName();

    DOMString getId();

    void setId(DOMString id);

    DOMString getClassName();

    void setClassName(DOMString className);


    DOMTokenList classList();

    DOMString slot();

    NamedNodeMap attributes();

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

    bool webkitMatchesSelector(DOMString selectors); // legacy alias of .matches

    HTMLCollection getElementsByTagName(DOMString qualifiedName);

    HTMLCollection getElementsByTagNameNS(DOMString _namespace, DOMString localName);

    HTMLCollection getElementsByClassName(DOMString classNames);

    Element insertAdjacentElement(DOMString where, Element element); // legacy
    void insertAdjacentText(DOMString where, DOMString data); // legacy
};


class Document {
public:
    DOMImplementation implementation;
    USVString URL;
    USVString documentURI;
    DOMString compatMode;
    DOMString characterSet;
    DOMString charset; // legacy alias of .characterSet
    DOMString inputEncoding; // legacy alias of .characterSet
    DOMString contentType;

    DocumentType _doctype;
    Element documentElement;

    HTMLCollection getElementsByTagName(DOMString qualifiedName);

    HTMLCollection getElementsByTagNameNS(DOMString _namespace, DOMString localName);

    HTMLCollection getElementsByClassName(DOMString classNames);

    Element createElement(DOMString localName, ElementCreationOptions options);

    Element createElement(DOMString localName, DOMString options);

    Element createElementNS(DOMString _namespace, DOMString qualifiedName, ElementCreationOptions options);

    Element createElementNS(DOMString _namespace, DOMString qualifiedName, DOMString options);

    DocumentFragment createDocumentFragment();

    Text createTextNode(DOMString data);

    CDATASection createCDATASection(DOMString data);

    Comment createComment(DOMString data);

    ProcessingInstruction createProcessingInstruction(DOMString target, DOMString data);

    Node importNode(Node node);

    Node importNode(Node node, bool deep);

    Node adoptNode(Node node);

    Attr createAttribute(DOMString localName);

    Attr createAttributeNS(DOMString _namespace, DOMString qualifiedName);

    Event createEvent(DOMString interface); // legacy

    Range createRange();

// NodeFilter.SHOW_ALL = 0xFFFFFFFF
    NodeIterator createNodeIterator(Node root, WhatToShow whatToShow, NodeFilter filter);

    NodeIterator createNodeIterator(Node root, WhatToShow whatToShow);

    NodeIterator createNodeIterator(Node root, NodeFilter filter);

    TreeWalker createTreeWalker(Node root, WhatToShow whatToShow, NodeFilter filter);

    TreeWalker createTreeWalker(Node root, WhatToShow whatToShow);

    TreeWalker createTreeWalker(Node root, NodeFilter filter);
};

class XMLDocument {

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

class Attr {
    DOMString namespaceURI;
    DOMString prefix;
    DOMString localName;
    DOMString name;
    DOMString value;
    Element *ownerElement;
};

struct ClientRect {
    float bottom;
    float left;
    float right;
    float top;

    float height;
    float width;
};

struct DOMRectInit {
    float x;
    float y;
    float height;
    float width;
};

struct DoubleRange {
    unsigned long max;
    unsigned long min;
};


class NamedNodeMap {
    unsigned long length;

    Attr *item(unsigned long index);

    Attr *getNamedItem(DOMString qualifiedName);

    Attr *getNamedItemNS(DOMString _namespace, DOMString localName);

    Attr *setNamedItem(Attr attr);

    Attr *setNamedItemNS(Attr attr);

    Attr *removeNamedItem(DOMString qualifiedName);

    Attr *removeNamedItemNS(DOMString _namespace, DOMString localName);
};


class NodeList {
public:
    Node getItem(unsigned long index);
    unsigned long length();
};

#endif //HTMLENGINE_DOM_H


#endif //HTMLENGINE_LIB_DOM_H
