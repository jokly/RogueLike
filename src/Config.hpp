#pragma once

#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Config {
public:
    static Config& Instance() {
        static Config conf;
        return conf;
    }

    void loadConfig(std::string filePath) {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(filePath, root);

        windowName = root.get<std::string>("windowName", "RogueLike");
        windowWidth = root.get<int>("windowWidth", 800);
        windowHeight = root.get<int>("windowHeight", 600);

        tileSetPath = root.get<std::string>("tileSetPath", "");
        mapPath = root.get<std::string>("mapPath", "");
        fontPath = root.get<std::string>("fontPath", "");
        spriteSize = root.get<int>("spriteSize", 16);

        for (boost::property_tree::ptree::value_type &object : root.get_child("objects")) {
            objects.insert(std::pair<std::string, char>(object.first, object.second.data()[0]));
        }
    }

    std::string windowName;
    int windowWidth;
    int windowHeight;

    std::string tileSetPath;
    std::string mapPath;
    std::string fontPath;

    int spriteSize;
    std::map<std::string, char> objects;

private:
    Config() {}
    ~Config() {}
    Config(Config const&) = delete;
    Config& operator= (Config const&) = delete;
};
