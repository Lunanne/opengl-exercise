#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>
#include <unordered_map>

#include "../Graphics/GraphicsTypes.h"
#include "../Graphics/Material.h"

#include "materialfileparser.h"

void MaterialFileParser::CreateFunctions()
{
    m_parseName = [this](Words& p_data)
    {
        m_currentMaterial->SetName(p_data[0]);
    };

    m_parseTexture = [this](Words& p_data)
    {
        m_currentMaterial->SetDiffuseTexture(p_data[0]);
    };

    std::pair<std::string, ParsingFunction> name("newmtl", m_parseName);
    std::pair<std::string, ParsingFunction> texture("map_Kd", m_parseTexture);
    m_parseFunctions.insert(texture);
    m_parseFunctions.insert(name);
}

MaterialFileParser::MaterialFileParser()
{
    CreateFunctions();
}

void MaterialFileParser::ParseMtlFile(const std::string& p_fileName, std::unordered_map<std::string, MaterialPtr>& p_materials)
{
    std::string filePath = "./Resources/" + p_fileName;
    std::ifstream file(filePath);
    std::string line;
    Words words;
    while (std::getline(file, line))
    {
        boost::split(words, line, boost::is_any_of(" "));
        if (words[0].compare("newmtl") == 0)
        {
            if (m_currentMaterial != NULL)
            {
                std::pair<std::string, MaterialPtr> material(m_currentMaterial->GetName(), m_currentMaterial);
                p_materials.insert(material);
            }
            m_currentMaterial = MaterialPtr(new Material);
        }

        if (m_parseFunctions.count(words[0]) > 0)
        {
            ParsingFunction function = m_parseFunctions.at(words[0]);
            words.erase(words.begin()); //not interested in the first entry anymore.
            function(words);
        }
    }
    if (m_currentMaterial != NULL)
    {
        std::pair<std::string, MaterialPtr> material(m_currentMaterial->GetName(), m_currentMaterial);
        p_materials.insert(material);
    }
}