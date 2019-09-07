#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

// Constante para limpar o console
const char *LIMPAR_CONSOLE_ANSI = "\e[1;1H\e[2J";

void limparConsole(){
    write(STDOUT_FILENO, LIMPAR_CONSOLE_ANSI, 12);
}

void abrirFirefox(){
    limparConsole();
    char URL;
	printf("Digite a URL que deseja abrir: ");
    scanf("%s", &URL);
    execlp("firefox", "--new-widow", &URL, NULL);
}

void exibeMenu(){
    int numeroDaOpcao;

    while(1){
        limparConsole();
        printf("<<<< Applications Menu >>>> \n");
        printf("1) Web Browser \n");
        printf("2) Text Editor \n");
        printf("3) Terminal \n");
        printf("4) Finalizar processo \n");
        printf("5) Quit\n");
        printf("Opção: ");
        scanf("%d", &numeroDaOpcao);

        // Impedir que o programa continue até que o usuario digite alguma coisa
        while (getchar() != '\n')
            continue;

        switch (numeroDaOpcao){
            case 1:
                    abrirFirefox();
                break;
            default:
                break;
        }
    
    }
}


int main(){
    exibeMenu();
}




