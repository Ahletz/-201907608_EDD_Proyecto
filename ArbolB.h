#ifndef ARBOL_B
#define ARBOL_B

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Estructura que contendrá los datos del vuelo
struct Avion {
    string vuelo;
    string numero_de_registro;
    string modelo;
    int capacidad;
    string aerolinea;
    string ciudad_destino;
    string estado;
};

// Nodo del árbol B
class BTreeNode {
public:
    vector<Avion> keys; // Vector que contendrá las llaves
    vector<BTreeNode*> children; // Vector de hijos del nodo
    bool leaf; // Indica si es hoja

    BTreeNode(bool leaf); // Constructor

    void traverse(); // Método para recorrer el árbol
    BTreeNode* search(const string& k); // Método para buscar una llave
    void insertNonFull(const Avion& k, int t); // Insertar llave en nodo no lleno
    void splitChild(int i, BTreeNode* y, int t); // Dividir nodo cuando está lleno
    void remove(const string& k, int t); // Eliminar una llave
    Avion removeFromLeaf(int idx); // Eliminar una llave de una hoja
    Avion removeFromNonLeaf(int idx, int t); // Eliminar una llave de un nodo no hoja
    Avion getPredecessor(int idx); // Obtener el predecesor
    Avion getSuccessor(int idx); // Obtener el sucesor
    void fill(int idx, int t); // Llenar el hijo que tiene menos de t-1 llaves
    void borrowFromPrev(int idx); // Tomar prestado del nodo anterior
    void borrowFromNext(int idx); // Tomar prestado del nodo siguiente
    void merge(int idx, int t); // Fusionar nodos

    friend class BTree; // Permite que BTree acceda a métodos privados
};

// Clase árbol B
class BTree {
public:
    BTreeNode* root; // Raíz
    int t; // Orden del árbol

    BTree(int _t) { // Constructor
        root = nullptr;
        t = _t;
    }

    void traverse() { // Método para recorrer el árbol
        if (root != nullptr) root->traverse();
    }

    BTreeNode* search(const string& k) { // Buscar clave en el árbol
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(const Avion& k); // Insertar nueva clave en el árbol
    Avion remove(const string& k); // Buscar y eliminar clave específica

    void graphviz(const string& filename); // Generar visualización del árbol en Graphviz

private:
    void graphvizHelper(ofstream& out, BTreeNode* node);
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
        root->keys.push_back(k);
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

Avion BTree::remove(const string& k) { //remover y obtener datos
    if (!root) {
        throw runtime_error("The tree is empty");
    }

    Avion removedAvion;
    try {
        root->remove(k, t);
    } catch (const Avion& avion) {
        removedAvion = avion;
    }

    if (root->keys.empty()) {
        BTreeNode* tmp = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete tmp;
    }

    return removedAvion;
}

void BTreeNode::remove(const string& k, int t) {
    int idx = 0;
    while (idx < keys.size() && keys[idx].numero_de_registro < k)
        ++idx;

    if (idx < keys.size() && keys[idx].numero_de_registro == k) {
        if (leaf)
            throw removeFromLeaf(idx);
        else
            throw removeFromNonLeaf(idx, t);
    } else {
        if (leaf) {
            throw runtime_error("The key does not exist in the tree");
        }

        bool flag = (idx == keys.size());
        if (children[idx]->keys.size() < t) {
            fill(idx, t);
        }

        if (flag && idx > keys.size()) {
            children[idx - 1]->remove(k, t);
        } else {
            children[idx]->remove(k, t);
        }
    }
}

Avion BTreeNode::removeFromLeaf(int idx) {
    Avion k = keys[idx];
    keys.erase(keys.begin() + idx);
    return k;
}

Avion BTreeNode::removeFromNonLeaf(int idx, int t) {
    Avion k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        Avion pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred.numero_de_registro, t);
    } else if (children[idx + 1]->keys.size() >= t) {
        Avion succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ.numero_de_registro, t);
    } else {
        merge(idx, t);
        children[idx]->remove(k.numero_de_registro, t);
    }
    return k;
}

Avion BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->keys.size()];
    return cur->keys[cur->keys.size() - 1];
}

Avion BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx, int t) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t) {
        borrowFromPrev(idx);
    } else if (idx != keys.size() && children[idx + 1]->keys.size() >= t) {
        borrowFromNext(idx);
    } else {
        if (idx != keys.size()) {
            merge(idx, t);
        } else {
            merge(idx - 1, t);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    for (int i = child->keys.size() - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->children.size() - 1; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->children.size() - 1];

    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];

    child->keys.push_back(sibling->keys[sibling->keys.size() - 1]);
    sibling->keys.pop_back();

    if (!child->leaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    if (!child->leaf)
        child->children.push_back(sibling->children[0]);

    keys[idx] = sibling->keys[0];

    sibling->keys.erase(sibling->keys.begin());

    if (!child->leaf)
        sibling->children.erase(sibling->children.begin());
}

void BTreeNode::merge(int idx, int t) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys.push_back(sibling->keys[i]);

    if (!child->leaf) {
        for (int i = 0; i < sibling->children.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

void BTree::graphviz(const string& filename) {
    ofstream out(filename);
    out << "digraph BTree {\n";
    out << "    node [shape=record];\n";
    if (root) {
        graphvizHelper(out, root);
    }
    out << "}\n";
    out.close();
}

void BTree::graphvizHelper(ofstream& out, BTreeNode* node) {
    out << "    node" << node << " [label=\"";
    for (int i = 0; i < node->keys.size(); ++i) {
        if (i != 0) out << " | ";
        out << "<f" << i << "> " << node->keys[i].numero_de_registro;
    }
    out << "\"];\n";

    for (int i = 0; i <= node->keys.size(); ++i) {
        if (node->children.size() > i) {
            out << "    \"node" << node << "\":f" << i << " -> \"node" << node->children[i] << "\";\n";
            graphvizHelper(out, node->children[i]);
        }
    }
}

#endif