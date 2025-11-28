// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura dos territórios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/**
 * Função de ataque entre dois territórios
 * @param atacante: ponteiro para o território atacante
 * @param defensor: ponteiro para o território defensor
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== ATAQUE ===\n");
    printf("%s (%s) ataca %s (%s)\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Valida se o ataque é contra território inimigo
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("ERRO: Nao pode atacar territorios da mesma cor!\n");
        return;
    }
    
    // Simula rolagem de dados (1-6) para atacante e defensor
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dado_atacante);
    printf("Dado do defensor: %d\n", dado_defensor);
    
    if (dado_atacante > dado_defensor) {
        // Atacante vence - conquista o território
        printf("VITORIA do atacante!\n");
        
        // Transfere cor e metade das tropas do defensor
        strcpy(defensor->cor, atacante->cor);
        int tropas_conquistadas = defensor->tropas / 2;
        defensor->tropas = tropas_conquistadas;
        
        printf("%s agora pertence a %s com %d tropas\n", 
               defensor->nome, defensor->cor, defensor->tropas);
        
    } else {
        // Defensor vence - atacante perde uma tropa
        printf("DERROTA do atacante!\n");
        atacante->tropas--;
        printf("%s perdeu 1 tropa. Agora tem %d tropas\n", 
               atacante->nome, atacante->tropas);
    }
}

/**
 * Função para liberar toda a memória alocada dinamicamente
 * @param territorios: vetor de ponteiros para territórios
 * @param missoes: vetor de strings com as missões
 * @param num_territorios: número de territórios alocados
 * @param num_jogadores: número de jogadores/missões
 */
void liberarMemoria(Territorio** territorios, char** missoes, int num_territorios, int num_jogadores) {
    // Libera memória dos territórios
    if (territorios != NULL) {
        for (int i = 0; i < num_territorios; i++) {
            if (territorios[i] != NULL) {
                free(territorios[i]);
            }
        }
        free(territorios);
    }
    
    // Libera memória das missões
    if (missoes != NULL) {
        for (int i = 0; i < num_jogadores; i++) {
            if (missoes[i] != NULL) {
                free(missoes[i]);
            }
        }
        free(missoes);
    }
    
    printf("Memoria liberada com sucesso!\n");
}

/**
 * Função para exibir informações de todos os territórios
 * @param territorios: vetor de ponteiros para territórios
 * @param num_territorios: número total de territórios
 */
void exibirTerritorios(Territorio** territorios, int num_territorios) {
    printf("\n=== ESTADO DOS TERRITORIOS ===\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("Territorio %d: %-15s | Cor: %-8s | Tropas: %2d\n", 
               i+1, territorios[i]->nome, territorios[i]->cor, territorios[i]->tropas);
    }
}

/**
 * Função para validar se um ataque é permitido
 * @param atacante: território atacante
 * @param defensor: território defensor
 * @return 1 se ataque válido, 0 se inválido
 */
int ataqueValido(Territorio* atacante, Territorio* defensor) {
    // Verifica se são o mesmo território
    if (strcmp(atacante->nome, defensor->nome) == 0) {
        printf("ERRO: Nao pode atacar o proprio territorio!\n");
        return 0;
    }
    
    // Verifica se são da mesma cor (aliados)
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("ERRO: Nao pode atacar territorios aliados!\n");
        return 0;
    }
    
    // Verifica se o atacante tem tropas suficientes
    if (atacante->tropas <= 1) {
        printf("ERRO: Atacante nao tem tropas suficientes!\n");
        return 0;
    }
    
    return 1;
}

int main() {
    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    int num_territorios = 6;
    int num_jogadores = 2;
    
    // Alocação dinâmica do vetor de territórios
    Territorio** territorios = (Territorio**)malloc(num_territorios * sizeof(Territorio*));
    if (territorios == NULL) {
        printf("Erro na alocacao de memoria para territorios!\n");
        return 1;
    }
    
    // Alocação dinâmica de cada território individual
    for (int i = 0; i < num_territorios; i++) {
        territorios[i] = (Territorio*)malloc(sizeof(Territorio));
        if (territorios[i] == NULL) {
            printf("Erro na alocacao de memoria para territorio %d!\n", i);
            return 1;
        }
    }
    
    // Alocação dinâmica do vetor de missões
    char** missoes = (char**)malloc(num_jogadores * sizeof(char*));
    if (missoes == NULL) {
        printf("Erro na alocacao de memoria para missoes!\n");
        return 1;
    }
    
    // Alocação dinâmica de cada missão individual
    for (int i = 0; i < num_jogadores; i++) {
        missoes[i] = (char*)malloc(50 * sizeof(char));
        if (missoes[i] == NULL) {
            printf("Erro na alocacao de memoria para missao %d!\n", i);
            return 1;
        }
    }
    
    // Inicialização dos territórios
    // Time Vermelho
    strcpy(territorios[0]->nome, "America do Norte");
    strcpy(territorios[0]->cor, "Vermelho");
    territorios[0]->tropas = 5;
    
    strcpy(territorios[1]->nome, "America do Sul");
    strcpy(territorios[1]->cor, "Vermelho");
    territorios[1]->tropas = 3;
    
    strcpy(territorios[2]->nome, "Africa");
    strcpy(territorios[2]->cor, "Vermelho");
    territorios[2]->tropas = 4;
    
    // Time Azul
    strcpy(territorios[3]->nome, "Europa");
    strcpy(territorios[3]->cor, "Azul");
    territorios[3]->tropas = 6;
    
    strcpy(territorios[4]->nome, "Asia");
    strcpy(territorios[4]->cor, "Azul");
    territorios[4]->tropas = 7;
    
    strcpy(territorios[5]->nome, "Oceania");
    strcpy(territorios[5]->cor, "Azul");
    territorios[5]->tropas = 2;
    
    // Inicialização das missões
    strcpy(missoes[0], "Conquistar 3 territorios azuis");
    strcpy(missoes[1], "Conquistar 3 territorios vermelhos");
    
    // Exibe estado inicial
    printf("=== WAR GAME SIMULATOR ===\n");
    exibirTerritorios(territorios, num_territorios);
    
    // Exibe missões
    printf("\n=== MISSOES ===\n");
    for (int i = 0; i < num_jogadores; i++) {
        printf("Jogador %d: %s\n", i+1, missoes[i]);
    }
    
    // Simulação de ataques
    printf("\n=== SIMULACAO DE ATAQUES ===\n");
    
    // Ataque válido: territórios de cores diferentes
    if (ataqueValido(territorios[0], territorios[3])) {
        atacar(territorios[0], territorios[3]);
    }
    
    // Ataque inválido: mesmo território
    if (ataqueValido(territorios[1], territorios[1])) {
        atacar(territorios[1], territorios[1]);
    }
    
    // Ataque inválido: territórios da mesma cor
    if (ataqueValido(territorios[0], territorios[1])) {
        atacar(territorios[0], territorios[1]);
    }
    
    // Outro ataque válido
    if (ataqueValido(territorios[4], territorios[2])) {
        atacar(territorios[4], territorios[2]);
    }
    
    // Exibe estado final
    exibirTerritorios(territorios, num_territorios);
    
    // Libera toda a memória alocada
    liberarMemoria(territorios, missoes, num_territorios, num_jogadores);
    
    return 0;
}