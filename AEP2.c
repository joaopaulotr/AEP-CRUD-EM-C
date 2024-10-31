#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//==========================================================================================================================================

#define CHAVE 5

void criptografar(char *senha) {
    for (int i = 0; i < strlen(senha); i++) {
        senha[i] = senha[i] + CHAVE;
    }
}

//==========================================================================================================================================

int verificaSenha(char senha){


    if (/* condition */)
    {
        return 1; //verificou corretamente
    }else{
        return 0; // não atingiu os parâmetros
    }
    
}

//==========================================================================================================================================

/*char descriptografar(char senha){
 

}
*/

//==========================================================================================================================================

//xxx exibirCadastros(){}

//==========================================================================================================================================

//xxx atualizarCadastro(){}

//==========================================================================================================================================

//xxx excluirCadastro(){}

//==========================================================================================================================================

void mostrarMenu() {
    printf("===================================\n");
    printf("    Bem-vindo ao nosso CRUD em C   \n");
    printf("===================================\n");
    printf("1. Criar Usuário\n");
    printf("2. Visualizar Cadastros\n");
    printf("3. Atualizar Cadastros\n");
    printf("4. Excluir Cadastros\n");
    printf("5. Sair\n");
    printf("===================================\n");
    printf("Escolha uma opção: ");
}

//==========================================================================================================================================

void opcao1() {
    printf("===============================\n");
    printf("Você escolheu Criar um usuário!\n");
    printf("===============================\n");
    printf("Digite o seu usuário:\n");
    scanf("%s", usuario);
    
    do
    {
    printf("===============================\n");
    printf("Agora digite sua senha");
    scanf("%s", senha);
    
    if verificaSenha(senha == 1){

    criptografar(senha);

    printf("Parabéns, agora você está cadastrado.");
    }else{

    printf("Senha não atingiu os parâmetros desejados, digite novamente.");

    }
        
    } while (verificaSenha != 1);
    
    printf("===============================\n");
}

//==========================================================================================================================================

void opcao2() {
    printf("===================================\n");
    printf("Você escolheu Visualizar cadastros!\n");
    printf("===================================\n");
}

//==========================================================================================================================================

void opcao3() {
    printf("====================================\n");
    printf("Você escolheu Atualizar um cadastro!\n");
    printf("====================================\n");
}

//==========================================================================================================================================

void opcao4() {
    printf("==================================\n");
    printf("Você escolheu Excluir um cadastro!\n");
    printf("==================================\n");
}

//==========================================================================================================================================

void opcao5() {
    printf("==========================================================\n");
    printf("Você escolheu Sair, muito obrigado por conferir nossa AEP!\n");
    printf("==========================================================\n");
}

//==========================================================================================================================================


int main() {
    char usuario[100][15];
    char senha[100][15];

    int escolha;
    do {
        system("cls");  
        mostrarMenu();
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
        printf("Pressione Enter para continuar...\n");
        getchar();
        getchar(); 
    } while (escolha != 6);



    return 0;
}
