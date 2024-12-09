//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 09 - Homework 05
#include <iostream>
#include <vector>
#include <string>

struct Node {
    std::string name;
    std::vector<Node*> children;

    Node(const std::string& name) : name(name) {}
};

class PhylogeneticTree {
public:
    Node* root;

    PhylogeneticTree(const std::string& rootName) {
        root = new Node(rootName);
    }

    void addChild(Node* parent, const std::string& childName) {
        Node* child = new Node(childName);
        parent->children.push_back(child);
    }

    void printTree(Node* node, int depth = 0) const {
        for(int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << node->name << std::endl;
        for(auto child : node->children) {
            printTree(child, depth +1);
        }
    }

    ~PhylogeneticTree() {
        // Implement destructor to free memory
    }
};

int main() {
    PhylogeneticTree tree("Life");
    tree.addChild(tree.root, "Bacteria");
    tree.addChild(tree.root, "Archaea");
    tree.addChild(tree.root, "Eukaryota");

    tree.printTree(tree.root);

    return 0;
}