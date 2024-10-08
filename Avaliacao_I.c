#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
void flush_input();
struct usuario{
    char nome[80], username[80], email[80], senha[80];
};
struct produto{
    char nomeproduto[80], codigo[4];
    float preco;
};
short int n;
int produto_a_editar;
int quantidade_de_produtos=3;
int main(){
    setlocale(LC_ALL,"");
    struct usuario *user=(struct usuario*)malloc(quantidade_de_produtos*sizeof(struct usuario));
    struct produto *product=(struct produto*)malloc(3*sizeof(struct produto));
    int validarusername(struct usuario user[], char usernametmp[]);
    int validaremail(struct usuario user[], char emailtmp[]);
    int validarsenha(struct usuario user[], char senhatmp[]);
    int compararcodigo(struct produto product[], char editcodigo[]);
    void excluir_produto(struct produto **product, int *quantidade_de_produtos, char codigotmp[]);
//Login e senha pré-definidos do programa:
    strcpy(user[0].nome, "Elton Caio Vieira de Lima"); strcpy(user[0].username, "eltonlima");
    strcpy(user[0].email, "elton@lima"); strcpy(user[0].senha, "0123456789");
    strcpy(user[1].nome, "Fulano"); strcpy(user[1].username, "fulanoa");
    strcpy(user[1].email, "fulano@fulano"); strcpy(user[1].senha, "fulano123");
    strcpy(user[2].nome, "Sicrano"); strcpy(user[2].username, "sicranoz");
    strcpy(user[2].email, "sicrano@sicrano"); strcpy(user[2].senha, "sicrano123");
    short int opcao, op;
    char usernametmp[80], emailtmp[80], senhatmp[80];
    do{
        puts("[SISTEMA]\n1 - Realizar Login\n2 - Verificação de validade de e-mail\n0 - Sair");
        scanf("%hi", &opcao); flush_input();
        switch(opcao){
            case 1:
            printf("1. Login: "); scanf("%79[^\n]", usernametmp); flush_input();
            if(validarusername(user, usernametmp)!=0){
                puts("[LOGIN INCORRETO!]\nTente novamente.");
                break;
            }
            printf("1. Senha: "); scanf("%79[^\n]", senhatmp); flush_input();
            if(validarsenha(user, senhatmp)!=0){
                puts("[SENHA INCORRETA!]\nTente novamente.");
                break;
            }
            printf("[LOGIN BEM SUCEDIDO!]\nBem vindo %s!\n", user[n].nome);
//Menu interno:
//Produtos pré-cadastrados do programa:
            strcpy(product[0].nomeproduto, "Frasco de Estus"); strcpy(product[0].codigo, "0000"); product[0].preco=15;
            strcpy(product[1].nomeproduto, "Frasco de Estus das Cinzas"); strcpy(product[1].codigo, "0001"); product[1].preco=15;
            strcpy(product[2].nomeproduto, "Bênção Divina"); strcpy(product[2].codigo, "0010"); product[2].preco=8000;
            int verificar_produto(struct produto product[], char codigo[]); short int op0;
            char codigotmp[4], editnome[80]; float editpreco;
            do{
                puts("[SISTEMA]\n1 - Cadastrar\n2 - Listar\n3 - Editar\n4 - Excluir\n0 - Sair");
                scanf("%hi", &op); flush_input();
                switch(op){
                    case 1: quantidade_de_produtos++;
                    product = (struct produto*) realloc(product, quantidade_de_produtos * sizeof(struct produto));
                    puts("[CADASTRAR NOVO PRODUTO]\nDigite o nome do produto: ");
                    scanf("%79[^\n]", product[quantidade_de_produtos-1].nomeproduto); flush_input();
                    puts("Crie um código para identificar o produto (4 caracteres, sem espaço):");
                    scanf("%4[^\n]", codigotmp);
                    do{
                        puts("[CÓDIGO JÁ EM USO!]\nTente novamente!");
                        scanf("%4[^\n]", codigotmp); flush_input();
                    }while(compararcodigo(product, codigotmp)!=0);
                    strcpy(product[quantidade_de_produtos-1].codigo, codigotmp);
                    printf("Preço do produto: "); scanf("%f", &product[quantidade_de_produtos-1].preco);
                    break;
                    case 2:
                    puts("[LISTA DE PRODUTOS]");
                    for(int i=0; i<quantidade_de_produtos; i++){
                        printf("[PRODUTO]: %s - [CÓDIGO]: %s - [PREÇO]: R$%.2f\n", product[i].nomeproduto, product[i].codigo, product[i].preco);
                    }
                    system("pause");
                    break;
                    case 3:
                    puts("3. Digite o código do produto que deseja editar:");
                    scanf("%4[^\n]", codigotmp); flush_input();
                    if(verificar_produto(product, codigotmp)!=0){
                        puts("[CÓDIGO INVÁLIDO!]");
                        break;
                    }else{
                        puts("[EDITAR]\n1 - Nome\n2 - Preço\n0 - Voltar"); scanf("%hi", &op0); flush_input();
                        switch(op0){
                            case 1: printf("1. Editar nome (atual: %s): ", product[produto_a_editar].nomeproduto);
                            scanf("%79[^\n]", editnome); flush_input();
                            strcpy(product[produto_a_editar].nomeproduto, editnome);
                            printf("[PRODUTO]: %s - [CÓDIGO]: %s - [PREÇO]: R$%.2f\n",
                            product[produto_a_editar].nomeproduto, product[produto_a_editar].codigo, product[produto_a_editar].preco);
                            break;
                            case 2: printf("2. Editar preço (atual: R$%.2f): ", product[produto_a_editar].preco);
                            scanf("%f", &editpreco); flush_input();
                            product[produto_a_editar].preco=editpreco;
                            break;
                            case 0: break;
                            default: puts("[OPÇÃO INVÁLIDA!]");
                        }
                    }
                    break;
                    case 4:
                    puts("[EXCLUIR]\nDigite o código do produto:");
                    scanf("%4[^\n]", codigotmp); flush_input();
                    excluir_produto(&product, &quantidade_de_produtos, codigotmp);
                    break;
                    case 0: puts("[SAINDO...]");
                    return 0;
                }
            }while(op!=0);
            break;
            case 2:
            printf("2. Digite o e-mail: "); scanf("%79[^\n]", emailtmp); flush_input();
            if(validaremail(user, emailtmp)==2){
                puts("[EMAIL INVÁLIDO!]\nAusência de caractere '@'.");
                break;
            }else if(validaremail(user, emailtmp)==1){
                puts("[E-MAIL JÁ EM USO!]");
                break;
            }else if(validaremail(user, emailtmp)==0){
                puts("[E-MAIL DISPONÍVEL!]");
                break;
            }
            break;
            case 0: puts("[SAINDO...]"); return 0;
        }
    }while(opcao!=0);
    free(user);
    return 0;
}
int validarusername(struct usuario user[], char usernametmp[]){
    for(int i=0; i<3; i++){
        if(strcmp(user[i].username, usernametmp)==0){
            return 0;
        }
    }
    return 1;
}
int validarsenha(struct usuario user[], char senhatmp[]){
    short int *pn=&n;
    for(int i=0; i<3; i++){
        if(strcmp(user[i].senha, senhatmp)==0){
            *pn=i;
            return 0;
        }
    }
    return 1;
}
int validaremail(struct usuario user[], char emailtmp[]){
    int x=strlen(emailtmp);
    for(int i=0; i<x; i++){
        if(emailtmp[i]=='@'){
            break;
        }else if(i==(x-1)){
            return 2;
        }
    }
    for(int i=0; i<3; i++){
        if(strcmp(user[i].email, emailtmp)==0){
            return 1;
        }
    }
    return 0;
}
int compararcodigo(struct produto product[], char codigotmp[]){
    for(int i=0; i<quantidade_de_produtos; i++){
        if(strcmp(product[i].codigo, codigotmp)==0){
            return 1;
        }
    }
    return 0;
}
int verificar_produto(struct produto product[], char codigotmp[]){
    int *p=&produto_a_editar;
    for(int i=0; i<quantidade_de_produtos; i++){
        if(strcmp(product[i].codigo, codigotmp)==0){
            *p=i;
            return 0;
        }
    }
    return 1;    
}
void flush_input(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF);
}
void excluir_produto(struct produto **product, int *quantidade_de_produtos, char codigotmp[]){
    int encontrado = 0;
    for (int i=0; i<*quantidade_de_produtos; i++){
        if (strcmp((*product)[i].codigo, codigotmp)==0){
            encontrado = 1;
            for (int j = i; j<*quantidade_de_produtos-1; j++) {
                (*product)[j]=(*product)[j+1];
            }
            (*quantidade_de_produtos)--;
            *product = (struct produto*)realloc(*product, *quantidade_de_produtos * sizeof(struct produto));
            puts("[PRODUTO EXCLUÍDO COM SUCESSO!]");
            break;
        }
    }
    if(!encontrado){
        puts("[CÓDIGO DO PRODUTO NÃO ENCONTRADO!]");
    }
}
