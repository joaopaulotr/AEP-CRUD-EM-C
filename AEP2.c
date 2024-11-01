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

bool verif_senha (const char *senha) {
    bool s1= false, s2= false, s3= false, s4= false, s5= false;
    int tam = strlen(senha);


        if (tam > 8 && tam < 12) s1 = true; // Validou o tamanho da senha

            for (int i=0; i < tam; i++) {
                char uni = senhaS[i]; //verifica caracter por caracter por meio de ponteiro

                if (uni >= 65 && uni <= 90) {
                    s2 = true; //verif letras maiusculas
                } 
                
                if (uni >= 97 && uni <= 122) {
                    s3 = true; // verif letras minusculas
                    }
                    
                     if (uni >= 48 && uni <= 57) {
                        s4 = true;  //verif numeros
                            }
                            
                             if (uni >= 32 && uni <= 47 || uni >= 58 && uni <= 64 || uni >= 91 && uni <= 96 || uni >= 123 && uni <= 126) { 
                                s5 = true; //verif caract especiais
                            }

            }

        if (s1 && s2 && s3 && s4 && s5) return true;

    else return false;
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
    printf("===================================\n");
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
    
    if verif_senha(senha){

    criptografar(senha);

    printf("Parabéns, agora você está cadastrado.");
    }else{

    printf("Senha não atingiu os parâmetros desejados, digite novamente.");

    }
        
    } while (verif_senha(senha) != false);
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
