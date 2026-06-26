#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int id;
    char numero[20];   //Numero como char permite 0 no comeco, ddd,
    char nome[20];
} contato; // estrutura que define um contato, com id sempre. O id deve auto acrementar quando se criar um novo contato
int i = 0;
char lixochar;
contato adicionar_novo(); // prototipo sem parametro da função de adcionar novos membros
void listar_contato(contato c);
contato *buscar_contato(contato c[], int tamanho); // retorna ponteiro (NULL se não achar)
void str_lower(const char *src, char *dest, int max);
void limpar_buffer(); //  limpa a linha dps do scanf

int main()
{
    int e = 0;
    contato c[20];

    while (1)
    {
        printf("////Lista de contatos////\n");
        printf("1-Adicionar contato\n");
        printf("2-Excluir contato\n");
        printf("3-Alterar um contato que ja exista\n");
        printf("4-Listar todos os contatos\n");
        printf("5-Buscar um contato\n");
        printf("6-Sair\n");
        while (scanf("%d", &e) != 1) // evita que seja valores invalidos
        {
            while ((lixochar = getchar()) != '\n' && lixochar != EOF)
                ;
        printf("Opcao invalida. Digite um numero.\n"); // Mostra mensagem de erro

        }
        limpar_buffer();

        switch (e)
        {
        case 1:
        {
            if (i >= 20)
            {
                printf("Limite de contatos atingido.\n");
                break;
            }
            c[i] = adicionar_novo();
            i++; // incrementa i após salvar o contato
            printf("Contato criado com sucesso\n");
            break;
        }
        case 2:
        {
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
            printf("Contato encontrado:\n");
            listar_contato(*encontrado);

            // calcula o índice do contato no array pela aritmética de ponteiros
            int idx = encontrado - c;
            // desloca os elementos seguintes para preencher o buraco
            for (int j = idx; j < i - 1; j++)
            {
                c[j] = c[j + 1];
            }
            i--;
            // reindexar IDs para manter sequência contínua
            for (int j = idx; j < i; j++)
                c[j].id = j + 1;
            printf("Contato excluido com sucesso.\n");
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
            while (scanf("%d", &es) != 1) // evita que seja valores invalidos
            {
                while ((lixochar = getchar()) != '\n' && lixochar != EOF)
                    ;
            }
            limpar_buffer();
            if (es == 1)
            {
                printf("Novo nome: ");
                scanf(" %19[^\n]", encontrado->nome);
                limpar_buffer();
            }
            else if (es == 2)
            {
                printf("Novo numero: ");
                scanf(" %19[^\n]", &encontrado->numero);
                limpar_buffer();
            }
            else if (es == 3)
            {
                printf("Novo nome: ");
                scanf(" %19[^\n]", encontrado->nome);
                limpar_buffer();
                printf("Novo numero: ");
                scanf(" %19[^\n", &encontrado->numero);
                limpar_buffer();
            }
            else 
            {
             printf("Opcao invalida. Nada foi alterado.\n");
                break;
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
        case 6:
        {
            printf("Programa Encerrado.\n");
            return 0;
        }
        default:
            printf("Opcao invalida, digite de 1 a 6.\n");
            break;
        }
    }
}

contato adicionar_novo()
{
    contato c;

    printf("Digite o nome: ");
    scanf(" %19[^\n]", c.nome); // faz o scanf ler até o enter
    limpar_buffer();

    printf("Digite o numero: ");
    while (scanf(" %19[^\n]", &c.numero) != 1)
    {
        while ((lixochar = getchar()) != '\n' && lixochar != EOF)
            ;
        printf("Erro ao ler numero\n");
    }
    limpar_buffer();
    c.id = 1 + i; // autoincremento do id

    return c;
}

void listar_contato(contato c)
{
    printf("Dados do contato\n");
    printf("ID: %d\n", c.id);
    printf("Nome: %s\n", c.nome);
    printf("Numero: %s\n", c.numero);
}

contato *buscar_contato(contato c[], int tamanho)
{
    int opcao, id_busca;
    char nome_busca[20], nome_lower[20], c_nome_lower[20], numero_busca[20];
    printf("Buscar por:\n");
    printf("1-Nome\n");
    printf("2-ID\n");
    printf("3-Numero\n");
    scanf("%d", &opcao);
    limpar_buffer();
    if (opcao == 1)
    {
        printf("Digite o nome (ou parte dele): ");
        scanf(" %19[^\n]", nome_busca);
        limpar_buffer();
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
        limpar_buffer();

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
        scanf(" %19[^\n]", &numero_busca);
        limpar_buffer();

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

void limpar_buffer()
{ 
    while ((lixochar = getchar()) != '\n' && lixochar != EOF)
        ;
}
