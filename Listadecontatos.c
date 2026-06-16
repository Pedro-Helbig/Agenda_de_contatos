#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int id;
    int numero;
    char nome[20];
} contato; // estrutura que define um contato, com id sempre. O id deve auto acrementar quando se criar um novo contato
int i = 0;
contato adicionar_novo(); // prototipo sem parametro da função de adcionar novos membros
void listar_contato(contato c);
contato *buscar_contato(contato c[], int tamanho); // retorna ponteiro (NULL se não achar)
void str_lower(const char *src, char *dest, int max);

int main()
{
    int e;
    contato c[20];

    while (1)
    {
        printf("////Lista de contatos////\n");
        printf("1-Adicionar contato\n");
        printf("2-Excluir contato\n");
        printf("3-Alterar um contato que ja exista\n");
        printf("4-Listar todos os contatos\n");
        printf("5-Buscar um contato\n");
        scanf("%d", &e);

        switch (e)
        {
        case 1:
        {
            c[i] = adicionar_novo();
            i++; // incrementa i após salvar o contato
            printf("Contato criado com sucesso\n");
            break;
        }
        case 3:
        {
            int es;
            if (i == 0)
            {
                printf("Nenhum contato cadastrado.\n");
                break;
            }
            contato *encontrado = buscar_contato(c, i);
            if (encontrado == NULL)
            {
                printf("Contato nao encontrado.\n");
                break;
            }

            printf("Contato encontrado.\n");
            listar_contato(*encontrado);
            printf("1-Alterar nome\n2-Alterar numero\n 3-Alterar nome e numero");
            scanf("%d", &es);
            if (es == 1)
            {
                printf("Novo nome: ");
                scanf(" %19[^\n]", encontrado->nome);
            }
            else if (es == 2)
            {
                printf("Novo numero: ");
                scanf("%d", &encontrado->numero);
            }
            else if (es == 3)
            {
                printf("Novo nome: ");
                scanf(" %19[^\n]", encontrado->nome);
                printf("Novo numero: ");
                scanf("%d", &encontrado->numero);
            }
            printf("Contato alterado com sucesso!\n");
            break;
        }
        case 4:
        {
            if (i == 0)
            {
                printf("Nenhum contato cadastrado.\n");
                break;
            }
            for (int j = 0; j < i; j++)
            { // percorre todos os contatos salvos
                listar_contato(c[j]);
            }
            break;
        }
        case 5:
        {
            if (i == 0)
            {
                printf("Nenhum contato cadastrado.\n");
                break;
            }
            contato *encontrado = buscar_contato(c, i);
            if (encontrado != NULL)
            {
                printf("Contato encontrado:\n");
                listar_contato(*encontrado);
            }
            else
            {
                printf("Contato nao encontrado.\n");
            }
            break;
        }
        default:
            break;
        }
    }
}

contato adicionar_novo()
{
    contato c;

    printf("Digite o nome: ");
    scanf(" %19[^\n]", c.nome); // faz o scanf ler até o enter

    printf("Digite o numero: ");
    if (scanf("%d", &c.numero) != 1)
    {
        printf("Erro ao ler numero\n");
    }
    c.id = 1 + i; // autoincremento do id

    return c;
}

void listar_contato(contato c)
{
    printf("Dados do contato\n");
    printf("ID: %d\n", c.id);
    printf("Nome: %s\n", c.nome);
    printf("Numero: %d\n", c.numero);
}

contato *buscar_contato(contato c[], int tamanho)
{
    int opcao, id_busca, numero_busca;
    char nome_busca[20], nome_lower[20], c_nome_lower[20];
    printf("Buscar por:\n");
    printf("1-Nome\n");
    printf("2-ID\n");
    printf("3-Numero\n");
    scanf("%d", &opcao);
    if (opcao == 1)
    {
        printf("Digite o nome (ou parte dele): ");
        scanf(" %19[^\n]", nome_busca);
        str_lower(nome_busca, nome_lower, 20);

        for (int j = 0; j < tamanho; j++)
        {
            str_lower(c[j].nome, c_nome_lower, 20);
            if (strstr(c_nome_lower, nome_lower) != NULL)
            {
                return &c[j]; // retorna ponteiro para o primeiro achado
            }
        }
    }
    else if (opcao == 2)
    {
        printf("Digite o ID: ");
        scanf("%d", &id_busca);

        for (int j = 0; j < tamanho; j++)
        {
            if (c[j].id == id_busca)
            {
                return &c[j];
            }
        }
    }
    else if (opcao == 3)
    {
        printf("Digite o numero: ");
        scanf("%d", &numero_busca);

        for (int j = 0; j < tamanho; j++)
        {
            if (c[j].numero == numero_busca)
            {
                return &c[j];
            }
        }
    }
    return NULL; // não encontrou
}

void str_lower(const char *src, char *dest, int max)
{ // Converte string para minúsculas padronizando a pesquisa
    int j = 0;
    while (src[j] && j < max - 1)
    {
        dest[j] = tolower((unsigned char)src[j]);
        j++;
    }
    dest[j] = '\0';
}