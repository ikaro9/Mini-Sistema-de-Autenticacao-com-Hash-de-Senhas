#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tamanho máximo de entrada do usuário
#define MAX_LOGIN 50
#define MAX_SENHA 50
#define HASH_SIZE 20 // 16 + 1 para '\0'

// Função para gerar hash simples DJB2
void gerar_hash(const char *senha, char *hash_saida)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *senha++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    // Converte hash para string hexadecimal curta
    sprintf(hash_saida, "%08lx", hash);
}

// Verifica se usuário já existe
int usuario_existe(const char *login)
{
    FILE *verifica = fopen("usuarios.txt", "r");
    if (verifica != NULL)
    {
        char login_arquivo[MAX_LOGIN];
        char hash_arquivo[HASH_SIZE];
        
        while (fscanf(verifica, "%s %s", login_arquivo, hash_arquivo) != EOF)
        {
            if (strcmp(login, login_arquivo) == 0)
            {
                fclose(verifica);
                return 1; // Usuário existe
            }
        }
        fclose(verifica);
    }
    return 0; // Usuário não existe
}

// Salva login e senha (em hash) no arquivo
void cadastrar_usuario()
{
    char login[MAX_LOGIN];
    char senha[MAX_SENHA];
    char hash[HASH_SIZE];

    printf("\n========= CADASTRO =========\n");
    printf("Login: ");
    scanf(" %49s", login);

    // Verifica se usuário já existe antes de pedir a senha
    if (usuario_existe(login))
    {
        printf("\n[ATENCAO] O usuario '%s' ja esta cadastrado!\n\n", login);
        return;
    }

    printf("Senha: ");
    scanf(" %49s", senha);
    printf("===========================\n");

    gerar_hash(senha, hash);

    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "%s %s\n", login, hash);
    fclose(file);

    printf("\n[SUCESSO] Cadastro realizado! Bem-vindo(a), %s!\n\n", login);
}

// Verifica login e senha com base no hash salvo
void autenticar_usuario()
{
    char login[MAX_LOGIN];
    char senha[MAX_SENHA];
    char hash_input[HASH_SIZE];
    char login_arquivo[MAX_LOGIN];
    char hash_arquivo[HASH_SIZE];
    int autenticado = 0;

    printf("\n========== LOGIN ===========\n");
    printf("Login: ");
    scanf(" %49s", login);
    printf("Senha: ");
    scanf(" %49s", senha);
    printf("===========================\n");

    gerar_hash(senha, hash_input);

    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL)
    {
        printf("\n[ATENCAO] Nenhum usuario cadastrado ainda.\n\n");
        return;
    }

    while (fscanf(file, "%s %s", login_arquivo, hash_arquivo) != EOF)
    {
        if (strcmp(login, login_arquivo) == 0 && strcmp(hash_input, hash_arquivo) == 0)
        {
            autenticado = 1;
            break;
        }
    }
    fclose(file);

    if (autenticado)
    {
        printf("\n===============================\n");
        printf("  BEM-VINDO(A), %s!\n", login);
        printf("  Voce esta autenticado no sistema\n");
        printf("===============================\n\n");
        
        // Menu após autenticação - apenas opção de sair
        int opcao;
        do {
            printf("-----------------------------\n");
            printf("0. Sair\n");
            printf("-----------------------------\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            
            if (opcao == 0) {
                printf("\nAte logo, %s! Volte sempre!\n\n", login);
            } else {
                printf("\nOpcao invalida! Digite 0 para sair.\n\n");
            }
        } while (opcao != 0);
    }
    else
    {
        printf("\n[ERRO] Credenciais invalidas! Acesso negado.\n\n");
    }
}

// Menu principal simplificado (apenas cadastrar e login)
void menu_principal()
{
    int opcao;
    do
    {
        printf("\n=== SISTEMA DE AUTENTICACAO ===\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("==============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_usuario();
            break;
        case 2:
            autenticar_usuario();
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (1); // Loop infinito (só sai com exit() ou CTRL+C)
}

// Função principal
int main()
{
    menu_principal();
    return 0;
}
