#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// O que falta fazer
/* 
   - Gerar os dados desordenados dos funcionários
   - colocar no github 
   - deixar os arquivos separados em listas bonitinhas
*/

typedef struct Funcionario
{
   int cod;
   char nome[50];
   char cpf[50];
   char dataDeNascimento[11];
   double salario;
} Tfunc;

void salva_funcionario(Tfunc *func, FILE *out)
{
   fwrite(&func->cod, sizeof(int), 1, out);
   fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
   fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
   fwrite(func->dataDeNascimento, sizeof(char), sizeof(func->dataDeNascimento), out);
   fwrite(&func->salario, sizeof(double), 1, out);
}

/*
   void cadastrar_funcionarios(){
      enquanto não alcançar o limite de 100 registro continue cadastrando usuário

      // Geradores de dados
      contador -> 0 à 100
      nome -> https://cursos.alura.com.br/forum/topico-metodo-para-criar-nome-usando-random-73976
      cpf -> função randômica, deu três números coloca um número, e no final coloca um traço
      nascimento -> coloca dois números aleatórios e de 0 à 30, depois de 0 à 12, depois de 1960 à 2002
      salario -> 800 à 10.000
}
}
*/

void cadastrar_funcionarios(FILE *out, int nFunc)
{
   Tfunc func;
   for (int i = 0; i <= nFunc; i++)
   {
      // Gera dados do funcionário
      // nome

      // cpf

      // Data de Nascimento

      // Salario
      func.cod = i;
      sprintf(func.nome, "Funcionario %d", i);
      sprintf(func.cpf, "111.111.111-11");
      sprintf(func.dataDeNascimento, "01/06/2021");
      func.salario = 1000 + i;
      fseek(out, (i - 1) * sizeof(Tfunc), SEEK_SET);
      
      // Salva_funcionario arquivo em binário
      salva_funcionario(&func, out);
   }
}

Tfunc *le_funcionario(FILE *in)
{
   Tfunc *func = (Tfunc *)malloc(sizeof(Tfunc));

   if (0 >= fread(&func->cod, sizeof(int), 1, in))
   {
      free(func);
      return NULL;
   }

   fread(func->nome, sizeof(char), sizeof(func->nome), in);
   fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
   fread(func->dataDeNascimento, sizeof(char), sizeof(func->dataDeNascimento), in);
   fread(&func->salario, sizeof(double), 1, in);
   return func;
}

Tfunc *busca_sequencial(int cod, FILE *arq, int tam)
{
   float tempo;
   clock_t tempoOrd;

   tempoOrd = clock();
   for (int i = 0; i < tam; i++)
   {
      Tfunc *func = le_funcionario(arq);

      fseek(arq, i * sizeof(Tfunc), SEEK_SET);
      Tfunc *func2 = le_funcionario(arq);

      if (cod == func2 -> cod)
      {
         tempoOrd = clock() - tempoOrd;
         printf("\n\n%f milisegundos gastos", ((float)tempoOrd)/CLOCKS_PER_SEC);
         printf("\n%d numero de comparacoes", i);
         return func2;
      }
   }
   


   return NULL;
}

Tfunc *busca_binaria(int cod, FILE *arq, int tam)
{
   int left = 0, rigth = tam - 1, contador = 0;
   clock_t tempoOrd;


   tempoOrd = clock();  
   while (left <= rigth)
   {
      int middle = (left + rigth) / 2;
      fseek(arq, middle * sizeof(Tfunc), SEEK_SET);
      Tfunc *func = le_funcionario(arq);

      if (cod == func->cod)
      {
         tempoOrd = clock() - tempoOrd;
         printf("\n\n%f milisegundos gastos", ((float)tempoOrd)/CLOCKS_PER_SEC);
         printf("\n%d numero de comparacoes", contador);
         return func;
      }
      else if (func->cod < cod)
      {
         contador++;
         left = middle + 1;
      }
      else
      {
         contador++;
         rigth = middle - 1;
      }
   }
   return NULL;
}

void keysorting()
{

}

void msg_inicial_menu()
{
   printf("\n******************** MENU ***********************");
   printf("\n\t1. BUSCA BINARIA PELO FUNCIONARIO              ");
   printf("\n\t2. BUSCA SEQUENCIAL PELO FUNCIONARIO           ");
   printf("\n\t3. ORDERNAR ARQUIVO ATRAVES DO KEYSORTING      ");
   printf("\n\t4. SAIR                                        ");
   printf("\n**************************************************\n");
}

