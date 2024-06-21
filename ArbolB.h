#ifndef ARBOL_B
#define ARBOL_B

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//estructura que contendra los datos del vuelo
struct Avion {

    string vuelo;
    string numero_de_registro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudad_destino;
    string estado;
};

//nodo del arbol b
class BTreeNode { //clase nodo 

public:
    vector<Avion> keys; //vector que contendra la llave
    vector<BTreeNode*> children; // vector hijo nodo 
    bool leaf; //nodo u hoja
    
    BTreeNode(bool leaf);  //contructor
    
    void traverse(); //metodo para recorrer el arbol
    BTreeNode* search(const string& k); //metodo para buscar una key
    void insertNonFull(const Avion& k, int t);  //insertar key en nodo no lleno
    void splitChild(int i, BTreeNode* y, int t); //metodo dividir nodo cuando esta lleno
    
    friend class BTree; //permite que btree acceda a metodo privados 
};

//clase arbol b
class BTree { 

public:
    BTreeNode* root; //raiz
    int t; //orden del arbol
    
    BTree(int _t) { //contructor
        root = nullptr;
        t = _t;
    }
    
    void traverse() { //metodo para recorrer el arbol
        if (root != nullptr) root->traverse();
    }
    
    BTreeNode* search(const string& k) { //buscar clave en el arbol
        return (root == nullptr) ? nullptr : root->search(k);
    }
    
    void insert(const Avion& k); //insertar nueva key en el arbol
};

BTreeNode::BTreeNode(bool leaf) {
    this->leaf = leaf;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf)
            children[i]->traverse();
        cout << " " << keys[i].numero_de_registro;
    }
    
    if (!leaf)
        children[i]->traverse();
}

BTreeNode* BTreeNode::search(const string& k) {
    int i = 0;
    while (i < keys.size() && k > keys[i].numero_de_registro)
        i++;
    
    if (i < keys.size() && keys[i].numero_de_registro == k)
        return this;
    
    if (leaf)
        return nullptr;
    
    return children[i]->search(k);
}

void BTreeNode::insertNonFull(const Avion& k, int t) {
    int i = keys.size() - 1;
    
    if (leaf) {
        keys.push_back(k);
        while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i].numero_de_registro > k.numero_de_registro)
            i--;
        i++;
        
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i], t);
            
            if (keys[i].numero_de_registro < k.numero_de_registro)
                i++;
        }
        children[i]->insertNonFull(k, t);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y, int t) {
    BTreeNode* z = new BTreeNode(y->leaf);
    z->keys.resize(t - 1);
    
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    
    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }
    
    y->keys.resize(t - 1);
    
    children.insert(children.begin() + i + 1, z);
    
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

void BTree::insert(const Avion& k) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(k); // Insertar clave en la raíz
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children.push_back(root);
            s->splitChild(0, root, t);
            
            int i = 0;
            if (s->keys[0].numero_de_registro < k.numero_de_registro)
                i++;
            s->children[i]->insertNonFull(k, t);
            
            root = s;
        } else {
            root->insertNonFull(k, t);
        }
    }
}


#endif