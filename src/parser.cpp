#include <parser.h>

namespace overkill
{

parser::parser(std::string_view _strview)
:strview(_strview)
{}


auto parser::next_line() -> std::string
{
    endofline = strview.find('\n', startofline);
    startofline = strview.find_first_of(whitelisted_characters, startofline);

    if (startofline == int(std::string::npos)) {
        std::cout << "\nPARSER ERROR ---->>> (startofline == std::string::npos)\n\n"
            << "Line: " << linecount;
        LOG_WARN("No whitelisted characters found after new-line character!! Line:");
        return "";
    }
    if (endofline == int(std::string::npos)) {
        std::cout << "\nPARSER ERROR ---->>> (endofline == std::string::npos)\n\n"
            << "Line: " << linecount;
        LOG_WARN("No end of file (new-line) character found! Line:");
        return "";        
    }

    linecount++;
    // Skip empty lines in between and eat whitespace
    while (endofline - startofline <= 0) {

        startofline = endofline + 1;
        endofline = strview.find('\n', startofline);
        startofline = strview.find_first_of(whitelisted_characters, startofline);

        if (startofline == int(std::string::npos)) {
            std::cout << "\nPARSER ERROR ---->>> (startofline == std::string::npos)\n\n"
                << "Line: " << linecount;
            LOG_WARN("No whitelisted characters found after new-line character!! Line:");
            return "";
        }
        if (endofline == int(std::string::npos)) {
            std::cout << "PARSER ERROR ---->>> (endofline == std::string::npos)"
                << "Line: " << linecount;
            LOG_WARN("No end of file (new-line) character found! Line:");
            return "";
        }
        linecount++;
    }

    auto line = std::string{
        strview.substr(startofline, endofline - startofline)
    };
    size_t lastCharacter = (endofline - startofline) - 1;
    auto lastValidCharacter = line.find_last_of(whitelisted_characters);
    if (lastValidCharacter != lastCharacter) {

        std::cout << "\nPARSER ERROR ---->>> (lastValidCharacter != lastCharacter)\n\n"
            << "Line: " << linecount << '\n'
            << "Linetext: " << line << '\n'
            << "index lastValidCharacter: " << lastValidCharacter << '\n'
            << "index lastCharacter: " << lastCharacter << '\n'
            << "line[lastValidCharacter]: " << line[lastValidCharacter] << '\n'
            << "line[lastCharacter]: " << line[lastCharacter] << '\n'
            << "int(line[lastValidCharacter]): " << int(line[lastValidCharacter]) << '\n'
            << "int(line[lastCharacter]): " << int(line[lastCharacter]) << '\n';
        LOG_WARN("Non-whitelisted character found after the end of line !!");
        return "";    
    }

    startofline = endofline + 1;
    return line;
};

auto parser::next_key_string() -> key_string
{
    auto line = next_line();

    if(line == "")
        return key_string{"","", PARSE_ERROR};

    std::string key = line.substr(0, line.find(":"));
    std::string valueString = "";

    if (line.find(":") + 2 < line.size())
        valueString = line.substr(line.find(":") + 2);
/*
#ifdef DEBUG
    std::stringstream ss;
    ss  << " key: "
        << std::setw(18) << std::left
        << key

        << " val: "
        << valueString;

    LOG_DEBUG("%s", ss.str().c_str());
#endif
*/
    return key_string{ key, valueString, PARSE_SUCCESS };
};


auto parser::next_key_integer() -> key_integer
{
    auto[key, valueString, err] = next_key_string();
    if (err)
        return key_integer{"",0, PARSE_ERROR};

    // @doc https://stackoverflow.com/a/18534114 - 15.04.2018
    try {

        int integer = std::stoi(valueString);
        return key_integer{ key, integer, PARSE_SUCCESS };
    }
    catch (std::invalid_argument& e) {
        // if no conversion could be performed
        LOG_WARN("std::stoi catch (std::invalid_argument& e) - no conversion could be performed");
    }
    catch (std::out_of_range& e) {
        // if the converted value would fall out of the range of the result type 
        // or if the underlying function (std::strtol or std::strtoull) sets errno 
        // to ERANGE.
        LOG_WARN("std::stoi catch (std::out_of_range& e) - the converted value would fall out of the range of the result type");

    }
    return key_integer{"",0, PARSE_ERROR};
}


auto parser::next_key_vertex() -> key_vertex { 
    

    auto[key, valueString, err] = next_key_string();
    if (err == PARSE_ERROR)
        return key_vertex{"", 0,0,0, PARSE_ERROR};


    std::stringstream ss;
    ss << valueString;


    // Parsing position
    float x,y,z;
    ss >> x >> y >> z;
    if (ss.fail()) {
        return key_vertex{"", 0,0,0, PARSE_ERROR};
    }

    return key_vertex{key, x,y,z, PARSE_SUCCESS };
}

auto parser::next_key_triangle() -> key_triangle
{ 
    auto[key, valueString, err] = next_key_string();
    if (err == PARSE_ERROR)
        return key_triangle{"", 0,0,0, PARSE_ERROR};

    std::stringstream ss;
    ss << valueString;
    

    GLuint a,b,c;

    ss >> a >> b >> c;
    if(ss.fail()){
        return key_triangle{"", 0,0,0, PARSE_ERROR};
    }

    return key_triangle{key, a,b,c, PARSE_SUCCESS };

}


} // ::mg