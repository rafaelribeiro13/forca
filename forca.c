#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h" 

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
   
    printf("**************************\n");
    printf("*     Jogo da forca      *\n");
    printf("**************************\n");

}

int letraexiste(char letra) {

    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(letra == palavrasecreta[i]) {
            return 1;
        }
    }

    return 0;
}

void chuta(){
    char chute;
    printf("Qual a letra? ");
    scanf(" %c", &chute);
    
    if (letraexiste(chute)) {
        printf("Voce acertou: a palavra tem a letra %c\n\n",chute);
    } else {
        printf("Voce errou: a palavra nao tem a letra %c\n\n",chute);
    }
    
    
    printf("\n");
    chutes[chutesdados] = chute;
    chutesdados++;

}

int jachutou(char letra) {
    int achou = 0;

    for (int j = 0; j < chutesdados; j++) {
        if (chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(){
    int erros = chuteserrados();


    printf(" _________       \n");
    printf(" |         |     \n");
    printf(" |         %c    \n", (erros >= 1 ? 'O' : ' '));
    printf(" |        %c%c%c \n", (erros >= 3 ? '/' : ' '), (erros >= 2 ?'|' : ' '), (erros >= 3 ? '\\': ' '));
    printf(" |        %c %c  \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |               \n");    
    printf(" |               \n"); 
    
    for (int i = 0; i < strlen(palavrasecreta); i++) {

        int achou = jachutou(palavrasecreta[i]);

        if (achou) {
            printf("%c ",palavrasecreta[i]); 
        } else {
            printf("_ ");
        }
            
    }
    printf("\n");
}

void adicionapalavra() {
    char quer;

    printf("Voce deseja adicionar uma palavra no jogo? [S/N]: ");
    scanf(" %c",&quer);

    if (quer == 'S' || quer == 's') {
        char novapalavra[TAMANHO_PALAVRA];
        
        printf("Digite a nova palavra em letras maiusculas: ");
        scanf("%s",&novapalavra);

        FILE* f;

        f = fopen("palavras.txt","r+");
        if (f == 0) {
            printf("Banco de dados nao disponivel\n\n");
            exit(1); 
        }

        int qtd;
        fscanf(f,"%d",&qtd);
        qtd++;

        fseek(f,0, SEEK_SET); 
        fprintf(f,"%d",qtd); 

        fseek(f,0,SEEK_END); 
        fprintf(f,"\n%s",novapalavra); 
        
        fclose(f);
    }
    
}

void escolhepalavra(){
    
    FILE* f; 
    
    f = fopen("palavras.txt","r"); 
    if (f == 0) {
        printf("Banco de dados nao disponivel\n\n");
        exit(1); 
    }
    
    int qntdepalavras;
    fscanf(f,"%d",&qntdepalavras); 

    srand(time(0));
    int randomico = rand();
    
    randomico = rand() % qntdepalavras;
    
    for (int i = 0; i <= randomico; i++) {
        fscanf(f,"%s", palavrasecreta);
    }
    

    fclose(f); 

}

int chuteserrados() {
    int erros = 0;
    for (int i = 0; i < chutesdados ; i++){
        int existe = 0;
        for (int j = 0; j < strlen(palavrasecreta); j++){
            if (chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;                
            }
        }
        
        if (!existe) {
            erros++;
        }
    }
    return erros;
}

int enforcou(){
    
    return chuteserrados() >=5;
    
}

int acertou() {
    for (int i = 0; i < strlen(palavrasecreta); i++) {
        if (!jachutou(palavrasecreta[i]) ) {
            return 0;
        }
        
    }
    return 1;
}

int main(){

    abertura();
    escolhepalavra();
    do
    {
        system("cls");
        printf("Voce ja deu %d chutes\n",chutesdados); 
        
        desenhaforca();
        chuta();

    } while ( !acertou() && !enforcou() );
    
    if (acertou()) {
        printf("Parabens voce ganhou\n");
    } else {
        printf("Puxa! Voce foi enforcado\n");
        printf("A palavra secreta era **%s**\n\n",palavrasecreta);
    }

    adicionapalavra();
    
    
}
