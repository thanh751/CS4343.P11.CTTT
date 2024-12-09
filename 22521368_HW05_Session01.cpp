//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Homework 05
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Represents a file or directory in the file system
#include <memory>

class FileSystemNode : public std::enable_shared_from_this<FileSystemNode> {
public:
    std::string name;
    bool isDirectory;
    std::vector<std::shared_ptr<FileSystemNode>> children;
    FileSystemNode* parent;

    FileSystemNode(const std::string& name, bool isDir, FileSystemNode* parent = nullptr)
        : name(name), isDirectory(isDir), parent(parent) {}
    
    void addChild(std::shared_ptr<FileSystemNode> child) {
        children.push_back(child);
    }

    bool removeChild(const std::string& name) {
        auto it = std::find_if(children.begin(), children.end(),
            [&name](const std::shared_ptr<FileSystemNode>& node) { return node->name == name; });
        if (it != children.end()) {
            children.erase(it);
            return true;
        }
        return false;
    }

    std::shared_ptr<FileSystemNode> getChild(const std::string& name) {
        auto it = std::find_if(children.begin(), children.end(),
            [&name](const std::shared_ptr<FileSystemNode>& node) { return node->name == name; });
        if (it != children.end()) {
            return *it;
        }
        return nullptr;
    }
};

// Manages the file system operations
class FileSystem {
public:
    std::shared_ptr<FileSystemNode> root;
    std::shared_ptr<FileSystemNode> current;

    FileSystem() {
        root = std::make_shared<FileSystemNode>("root", true, nullptr);
        current = root;
    }

    void mkdir(const std::string& name) {
        if (current->getChild(name)) {
            std::cout << "Directory already exists.\n";
            return;
        }
        auto newDir = std::make_shared<FileSystemNode>(name, true, current.get());
        current->addChild(newDir);
    }

    void touch(const std::string& name) {
        if (current->getChild(name)) {
            std::cout << "File already exists.\n";
            return;
        }
        auto newFile = std::make_shared<FileSystemNode>(name, false, current.get());
        current->addChild(newFile);
    }

    void ls() {
        for (auto& child : current->children) {
            std::cout << (child->isDirectory ? "DIR " : "FILE ") << child->name << "\n";
        }
    }

    void cd(const std::string& path) {
        if (path == "..") {
            if (current->parent) {
                current = std::shared_ptr<FileSystemNode>(current->parent->shared_from_this());
            }
            return;
        }
        auto node = current->getChild(path);
        if (node && node->isDirectory) {
            current = node;
        } else {
            std::cout << "Invalid directory.\n";
        }
    }

    void rm(const std::string& name) {
        if (!current->removeChild(name)) {
            std::cout << "File or directory not found.\n";
        }
    }
};

int main() {
    FileSystem fs;
    std::string command, arg;
    while (true) {
        std::cout << ">> ";
        std::cin >> command;
        if (command == "mkdir") {
            std::cin >> arg;
            fs.mkdir(arg);
        }
        else if (command == "touch") {
            std::cin >> arg;
            fs.touch(arg);
        }
        else if (command == "ls") {
            fs.ls();
        }
        else if (command == "cd") {
            std::cin >> arg;
            fs.cd(arg);
        }
        else if (command == "rm") {
            std::cin >> arg;
            fs.rm(arg);
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }
    return 0;
}