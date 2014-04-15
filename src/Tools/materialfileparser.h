#ifndef MATERIALFILEPARSER_H
#define MATERIALFILEPARSER_H

#include <functional>
#include <unordered_map>
#include <vector>

typedef std::vector<std::string> Words;
typedef std::function<void(Words&)> ParsingFunction;

class MaterialFileParser
{
public:
    MaterialFileParser();
    void ParseMtlFile(const std::string& p_fileName, std::unordered_map<std::string, MaterialPtr>& p_materials);

private:
    MaterialPtr m_currentMaterial;
    std::unordered_map<std::string, ParsingFunction> m_parseFunctions;
    ParsingFunction m_parseName;
    ParsingFunction m_parseTexture;

    void CreateFunctions();
};
#endif
