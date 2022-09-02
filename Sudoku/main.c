#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printarTabuleiro(int tabuleiro[9][9]);

int menu(){
    int opcao;
    
    printf("----BEM VINDO AO SUDOKU----\n");
    printf("1-Carregar jogo \n2-Novo Jogo Aleatorio \n3-Sair\n");
    scanf("%d", &opcao);
    if (opcao != 1 && opcao != 2 && opcao != 3 ){
        system("clear");
        printf("OPCAO INVALIDA\n");
        opcao = menu();
    }
    return opcao;
}


void lerArquivo(FILE * table, int jogo[9][9], int jogoResolvido[9][9]){

    char c;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(table,"%c", &c);
            if(c == '.'){
                jogo[i][j] = 0;

            }else{
                jogo[i][j] = atoi(&c);
            }
        }
        fscanf(table,"%c", &c);
    }
    
    //ler o \n
    fscanf(table,"%c", &c);

    //jogo resolvido
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(table,"%c", &c);
            jogoResolvido[i][j] = atoi(&c);
        }
        fscanf(table,"%c", &c);
    }

}

int menuJogada(int jogo[9][9]){
    int opcao;
    printf("1-Adicionar Jogada\n");
    printf("2-Remover Jogada\n");
    printf("3-Salvar Jogo\n");
    printf("4-Conferir Jogo\n");
    printf("5-Mostrar Resposta\n");
    printf("6-Voltar\n");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao !=5 && opcao !=6){
        system("clear");
        printarTabuleiro(jogo);
        printf("OPCAO INVALIDA\n");
        opcao = menuJogada(jogo);
    }

    return opcao;
}

void removerJogada(int jogo[9][9], int mascara[9][9]){
    int linha,coluna;
    printf("Digite a linha coluna para excluir: ");
    scanf("%d %d", &linha, &coluna);
    if ((linha <= 9 && linha > 0) && (coluna <= 9 && coluna > 0)){
       if(mascara[linha-1][coluna-1] == 0){

           jogo[linha-1][coluna-1] = 0 ;

        }else{
           printf("Posicao Fixa!\n");
           removerJogada(jogo, mascara);
       }
    }else{
        printf("Posicao invalida!\n");
        removerJogada(jogo, mascara);
    }
}


void adicionarJogada(int jogo[9][9], int mascara[9][9]){
    int linha,coluna,valor;

    printf("Digite a linha coluna e valor: ");
    scanf("%d %d %d", &linha, &coluna, &valor);
    if ((linha <= 9 && linha > 0) && (coluna <= 9 && coluna > 0) && (valor <=9 && valor > 0)){
       if(mascara[linha-1][coluna-1] == 0){
           jogo[linha-1][coluna-1] = valor;
       }else{
           printf("Posicao Fixa!\n");
           adicionarJogada(jogo, mascara);
       }
    }else{
        printf("Posicao ou valor invalidos!\n");
        adicionarJogada(jogo, mascara);
    }
} 

void printarTabuleiro(int tabuleiro[9][9]){
    system("clear");
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if( tabuleiro[i][j] == 0){
                printf("|   ");
            }else{
                printf("| %d ", tabuleiro[i][j]);
            }

        }
        printf("|");
        printf("\n-------------------------------------\n");
    }
}

