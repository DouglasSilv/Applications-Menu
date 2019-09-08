#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdbool.h>

// Constante para limpar o console
const char *LIMPAR_CONSOLE_ANSI = "\e[1;1H\e[2J";

// Variaveis para controlar os PID's dos processos filhos
int web_browser_pid;

void limparConsole(){
    write(STDOUT_FILENO, LIMPAR_CONSOLE_ANSI, 12);
}

char* obtemDescricaoProcesso(int n, int pid){
    char* descricao = malloc(20 * sizeof(char));
    switch (n){
    case 1:
        sprintf(descricao, "(executando, pid=%d)", pid);
        return descricao;
    case 0:
        return "(concluido)";
    case -1:
        return "(falhou)";
    default:
        break;
    }
}

char* abrirFirefox(){
    limparConsole();
    char URL[256];
	printf("Digite a URL que deseja abrir: ");
    scanf("%s", URL);

    // Configurar a saida do comando execlp para o arquivo log.txt
    int outfd = open("log.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (!outfd){
        perror("open");
    }

    // Fork para abrir o Firefox em um novo processo;
    pid_t pid = fork();
    if ((pid < 0)) {
        close(outfd);
        return obtemDescricaoProcesso(-1, web_browser_pid);
    } else if (pid == 0) {
        // Substituir a saida padrão para o arquivo log.txt
        dup2(outfd, 1);
        close(outfd);
        execlp("firefox", "-new-tab", &URL, NULL);
    } else {
        close(outfd);
        web_browser_pid = pid;
        return obtemDescricaoProcesso(1, web_browser_pid);;
    }
    
}

void exibeMenu(){
    int numeroDaOpcao;
    char* estados[3] = {" ", " ", " "};
    bool menuAtivo = true;
    while(menuAtivo){
        struct timeval tmo;
        fd_set readfds;
        limparConsole();
        printf("<<<< Applications Menu >>>> \n");
        printf("1) Web Browser %s\n", estados[0]);
        printf("2) Text Editor \n");
        printf("3) Terminal \n");
        printf("4) Finalizar processo \n");
        printf("5) Quit\n");
        printf("Opção: ");
        fflush(stdout);

        // Espera por 5 segundos o input do usuario
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        tmo.tv_sec = 5;
        tmo.tv_usec = 0;

        // Caso o usuario nao tenha selecionado uma opção, atualiza o  menu
        if (select(1, &readfds, NULL, NULL, &tmo) == 0) {
            continue;
        }

        scanf("%d", &numeroDaOpcao);
        switch (numeroDaOpcao){
        case 1:
            estados[0] = abrirFirefox();
            break;
        default:
            break;
        }
    
    }
}


int main(){
    exibeMenu();
}




