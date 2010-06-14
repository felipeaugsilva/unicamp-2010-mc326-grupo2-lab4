/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laborat�rio 04 - B-Tree
   
/******************************************************************************/

/* btree.h - Arquivo header para manipula��o da B-Tree */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "envelope.h"

#define tamPrimCampoHd 20
#define tamUltCampoHd 40
#define NIL     -1
#define NOKEY   -1
#define MAXORDEM 10
#define TAMCHAVE 6



/* Defini��o de tipo booleano */
typedef enum {false, true} Boolean;


/* Defini��o de um vetor de ponteiros para caractere. Uma vez inicializados,
   cada um dos ponteiros do vetor ir� apontar para a posi��o inicial do
   conte�do do campo[i] do registro correspondente. Caso seja necess�rio
   carregar mais de um registro do banco de dados na mem�ria, cada um de seus 
   campos poder� ser acessado por: registro[m].campo[n]   */
typedef char** Record;


/* Defini��o de estrutura que armazena as caracter�sticas de um campo de um
   arquivo de dados. Estas caracter�sticas devem ser extra�das de um arquivo de
   configura��o ou de uma se��o espec�fica do arquivo de dados */
typedef struct {
        char nome[tamPrimCampoHd+1];
        char tipo;
        int inicio;
        int tamanho;
        Boolean obrig;
        char msg[tamUltCampoHd+1];
        } Header;
        

/* Estrutura das chaves */
typedef struct {
        char vrChave[TAMCHAVE];     /* chave */
        int  RRNrecord;      /* RRN do registro no arquivo de dados */
        } CHAVE;


/* Estrutura de um n� da Btree */
typedef struct {
        int keycount;                /* n�mero de chaves no n� */
        CHAVE  key[MAXORDEM-1];      /* chaves */
        int child[MAXORDEM];         /* RRNs dos descendentes */
        } BTPAGE;

#define PAGESIZE sizeof(BTPAGE)



/*** Prot�tipos das Fun��es ***************************************************/

void AbreArquivoDados(char* nome, FILE** arqDados, FILE** arqCfg);
/* Abre o arquivo de dados e seu respectivo arquivo de configura��o (.cfg) */

void TiraBrancosDoFinal(char* s);
/* Elimina todos os brancos em excesso no final de uma string. */

void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg);
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

Record LeRegistro(FILE* arq, int n, Header* h);
/* Retorna um registro com 'n' campos lido em 'arq'.
   Retorna NULL se acabou o arquivo. */

void EscreveRegistro(Record rec, FILE* arq, int numcampos, Header* h);
/* Grava, na posi��o corrente em arq, os dados de rec */

void LiberaRegistro(Record registro, int n);
/* Libera todas as strings apontadas por record e tamb�m os apontadores */ 

void btread(short rrn, BTPAGE *page_ptr, FILE* btfd);
/* L� p�gina de n�mero 'rrn' do arquivo de �ndices */

void btwrite(short rrn, BTPAGE *page_ptr, FILE* btfd);
/* Escreve p�gina de n�mero 'rrn' no arquivo de �ndices */

short create_root(CHAVE key, short left, short right, FILE* btfd);
/* Cria a raiz da Btree, inserindo a chave 'key' */

short getpage(FILE* btfd);
/* Pega o pr�ximo bloco dispon�vel para uma nova p�gina */

//short getroot();
/* L� RRN da raiz */

Boolean insert(short rrn, CHAVE key, short *promo_r_child, CHAVE *promo_key,
                                       int ordem, Boolean *duplic, FILE* btfd);
/* Fun��o para inserir 'key' na Btree. Usa chamadas recursivas at� atingir uma
   folha e ent�o insere. Se o n� estiver cheio, chama split() para divid�-lo.
   Se as promo��es ocorrerem at� a raiz, coloca a chave do meio em 'promo_key'
   e seu filho direito em 'promo_r_child'. Se j� tiver uma chave igual no n�,
   seta duplic como true. */

void ins_in_page(CHAVE key, short r_child, BTPAGE *p_page);
/* Insere key e r_child em p_page */

void pageinit(BTPAGE *p_page);
/* Inicializa uma p�gina, colocando -1 em todos as chaves e NIL nos
   apontadores para os descendentes */

void putroot(short root, FILE* btfd);
/* Coloca RRN da raiz no inicio do arquivo de �ndices */

Boolean search_node(CHAVE key, BTPAGE *p_page, short *pos);
/* Retorna true se key est� no n� ou false caso contr�rio. Em qualquer caso
   coloca a posi��o correta da chave em pos */

void split(CHAVE key, short r_child, BTPAGE *p_oldpage, CHAVE *promo_key,
                short *promo_r_child, BTPAGE *p_newpage, int ordem, FILE* btfd);
/* Divide o n� criando um novo n� e passando metade das chaves para o novo n�.
   Promove a chave do meio e o RRN do novo n�. */                       


