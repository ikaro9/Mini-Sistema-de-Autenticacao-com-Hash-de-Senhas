# Mini Sistema de Autenticação com Hash de Senhas 
Neste projeto, implementamos um sistema simples de cadastro e login com senhas armazenadas em hash.

![Linguagem](https://img.shields.io/badge/linguagem-C-blue)
![Último commit](https://img.shields.io/github/last-commit/ikaro9/Mini-Sistema-de-Autenticacao-com-Hash-de-Senhas)


## Como Compilar e Executar

Para compilar e executar este programa C, você precisará de um **compilador C** instalado em seu sistema. O [GCC (GNU Compiler Collection)](https://gcc.gnu.org/) é altamente recomendado e amplamente utilizado.

---

### Pré-requisitos

* **Compilador C:** Certifique-se de ter um compilador C (como o GCC) configurado e acessível via linha de comando. Você pode verificar se o GCC está instalado executando:
    ```bash
    gcc --version
    ```
    Se não estiver instalado, você pode encontrá-lo nos gerenciadores de pacotes da maioria dos sistemas operacionais (ex: `sudo apt install build-essential` no Ubuntu/Debian, `brew install gcc` no macOS).

---

### Passos para Compilação e Execução

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/ikaro9/Mini-Sistema-de-Autenticacao-com-Hash-de-Senhas.git
   
   
2.  **Acesse o diretório do projeto:**
    Abra um terminal ou prompt de comando e navegue até a pasta raiz deste repositório onde o(s) arquivo(s) `.c` está(ão) localizado(s).

    ```bash
    cd Mini-Sistema-de-Autenticacao-com-Hash-de-Senhas
    ```

3.  **Compile o programa:**
    Utilize o GCC para compilar o código-fonte. Se o arquivo principal for `nome_do_arquivo.c` e você quiser que o executável seja chamado de `nome_do_executavel`, use o seguinte comando:

    ```bash
    gcc -g -o nome_do_executavel nome_do_arquivo.c
    ```
    * `-o nome_do_executavel`: Define o nome do arquivo executável.

4.  **Execute o programa compilado:**
    Depois de uma compilação bem-sucedida, você pode rodar o executável gerado:

    ```bash
    ./nome_do_executavel
    ```
    O programa então iniciará sua execução no terminal.

## Como usar o sistema

### 1. Acesso inicial

Ao iniciar o sistema:

- Digite `1` para **se cadastrar**.
- Digite `2` para **fazer login**.

> **Observação:** Caso seja sua primeira vez no sistema, é necessário realizar o cadastro antes de efetuar o login.

### 2. Cadastro

Ao escolher a opção `1`:

- Informe um **email** e uma **senha** para criar sua conta.
- **Importante:** Um email **não pode ser cadastrado mais de uma vez**.

### 3. Login

Ao escolher a opção `2`:

- Digite o **email** e a **senha** cadastrados.
- Se as credenciais estiverem corretas, você será autenticado no sistema.

### 4. Dentro do sistema

Após fazer login com sucesso, você poderá utilizar as funcionalidades disponíveis.

- Para **sair do sistema**, digite `0`.



## Integrantes
- Alexsandro Rocha dos Santos
- Ikaro Ferreira Brito
- Gabriel José N. de Medeiros
- Paulo Gabriel V. de Souza Paiva

**Disciplina:** Laboratório de Algoritmos e Estruturas de Dados II  
**Professor:** Kennedy Reurison Lopes

## Contato
Se quiser entrar em contato com algum dos integrantes do projeto para tirar dúvidas ou contribuir com o projeto, acesse o email.
- **Alexsandro Rocha dos Santos**
  Email: alexrochapdf@gmail.com
- **Ikaro Ferreira Brito**
  Email: ikarobrito722@gmail.com
- **Gabriel José N. de Medeiros**
  Email: gabriel1002d@gmail.com
- **Paulo Gabriel V. de Souza Paiva**
  Email: bengabrielcsp@gmail.com

