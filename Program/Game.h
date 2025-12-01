#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream> 
using namespace std;

struct Node {
    string nama; // Nama game
    string genre; // Genre game     
    bool isGenre;  // Penanda apakah node ini adalah node genre
    vector<Node*> children; // Daftar dari anak node / daftar dari tree
};

class Game {
private:
    Node* root; // Root utama dari tree
    bool isAdmin_LogIn = false; /* Status admin sebelum melakukan proses login
    jika admin sudah menyelesaikan proses login maka isAdmin_Login nya berubah menjadi true*/

    const string Admin_Username = "admin";
    const string Admin_Password = "admin";

    // Fungsi rekursif 
    Node* CariGenreNode(Node* node, const string& genre); // Mencari node genre
    void TampilkanTree(Node* node, int depth); // Menampilkan seluruh tree
    void CariHuruf(Node* node, char h); // Cari game berdasarkan huruf awal
    void CariGenre(Node* node, const string& genre); // Cari game berdasarkan genre
    bool HapusGameRec(Node* node, const string& nama); // Hapus game secara rekursif

    // Fungsi Save Game 
    void SaveToFile(Node *node, ofstream& file); // Simpan tree ke file

public:
    Game();
    ~Game();

    // Admin functions
    void LoginAdmin(const string& username, const string& password);
    void TambahGame(const string& nama, const string& genre);
    void HapusGame(const string& nama);
    void TampilkanSemuaGame();

    // User functions
    void CariGameBerdasarkanGenre(const string& genre);
    void CariGameBerdasarkanHurufAwal(char huruf);

    // Save dan Load data
    void Save();
    void Load();
};

#endif