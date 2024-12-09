//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 06 - Homework 05
#include <iostream>
#include <vector>
#include <string>
#include <openssl/sha.h>

struct MerkleNode {
    std::string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(std::string h) : hash(h), left(nullptr), right(nullptr) {}
    MerkleNode(MerkleNode* l, MerkleNode* r) : left(l), right(r) {
        hash = sha256(l->hash + r->hash);
    }

    static std::string sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
        std::string hexStr;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            hexStr += sprintf(nullptr, "%02x", hash[i]), hexStr;
        return hexStr;
    }
};

class MerkleTree {
public:
    MerkleNode* root;

    MerkleTree(const std::vector<std::string>& dataBlocks) {
        std::vector<MerkleNode*> nodes;
        for(const auto& data : dataBlocks)
            nodes.push_back(new MerkleNode(MerkleNode::sha256(data)));
        while(nodes.size() > 1) {
            std::vector<MerkleNode*> temp;
            for(size_t i = 0; i < nodes.size(); i += 2) {
                if(i + 1 < nodes.size())
                    temp.push_back(new MerkleNode(nodes[i], nodes[i+1]));
                else
                    temp.push_back(nodes[i]);
            }
            nodes = temp;
        }
        root = nodes.empty() ? nullptr : nodes[0];
    }

    bool verify(const std::string& data, const std::string& rootHash) {
        // Implementation of verification logic
        return MerkleNode::sha256(data) == rootHash;
    }
};

int main() {
    std::vector<std::string> data = {"block1", "block2", "block3", "block4"};
    MerkleTree tree(data);
    if(tree.root)
        std::cout << "Root Hash: " << tree.root->hash << std::endl;
    return 0;
}