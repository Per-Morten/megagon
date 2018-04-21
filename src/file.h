#include <string>
#include <vector>
#include <string_view>
#include <fstream>
#include <experimental/optional>

#include <glm/glm.hpp>
#include <parser.h>
#include <logger.h>


namespace mg
{

struct vertex_data
{
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> indicies;
};

auto file_to_string(const std::string filepath)   -> std::experimental::optional<std::string>;
auto load_vertex_data(const std::string filepath) -> vertex_data;

}
