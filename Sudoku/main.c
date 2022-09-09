#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printarTabuleiro(int tabuleiro[9][9]);

int menu(){
    int opcao;
    system("clear");
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
    printf("4-Voltar\n");
    printf("5-Conferir\n");
    printf("6-Sair do jogo\n");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5 && opcao != 6){
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
           jogo[linha-1][coluna-1] = 0;
       }else{
           printf("Posicao Fixa!\n");
           removerJogada(jogo, mascara);
       }
    }else{
        printf("Posicao invalida!\n");
        removerJogada(jogo, mascara);
    }
}

void salvarJogo(int jogoSalvo[9][9], int jogoResolvido[9][9], int mascara[9][9]){
    FILE * savedGame;
    savedGame = fopen("savedGame.txt", "w");

    //salva o tabuleiro no estado atual
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(jogoSalvo[i][j] == 0){
                fprintf(savedGame, ".");
            }else{
                fprintf(savedGame, "%d", jogoSalvo[i][j]);
            }
        }
        fprintf(savedGame, "\n");
    }

    fprintf(savedGame, "\n");

    //salva a solucao do tabuleiro principal
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fprintf(savedGame, "%d", jogoResolvido[i][j]);
        }
        fprintf(savedGame, "\n");
    }

    fprintf(savedGame, "\n");

    //salva a mascara
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(mascara[i][j] == 0){
                fprintf(savedGame, ".");
            }else{
                fprintf(savedGame, "%d", mascara[i][j]);
            }
        }
        fprintf(savedGame, "\n");
    }

    fclose(savedGame);
    printf("Jogo Salvo\n");

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

void carregarJogo(int jogo[9][9], int mascara[9][9], int jogoResolvido[9][9], time_t start){
    FILE *jogoSalvo;
    jogoSalvo = fopen("savedGame.txt", "r");


    char c;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogoSalvo,"%c", &c);
            if(c == '.'){
                jogo[i][j] = 0;

            }else{
                jogo[i][j] = atoi(&c);
            }
        }
        fscanf(jogoSalvo,"%c", &c);
    }
    
    //ler o \n
    fscanf(jogoSalvo,"%c", &c);

    //jogo resolvido
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogoSalvo,"%c", &c);
            jogoResolvido[i][j] = atoi(&c);
        }
        fscanf(jogoSalvo,"%c", &c);
    }

    //ler o \n
    fscanf(jogoSalvo,"%c", &c);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fscanf(jogoSalvo,"%c", &c);
            if(c == '.'){
                mascara[i][j] = 0;

            }else{
                mascara[i][j] = atoi(&c);
            }
        }
        fscanf(jogoSalvo,"%c", &c);
    }
    fclose(jogoSalvo);
    start = time(NULL);
}


void conferirJogo(int jogo[9][9], int jogoResolvido[9][9], time_t start){
    int jogoIncorreto = 0;

    time_t dif = time(NULL) - start;
    int minutes = dif/60;
    int seconds = dif%60;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){

            if( jogo[i][j] == 0 ){
                printf("Jogo nao completo!\n");
                return;
            }else{
                
                if(jogo[i][j] != jogoResolvido[i][j]){
                    jogoIncorreto = 1;
                }
            }

            
        }
    }
    if( jogoIncorreto == 1){
        printf("O jogo esta incorreto! \n");

    }else{
        printf("Parabens jogo correto! Voce gastou %d minutos e %d segundos", minutes, seconds);
    }
}


void printarTabuleiro(int tabuleiro[9][9]){
    int contadorCol = 0;
    int contadorLin = 0;

    system("clear");
    printf("\n+===+===+===+===+===+===+===+===+===+\n");
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
        
            if(i == 0 && j == 0){
                contadorCol = 1;
                if( tabuleiro[i][j] == 0){
                    printf("\u2551   ");
                }else{
                    printf("\u2551 %d ", tabuleiro[i][j]);
                }
                continue;
            }




            if(contadorCol == 3){
                contadorCol = 1;
                if( tabuleiro[i][j] == 0){
                    printf("\u2551   ");
                }else{
                    printf("\u2551 %d ", tabuleiro[i][j]);
                }

            }else{
                if( tabuleiro[i][j] == 0){
                    printf("|   ");
                }else{
                    printf("| %d ", tabuleiro[i][j]);
                }
                contadorCol++;
            }
            
            
        }
        printf("\u2551");
        if (contadorLin == 2){
            contadorLin = 0;
            printf("\n+===+===+===+===+===+===+===+===+===+\n");
            continue;
        }else{
            printf("\n+---+---+---+---+---+---+---+---+---+\n");
        }

        contadorLin ++;
    }
}

void criarMascara(int jogo[9][9], int mascara[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            mascara[i][j] = jogo[i][j];
        }
    }
}


int main(){
    
    FILE *table;

    int jogo[9][9];
    int jogoResolvido[9][9];
    int mascara[9][9];
    time_t start = time(NULL); 
    int randomNumber;
    char nomeJogo[100];

    int opcaoMenuJogo;

    while(1){
        int opcaoMenuInicial = menu();

        switch (opcaoMenuInicial){
            case 1:
                carregarJogo(jogo, mascara, jogoResolvido, start);
                break;
            case 2: //jogo novo
                randomNumber = rand() %5;
                sprintf(nomeJogo , "table%d.txt", randomNumber+1);
                table = fopen(nomeJogo, "r");
                lerArquivo(table, jogo, jogoResolvido);
                criarMascara(jogo, mascara);
                break;
            default:
                return 0;
                break;
        }   

        do {
            printarTabuleiro(jogo);
            opcaoMenuJogo = menuJogada(jogo);
            switch (opcaoMenuJogo){
                case 1: //adicionar jogada
                    adicionarJogada(jogo,mascara);

                    break;
                case 2: //remover jogada
                    removerJogada(jogo, mascara);
                    break;
                case 3: //salvar
                    salvarJogo(jogo,jogoResolvido,mascara);
                    break;
                case 4: //voltar
                    break;
                case 5: //Conferir
                    conferirJogo(jogo, jogoResolvido, start);
                    char c;
                    setbuf(stdin,NULL);
                    scanf("%c" , &c);
                    break;

                default: //sair
                    return 0;
                    break;
            }

        }while(opcaoMenuJogo == 1 || opcaoMenuJogo == 2 || opcaoMenuJogo == 3 || opcaoMenuJogo == 5);
        
    }
    

    fclose(table);
    return 0;

}