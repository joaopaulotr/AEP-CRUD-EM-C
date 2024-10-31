//Professor Alexandre Moreno
algoritmo "AEP2024-2"
var
     nome:vetor[1..20] de caracter
    senha:vetor[1..20] de caracter
       op:caracter
  totuser:inteiro
//--------------------------------------------
procedimento menu
inicio
  Repita
    limpatela
    escreval
    escreval("M E N U")
    escreval
    escreval("1 - Inserir ")
    escreval("2 - Alterar ")
    escreval("3 - Excluir ")
    escreval("4 - Listar  ")
    escreval("5 - Créditos")
    escreval("6 - Fim     ")
    escreva ("  Opcao: ")
    leia(op)
    escolha op
       caso "1"
         inserir
       caso "2"
         alterar
       caso "3"
         excluir
       caso "4"
         listar(0) //mostra usuarios
       caso "5"
         creditos
       caso "f4","F4"
         listar(2) //mostra usuarios e senhas crioptografadas
       caso "f5","F5"
         listar(1) //mostra usuarios e senhas visíveis
    fimescolha
  Ate op="6"
fimprocedimento
//--------------------------------------------
Procedimento inserir
var
  senha2,parada:caracter
  p:inteiro
inicio
  Repita
    limpatela
    escreval
    escreval("I N S E R I R")
    escreva("Nome do Usuario: ")
    leia(nome[totuser+1])
    p<-buscaUsuario(nome[totuser+1])
    //p terá o índice (maior que zero) onde foi encontrado o usuário ou -1 caso nao encontre
    se (p>0) entao
      escreval("Usuário já cadastrado!")
      leia(parada)
    fimse
  Ate (p=-1) e (compr(nome[totuser+1])>=3)
  Repita
    escreva("          Senha: ")
    leia(senha[totuser+1])
  Ate (senhaValida(senha[totuser+1]))
  Repita
    escreva(" Repita a Senha: ")
    leia(senha2)
  Ate (senhaValida(senha2) e (senha[totuser+1]=senha2))
  totuser<-totuser+1
  //grava no arquivo - essa opção nao é possivel no visualg
  classifica
fimprocedimento
//--------------------------------------------
Procedimento alterar
var
  senha2,parada:caracter
  p:inteiro
inicio
  Repita
    limpatela
    escreval
    escreval("A L T E R A R   S E N H A")
    escreva("Nome do Usuario: ")
    leia(nome[totuser+1])
    p<-buscaUsuario(nome[totuser+1])
    //p terá o índice (maior que zero) onde foi encontrado o usuário ou -1 caso nao encontre
    se (p=-1) entao
      escreval("Usuário não encontrado!")
      leia(parada)
    fimse
  Ate (p>0) e (compr(nome[totuser+1])>=3)
  Repita
    escreva("     Nova Senha: ")
    leia(senha[p])
  Ate (senhaValida(senha[p]))
  Repita
    escreva(" Repita a Senha: ")
    leia(senha2)
  Ate (senhaValida(senha2) e (senha[p]=senha2))
  //grava no arquivo - essa opção nao é possivel no visualg
fimprocedimento
//--------------------------------------------
Procedimento excluir
var
  senha2,parada:caracter
  x,p:inteiro
inicio
  Repita
    limpatela
    escreval
    escreval("E X C L U I R")
    escreva("Nome do Usuario: ")
    leia(nome[totuser+1])
    p<-buscaUsuario(nome[totuser+1])
    //p terá o índice (maior que zero) onde foi encontrado o usuário ou -1 caso nao encontre
    se (p=-1) entao
      escreval("Usuário não encontrado!")
      leia(parada)
    fimse
  Ate (p>0) e (compr(nome[totuser+1])>=3)
  escreval
  escreva ("Confirma exclusao?  ")
  leia(parada)
  se (maiusc(parada)="S") entao
     para x de p ate totuser faca
         nome[x]<-nome[x+1]
        senha[x]<-senha[x+1]
     fimpara
     totuser<-totuser-1
     //grava no arquivo - essa opção nao é possivel no visualg
  fimse
fimprocedimento
//--------------------------------------------
procedimento listar(tp:inteiro)
var
  x:inteiro
inicio
  limpatela
  escreval("---------------------------------------------------------")
  escreval("Usuário         Senha")
  escreval("---------------------------------------------------------")
  para x de 1 ate totuser faca
    escolha tp
      caso 0
        escreval(nome[x]:15)
      caso 1
        escreval(crip2(nome[x]):15," ",crip2(senha[x]))
      caso 2
        escreval(nome[x]:15," ",senha[x])
    fimescolha
  fimpara
  escreval("---------------------------------------------------------")
  escreval
  escreva ("Pressione ENTER para voltar o MENU ")
  leia(op)
fimprocedimento
//--------------------------------------------
procedimento creditos
var
  lin:vetor[1..14] de caracter
  x,y:inteiro
    c:caracter
