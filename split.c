/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laboratório 04 - B-Tree
   
/******************************************************************************/

/* btutil.c...
   Contains split() function for btree program:
            
          -- split node by creating new node and moving half of the keys
                    to new node. Promote middle key and rrn of new node.
                    
          Arguments:
              key:               key to be inserted
              promo_key:         key to be promoted up from here
              r_child:           child rrn to be inserted
              promo_r_child:     rrn to be promoted up from here
              p_oldpage          pointer to old page structure
              p_newpage          pointer to new page structure                       
*/

#include "btree.h"

void split(CHAVE key, short r_child, BTPAGE *p_oldpage, CHAVE *promo_key,
                short *promo_r_child, BTPAGE *p_newpage, int ordem, FILE* btfd){

      int MAXKEYS = ordem - 1;
      int MINKEYS = MAXKEYS / 2;
      int i;
int j;
      int mid;                                                                       /* tells where split is to occur            */
      CHAVE workkeys[MAXKEYS+1];                                                     /* temporarily holds keys, before split     */
      int workch[MAXKEYS+2];                                                         /* temporarily holds children, before split */
      
      for(i=0; i < MAXKEYS; i++) {                                                   /* move keys and children from*/
               memmove(&workkeys[i], &p_oldpage->key[i], sizeof(CHAVE));             /*old page into work arrays   */
               workch[i] = p_oldpage->child[i];
      }
      workch[i] = p_oldpage->child[i];
      for(i = MAXKEYS; strcmp(key.vrChave, workkeys[i-1].vrChave) < 0 && i > 0; i--){/* insert new key  */
               memmove(&workkeys[i], &workkeys[i-1], sizeof(CHAVE));
               workch[i+1] = workch[i];
      }
      memmove(&workkeys[i], &key, sizeof(CHAVE));

printf("\n***Em SPLIT: Chave inserida=%s\nworkArray:", key.vrChave);
for(j=0; j < MAXKEYS+1; j++) printf("[%d] %6s ", j, &workkeys[j].vrChave);
printf("\n\noldpage  :");

      workch[i+1] = r_child;
      
      *promo_r_child = getpage(btfd);                                             /* create new page for split      */
      pageinit(p_newpage, ordem);                                                        /* and promote rrn of new page    */
      
      for(i=0; i < MINKEYS; i++) {                                                /* move first half of keys   */
               memmove(&p_oldpage->key[i], &workkeys[i], sizeof(CHAVE));          /* and children to old page, */
               p_oldpage->child[i] = workch[i];                                   /* second half to new page   */
               memmove(&p_newpage->key[i], &workkeys[i+1+MINKEYS], sizeof(CHAVE));
               p_newpage->child[i] = workch[i+1+MINKEYS];
               memset (p_oldpage->key[i+MINKEYS].vrChave, NOKEY, TAMCHAVE);       /* mark second half of */
               p_oldpage->child[i+1+MINKEYS] = NIL;                               /* old page as empty   */
      }

memmove(&p_newpage->key[i], &workkeys[i+1+MINKEYS], sizeof(CHAVE));
p_newpage->child[i] = workch[i+1+MINKEYS];


      p_oldpage->child[MINKEYS] = workch[MINKEYS];
      p_newpage->child[MINKEYS] = workch[i+1+MINKEYS];
      p_newpage->keycount = MAXKEYS - MINKEYS;
      p_oldpage->keycount = MINKEYS;      
      memmove(promo_key, &workkeys[MINKEYS],sizeof(CHAVE));                       /* promote middle key   */


for(j=0; j < MAXKEYS+1; j++) printf("[%d] %6s ", j, &p_oldpage->key[j].vrChave);
printf("\nKeyCount: %d\n\n", p_oldpage->keycount);
printf("newpage  :");
for(j=0; j < MAXKEYS+1; j++) printf("[%d] %6s ", j, &p_newpage->key[j].vrChave);
printf("\nKeyCount: %d\n\n", p_newpage->keycount);
printf("Chave promovida=%s\n", promo_key->vrChave);
//system("pause");






} /* split */
