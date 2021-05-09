#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int dia, mes, ano;
} data_t;
typedef struct contato
{
    char nome[96];
    char cpf[12];
    data_t aniversario;
} contato_t;

void menu();
void inserirContato();
void buscarContato();

int main()
{
    menu();
}

void menu()
{

    int op;
    while (1)
    {
        printf("-----------------------------------------------------\n");
        printf("\n1- Inserir um contato:\n");
        printf("2- Editar um contato:\n");
        printf("3- Buscar contato:\n");
        printf("4- Buscar aniversariante:\n");
        printf("5- Excluir um contato:\n");
        printf("6- Sair:\n");
        scanf("%d", &op);
        getchar();
        switch (op)
        {
        case 1:
            inserirContato();
            break;
        case 2:
            //editarContato();
            break;
        case 3:
            buscarContatoNome();
            break;
        case 4:
            buscarContatoAniversario();
            break;
        case 5:
            printf("inserir");
            break;
        case 6:
            return;
        default:
            printf("opcao invalida tente novamente\n");
            break;
        }
    }
}

void inserirContato()
{
    FILE *pf;
    pf = fopen("agenda.txt", "a");

    if (pf == NULL)
    {
        printf("Error!");
        return;
    }
    else
    {
        contato_t novoContato;

        printf("Digite o nome:\n");
        fgets(novoContato.nome, 96, stdin);
        novoContato.nome[strlen(novoContato.nome) - 1] = '\0';

        printf("Digite o cpf:\n");
        fgets(novoContato.cpf, 12, stdin);
        novoContato.nome[strlen(novoContato.cpf) - 1] = '\0';

        printf("Digite o dia: ");
        scanf("%i", &novoContato.aniversario.dia);

        printf("Digite o mes: ");
        scanf("%i", &novoContato.aniversario.mes);

        printf("Digite o ano: ");
        scanf("%i", &novoContato.aniversario.ano);

        const char *PERSON_FORMAT = "%s, %s, %d/%d/%d\n";

        fprintf(pf, PERSON_FORMAT, novoContato.nome, novoContato.cpf, novoContato.aniversario.dia, novoContato.aniversario.mes, novoContato.aniversario.ano);

        fclose(pf);
    }
}

void buscarContatoNome()
{

    FILE *pf;
    pf = fopen("agenda.txt", "r");

    if (pf == NULL)
    {
        printf("Error!");
        return;
    }
    else
    {
        char buffer[150];
        const char *PERSON_FORMAT_IN = "%[a-zA-Z ], %[0-9], %d/%d/%d"; // string que irá ler -> "Alex Silva, 44561575855, 2/1/1995"
        printf("Qual o nome do contato voce quer buscar?\n");
        char nome[96];
        scanf("%[a-zA-Z ]", nome);
        int i = 0;

        while (!feof(pf))
        {

            contato_t contato;
            sscanf(buffer, PERSON_FORMAT_IN, contato.nome, contato.cpf, &contato.aniversario.dia, &contato.aniversario.mes, &contato.aniversario.ano);

            if (strcmp(nome, contato.nome) == 0)
            {
                i++;
                printf("-----------------------------------------------------\n");
                printf("%s, %s, %d/%d/%d\n", contato.nome, contato.cpf, contato.aniversario.dia, contato.aniversario.mes, contato.aniversario.ano);
            }
            fgets(buffer, 150, pf);
        }
        if (i == 0)
        {
            printf("-----------------------------------------------------\n");
            printf("Nenhum contato encontrado.\n");
        }

        fclose(pf);
    }
}

void buscarContatoAniversario()
{
    FILE *pf;
    pf = fopen("agenda.txt", "r");

    if (pf == NULL)
    {
        printf("Error!");
        return;
    }
    else
    {
        char buffer[150];
        const char *PERSON_FORMAT_IN = "%[a-zA-Z ], %[0-9], %d/%d/%d"; // string que irá ler -> "Alex Silva, 44561575855, 2/1/1995"
        printf("Qual dia/mes voce quer buscar nos contatos?  (ex: 1/12)\n");
        int dia, mes;
        scanf("%d/%d", &dia, &mes);

        while (!feof(pf))
        {

            contato_t contato;
            sscanf(buffer, PERSON_FORMAT_IN, contato.nome, contato.cpf, &contato.aniversario.dia, &contato.aniversario.mes, &contato.aniversario.ano);
            int i = 0;

            if (dia == contato.aniversario.dia && mes == contato.aniversario.mes)
            {
                printf("-----------------------------------------------------\n");
                printf("%s, %s, %d/%d/%d\n", contato.nome, contato.cpf, contato.aniversario.dia, contato.aniversario.mes, contato.aniversario.ano);
            }
            fgets(buffer, 150, pf);
        }

        fclose(pf);
    }
}
