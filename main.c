#include<stdio.h>
#include<stdlib.h> // Para função srand() e system()
#include<windows.h> // Para função SetConsoleCursorPosition()
#include<conio.h> // Para função getch() e kbhit()
#include<time.h> // Para função rand()

// Variáveis Globais
int c[300][2], pontos=1, cx=2, cy=2;  // cx c cy sao as Coordenadas iniciais da cabeça da cobra, c é a matriz que armazena as partes da cobra
int comida[2], velo=150;

// FUNÇÕES
void gotoxy(int x, int y){ // posiciona o cursor do console na posição (x, y).

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

void desenha(int (*cobra)[2]){ //  desenha a cobra no console, usando a matriz cobra que armazena as coordenadas das partes da cobra.

    int i;
    for(i=0; i<pontos; i++){
        gotoxy(cobra[i][0],cobra[i][1]);
        printf("%c",219);
    }
}

void atualiza(int (*cobra)[2]){ //atualiza a posição da cobra no console, movendo cada parte para a posição da parte anterior.

    int i;
    gotoxy(cobra[pontos-1][0],cobra[pontos-1][1]);
    printf(" ");
    for(i=pontos-1; i>0; i--){
        cobra[i][0] = cobra[i-1][0];
        cobra[i][1] = cobra[i-1][1];
    }
    cobra[0][0] = cx;
    cobra[0][1] = cy;
}

int analiza(int (*cobra)[2]){ // verifica se a cobra colidiu com o próprio corpo, retornando 1 se houver colisão e 0 caso contrário.
    int i, retorno=0;
    for(i=1; i<pontos; i++){
        if(cx==cobra[i][0] && cy==cobra[i][1]){
            retorno=1;
        }
    }
    return retorno;
}

void geraComida(int (*comida)[2]){ // Esta função gera a posição aleatória da comida e a desenha no console.
    gotoxy((*comida)[0],(*comida)[1]);
    printf(" ");
    srand(time(NULL));
    (*comida)[0] = (rand() % 48) +1;
    (*comida)[1] = (rand() % 18) +1;
    gotoxy((*comida)[0],(*comida)[1]);
    printf("%c",4);
}

int main(){
    int i, gameover=0;
    int tecla;

    for(i=0; i<50; i++){ // desenha Linha superior
        gotoxy(i,0);
        printf("%c",219);
        Sleep(5); // Pausa execução por 5 milissegunos, para efeito visual
    }
    for(i=0; i<20; i++){ // desenha Coluna da direita
        gotoxy(50,i);
        printf("%c",219);
        Sleep(5); // Pausa execução por 5 milissegundos, para efeito visual
    }
    for(i=50; i>=0; i--){ // desenha Linha inferior
        gotoxy(i,20);
        printf("%c",219);
        Sleep(05); // Pausa execução por 5 milissegundos, para efeito visual
    }
    for(i=20; i>0; i--){ // desenha Coluna da esquerda
        gotoxy(0,i);
        printf("%c",219);
        Sleep(5); // Pausa execução por 5 milissegundos, para efeito visual
    }

    int (*cobra)[2] = malloc(sizeof(int[300][2])); // Aloca espaço para a cobra, reservando espaço de 300
    cobra[0][0] = cx;
    cobra[0][1] = cy;

    geraComida(&comida); // Gera a primeira comida
    desenha(cobra); // Desenha a cobra
    tecla='d'; // A direção é para a direita por padrão
    while(gameover==0){ // Enquanto o usuário não perder fica em 0
        gotoxy(52,2); // Move o cursor para c: 52, l: 2
        printf("Pontos: %d\t",pontos);
        gotoxy(52,4);
        printf("Velocidade: %.2f caracteres/s",1000/velo);
        if(kbhit()) // Se alguma tecla for apertada, o valor vai para a variável 'tecla'
            tecla=getch(); 

        if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // Se a cabeça da cobra estiver na parede superior, o jogo acaba
        }                    
        if(tecla=='a' || tecla=='A' || tecla==75){
            cx--;
            if(cx==0) break; // Se a cabeça da cobra estiver na parede da esquerda, o jogo acaba
        }                    
        if(tecla=='s' || tecla=='S' || tecla==80){
            cy++;
            if(cy==20) break; // Se a cabeça da cobra estiver na parede de baixo, o jogo acaba
        }                     
        if(tecla=='d' || tecla=='D' || tecla==77){
            cx++;
            if(cx>=50) break; // Se a a cabeça da cobra estiver na parede da direida,o jogo acaba
        }                     

        if(cx==comida[0] && cy==comida[1]){ // Se a cobra comer a comida, aumenta pontos
            pontos++;
            if(velo>50) velo-=10; // Velocidade em milissegundos abaixa (jogo fica mais rapido)
            geraComida(&comida);
        }
        gameover=analiza(cobra);
        atualiza(cobra); // Atualiza a cobra
        desenha(cobra); // Desenha a cobra
        gotoxy(50,20);
        Sleep(velo);
    }
    system("cls"); // Quando o usuário perder, limpa a tela e exibe uma mensagem final
    printf("Voce perdeu! Fez %d pontos.\n",pontos);
    free(cobra); // Libera a memória alocada para a cobra
    system("pause");
}
