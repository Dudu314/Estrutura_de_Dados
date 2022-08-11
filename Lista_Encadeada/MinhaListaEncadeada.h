#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    //Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    //Lembre-se de implementar o construtor e destrutor da classe
    
    public:
    MinhaListaEncadeada(){
        this->_tamanho = 0;
        this->_primeiro = nullptr;
    };

    std::size_t tamanho() const{
        return this->_tamanho;
    };
    
    bool vazia() const{
        if(tamanho() == 0)
        return true;
        
        return false;
    }
    
    std::size_t posicao(T dado) const{
        if(vazia())
        throw ExcecaoListaEncadeadaVazia();
            
        Elemento<T>* atual = this->_primeiro;
        
        if(atual->dado == dado){
            return 0;
        }
        
        for(size_t i = 0; i < tamanho(); i++){
            if(atual->dado == dado){
                return i;
            }
            atual = atual->proximo;
        }
        throw ExcecaoDadoInexistente();
    }
    
    bool contem(T dado) const{
        Elemento<T>* atual = this->_primeiro;

        for(size_t i = 0; i < tamanho(); i++){
            if(atual->dado == dado){
                return true;
            }
            atual = atual->proximo;
        }
        return false;
    }
    
    void inserirNoInicio(T dado){
        Elemento<T>* novo = new Elemento<T>(dado,this->_primeiro);
        
        this->_primeiro = novo;
        this->_tamanho++;
    }
    
    void inserir(std::size_t posicao, T dado){
        if(posicao < 0 || posicao > tamanho())
        throw ExcecaoPosicaoInvalida();
        
        Elemento<T>* atual = this->_primeiro;
        Elemento<T>* novo = new Elemento<T>(dado,nullptr);

        if(atual == nullptr){
            this->_primeiro = novo;
        }else if(posicao == 0){
            novo->proximo = atual;
            this->_primeiro = novo;
        }else{
            for(size_t i = 1; i < posicao; i++){
                atual = atual->proximo;
            }
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
        this->_tamanho++;
    }
    
    void inserirNoFim(T dado){
        Elemento<T>* novo = new Elemento<T>(dado,this->_primeiro);

        if(this->_primeiro == nullptr){
            this->_primeiro = novo;
        }else{
            while(novo->proximo->proximo != nullptr){
                novo->proximo = novo->proximo->proximo;
            }
            novo->proximo->proximo = novo;
            novo->proximo = nullptr;
        }
        this->_tamanho++;
    }
    
    T removerDoInicio(){
        if(vazia())
        throw ExcecaoListaEncadeadaVazia();        
        
        Elemento<T>* trash;
        trash = this->_primeiro;

        T myDado = this->_primeiro->dado;
        this->_primeiro = this->_primeiro->proximo;
        
        delete trash;
        this->_tamanho--;

        return myDado;
    }
    
    T removerDe(std::size_t posicao){
        if(posicao < 0 || posicao >= this->_tamanho)
        throw ExcecaoPosicaoInvalida();
            
        Elemento<T>* atual = this->_primeiro;
        Elemento<T>* trash;
        
        T myDado;
        if(posicao == 0) {
            trash = atual;
            myDado = atual->dado;
            this->_primeiro = atual->proximo;
        }else{
            for(size_t i = 1; i < posicao; i++){
                atual = atual->proximo;
            }

            trash = atual->proximo;
            myDado = atual->proximo->dado;
            atual->proximo = atual->proximo->proximo;
        }

        delete trash;
        this->_tamanho--;

        return myDado;
    }
    
    T removerDoFim(){
        if(vazia())
        throw ExcecaoListaEncadeadaVazia();
            
        Elemento<T>* atual = this->_primeiro;
        Elemento<T>* trash;
        
        for(size_t i = 2; i < tamanho(); i++){
            atual = atual->proximo;
        }
        
        T myDado;
        
        if(atual->proximo == nullptr){
            trash = atual;
            myDado = atual->dado;
            this->_primeiro = nullptr;
        }else{
            trash = atual->proximo;
            myDado = atual->proximo->dado;
            atual->proximo = atual->proximo->proximo;
        }

        delete trash;
        this->_tamanho--;

        return myDado;
    }
    
    void remover(T dado){
        if(vazia())
        throw ExcecaoListaEncadeadaVazia();
            
        Elemento<T>* atual = this->_primeiro;
        Elemento<T>* trash{nullptr};
        
        bool existente = false;

        if(atual->dado == dado){
            trash = atual;
            this->_primeiro = atual->proximo;

            existente = true;
        }else{
            for(size_t i = 2; i < tamanho(); i++){
                if(atual->proximo->dado == dado){
                    trash = atual->proximo;
                    atual->proximo = atual->proximo->proximo;

                    existente = true;
                    i += this->_tamanho;
                }
                atual = atual->proximo;
            }
        }

        if(trash != nullptr)
            delete trash;
             
        if(!existente)
            throw ExcecaoDadoInexistente();

        this->_tamanho--;        
    }
    
    ~MinhaListaEncadeada(){
        while(!vazia()){
            removerDoInicio();
        }
    };
};

#endif