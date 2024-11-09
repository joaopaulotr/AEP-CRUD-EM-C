#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

//==========================================================================================================================================

char usuario[15][100]; // Vari�veis globais
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
            s2 = true; // Verifica letras mai�sculas
        }
        if (uni >= 97 && uni <= 122) {
            s3 = true; // Verifica letras min�sculas
        }
        if (uni >= 48 && uni <= 57) {   
            s4 = true; // Verifica n�meros
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
        printf ("Voc� escolheu atualizar o usu�rio! \n");
        printf ("Qual usu�rio deseja modificar? \n");
        scanf ("%s", novousuario);

        indice = buscaUsuario(novousuario); 

        if (indice == -1) {
            printf ("Usu�rio n�o encontrado! \n");
            printf ("Digite ENTER para continuar... \n");
            getchar ();
            getchar ();
        }
    } while (indice == -1);

    printf ("Deseja atualizar usu�rio [U] ou senha [S] ? \n");
    getchar();
    scanf ("%c", &escolhaatualiza);

    if (toupper(escolhaatualiza) == 'U') {
        printf ("Digite o nome do novo usu�rio:  \n");
        scanf ("%s", usuario[indice]);
        printf ("Usu�rio atualizado com sucesso! \n");

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
                printf ("A senha digitada n�o corresponde aos par�metros desejados, tente novamente... \n");
                }
        }  while (!verif_senha(novasenha));
    } else printf ("A op��o digitada n�o existe! \n"); 

    salvarCadastro();
}

//==========================================================================================================================================

void excluirCadastro() {
    char usuarioexclusao[100], escolha;
    int x, y;

    do {
        system("cls");
        printf("EXCLUIR: \n");
        printf("Qual usu�rio deseja excluir? \n");
        scanf("%s", usuarioexclusao);

        y = buscaUsuario(usuarioexclusao); // Busca o �ndice do usu�rio para ver onde ele est� localizado e se j� existe

        if (y == -1) { // Se o �ndice for -1, significa que n�o foi encontrado
            printf("Usu�rio n�o encontrado! \n");
            printf("Digite ENTER para continuar... \n");
            getchar();
            getchar();
        }
    } while (y == -1);

    getchar();
    printf("Digite 'S' para confirmar a exclus�o: \n");
    scanf(" %c", &escolha);

    if (toupper(escolha) == 'S') {
        for (int x = y; x < numusuarios; x++) {
            // Esse loop � respons�vel por "arrumar" a lista sem que sobrem espa�os ap�s tirar um usu�rio
            strcpy(usuario[x], usuario[x + 1]);
            strcpy(senha[x], senha[x + 1]);
        }
        numusuarios--;
        printf("Usu�rio exclu�do com sucesso! \n");
    } else {
        printf("Exclus�o cancelada! \n");
    }
    salvarCadastro();
}

//==========================================================================================================================================

int buscaUsuario(char *nomeBuscado) {
    // Fun��o que busca o �ndice (onde ele est�) do usu�rio
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
    printf("1. Criar Usu�rio\n");
    printf("2. Visualizar Cadastros\n");
    printf("3. Atualizar Cadastros\n");
    printf("4. Excluir Cadastros\n");
    printf("5. Sair\n");
    printf("===================================\n");
    printf("Escolha uma op��o: \n");
    printf("===================================\n");
}

//==========================================================================================================================================

void mostrarMenuUsuario() {
    printf("===================================\n");
    printf(" Bem-vindo ao nosso CRUD em C \n");
    printf("===================================\n");
    printf("1. Criar Usu�rio\n");
    printf("2. Atualizar Cadastros\n");
    printf("3. Sair\n");
    printf("===================================\n");
    printf("Escolha uma op��o: \n");
    printf("===================================\n");
}

//==========================================================================================================================================

void opcao1() {
    printf("===============================\n");
    printf("Voc� escolheu Criar um usu�rio!\n");
    printf("===============================\n");
    printf("Digite o seu usu�rio:\n");
    scanf("%99s", usuario[numusuarios]); // Corrigi a refer�ncia ao array de usu�rios

    do {
        printf("===============================\n");
        printf("Agora digite sua senha: \n");
        scanf("%s", senha [numusuarios]); // Corrigi a refer�ncia ao array de senhas

        if (verif_senha(senha[numusuarios])) {
            criptografar(senha[numusuarios]);
            printf("Parab�ns, agora voc� est� cadastrado.\n");
            numusuarios++; // Incrementa o n�mero de usu�rios
            salvarCadastro();
            break;
        } else {
            printf("Senha n�o atingiu os par�metros desejados, digite novamente.\n");
        }
    } while (!verif_senha(senha[numusuarios]));

    printf("===============================\n");
}

//==========================================================================================================================================

void opcao2() {
    printf("===================================\n");
    printf("Voc� escolheu Visualizar cadastros!\n");
    printf("===================================\n");

    listarCadastro ();
}

//==========================================================================================================================================

void opcao3() {
    printf("====================================\n");
    printf("Voc� escolheu Atualizar um cadastro!\n");
    printf("====================================\n");

    atualizarCadastro ();
}

//==========================================================================================================================================

void opcao4() {
    printf("==================================\n");
    printf("Voc� escolheu Excluir um cadastro!\n");
    printf("==================================\n");
    excluirCadastro();
}

//==========================================================================================================================================

void opcao5() {
    printf("==========================================================\n");
    printf("Voc� escolheu Sair, muito obrigado por conferir nossa AEP!\n");
    printf("==========================================================\n");
}

//==========================================================================================================================================
void infos(){
        printf("===================================\n");
        printf("Voc� escolheu Ver as informa��es!\n");
        printf("===================================\n");
        printf("Bem vindos ao sistema de Gerenciamento\n");
        printf("de dados, esse CRUD foi desenvolvido em C.\n");
        printf("====================================\n");
        printf("Desenvolvido pelos alunos (ESOFT2S-A):\n");
        printf("Jo�o Paulo Traguetta Rufino\n");
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


    printf ("Selecione uma op��o:\nUsu�rio (U)\nAdministrador (A)\nInforma��es e Cr�ditos (I)\n");
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
                printf("Op��o inv�lida! Tente novamente.\n");
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
                printf("Op��o inv�lida! Tente novamente.\n");
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
        } else printf ("Op��o inv�lida! Digite novamente... \n");
        getchar ();
    return 0;
}