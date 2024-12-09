//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 10 - Homework 05
#include <iostream>
#include <unordered_map>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(const std::string& word) {
        TrieNode* node = root;
        for(char ch : word){
            if(node->children.find(ch) == node->children.end()){
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    bool search(const std::string& word) const {
        TrieNode* node = root;
        for(char ch : word){
            if(node->children.find(ch) == node->children.end()){
                return false;
            }
            node = node->children.at(ch);
        }
        return node->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) const {
        TrieNode* node = root;
        for(char ch : prefix){
            if(node->children.find(ch) == node->children.end()){
                return false;
            }
            node = node->children.at(ch);
        }
        return true;
    }
};

int main(){
    Trie trie;
    trie.insert("hello");
    trie.insert("hell");
    trie.insert("heaven");
    trie.insert("goodbye");

    std::cout << trie.search("hello") << "\n";     // 1
    std::cout << trie.search("hell") << "\n";      // 1
    std::cout << trie.search("heaven") << "\n";    // 1
    std::cout << trie.search("good") << "\n";      // 0
    std::cout << trie.startsWith("he") << "\n";    // 1
    std::cout << trie.startsWith("goo") << "\n";   // 1
    std::cout << trie.startsWith("bad") << "\n";   // 0

    return 0;
}