#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
void flush_input();
struct usuario{
    char nome[80], username[80], email[80], senha[80];
};
short int n;
int main(){
    setlocale(LC_ALL,"");
    struct usuario *user=(struct usuario*)malloc(3*sizeof(struct usuario));
    int validarusername(struct usuario user[], char usernametmp[]);
    int validaremail(struct usuario user[], char emailtmp[]);
    int validarsenha(struct usuario user[], char senhatmp[]);
//Login e senha pré-definidos do programa:
    strcpy(user[0].nome, "Elton Caio Vieira de Lima"); strcpy(user[0].username, "setocaio");
    strcpy(user[0].email, "elton.lima@alunos.ufersa.edu.br"); strcpy(user[0].senha, "0123456789");
    strcpy(user[1].nome, "Fulano"); strcpy(user[1].username, "fulanoa");
    strcpy(user[1].email, "fulano@fulano"); strcpy(user[1].senha, "fulano123");
    strcpy(user[2].nome, "Sicrano"); strcpy(user[2].username, "sicranoz");
    strcpy(user[2].email, "sicrano@sicrano"); strcpy(user[2].senha, "sicrano123");
    short int opcao;
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
            case 0: puts("[SAINDO]"); return 0;
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
        }else if(i==x){
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
void flush_input(){
    int c;
    while((c=getchar())!='\n'&&c!=EOF);
}