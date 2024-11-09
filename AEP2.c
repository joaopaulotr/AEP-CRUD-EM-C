#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

//==========================================================================================================================================

char usuario[15][100]; // Variáveis globais
char senha[15][100];
int numusuarios = 0;


//==========================================================================================================================================
void lerArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
     while (fscanf(arquivo, "%s %s", usuario[numusuarios], senha[numusuarios]) == 2) {
         numusuarios++;
         if (numusuarios >= 15) break;
     }
    fclose(arquivo);
}
//==========================================================================================================================================
void salvarCadastro () {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf ("Erro ao carregar o arquivo.\n");
    }
    for (int i = 0; i < numusuarios; i++) {
        fprintf(arquivo, "%s %s\n", usuario [i], senha [i]);
    }
    fclose (arquivo);
}
//==========================================================================================================================================

void ordenaPosicao() {
    char *tmp;  
    for (int i = 0; i < numusuarios - 1; i++) {
        for (int y = i + 1; y < numusuarios; y++) {  
            if (strcmp(usuario[i], usuario[y]) > 0) {  

                strcpy(tmp, usuario[i]);
                strcpy(usuario[i], usuario[y]);
                strcpy(usuario[y], tmp);
            }
        }
    }
}

//==========================================================================================================================================

#define CHAVE 5

void criptografar(char *senha) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] = senha[i] + CHAVE;
    }
}

//==========================================================================================================================================

bool verif_senha(const char *senha) {
    bool s1 = false, s2 = false, s3 = false, s4 = false, s5 = false;
    int tam = strlen(senha);

    if (tam >= 8 && tam <= 12){
        s1 = true; // Validou o tamanho da senha
        }
    for (int i = 0; i < tam; i++) {
        char uni = senha[i]; // Verifica caracter por caracter por meio de ponteiro

        if (uni >= 65 && uni <= 90) {
            s2 = true; // Verifica letras maiúsculas
        }
        if (uni >= 97 && uni <= 122) {
            s3 = true; // Verifica letras minúsculas
        }
        if (uni >= 48 && uni <= 57) {   
            s4 = true; // Verifica números
        }
        if ((uni >= 32 && uni <= 47) || (uni >= 58 && uni <= 64) || (uni >= 91 && uni <= 96) || (uni >= 123 && uni <= 126)) {
            s5 = true; // Verifica caracteres especiais
        }
    }

    if (s1 && s2 && s3 && s4 && s5)
        return true;
    else
        return false;
}

//==========================================================================================================================================

void descriptografar(char *senha) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] = senha[i] - CHAVE;
    }
}

//==========================================================================================================================================

void listarCadastro () {
printf("============================== \n");
    for (int i = 0; i < numusuarios; i++) {
        printf ("%s %s \n",usuario [i], senha [i], "(Senha Criptografada)");        
    }
printf("============================== \n");
}

//==========================================================================================================================================

void atualizarCadastro () {
    char novousuario [100], escolhaatualiza, novasenha [100];
    int indice;

    do {
        printf ("Você escolheu atualizar o usuário! \n");
        printf ("Qual usuário deseja modificar? \n");
        scanf ("%s", novousuario);

        indice = buscaUsuario(novousuario); 

        if (indice == -1) {
            printf ("Usuário não encontrado! \n");
            printf ("Digite ENTER para continuar... \n");
            getchar ();
            getchar ();
        }
    } while (indice == -1);

    printf ("Deseja atualizar usuário [U] ou senha [S] ? \n");
    getchar();
    scanf ("%c", &escolhaatualiza);

    if (toupper(escolhaatualiza) == 'U') {
        printf ("Digite o nome do novo usuário:  \n");
        scanf ("%s", usuario[indice]);
        printf ("Usuário atualizado com sucesso! \n");

    } else if (toupper(escolhaatualiza) == 'S') {
        do {
            printf ("Digite a nova senha: \n");
            scanf ("%s", novasenha);

            if (verif_senha(novasenha)) {
                criptografar(novasenha);

                strcpy (senha[indice], novasenha);
                printf ("Senha atualizada com sucesso! \n");
                break;
            }  else {
                printf ("A senha digitada não corresponde aos parâmetros desejados, tente novamente... \n");
                }
        }  while (!verif_senha(novasenha));
    } else printf ("A opção digitada não existe! \n"); 

    salvarCadastro();
}

//==========================================================================================================================================

void excluirCadastro() {
    char usuarioexclusao[100], escolha;
    int x, y;

    do {
        system("cls");
        printf("EXCLUIR: \n");
        printf("Qual usuário deseja excluir? \n");
        scanf("%s", usuarioexclusao);

        y = buscaUsuario(usuarioexclusao); // Busca o índice do usuário para ver onde ele está localizado e se já existe

        if (y == -1) { // Se o índice for -1, significa que não foi encontrado
            printf("Usuário não encontrado! \n");
            printf("Digite ENTER para continuar... \n");
            getchar();
            getchar();
        }
    } while (y == -1);

    getchar();
    printf("Digite 'S' para confirmar a exclusão: \n");
    scanf(" %c", &escolha);

    if (toupper(escolha) == 'S') {
        for (int x = y; x < numusuarios; x++) {
            // Esse loop é responsável por "arrumar" a lista sem que sobrem espaços após tirar um usuário
            strcpy(usuario[x], usuario[x + 1]);
            strcpy(senha[x], senha[x + 1]);
        }
        numusuarios--;
        printf("Usuário excluído com sucesso! \n");
    } else {
        printf("Exclusão cancelada! \n");
    }
    salvarCadastro();
}

