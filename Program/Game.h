#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Struktur Node untuk Tree
struct Node {
    string nama;      // menyimpan nama game atau nama genre
    string genre;     // menyimpan nama genre
    bool isGenre;     // menandai apakah node ini adalah genre atau game
    vector<Node*> children; // menyimpan anak node(game yang berada dalam genre)
};

// Kelas Game
class Game {
private:
    Node* root; // Root dari tree

    const string Admin_Username = "admin"; // Username admin yang valid
    const string Admin_Password = "admin"; // Password admin yang valid

    // Fungsi rekursif
    Node* CariGenreNode(Node* node, const string& genre); // Mencari node genre secara rekursif
    void TampilkanTree(Node* node, int depth); // Menampilkan tree secara rekursif
    void CariHuruf(Node* node, char huruf); // Mencari game berdasarkan huruf awal
    void CariGenre(Node* node, const string& genre); // Mencari game berdasarkan genre
    bool HapusGameRec(Node* node, const string& nama); // Menghapus game secara rekursif

    // Save
    void SaveToFile(Node *node, ofstream& file); // Menyimpan data ke file secara rekursif

public:
    bool isAdmin_LogIn = false; // Status login admin

    Game(); // Constructor membuat root dan genre default
    ~Game(); // Destructor untuk membersihkan memori(tidak wajib)

    // Admin commands
    void LoginAdmin(const string& username, const string& password); // Login sebagai admin dengan username dan password
    void TambahGame(const string& nama, const string& genre, bool bypassAdmin = false); // Menambah game pada genre tertentu
    void HapusGame(const string& nama); // Menghapus game berdasarkan nama

    // User commands
    void CariGameBerdasarkanGenre(const string& genre); // mencari game berdasarkan genre
    void CariGameBerdasarkanHurufAwal(char huruf); // mencari game berdasarkan huruf awal

    // User dan Admin commands
    void TampilkanSemuaGame(); // Menampilkan seluruh genre dan game

    // Save load
    void Save(bool bypassAdmin = false); // Menyimpan data ke file
    void Load(); // Memuat data dari file dan menambah data dari tree
};

#endif
