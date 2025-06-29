#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Tamanho máximo de entrada do usuário
#define MAX_LOGIN 50
#define MAX_SENHA 50
#define HASH_SIZE 65  // 64 + 1 para '\0'

// Função para gerar hash SHA-256 da senha
void gerar_hash_sha256(const char *senha, char *hash_saida) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)senha, strlen(senha), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_saida + (i * 2), "%02x", hash[i]);
    }
    hash_saida[64] = '\0'; // Finaliza string
}

// Salva login e senha (em hash) no arquivo
void cadastrar_usuario() {
    char login[MAX_LOGIN];
    char senha[MAX_SENHA];
    char hash[HASH_SIZE];

    printf("=== Cadastro ===\n");
    printf("Login: ");
    scanf(" %49s", login);
    printf("Senha: ");
    scanf(" %49s", senha);

    gerar_hash_sha256(senha, hash);

    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "%s %s\n", login, hash);
    fclose(file);

    printf("Cadastro realizado com sucesso!\n\n");
}

// Verifica login e senha com base no hash salvo
void autenticar_usuario() {
    char login[MAX_LOGIN];
    char senha[MAX_SENHA];
    char hash_input[HASH_SIZE];
    char login_arquivo[MAX_LOGIN];
    char hash_arquivo[HASH_SIZE];
    int autenticado = 0;

    printf("=== Login ===\n");
    printf("Login: ");
    scanf(" %49s", login);
    printf("Senha: ");
    scanf(" %49s", senha);

    gerar_hash_sha256(senha, hash_input);

    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL) {
        printf("Nenhum usuário cadastrado.\n\n");
        return;
    }

    while (fscanf(file, "%s %s", login_arquivo, hash_arquivo) != EOF) {
        if (strcmp(login, login_arquivo) == 0 && strcmp(hash_input, hash_arquivo) == 0) {
            autenticado = 1;
            break;
        }
    }
    fclose(file);

    if (autenticado) {
        printf("Login realizado com sucesso!\n\n");
    } else {
        printf("Credenciais inválidas.\n\n");
    }
}

// Menu principal
void menu() {
    int opcao;
    do {
        printf("=== Sistema de Autenticacao ===\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_usuario();
                break;
            case 2:
                autenticar_usuario();
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    menu();
    return 0;
}
