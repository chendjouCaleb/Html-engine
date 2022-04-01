cmake_minimum_required(VERSION 3.15)
project(htmlEngine)

set(CMAKE_CXX_STANDARD 20)

#FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
#FILE(GLOB_RECURSE ENGINE_HEADERS *.hpp *.h *.inl)

#add_executable(htmlEngine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib/include)

add_executable(htmlEngine main.cpp lib/include/dom.h lib/dom/dom.cpp lib/include/parser.h lib/parser/html/parser.cpp lib/include/charItertor.h lib/utilities/charIterator.cpp lib/include/htmlTokenizer.h lib/parser/html/HtmlTokenizer.cpp lib/include/lib.dom.h lib/include/textIterator.h lib/utilities/TextIterator.cpp lib/include/css.h lib/parser/css/CssTokenizer.cpp lib/include/token.h lib/include/Iterator.h lib/parser/css/CssParser.cpp lib/parser/css/css.cpp lib/include/selector.h lib/include/dom/document.hpp lib/dom/node.cpp lib/dom/text.cpp lib/dom/element.cpp lib/dom/attr.cpp lib/dom/namedNodeMap.cpp)