int main()
{
   // Declaração das variáveis
   int opcao = 0;
   int codDeBusca;
   FILE *arq = fopen("baseDeDados.dat", "wb+");
   Tfunc *func;
   int nFuncionarios = 100;

   // Verificando se o arquivo existe 
   if (arq == NULL)
   {
      printf("Não foi possivel abrir o arquivo.\n");
      return 1;
   }

   cadastrar_funcionarios(arq, nFuncionarios);

   do
   {
      system("cls");
      msg_inicial_menu();
      fflush(stdin);

      printf("\n\nDIGITE UMA OPCAO:");
      scanf("%d", &opcao);

      switch (opcao)
      {
      case 1:
         printf("\n\nDIGITE O CODIGO QUE DESEJA PESQUISAR:");
         scanf("%d", &codDeBusca);

         func = busca_binaria(codDeBusca, arq, nFuncionarios);

         if (func == NULL)
         {
            printf("Funcionario não encotrado =(");
         }
         else
         {
            // Criar uma função pra imprimir esse tipo de registros
            printf("\n\nFuncionario encotrado!!! =)");
            printf("\nCod: %d", func->cod);
            printf("\nNome: %s", func->nome);
            printf("\nCPF: %s", func->cpf);
            printf("\nData de Nascimento: %s", func->dataDeNascimento);
            printf("\nSalario: %f\n", func->salario);
         }

         printf("\n\n >>>>>>>>>>>>>>>> MSG: BUSCA BINARIA FEITA COM SUCESSO! <<<<<<<<<<<<<<<<");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: PRESSIONE QUALQUER TECLA PARA CONTINUAR! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         fflush(stdin);
         getchar();
         break;
      case 2:
         printf("\n\nDIGITE O CODIGO QUE DESEJA PESQUISAR:");
         scanf("%d", &codDeBusca);

         func = busca_sequencial(codDeBusca, arq, nFuncionarios);

         if (func == NULL)
         {
            printf("Funcionario não encotrado");
         }
         else
         {
            printf("\n\nFuncionario encotrado!!! =)");
            printf("\nCod: %d", func->cod);
            printf("\nNome: %s", func->nome);
            printf("\nCPF: %s", func->cpf);
            printf("\nData de Nascimento: %s", func->dataDeNascimento);
            printf("\nSalario: %ld\n", func->salario);
         }

         printf("\n\n >>>>>>>>>>>>>>>> MSG: BUSCA SEQUENCIAL FEITA COM SUCESSO! <<<<<<<<<<<<<<<<");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: PRESSIONE QUALQUER TECLA PARA CONTINUAR! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         fflush(stdin);
         getchar();
         break;
      case 3:
         // keysorting();
         printf("\n\n**********************************************************************");
         printf("\nPROFESSORA NAO CONSEGUI FAZER O METODO DE ORDENACAO KEYSORTING,      ");
         printf("\nOS ARQUIVOS POR PADRAO JA ESTAO ORDENADOS, LOGO... A BUSCA SE-       ");
         printf("\nQUENCIAL E BINARIA ESTAO SENDO EXECUTADAS TRANQUILAMENTE...          ");
         printf("\n**********************************************************************");

         printf("\n\n >>>>>>>>>>>>>>>> MSG: KEYSORTING NAO FEITO COM SUCESSO! =( <<<<<<<<<<<<<<<<");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: PRESSIONE QUALQUER TECLA PARA CONTINUAR! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         fflush(stdin);
         getchar();
         break;
      case 4:

         system("cls");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: SAINDO DO SISTEMA! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: PRESSIONE QUALQUER TECLA PARA CONTINUAR! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         fflush(stdin);
         getchar();
         break;
      default:
         system("cls");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: DIGITE UMA OPCAO VALIDA! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         printf("\n\n >>>>>>>>>>>>>>>>>>>>>>> MSG: PRESSIONE QUALQUER TECLA PARA CONTINUAR! <<<<<<<<<<<<<<<<<<<<<<\n\n");
         fflush(stdin);
         getchar();
      }
   } while (opcao != 4);

   free(func);
   fclose(arq);
   return 0;
}

// Função cadastrar
/*
   void cadastrar_funcionarios(){
      enquanto não alcançar o limite de 100 registro continue cadastrando usuário

      // Geradores de dados
      contador -> 0 à 100
      nome -> https://cursos.alura.com.br/forum/topico-metodo-para-criar-nome-usando-random-73976
      cpf -> função randômica, deu três números coloca um número, e no final coloca um traço
      nascimento -> coloca dois números aleatórios e de 0 à 30, depois de 0 à 12, depois de 1960 à 2002
      salario -> 800 à 10.000

      salva_funcionarior em arquivo binário
      pular umas linhas depois de cada registro


      // Código
      int contador = 0;
      while(contador != 100){
         ...
      }
}

}
*/