//==========================================================================================================================================

int buscaUsuario(char *nomeBuscado) {
    // Função que busca o índice (onde ele está) do usuário
    for (int i = 0; i < numusuarios; i++) {
        if (strcmp(usuario[i], nomeBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

//==========================================================================================================================================

void mostrarMenuAdm() {
    printf("===================================\n");
    printf(" Bem-vindo ao nosso CRUD em C \n");
    printf("===================================\n");
    printf("1. Criar Usuário\n");
    printf("2. Visualizar Cadastros\n");
    printf("3. Atualizar Cadastros\n");
    printf("4. Excluir Cadastros\n");
    printf("5. Sair\n");
    printf("===================================\n");
    printf("Escolha uma opção: \n");
    printf("===================================\n");
}

//==========================================================================================================================================

void mostrarMenuUsuario() {
    printf("===================================\n");
    printf(" Bem-vindo ao nosso CRUD em C \n");
    printf("===================================\n");
    printf("1. Criar Usuário\n");
    printf("2. Atualizar Cadastros\n");
    printf("3. Sair\n");
    printf("===================================\n");
    printf("Escolha uma opção: \n");
    printf("===================================\n");
}

//==========================================================================================================================================

void opcao1() {
    printf("===============================\n");
    printf("Você escolheu Criar um usuário!\n");
    printf("===============================\n");
    printf("Digite o seu usuário:\n");
    scanf("%99s", usuario[numusuarios]); // Corrigi a referência ao array de usuários

    do {
        printf("===============================\n");
        printf("Agora digite sua senha: \n");
        scanf("%s", senha [numusuarios]); // Corrigi a referência ao array de senhas

        if (verif_senha(senha[numusuarios])) {
            criptografar(senha[numusuarios]);
            printf("Parabéns, agora você está cadastrado.\n");
            numusuarios++; // Incrementa o número de usuários
            salvarCadastro();
            break;
        } else {
            printf("Senha não atingiu os parâmetros desejados, digite novamente.\n");
        }
    } while (!verif_senha(senha[numusuarios]));

    printf("===============================\n");
}

//==========================================================================================================================================

void opcao2() {
    printf("===================================\n");
    printf("Você escolheu Visualizar cadastros!\n");
    printf("===================================\n");

    listarCadastro ();
}

//==========================================================================================================================================

void opcao3() {
    printf("====================================\n");
    printf("Você escolheu Atualizar um cadastro!\n");
    printf("====================================\n");

    atualizarCadastro ();
}

//==========================================================================================================================================

void opcao4() {
    printf("==================================\n");
    printf("Você escolheu Excluir um cadastro!\n");
    printf("==================================\n");
    excluirCadastro();
}

//==========================================================================================================================================

void opcao5() {
    printf("==========================================================\n");
    printf("Você escolheu Sair, muito obrigado por conferir nossa AEP!\n");
    printf("==========================================================\n");
}

//==========================================================================================================================================
void infos(){
        printf("===================================\n");
        printf("Você escolheu Ver as informações!\n");
        printf("===================================\n");
        printf("Bem vindos ao sistema de Gerenciamento\n");
        printf("de dados, esse CRUD foi desenvolvido em C.\n");
        printf("====================================\n");
        printf("Desenvolvido pelos alunos (ESOFT2S-A):\n");
        printf("João Paulo Traguetta Rufino\n");
        printf("Heitor Ferrari Crivelin\n");
        printf("Maria Eduarda Furlan\n");
        printf("====================================\n");
 

}
//==========================================================================================================================================


int main () {
    int escolhaCargo, escolha;


    setlocale(LC_ALL, "Portuguese");

    printf("===================================\n");
    printf(" Bem-vindo ao nosso CRUD em C \n");
    printf("===================================\n");


    printf ("Selecione uma opção:\nUsuário (U)\nAdministrador (A)\nInformações e Créditos (I)\n");
    printf("===================================\n");
        scanf ("%c", &escolhaCargo);

    if (toupper(escolhaCargo) == 'A') {


    do {
        mostrarMenuAdm();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                opcao1();
                break;
            case 2:
                opcao2();
                break;
            case 3:
                opcao3();
                break;
            case 4:
                opcao4();
                break;
            case 5:
                opcao5();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        if (escolha != 5) {
        printf("Pressione Enter para continuar...\n");
        getchar();
        getchar();
        }

    } while (escolha != 5);
    }  else if(toupper (escolhaCargo) == 'U') {

        do {
        system("cls");
        mostrarMenuUsuario();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                opcao1();
                break;
            case 2:
                opcao3();
                break;
            case 3:
                opcao5();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        if (escolha != 3) {
        printf("Pressione Enter para continuar...\n");
        getchar();
        getchar();
        }

    } while (escolha != 3);
    }
    else if (toupper (escolhaCargo) == 'I'){ 
          infos();  
        } else printf ("Opção inválida! Digite novamente... \n");
        getchar ();
    return 0;
}