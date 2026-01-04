// bioskop.h
#ifndef BIOSKOP_H
#define BIOSKOP_H

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>
#include <cctype>
#include "ktp.h"  // <<<<< PENTING: include ktp.h
using namespace std;

// ======================================================================================
// UTILITAS
// ======================================================================================
void garis() {
    cout << "--------------------------------------------------\n";
}
void cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ======================================================================================
// PEMESANAN & SINGLE LINKED LIST
// ======================================================================================
struct Pemesanan {
    string nama, judulFilm;
    int jumlah, total;
    Pemesanan* next;
    Pemesanan(string n = "", string f = "", int j = 0)
        : nama(n), judulFilm(f), jumlah(j), total(j * 50000), next(nullptr) {}
};

class RiwayatSLL {
public:
    Pemesanan* head = nullptr;

    void tambah(string nama, string film, int jumlah) {
        Pemesanan* p = new Pemesanan(nama, film, jumlah);
        p->next = head;
        head = p;
    }

    void tampilkan() {
        if (!head) {
            cout << "Belum ada riwayat.\n";
            return;
        }
        Pemesanan* curr = head;
        int i = 1;
        while (curr) {
            cout << i++ << ". " << curr->nama << " - " << curr->judulFilm << "\n";
            curr = curr->next;
        }
    }

    int jumlahTransaksi() {
        int c = 0;
        Pemesanan* curr = head;
        while (curr) { c++; curr = curr->next; }
        return c;
    }

    int totalPendapatan() {
        int total = 0;
        Pemesanan* curr = head;
        while (curr) {
            total += curr->total;
            curr = curr->next;
        }
        return total;
    }
};

// ======================================================================================
// FILM & AVL TREE (SESUAI NOTULENSI)
// ======================================================================================
struct Film {
    string judul, genre;
    int harga;
    Film(string j = "", string g = "", int h = 0) : judul(j), genre(g), harga(h) {}
    bool operator<(const Film& f) const { return judul < f.judul; }
    bool operator>(const Film& f) const { return judul > f.judul; }
};

struct AVLNode {
    Film data;
    AVLNode *left = nullptr, *right = nullptr;
    int height = 1;
    AVLNode(Film f) : data(f) {}
};

class AVLTree {
private:
    AVLNode* root = nullptr;

    int getHeight(AVLNode* n) {
        return n ? n->height : -1; // Notulensi: Height(Null) = -1
    }

    int getBalance(AVLNode* n) {
        if (!n) return 0;
        return getHeight(n->left) - getHeight(n->right); // BF = h(kiri) - h(kanan)
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    AVLNode* insertRec(AVLNode* node, Film film) {
        if (!node) return new AVLNode(film);
        if (film < node->data)
            node->left = insertRec(node->left, film);
        else if (film > node->data)
            node->right = insertRec(node->right, film);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && film < node->left->data) // LL
            return rotateRight(node);
        if (balance < -1 && film > node->right->data) // RR
            return rotateLeft(node);
        if (balance > 1 && film > node->left->data) { // LR
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && film < node->right->data) { // RL
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(AVLNode* node, int& idx) {
        if (!node) return;
        inorder(node->left, idx);
        cout << left << setw(3) << ++idx
             << setw(25) << node->data.judul
             << setw(12) << node->data.genre
             << "Rp " << node->data.harga << "\n";
        inorder(node->right, idx);
    }

    Film* searchRec(AVLNode* node, const string& judul) {
        if (!node || node->data.judul == judul) return node ? &node->data : nullptr;
        if (judul < node->data.judul)
            return searchRec(node->left, judul);
        return searchRec(node->right, judul);
    }

public:
    void insert(Film film) { root = insertRec(root, film); }
    void display() {
        if (!root) { cout << "Belum ada film.\n"; return; }
        garis();
        cout << left << setw(3) << "No"
             << setw(25) << "JUDUL"
             << setw(12) << "GENRE"
             << "HARGA\n";
        garis();
        int idx = 0;
        inorder(root, idx);
        garis();
    }
    Film* search(const string& judul) { return searchRec(root, judul); }
};

// ======================================================================================
// HUFFMAN TREE (manual, tanpa unordered_map)
// ======================================================================================
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    bool operator>(const HuffmanNode& other) const { return freq > other.freq; }
};

class HuffmanTree {
private:
    struct Kode {
        char ch;
        string code;
    } kode[128];
    int kodeCount = 0;
    HuffmanNode* root = nullptr;

    void buildCodes(HuffmanNode* node, string s) {
        if (!node) return;
        if (!node->left && !node->right) {
            kode[kodeCount].ch = node->ch;
            kode[kodeCount].code = s;
            kodeCount++;
        }
        buildCodes(node->left, s + "0");
        buildCodes(node->right, s + "1");
    }

    void destroy(HuffmanNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    HuffmanTree(const string& text) : root(nullptr), kodeCount(0) {
        if (text.empty()) return;

        int freq[128] = {0};
        for (char c : text) if (c >= 0 && c < 128) freq[c]++;

        HuffmanNode* nodes[128];
        int count = 0;
        for (int i = 0; i < 128; i++) {
            if (freq[i] > 0) {
                nodes[count++] = new HuffmanNode(char(i), freq[i]);
            }
        }

        while (count > 1) {
            int min1 = 0, min2 = 1;
            if (nodes[min1]->freq > nodes[min2]->freq) min2 = 0, min1 = 1;
            for (int i = 2; i < count; i++) {
                if (nodes[i]->freq < nodes[min1]->freq) {
                    min2 = min1;
                    min1 = i;
                } else if (nodes[i]->freq < nodes[min2]->freq) {
                    min2 = i;
                }
            }
            HuffmanNode* left = nodes[min1];
            HuffmanNode* right = nodes[min2];
            HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            nodes[min1] = parent;
            for (int i = min2; i < count - 1; i++) nodes[i] = nodes[i + 1];
            count--;
        }

        if (count == 1) {
            root = nodes[0];
            buildCodes(root, "");
        }
    }

    ~HuffmanTree() {
        if (root) destroy(root);
    }

    string encode(const string& text) {
        string result = "";
        for (char c : text) {
            for (int i = 0; i < kodeCount; i++) {
                if (kode[i].ch == c) {
                    result += kode[i].code;
                    break;
                }
            }
        }
        return result;
    }

    double efisiensi(const string& text) {
        int asli = text.length() * 8;
        string encoded = encode(text);
        int huf = encoded.length();
        return (asli == 0) ? 0.0 : (1.0 - (double)huf / asli) * 100.0;
    }
};

// ======================================================================================
// LAPORAN & FUNGSI UTAMA
// ======================================================================================
void tampilkanLaporan(RiwayatSLL& riwayat) {
    garis();
    cout << "LAPORAN SISTEM\n";
    garis();
    cout << "Jumlah Transaksi : " << riwayat.jumlahTransaksi() << "\n";
    cout << "Total Pendapatan : Rp " << riwayat.totalPendapatan() << "\n";
    garis();
}

// Fungsi utama (diimplementasi di main.cpp)
void jalankanSistem(KTP& ktpUser);

#endif