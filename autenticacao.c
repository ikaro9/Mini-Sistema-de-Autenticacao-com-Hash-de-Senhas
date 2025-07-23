#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LOGIN 50
#define MAX_SENHA 50
#define SALT_SIZE 9      // 8 + 1 para '\0'
#define HASH_SIZE 20     // hash convertido para string (8 hex chars + '\0')

// Função para gerar hash DJB2 simples

void gerar_hash(const char *entrada, char *hash_saida)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *entrada++))
        hash = ((hash << 5) + hash) + c;

    sprintf(hash_saida, "%08lx", hash);
}

// Função para gerar sal aleatório

void gerar_salt(char *salt_saida)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_SIZE - 1; i++)
    {
        salt_saida[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt_saida[SALT_SIZE - 1] = '\0';
}

// Verifica se usuário já existe

int usuario_existe(const char *login)
{
    FILE *verifica = fopen("usuarios.txt", "r");
    if (verifica != NULL)
    {
        char login_arquivo[MAX_LOGIN], salt_arquivo[SALT_SIZE], hash_arquivo[HASH_SIZE];

        while (fscanf(verifica, "%s %s %s", login_arquivo, salt_arquivo, hash_arquivo) != EOF)
        {
            if (strcmp(login, login_arquivo) == 0)
            {
                fclose(verifica);
                return 1;
            }
        }
        fclose(verifica);
    }
    return 0;
}

// Cadastrar novo usuário

void cadastrar_usuario()
{
    char login[MAX_LOGIN];
    char senha[MAX_SENHA];
    char salt[SALT_SIZE];
    char senha_salgada[MAX_SENHA + SALT_SIZE];
    char hash[HASH_SIZE];

    printf("\n========= CADASTRO =========\n");
    printf("Login: ");
    scanf(" %49s", login);

    if (usuario_existe(login))
    {
        printf("\n[ATENCAO] O usuario '%s' ja esta cadastrado!\n\n", login);
        return;
    }

    printf("Senha: ");
    scanf(" %49s", senha);
    printf("===========================\n");

    gerar_salt(salt);
    snprintf(senha_salgada, sizeof(senha_salgada), "%s%s", senha, salt);
    gerar_hash(senha_salgada, hash);

    FILE *file = fopen("usuarios.txt", "a");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(file, "%s %s %s\n", login, salt, hash);
    fclose(file);

    printf("\n[SUCESSO] Cadastro realizado! Bem-vindo(a), %s!\n\n", login);
}

// Autenticar o usuário

void autenticar_usuario()
{
    char login[MAX_LOGIN], senha[MAX_SENHA], senha_salgada[MAX_SENHA + SALT_SIZE];
    char hash_input[HASH_SIZE];
    char login_arquivo[MAX_LOGIN], salt_arquivo[SALT_SIZE], hash_arquivo[HASH_SIZE];
    int autenticado = 0;

    printf("\n========== LOGIN ===========\n");
    printf("Login: ");
    scanf(" %49s", login);
    printf("Senha: ");
    scanf(" %49s", senha);
    printf("===========================\n");

    FILE *file = fopen("usuarios.txt", "r");
    if (file == NULL)
    {
        printf("\n[ATENCAO] Nenhum usuario cadastrado ainda.\n\n");
        return;
    }

    while (fscanf(file, "%s %s %s", login_arquivo, salt_arquivo, hash_arquivo) != EOF)
    {
        if (strcmp(login, login_arquivo) == 0)
        {
            snprintf(senha_salgada, sizeof(senha_salgada), "%s%s", senha, salt_arquivo);
            gerar_hash(senha_salgada, hash_input);

            if (strcmp(hash_input, hash_arquivo) == 0)
            {
                autenticado = 1;
            }
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

        int opcao;
        do {
            printf("-----------------------------\n");
            printf("0. Sair\n");
            printf("-----------------------------\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            if (opcao == 0)
            {
                printf("\nAte logo, %s! Volte sempre!\n\n", login);
            }
            else
            {
                printf("\nOpcao invalida! Digite 0 para sair.\n\n");
            }
        } while (opcao != 0);
    }
    else
    {
        printf("\n[ERRO] Credenciais invalidas! Acesso negado.\n\n");
    }
}

// Menu principal

void menu_principal()
{
    srand(time(NULL)); // Inicializa gerador de números aleatórios para salt
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
    } while (1);
}

// Função principal

int main()
{
    menu_principal();
    return 0;
}