#include <file.h>


namespace mg
{


auto file_to_string(const std::string filepath) -> std::experimental::optional<std::string>
{
    std::ifstream infile(filepath);

    if (!infile) 
    {
        LOG_WARN("file not found: %s", filepath.data());
        return std::experimental::nullopt;
    }
    std::stringstream ss;
    ss << infile.rdbuf();
    return ss.str();
}


auto load_vertex_data(const std::string filepath) -> vertex_data 
{
    auto parsestring = file_to_string("vertexdata/"+filepath);
    if (!parsestring) 
    {
        LOG_ERROR("(!parsestring) undefined");
    }

    overkill::parser p { *parsestring };
    
    vertex_data vdata;

    // VERTICES
    auto [vertices_key, vertices_count, err0] = p.next_key_integer();
    if(err0)
    {
        LOG_ERROR("Parse error ex. 'vertices: 8'");
    }
    
    LOG_DEBUG("vertices: %d", vertices_count);


    for (size_t i = 0; i < vertices_count; ++i) 
    {
        auto [vkey, x, y, z, err1] = p.next_key_vertex();

        if (err1) 
        {
            LOG_ERROR("Parse error ex. 'v:  1.000000  1.000000 -1.000000'");
        }

        LOG_DEBUG("v: %.4f %.4f %.4f",x,y,z);
        vdata.vertices.emplace_back(glm::vec3{x,y,z});
    }

    // INDICIES
    auto [indicies_key, indicies_count, err2] = p.next_key_integer();
    if(err2)
    {
        LOG_ERROR("Parse error ex. 'triangles: 12'");
    }  

    LOG_DEBUG("triangles: %d", indicies_count);

    for (size_t i = 0; i < indicies_count; ++i) 
    {
        auto [ikey, a, b, c, err3] = p.next_key_triangle();

        if (err3)
        {
            LOG_ERROR("Parse error ex. 't: 5 2 1'");
        }
        LOG_DEBUG("t: %u %u %u", a,b,c);
        vdata.indicies.emplace_back(a);
        vdata.indicies.emplace_back(b);
        vdata.indicies.emplace_back(c);
    }

    return vdata;
}


} // ::mg