inicio
  lin[1]<-"Programa desenvolvido  pelo professor Alexandre Moreno");
  lin[2]<-"como exemplo que contempla requisitos práticos da  AEP ");
  lin[3]<-"para turmas do 2°semestre de Análise e Desenvolvimento");
  lin[4]<-"de Sistemas e Engenharia de Software 2024 /Unicesumar.");
  lin[5]<-"             ");
  lin[6]<-"Requisitos: CRUD (create/read/update/delete) de users");
  lin[7]<-"com criptografia dos  dados salvos em  arquivo texto.");
  lin[8]<-"             ");
  lin[9]<-"Possui funcionalidades como procedimentos, funções, ");
  lin[10]<-"passagem de parâmetros por valor e  por referência, ");
  lin[11]<-"variáveis gobais e locais, criptografia, vetores,");
  lin[12]<-"arquivo texto e classificação.");
  lin[13]<-"                                     ");
  lin[14]<-"Pressione ENTER para retornar ao Menu.");
  limpatela
  para x de 1 ate 14 faca
    para y de 1 ate compr(lin[x]) faca
      c<-copia(lin[x],y,1)
      escreva(c)
      tempox(1000)
    fimpara
    escreval
  fimpara
  leia(op)
fimprocedimento
//--------------------------------------------
procedimento leArquivo
arquivo "C:\MORENO\DadUser2.TXT"
var
  x:inteiro
inicio
  totuser<-10 //fixo para nao dar erro no visualg
  para x de 1 ate totuser faca
    leia(nome[x])
    leia(senha[x])
    nome[x]<-desCrip2(nome[x])
    senha[x]<-desCrip2(senha[x])
  fimpara
fimprocedimento
//--------------------------------------------
funcao Crip2(s:caracter):caracter
var
  tmp:caracter
  x,c:inteiro
inicio
   tmp<-""
   para x de 1 ate compr(s) faca
     c<-asc(copia(s,x,1))
     tmp<-tmp+carac(c+x)  //soma a posição do caracter ao numero ascii
   fimpara
   retorne tmp
fimfuncao
//--------------------------------------------
funcao DesCrip2(s:caracter):caracter
var
  tmp:caracter
  x,c:inteiro
inicio
   tmp<-""
   para x de 1 ate compr(s) faca
     c<-asc(copia(s,x,1))
     tmp<-tmp+carac(c-x) //subtrai a posição do caracter ao numero ascii
   fimpara
   retorne tmp
fimfuncao
//--------------------------------------------
procedimento tempox(t:inteiro)
var
  z,k:inteiro
inicio
  para z de 1 ate t faca
    k:=k+1
  fimpara
fimprocedimento
//--------------------------------------------
funcao buscaUsuario(chave:caracter):inteiro
var
  indice,x:inteiro
inicio
  indice<- (-1)
  para x de 1 ate totuser faca
    se (chave=nome[x]) entao
      indice<-x
    fimse
  fimpara
  retorne indice
fimfuncao
//--------------------------------------------
Procedimento classifica //selection sort
var
  tmp:caracter
  x,y:inteiro
inicio
  para x de 1 ate totuser-1 faca
    para y  de x+1 ate totuser faca
       se (nome[y]<nome[x]) entao
              tmp<-nome[x]
          nome[x]<-nome[y]
          nome[y]<-tmp

              tmp<-senha[x]
         senha[x]<-senha[y]
         senha[y]<-tmp
       fimse
    fimpara
  fimpara
fimprocedimento
//--------------------------------------------
funcao senhaValida(s:caracter):logico
var
  c:caracter
  x:inteiro
  v1,v2,v3,v4,v5:logico
inicio
  v1<-falso
  v2<-falso
  v3<-falso
  v4<-falso
  v5<-falso
  se (compr(s)>=8) e (compr(s)<=20) entao
    v1<-verdadeiro
    para x de 1 ate compr(s) faca
      c<-copia(s,x,1)
      se (asc(c)>=65) e (asc(c)<=90) entao //letras maiúsculas
        v2<-verdadeiro
      fimse
      se (asc(c)>=97) e (asc(c)<=122) entao //letras minúsculas
        v3<-verdadeiro
      fimse
      se (asc(c)>=48) e (asc(c)<=57) entao  //números
        v4<-verdadeiro
      fimse
      se ((asc(c)>=32) e (asc(c)<=47)) ou ((asc(c)>=58) e (asc(c)<=64)) ou ((asc(c)>=91) e (asc(c)<=96)) ou ((asc(c)>=123) e (asc(c)<=126))entao
        v5<-verdadeiro
      fimse
    fimpara
  fimse
  se (v1) e (v2) e (v3) e (v4) e (v5) entao
    retorne verdadeiro
  senao
    retorne falso
  fimse
fimfuncao
//--------------------------------------------
inicio
   leArquivo
   classifica
   menu
fimalgoritmo
