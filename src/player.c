#include "../headers/player.h"

/*
    OBJETIVO: Verificar se 'player' está alocado corretamente.
    ENTRADAS: Ponteiro para 'player'.
    SAIDA: 1 quando é nulo, 2 quando a mão é nula, 3 quando o próximo é nulo, 0 quando tá safe.
    PRE-CONDICAO: -
    POS-CONDICAO: Nada é alterado.
*/
char invalido(tPlayer *player){
    if(player == NULL) return 1;
    if(player->mao == NULL) return 2;
    if(player->proximo == NULL) return 3;
    return 0;
}

/*
    OBJETIVO: Funcao que seta a quantidade de pontos de um player.
    ENTRADAS: Ponteiro tPLayer* para 'player alvo' e uma Variavel char para 'pontos'.
    SAIDA: -
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: Quantidade de pontos atribuida ao jogador.
*/
void pSetPontos(tPlayer *player, char pontos){
    if(player != NULL)
        player->points = pontos;
}

/*
    OBJETIVO: Funcao que retorna a quantidade de pontos de um player.
    ENTRADAS: Ponteiro tPLayer* para 'player alvo'.
    SAIDA: Pontuacao de um player dado.
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: Nada alterado.
*/
char pGetPontos(tPlayer *player){
    if(player != NULL)
        return player->points;
    return 0;
}

/*
    OBJETIVO: Funcao que seta o ID de um player (humano ou bot).
    ENTRADAS: Ponteiro tPLayer* para 'player' e uma Variavel char para dizer que eh humano.
    SAIDA: -
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: ID humano atribuido ao jogador.
*/
void pSetId(tPlayer *player, char humano){
    if(player != NULL)
        player->Id = humano;
}

/*
    OBJETIVO: Funcao que retorna ID de um player.
    ENTRADAS: Ponteiro tPLayer* para 'player alvo'.
    SAIDA: ID de um player dado.
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: Nada alterado.
*/
char pGetId(tPlayer *player){
    if(player != NULL)
        return player->Id;
    return 0;
}

/*
    OBJETIVO: Funcao que seta qual sera a proxima celula.
    ENTRADAS: Ponteiro tPLayer* para 'player' e Ponteiro tPLayer* para 'proximo player'.
    SAIDA: -
    PRE-CONDICAO: Player atual e o proximo existirem.
    POS-CONDICAO: O proximo do Player de entrada ser o Player 'proximo' tambem da entrada.
*/
void pSetProximo(tPlayer *player, tPlayer *proximo){
    if(player != NULL)
        player->proximo = proximo;
}

/*
    OBJETIVO: Funcao que retorna o proximo player de uma celula na lista.
    ENTRADAS: Ponteiro tPLayer* para 'player alvo'.
    SAIDA: Ponteiro tPLayer* para 'proximo player'.
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: Proximo player retornado.
*/
tPlayer* pGetProximo(tPlayer *player){
    if(player != NULL)
        return player->proximo;
    return NULL;
}

/*
    OBJETIVO: Funcao que seta a 'mao' do jogador.
    ENTRADAS: Ponteiro tPLayer* para 'player' e Ponteiro tDeck* para 'mao'.
    SAIDA: -
    PRE-CONDICAO: Player atual e o deck da mao existirem.
    POS-CONDICAO: Mao do jogador ser o deck passado na entrada.
*/
void pSetMao(tPlayer *player, tDeck *mao){
    if(player != NULL)
        player->mao = mao;
}

/*
    OBJETIVO: Funcao que retorna a 'mao' do jogador.
    ENTRADAS: Ponteiro tPLayer* para 'player alvo'.
    SAIDA: Ponteiro tDeck* para 'mao'.
    PRE-CONDICAO: Player existir.
    POS-CONDICAO: Mao do jogador retornada.
*/
tDeck* pGetMao(tPlayer *player){
    if(player != NULL)
        return player->mao;
    return NULL; 
}

