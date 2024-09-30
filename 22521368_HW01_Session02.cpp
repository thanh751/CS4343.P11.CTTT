//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 02 - Homework 02
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class SongNode {
public:
    string songName;
    SongNode* next;
    SongNode* prev;

    SongNode(string name){
        name = songName;
        next=NULL;
        prev=NULL;
    }
};

class MusicPlayer {
private:
    SongNode* head;
    SongNode* tail;
    SongNode* current;
    unordered_map<string, SongNode*> songMap;

public:
    MusicPlayer(){
        head=NULL;
        tail=NULL;
        current=NULL;
    }

    void addSong(const string& songName) {
        if (songMap.find(songName) != songMap.end()) {
            return; 
        }
        SongNode* newNode = new SongNode(songName);
        songMap[songName] = newNode;
        if (!head) {
            head = tail = current = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void playNext() {
        if (!current) return;
        current = current->next ? current->next : head;
    }

    void playPrevious() {
        if (!current) return;
        current = current->prev ? current->prev : tail;
    }

    void removeSong(const string& songName) {
        if (songMap.find(songName) == songMap.end()) {
            return; 
        }
        SongNode* nodeToDelete = songMap[songName];
        if (nodeToDelete == head && nodeToDelete == tail) {
            head = tail = current = NULL;
        } else if (nodeToDelete == head) {
            head = head->next;
            head->prev = NULL;
            if (current == nodeToDelete) current = head;
        } else if (nodeToDelete == tail) {
            tail = tail->prev;
            tail->next = NULL;
            if (current == nodeToDelete) current = tail;
        } else {
            nodeToDelete->prev->next = nodeToDelete->next;
            nodeToDelete->next->prev = nodeToDelete->prev;
            if (current == nodeToDelete) current = nodeToDelete->next;
        }
        songMap.erase(songName);
        delete nodeToDelete;
    }

    void displayPlaylist() {
        SongNode* temp = head;
        while (temp) {
            cout << temp->songName << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;
    MusicPlayer player;
    for (int i = 0; i < n; ++i) {
        string operation;
        cin >> operation;
        if (operation == "ADD") {
            string songName;
            cin >> songName;
            player.addSong(songName);
        } else if (operation == "NEXT") {
            player.playNext();
        } else if (operation == "PREV") {
            player.playPrevious();
        } else if (operation == "REMOVE") {
            string songName;
            cin >> songName;
            player.removeSong(songName);
        } else if (operation == "DISPLAY") {
            player.displayPlaylist();
        }
    }
    return 0;
}

