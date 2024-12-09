//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 02 - Homework 05
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>

struct XMLNode : public std::enable_shared_from_this<XMLNode> {
    std::string name;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<std::shared_ptr<XMLNode>> children;
    std::string text;

    std::shared_ptr<XMLNode> findElement(const std::string& elementName) {
        if (name == elementName) {
            return shared_from_this();
        }
        for (auto& child : children) {
            auto result = child->findElement(elementName);
            if (result) return result;
        }
        return nullptr;
    }

    std::string getAttribute(const std::string& attr) {
        if (attributes.find(attr) != attributes.end()) {
            return attributes[attr];
        }
        return "";
    }
};

class XMLParser {
public:
    std::shared_ptr<XMLNode> root;

    bool parse(const std::string& content) {
        std::istringstream ss(content);
        std::string token;
        std::vector<std::shared_ptr<XMLNode>> stack;

        while (ss >> token) {
            if (token[0] == '<') {
                if (token[1] == '/') {
                    stack.pop_back();
                } else {
                    auto node = std::make_shared<XMLNode>();
                    size_t pos = token.find(' ');
                    size_t end = token.find('>');
                    if (pos != std::string::npos && pos < end) {
                        node->name = token.substr(1, pos - 1);
                        // Attribute parsing can be added here
                    } else {
                        node->name = token.substr(1, token.find('>') - 1);
                    }
                    if (stack.empty()) {
                        root = node;
                    } else {
                        stack.back()->children.push_back(node);
                    }
                    if (token[token.size() - 2] != '/') {
                        stack.push_back(node);
                    }
                }
            } else {
                if (!stack.empty()) {
                    stack.back()->text += token + " ";
                }
            }
        }
        return true;
    }

    std::shared_ptr<XMLNode> findElement(const std::string& elementName) {
        if (root) {
            return root->findElement(elementName);
        }
        return nullptr;
    }
};

int main() {
    std::ifstream file("input.xml");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    XMLParser parser;
    if (parser.parse(content)) {
        auto element = parser.findElement("tagname");
        if (element) {
            std::cout << "Element found: " << element->name << std::endl;
            std::cout << "Attribute value: " << element->getAttribute("attr") << std::endl;
        } else {
            std::cout << "Element not found." << std::endl;
        }
    }
    return 0;
}