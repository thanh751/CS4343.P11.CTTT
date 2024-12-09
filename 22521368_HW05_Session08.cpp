//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 08 - Homework 05
#include <iostream>
#include <vector>
#include <string>
#include <openssl/sha.h>

// Function to compute SHA-256 hash
std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    std::string hexHash;
    char buf[3];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(buf, "%02x", hash[i]);
        hexHash += buf;
    }
    return hexHash;
}

struct MerkleNode {
    std::string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(const std::string& hash) : hash(hash), left(nullptr), right(nullptr) {}
};

class MerkleTree {
public:
    MerkleNode* root;

    MerkleTree(const std::vector<std::string>& data) {
        std::vector<MerkleNode*> nodes;
        for(const auto& d : data) {
            nodes.push_back(new MerkleNode(sha256(d)));
        }
        while(nodes.size() > 1) {
            std::vector<MerkleNode*> newLevel;
            for(size_t i = 0; i < nodes.size(); i += 2) {
                if(i + 1 < nodes.size()) {
                    std::string combined = nodes[i]->hash + nodes[i+1]->hash;
                    MerkleNode* parent = new MerkleNode(sha256(combined));
                    parent->left = nodes[i];
                    parent->right = nodes[i+1];
                    newLevel.push_back(parent);
                } else {
                    newLevel.push_back(nodes[i]);
                }
            }
            nodes = newLevel;
        }
        root = nodes.empty() ? nullptr : nodes[0];
    }

    ~MerkleTree() {
        // Destructor implementation to free nodes
    }
};

int main() {
    std::vector<std::string> transactions = {"Tx1", "Tx2", "Tx3", "Tx4"};
    MerkleTree tree(transactions);
    if(tree.root) {
        std::cout << "Merkle Root: " << tree.root->hash << std::endl;
    }
    return 0;
}