void criarMascara(int jogo[9][9], int mascara[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            mascara[i][j] = jogo[i][j];
        }
    }
}
void salvarArquivo(int jogo[9][9],int mascara[9][9], int jogoResolvido[9][9]){

    FILE *arq;
    arq = fopen("jogoSalvo.txt","w");

    //Salvar o game
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(jogo[i][j] == 0){

                fprintf(arq,".");    
            }
            else{
                fprintf(arq,"%d",jogo[i][j]);
            }
        }
        fprintf(arq,"\n");
    }

    fprintf(arq,"\n");

    //Salvar a mascara
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(mascara[i][j] == 0){

                fprintf(arq,".");    
            }
            else{
                fprintf(arq,"%d",mascara[i][j]);
            }
        }
        fprintf(arq,"\n");
    }

    fprintf(arq,"\n");

    //Salva jogo resolvido
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
               
            fprintf(arq,"%d",jogoResolvido[i][j]);
    
        }
        fprintf(arq,"\n");
    }
    fclose(arq);
}
void carregarJogo(int jogo[9][9], int mascara[9][9], int jogoResolvido[9][9]){

    FILE *jogo_salvo;
    jogo_salvo = fopen("jogoSalvo.txt","r");

    char c;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogo_salvo,"%c", &c);
            if(c == '.'){
                jogo[i][j] = 0;

            }else{
                jogo[i][j] = atoi(&c);
            }
        }
    }
    //ler o \n
    fscanf(jogo_salvo,"%c", &c);

    // Ler máscara
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogo_salvo,"%c", &c);
            if(c == '.'){ 
                mascara[i][j] = 0;
            }else{
                mascara[i][j] = atoi(&c);
            }
        }
        fscanf(jogo_salvo,"%c", &c);
    }
    
    //ler o \n
    fscanf(jogo_salvo,"%c", &c);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogo_salvo,"%c", &c);
            jogoResolvido[i][j] = atoi(&c);
        }
        fscanf(jogo_salvo,"%c", &c);
    }
}


int conferir(int jogo[9][9], int jogoResolvido[9][9]){

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
           if(jogoResolvido[i][j] != jogo[i][j]){
                printf("A casa %d %d se encontra errada!\n", i+1, j+1);
                printf("Digite uma tecla para continuar:\n");
                char c;
                setbuf(stdin,NULL);
                scanf("%c",&c);
                return 0;
            }
        }
    }
    return 1;
}
int main(){
    FILE *table;
    
    int jogo[9][9];
    int jogoResolvido[9][9];
    int mascara[9][9];
    int r;

    char nomeJogo[100];
    
    srand(time(NULL));
    

    int opcaoMenuInicial = 0;
    int opcaoMenuJogo;

    while(opcaoMenuInicial != 3){

        opcaoMenuInicial = menu();
        
        switch (opcaoMenuInicial){

            case 1: // Carregar game
                carregarJogo(jogo, mascara, jogoResolvido);
                opcaoMenuJogo = 0;
            break;

            case 2: //jogo Alertório

                r = rand() %5;
                sprintf(nomeJogo , "table%d.txt",r+1);
                table = fopen(nomeJogo, "r");

                lerArquivo(table, jogo, jogoResolvido);
                criarMascara(jogo, mascara);
                opcaoMenuJogo = 0;
            break;

            case 3:
                return 0;
            break;

            default:
                printf("OP inválida\n");
            break;
        }
        
        while(opcaoMenuJogo != 6){

            printarTabuleiro(jogo);
            opcaoMenuJogo = menuJogada(jogo);

            switch (opcaoMenuJogo){
                
                case 1: //adicionar jogada
                    adicionarJogada(jogo,mascara);
                    printarTabuleiro(jogo);
                break;

                case 2: //remover jogada
                    removerJogada(jogo, mascara);
                    printarTabuleiro(jogo);
                break;

                case 3: //salvar]
                    salvarArquivo(jogo,mascara,jogoResolvido);
                break;
                case 4:
                    if(conferir(jogo, jogoResolvido) != 0){
                        printf("----------------------------\n");
                        printf("\nPARABÉNS JOGO CORRETO!\n");
                        printf("----------------------------\n");
                        opcaoMenuJogo = 6;
                    }
                    break;
                case 5:
                    printarTabuleiro(jogoResolvido);
                break;
                case 6:
                    printf("voltando\n");
                break;
                default:
                    printf("OP inválida\n");
                break;
            }
        }
    }
    fclose(table);
    return 0;
}