/*
    OBJETIVO: Iniciar 'Player' vazio corretamente.
    ENTRADAS: -
    SAIDA: Ponteiro para tPlayer, apontando para o jogador criado.
    PRE-CONDICAO: -
    POS-CONDICAO: Inicializado, porém sem elementos, ou zerados.
*/
tPlayer* iniciaPlayerVazio(int i){
    tPlayer *player = (tPlayer*) malloc(sizeof(tPlayer));
    pSetPontos(player, 0);
    pSetProximo(player, NULL);
    pSetMao(player, iniciaVazio());
    pSetId(player, i);
    
    return player;
}

/*
    OBJETIVO: Iniciar 'n' quantidades de tPlayers vazios corretamente.
    ENTRADAS: A quantidade de players a ser inicializada.
    SAIDA: Ponteiro para tPlayer, apontando para o jogador criado.
    PRE-CONDICAO: n > 0.
    POS-CONDICAO: Inicializados, porém sem elementos, ou zerados.
*/
tPlayer* iniciaNPlayers(int n){
    if(n < 1)
        return NULL;
    tPlayer *cabeca, *atual;
    cabeca = atual = iniciaPlayerVazio(0);
    for(int i = 1; i < n; i++){
        atual->proximo = iniciaPlayerVazio(i);   //percorre criando os outros N players
        atual = atual->proximo;
    }   
    atual->proximo = cabeca;    //faz a lista ficar circular;

    tPlayer *aux = cabeca;
    do{
        printf("ID DO ALOCADO: %d\n", pGetId(aux));
        aux = pGetProximo(aux);
    }while(aux != cabeca);

    return cabeca;
}

/*
    OBJETIVO: Imprimir 'mao' na tela.
    ENTRADAS: Ponteiro para 'player'.
    SAIDA: -
    PRE-CONDICAO: 'deck' existe e está alocado corretamente.
    POS-CONDICAO: Nada é alterado.
*/
void imprimeMao(tPlayer *player){
    if(player != NULL)
        imprimeDeck(pGetMao(player));
}

/*
    OBJETIVO: Faz 'player' compra a carta do topo de 'deck'.
    ENTRADAS: Ponteiro para 'player' e ponteiro para 'deck'.
    SAIDA: -
    PRE-CONDICAO: 'deck' existe e está alocado corretamente, o mesmo para player.
    POS-CONDICAO: Nada é alterado.
*/
void compraCarta(tPlayer *player, tDeck *deck){
    if(invalido(player) == 1) return;
    if(invalido(player) == 2) pSetMao(player, iniciaVazio());

    transfereCelula(pGetMao(player), deck, 0);
}

/*
    OBJETIVO: Faz 'player' jogar a carta da posição 'n' da sua mão em 'deck'.
    ENTRADAS: Ponteiro para 'player' e ponteiro para 'deck' e a posição da carta.
    SAIDA: -
    PRE-CONDICAO: 'deck' existe e está alocado corretamente, o mesmo para player.
    POS-CONDICAO: Nada é alterado.
    OBS: 'n' É EM CONTAGEM NATURAL, E NÃO 'ÍNDICE DE VETOR'!!
*/
void jogaCarta(tPlayer *player, tDeck *deck, int n){
    if(invalido(player) == 1 || invalido(player) == 2) 
        return;
    // printf("Quantidade na mao = %d\n", player->mao->quantidade);
    if(player->mao->quantidade < n){
        printf("\nA mao nao tem essa quantidade de cartas!\n");
        return;
    }

    transfereCelula(deck, pGetMao(player), n -1);
}

/*
    OBJETIVO: Desalocar toda a memória ocupada por 'player'.
    ENTRADAS: Ponteiro para 'player'.
    SAIDA: -
    PRE-CONDICAO: 'player' existe e está alocado corretamente.
    POS-CONDICAO: 'player' não ocupa mais espaço no HEAP e aponta para NULL.
*/
void destroiPlayers(tPlayer *player){
    if(player == NULL)
        return;

    tPlayer *aux = player;
    tPlayer *anterior = NULL;
    do{
        destroiDeck(aux->mao);
        anterior = aux;
        aux = aux->proximo;
        free(anterior);
    } while(aux != player);
}