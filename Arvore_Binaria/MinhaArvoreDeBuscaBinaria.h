#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.h"
#include <cassert>
#include <utility>
#include <vector>

/**
 * @brief Representa uma árvore binária de busca.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>{

    public:

    // Construtor
    
    MinhaArvoreDeBuscaBinaria(){
        this->_raiz = nullptr;
    };

    bool vazia() const{
        if(this->_raiz == nullptr)
        return true;

        return false;
    };

    int quantidade() const{
        if(vazia())
        return 0;

        int counter = 1;
        MinhaListaEncadeada<Nodo<T> *> *lista = new MinhaListaEncadeada<Nodo<T>*>();
        Nodo<T> *aux = this->_raiz;
        lista->inserirNoInicio(aux);

        while(!lista->vazia()){
            if(aux->filhoEsquerda != nullptr){
                if(aux->filhoDireita != nullptr){
                    counter += 2;
                    lista->inserirNoInicio(aux->filhoEsquerda);
                    lista->inserirNoInicio(aux->filhoDireita);
                }else{
                    counter++;
                    lista->inserirNoInicio(aux->filhoEsquerda);
                }
            }else if(aux->filhoDireita != nullptr){
                counter++;
                lista->inserirNoInicio(aux->filhoDireita);
            }
            aux = lista->removerDoInicio();
        }
        delete lista;
        return counter;
    };

    bool contem(T chave) const{
        Nodo<T> *atual = this->_raiz;
        while(atual != nullptr){
            if(atual->chave == chave){
                return true;
            }else {
                if(atual->chave > chave){
                    atual = atual->filhoEsquerda;
                }else{
                    atual = atual->filhoDireita;
                }
            }
        }
        return false;
    };

    // Altura

    std::optional<int> altura(T chave) const{
        if(!contem(chave)){
            return std::nullopt;
        }

        Nodo<T> *atual = this->_raiz;
        while(atual->chave != chave){
            if(atual->chave > chave){
                atual = atual->filhoEsquerda;
            }else {
                atual = atual->filhoDireita;
            }
        }
        return atual->altura;
    };

    // Inserir

    int inserir_rec(T chave, Nodo<T>* root){
        int alt_atual = 1;
        
        if(root == nullptr){
            this->_raiz = new Nodo<T>();
            this->_raiz->chave = chave;
            return 0;
        }else{
            if(root->chave > chave){
                if(root->filhoEsquerda != nullptr)
                alt_atual = inserir_rec(chave, root->filhoEsquerda) + 1;
                else{
                    root->filhoEsquerda = new Nodo<T>();
                    root->filhoEsquerda->chave = chave;
                }                
            }else{
                if(root->filhoDireita != nullptr)
                alt_atual = inserir_rec(chave, root->filhoDireita) + 1;
                else{
                    root->filhoDireita = new Nodo<T>();
                    root->filhoDireita->chave = chave;
                }
            }
        }
        if(root->altura < alt_atual)
        root->altura = alt_atual;

        return alt_atual; 
    };


    void inserir(T chave){
        inserir_rec(chave, this->_raiz);
    };

    // Remover

    void remover_rec(T chave, Nodo<T>* subraiz, Nodo<T>* pai = nullptr){
        bool ver_alt = true;
        if(subraiz->chave == chave){
            if(subraiz->filhoDireita == nullptr){
                if(subraiz != this->_raiz){
                    if(pai->chave > chave){
                        pai->filhoEsquerda = subraiz->filhoEsquerda;
                    }else{
                        pai->filhoDireita = subraiz->filhoEsquerda;
                    }
                }else{
                    this->_raiz = subraiz->filhoEsquerda;
                }
                delete subraiz;
                ver_alt = false;
            }else{
                pai = subraiz;
                Nodo<T>* aux = subraiz->filhoDireita;
                while(aux->filhoEsquerda != nullptr){
                    pai = aux;
                    aux = aux->filhoEsquerda;
                }
                subraiz->chave = aux->chave;
                remover_rec(aux->chave, aux, pai);
            }
        }else{
            pai = subraiz;
            if(subraiz->chave > chave){
                subraiz = subraiz->filhoEsquerda;
            }else{
                subraiz = subraiz->filhoDireita;
            }
            remover_rec(chave, subraiz, pai);
          }
        if(ver_alt){
            if(pai->filhoEsquerda != nullptr){
                if(pai->filhoDireita != nullptr){
                    pai->altura = std::max(pai->filhoEsquerda->altura, pai->filhoDireita->altura) + 1;
                }else{
                    pai->altura = pai->filhoEsquerda->altura + 1;
                }
            }else if(pai->filhoDireita != nullptr){
                pai->altura = pai->filhoDireita->altura + 1;
            }else{
                pai->altura = 0;
            }
        }
    };
    
    void remover(T chave){
        if(contem(chave))
        remover_rec(chave, this->_raiz);
    };

    // Filho Esquerda e Direita
    
    std::optional<T> filhoEsquerdaDe(T chave) const{
        if(!contem(chave))
        return std::nullopt;

        Nodo<T>* atual = this->_raiz;
        while(atual->chave != chave){
            if(atual->chave > chave){
                atual = atual->filhoEsquerda;
            }else{
                atual = atual->filhoDireita;
            }
        }

        if(atual->filhoEsquerda == nullptr)
        return std::nullopt;

        return atual->filhoEsquerda->chave;
    };

    std::optional<T> filhoDireitaDe(T chave) const{
        if(!contem(chave))
        return std::nullopt;

        Nodo<T>* atual = this->_raiz;
        while(atual->chave != chave){
            if(atual->chave > chave){
                atual = atual->filhoEsquerda;
            }else{
                atual = atual->filhoDireita;
            }
        }

        if(atual->filhoDireita == nullptr)
        return std::nullopt;

        return atual->filhoDireita->chave;
    };

    // Ordenadores

    void a_emOrdem(Nodo<T>* root, MinhaListaEncadeada<T>* lista) const{
        if(root != nullptr){
            a_emOrdem(root->filhoEsquerda, lista);
            lista->inserirNoFim(root->chave);
            a_emOrdem(root->filhoDireita, lista);
        }
    };

    ListaEncadeadaAbstrata<T> *emOrdem() const{
        MinhaListaEncadeada<T>* m_lista = new MinhaListaEncadeada<T>();
        a_emOrdem(this->_raiz, m_lista);

        return m_lista;
    };

    void a_preOrdem(Nodo<T>* root, MinhaListaEncadeada<T>* lista) const{
        if(root != nullptr){
            lista->inserirNoFim(root->chave);
            a_preOrdem(root->filhoEsquerda, lista);
            a_preOrdem(root->filhoDireita, lista);
        }
    };

    ListaEncadeadaAbstrata<T> *preOrdem() const{
        MinhaListaEncadeada<T>* m_lista = new MinhaListaEncadeada<T>();
        a_preOrdem(this->_raiz, m_lista);

        return m_lista;
    };

    void a_posOrdem(Nodo<T>* root, MinhaListaEncadeada<T>* lista) const{
        if(root != nullptr){
            a_posOrdem(root->filhoEsquerda, lista);
            a_posOrdem(root->filhoDireita, lista);
            lista->inserirNoFim(root->chave);
        }
    };

    ListaEncadeadaAbstrata<T> *posOrdem() const{
        MinhaListaEncadeada<T>* m_lista = new MinhaListaEncadeada<T>();
        a_posOrdem(this->_raiz, m_lista);

        return m_lista;
    };

    // Destrutor

    ~MinhaArvoreDeBuscaBinaria(){
        while(!vazia()){
            remover(this->_raiz->chave);
        }
    };
};

#endif