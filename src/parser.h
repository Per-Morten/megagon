#pragma once

#include <string>
#include <string_view>
#include <iomanip>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include <logger.h>


namespace overkill 
{

struct key_integer  { std::string key; int i;            int parseerror; };
struct key_string   { std::string key; std::string str;  int parseerror; };
struct key_vertex   { std::string key; float x,y,z;      int parseerror; };
struct key_triangle { std::string key; GLuint a,b,c;     int parseerror; };

const int PARSE_SUCCESS = 0;
const int PARSE_ERROR   = 1;

/// <summary> Translates files into internal datastructure </summary>
class parser
{
private:
    std::string_view strview;
    int startofline =  0;
    int endofline = 9999999;
    int linecount = 0;
    const std::string whitelisted_characters = "0123456789abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ-:";

    auto next_key_string()   -> key_string;

public:
    parser(std::string_view _strview);
    auto next_line()         -> std::string;
    auto next_key_integer()  -> key_integer;
    auto next_key_vertex()   -> key_vertex;
    auto next_key_triangle() -> key_triangle;
};


}
