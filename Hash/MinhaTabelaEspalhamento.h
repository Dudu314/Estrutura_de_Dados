#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template<typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, _capacidade>
{
    public:
    MinhaTabelaEspalhamento(){};


    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    std::size_t capacidade() const{
        return _capacidade;
        };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    void inserir(T dado){
        if(!contem(dado)){
            size_t ind = funcaoEspalhamento(dado);
            this->_tabela[ind].inserirNoFim(dado);
        }
    };
    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
    void remover(T dado){
        if(!contem(dado)){
            throw ExcecaoDadoInexistente();
        }
        size_t ind = funcaoEspalhamento(dado);
        this->_tabela[ind].remover(dado);
    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    bool contem(T dado) const{
        size_t ind = funcaoEspalhamento(dado);
        bool contem_l = this->_tabela[ind].contem(dado);
        return contem_l;
    };

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t quantidade() const{
        size_t total = 0;
        for(size_t i = 0; i < _capacidade; i++){
            size_t tamanho_l = this->_tabela[i].tamanho();
            total += tamanho_l;
        }
        return total;
        };

    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    std::size_t funcaoEspalhamento(T dado) const{
        int total_dado = 0;
        std::string s;
        s = dado;
        for(size_t i = 0; i < s.length(); i++){
            int letter = s[i];
            total_dado += letter;
        };
        return total_dado % _capacidade;
    };

    ~MinhaTabelaEspalhamento(){};
};

#endif