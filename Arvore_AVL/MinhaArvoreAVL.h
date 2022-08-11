#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
    public:
    MinhaArvoreAVL(){};
    
    int get_b(Nodo<T>* root) {
        int h_esquerda = -1;
        int h_direita = -1;
        if(root->filhoEsquerda != nullptr)
            h_esquerda = root->filhoEsquerda->altura;

        if(root->filhoDireita != nullptr)
            h_direita = root->filhoDireita->altura;

        return h_esquerda - h_direita;
    };

    void r_esq(Nodo<T>* pai, Nodo<T>* root){
        Nodo<T>* filho = pai->filhoDireita;

        pai->filhoDireita = filho->filhoEsquerda;
        filho->filhoEsquerda = pai;

        if(pai != this->_raiz){
            if(root->chave > filho->chave){
                root->filhoEsquerda = filho;
            }else{
                root->filhoDireita = filho;
            }
        }else{
            this->_raiz = filho;
        }
    };

    void r_dir(Nodo<T>* pai, Nodo<T>* root){
        Nodo<T>* filho = pai->filhoEsquerda;

        pai->filhoEsquerda = filho->filhoDireita;
        filho->filhoDireita = pai;

        if(pai != this->_raiz){
            if(root->chave > filho->chave){
                root->filhoEsquerda = filho;
            }else{
                root->filhoDireita = filho;
            }
        }else{
            this->_raiz = filho;
        }
    };

    void r_esq_dir(Nodo<T>* pai, Nodo<T>* root){
        Nodo<T>* filho = pai->filhoEsquerda;
        Nodo<T>* neto = filho->filhoDireita;

        filho->filhoDireita = neto->filhoEsquerda;
        neto->filhoEsquerda = filho;
        pai->filhoEsquerda = neto->filhoDireita;
        neto->filhoDireita = pai;

        if(pai != this->_raiz){
            if(root->chave > neto->chave){
                root->filhoEsquerda = neto;
            }else{
                root->filhoDireita = neto;
            }
        }else{
            this->_raiz = neto;
        }
    };

    void r_dir_esq(Nodo<T>* pai, Nodo<T>* root){
        Nodo<T>* filho = pai->filhoDireita;
        Nodo<T>* neto = filho->filhoEsquerda;

        filho->filhoEsquerda = neto->filhoDireita;
        neto->filhoDireita = filho;
        pai->filhoDireita = neto->filhoEsquerda;
        neto->filhoEsquerda = pai;

        if(pai != this->_raiz){
            if(root->chave > neto->chave){
                root->filhoEsquerda = neto;
            }else{
                root->filhoDireita = neto;
            }
        }else{
            this->_raiz = neto;
        }
    };
    
    int minha_altura(Nodo<T>* root) const{
        if(root == nullptr){
            return -1;
        }else{
            root->altura = std::max(minha_altura(root->filhoEsquerda),minha_altura(root->filhoDireita)) + 1;
            return root->altura;
        }
    };
    
    int avalia_b(T chave, Nodo<T>* n_pai, Nodo<T>* root = nullptr){
        int b_filho;
        if(n_pai == nullptr){
            if(root->filhoEsquerda == n_pai){
                if(root->filhoDireita != nullptr)
                return get_b(root->filhoDireita);
            }else{
                if(root->filhoEsquerda != nullptr)
                return get_b(root->filhoEsquerda);
            }
            return 0;
        }else if(n_pai->chave == chave){
            return 0;
        }else{
            if(n_pai->chave > chave){
                b_filho = avalia_b(chave, n_pai->filhoEsquerda, n_pai);
            }else{
                b_filho = avalia_b(chave, n_pai->filhoDireita, n_pai);
            }
        }
        if(b_filho == 10) //Caso já tenha ocorrido a rotação
        return 10;

        int b_pai = get_b(n_pai);
        if(b_pai > 1 || b_pai < -1){
            if(b_pai > 1){
                if(b_filho < 0){    //b_pai = 2 e b_filho < 0
                    r_esq_dir(n_pai, root);
                }else{              //b_pai = 2 e b_filho >= 0
                    r_dir(n_pai, root);
                }
            }else{
                if(b_filho > 0){    //b_pai = -2 e b_filho > 0
                    r_dir_esq(n_pai, root);
                }else{              //b_pai = -2 e b_filho <= 0
                    r_esq(n_pai, root);
                }
            }
            return 10; //Quando ocorre rotação
        }
        return b_pai;        
    };

    void inserir(T chave){
        MinhaArvoreDeBuscaBinaria<T>::inserir(chave);
        avalia_b(chave, this->_raiz);
        minha_altura(this->_raiz);
    };

    void remover(T chave){
        MinhaArvoreDeBuscaBinaria<T>::remover(chave);
        if(!this->vazia()){
            avalia_b(chave, this->_raiz);
            minha_altura(this->_raiz);
        }
    };
};

#endif