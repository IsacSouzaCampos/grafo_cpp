#include <iostream>
#include "grafo.h"



Grafo::Grafo() = default;

void Grafo::inserirVertice(int data) {
    int index = ultimo;
    listaVertices.push_back(Vertice(data, index));
    vertices++;
    ultimo++;
}


bool Grafo::inserirAresta(int v1, int v2, int peso) {
    for(auto& vi : listaVertices) {
        if(vi.getIndex() == v1) {
            for(auto& vj : listaVertices) {
                if(vj.getIndex() == v2) {
                    pair<Vertice, Vertice> p1(vi, vj);
                    listaArestas.push_back(make_pair(p1, peso));
                    arestas++;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::deletarVertice(int index) {
    for(auto& v : listaVertices){
        if(v.getIndex() == index) {
            for(auto& a : listaArestas) {
                if(a.first.first == v || a.first.second == v) {
                    pair<Vertice, Vertice> p1(a.first.first, a.first.second);
                    listaArestas.remove(make_pair(p1, a.second));
                }
            }
            listaVertices.remove(v);
            vertices--;
            return true;;
        }
    }
    return false;
}

bool Grafo::deletarAresta(int v1, int v2) {
    for(auto& a : listaArestas) {
        if(a.first.first.getIndex() == v1 && a.first.second.getIndex() == v2) {
            pair<Vertice, Vertice> p1(a.first.first, a.first.second);
            listaArestas.remove(make_pair(p1, a.second));
            arestas--;
            return true;
        }
    }
    return false;
}

void Grafo::imprimirListaAdjacentes() {
    if(listaVertices.empty())
        throw out_of_range("lista vazia!");
    for(auto& vi : listaVertices) {
        cout << "[v" << vi.getIndex() << "]: " << flush;
        for(auto& a : listaArestas) {
            if(a.first.first == vi)
                cout << "[v" << a.first.second.getIndex() << "] / " << flush;
        }
        cout << endl;
    }
}

void Grafo::imprimirVertices() {
    for(auto& v : listaVertices)
        cout << v.getData() << endl;
}

void Grafo::DFS() {
    stack<Vertice> stack;   // cria a stack
    for(auto& a : listaArestas) {   // setta todos os vertices para branco
        a.first.first.setColor(color::BRANCO);
        a.first.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());  // copia do primeiro vertice da lista
    stack.push(raiz);   // poe o vertice na stack

    while(!stack.empty()) {
        auto current = stack.top();    // cópia do vertice da stack
        atualizarCorLista(current, color::CINZA);

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    branco = true;
                    break;
                }
            }
        }
        if(!branco) {
            atualizarCorLista(current, color::PRETO);
            cout << current.getData() << endl;
            stack.pop();
        }
        
        for(auto& a : listaArestas) {
            if(a.first.first == current){
                if(a.first.second.getColor() == color::BRANCO) {
                    atualizarCorLista(a.first.second, color::CINZA);
                    stack.push(a.first.second);
                }
            }
        }
    }
}

void Grafo::BFS() {
    queue<Vertice> queue;
    for(auto& a : listaArestas) {
        a.first.first.setColor(color::BRANCO);
        a.first.second.setColor(color::BRANCO);
    }

    auto raiz = *(listaVertices.begin());
    queue.push(raiz);

    while(!queue.empty()) {
        auto current = queue.front();
        atualizarCorLista(current, color::PRETO);

        bool branco = false;
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    branco = true;
                    break;
                }
            }
        }
        if(!branco)
            atualizarCorLista(current, color::PRETO);
        
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                if(a.first.second.getColor() == color::BRANCO) {
                    atualizarCorLista(a.first.second, color::CINZA);
                    queue.push(a.first.second);
                }
            }
        }
        queue.pop();
        cout << current.getData() << endl;
    }
}

list<pair<int, int>> Grafo::dijkstra() {
    // int qtd_fechados = listaVertices.size();
    list <pair<int, int>> caminhos; // pair<atual, anterior>
    typedef pair<int, Vertice> p;
    priority_queue<p, vector<p>, greater<p>> dist;
    for(auto& v : listaVertices) {
        v.setColor(color::BRANCO);
        v.setDistancia(INT_MAX/2);
        caminhos.push_back(make_pair(v.getIndex(), v.getIndex()));
    }

    auto& temp = *(listaVertices.begin());
    temp.setDistancia(0);
    auto current = *(listaVertices.begin());
    current.setColor(color::PRETO);
    current.setDistancia(0);
    dist.push(make_pair(0, current));

    while(!dist.empty()) {
        dist.pop();
        for(auto& a : listaArestas) {
            if(a.first.first == current) {
                for(auto& v : listaVertices) {
                    if(v == a.first.second && v.getDistancia() > current.getDistancia() + a.second) {
                        v.setDistancia(current.getDistancia() + a.second);
                        dist.push(make_pair(v.getDistancia(), v));
                        for(auto& c : caminhos) {
                            if(c.first == v.getIndex())
                                c.second = current.getIndex();
                        }
                    }
                }
            }
        }
        current = dist.top().second;
    }

    // for(auto& v : listaVertices)
    //     cout << v.getData() << " - " << v.getDistancia() << endl;
    return caminhos;
}

void Grafo::maze(int index1, int index2) {
    Vertice v1, v2;
    for(auto& v : listaVertices) {
        if(v.getIndex() == index1) {
            v1 = v;
        } else if(v.getIndex() == index2) {
            v2 = v;
        }
    }


}

void Grafo::atualizarCorLista(Vertice& v, color cor) {
    for(auto& a : listaArestas) {
        if(a.first.first == v) {
            a.first.first.setColor(cor);
        } else if(a.first.second == v) {
            a.first.second.setColor(cor);
        }
    }
}

void Grafo::imprimirCaminho(int index1, int index2, list<pair<int, int>> caminhos) {
    stack<int> stack;

    int current = index2;
    stack.push(current);
    while(current != index1) {
        for(auto& c : caminhos) {
            if(c.first == current) {
                stack.push(c.second);
                current = c.second;
                break;
            }
        }
    }

    cout << stack.top();
    stack.pop();
    while(!stack.empty()) {
        cout << " -> " << stack.top();
        stack.pop();
    }
}
