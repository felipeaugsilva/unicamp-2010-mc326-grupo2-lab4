/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laboratório 04 - B-Tree
   
/******************************************************************************/



#include "btree.h"


int create_root(char key, int left, int right) {
           BTPAGE page;
           int rrn;
           rrn = getpage();
           pageinit(&page);
           page.key[0] = key;
           page.child[0] = left;
           page.child[1] = right;
           page.keycount = 1;
           btwrite(rrn, &page);
           putroot(rrn);
           return (rrn);
}

void pageinit(BTPAGE *p_page) {        /* p_page: pointer to a page  */
           int j;
           for(j = 0; j < MAXKEYS; j++) {
                 p_page->key[j] = NOKEY;
                 p_page->child[j] = NIL;      
           }
           p_page->child[j] = NIL;      
}

Boolean search_node(char key, BTPAGE *p_page, int *pos) {
                 /* pos: position where key is or should be inserted */
           
           int i;
           for(i=0; i < p_page->keycount && key > p_page->key[i]; i++);
           *pos = i;
           
           if(*pos < p_page->keycount && key == p_page->key[*pos])
                   return true;      /* key in in the page */
           else return false;          /* key in not in the page */
}

void ins_in_page(char key, int r_child, BTPAGE *p_page) {
           int i;
           for(i = p_page->keycount; key < p_page->key[i-1] && i > 0; i--){
                 p_page->key[i] = p_page->key[i-1];
                 p_page->child[i+1] = p_page->child[i];
           }
           p_page->keycount++;
           p_page->key[i] = key;
           p_page->child[i+1] = r_child;
}
