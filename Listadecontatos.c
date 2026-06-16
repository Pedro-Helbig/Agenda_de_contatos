#include <stdio.h>

typedef struct
{
    int id;
    int numero;
    char nome[20];
} contato;  //estrutura que define um contato, com id sempre. O id deve auto acrementar quando se criar um novo contato
int i = 0;
contato adicionar_novo();   //prototipo sem parametro da função de adcionar novos membros
void listar_contato(contato c);

int main(){
    int e;
    contato c[20];

    while(1){                          
        printf("////Lista de contatos////\n");
        printf("1-Adicionar contato\n");
        printf("2-Excluir contato\n");
        printf("3-Alterar um contato que ja exista\n");
        printf("4-Listar todos os contatos\n");
        printf("5-Buscar um contato\n");
        scanf("%d", &e);

        switch (e)
        {
        case 1:{
            c[i] = adicionar_novo();
            i++;                       // incrementa i após salvar o contato
            printf("Contato criado com sucesso\n");
            break;
        }
        case 4:{
            for(int j = 0; j < i; j++){  // percorre todos os contatos salvos
                listar_contato(c[j]);
            }
            break;
        }
        default:
            break;
        }
    }
}                                     

contato adicionar_novo(){
    contato c;

    printf("Digite o nome: ");
    scanf("%19s", c.nome);

    printf("Digite o numero: ");
    scanf("%d", &c.numero);

    c.id = 1+i; // depois você pode fazer auto incremento

    return c;
}

void listar_contato(contato c){
    printf("Dados do contato\n");
    printf("ID: %d\n", c.id);
    printf("Nome: %s\n", c.nome);
    printf("Numero: %d\n", c.numero);
}