#pragma once
#include <string>
#include <vector>
#include <map>

struct Tag
{
    std::string name;  
};

struct TagWithAttrbute : public Tag
{
    std::map<std::string, std::string> attributes;    
};

struct StartTag : public TagWithAttrbute
{

};

struct EndTag : public Tag
{

};

struct EmptyElementTag : public TagWithAttrbute
{
    
};

struct Element
{

};

struct ContentElement : public Element
{
    StartTag start_tag;
    std::string content;
    EndTag end_tag;
};

struct EmptyElement : public Element
{
    EmptyElementTag tag;
};

