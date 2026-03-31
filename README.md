# Sistema de Gerenciamento Acadêmico em C
Este projeto consiste em um sistema simples de gerenciamento acadêmico desenvolvido em linguagem C. Ele permite o cadastro, listagem e persistência de dados de alunos utilizando arquivos e alocação dinâmica de memória.

---

## Funcionalidades
O sistema implementa operações básicas de um CRUD simplificado:
- Cadastro de novos alunos  
- Listagem de alunos com cálculo de média  
- Salvamento de dados em arquivo  
- Carregamento automático dos dados ao iniciar o programa  
- Encerramento seguro com persistência automática  

---

## Conceitos Utilizados
Este projeto foi desenvolvido com foco em praticar conceitos fundamentais da linguagem C:
- Estruturas (`struct`)
- Ponteiros
- Alocação dinâmica (`malloc`, `realloc`, `free`)
- Manipulação de arquivos (`fopen`, `fprintf`, `fscanf`, `fgets`)
- Passagem por referência
- Tratamento de buffer de entrada
- Organização modular de código

---

## Estrutura de Dados
Cada aluno é representado pela seguinte estrutura:
```c
typedef struct{
    int ra;
    char nome[50];
    float notas[3];
} Aluno;
```

---

## Como Compilar e Executar

**Pré-requisitos:** GCC instalado na máquina.
```bash
# Compilar
gcc -o sistema main.c

# Executar
./sistema
```

> No Windows, o executável gerado será `sistema.exe`. Execute com `sistema.exe` no terminal.

---

## Como Usar

Ao iniciar, o sistema tenta carregar automaticamente os dados do arquivo `alunos.txt`. Em seguida, exibe o menu interativo:
```
=== Sistema de Gerenciamento Academico ===
1. Cadastrar Novo Aluno
2. Listar Alunos e Medias
3. Salvar Dados Manualmente
0. Sair
```

| Opção | Descrição |
|-------|-----------|
| `1` | Solicita RA, nome e 3 notas do aluno |
| `2` | Exibe todos os alunos com média e situação (Aprovado/Reprovado) |
| `3` | Salva os dados atuais no arquivo `alunos.txt` |
| `0` | Salva automaticamente e encerra o programa |

**Critério de aprovação:** média maior ou igual a 6,0.

---

## Persistência de Dados

Os dados são salvos no arquivo `alunos.txt`, gerado automaticamente na mesma pasta do executável. O formato do arquivo é:
```
<total_de_alunos>
<ra>
<nome>
<nota1> <nota2> <nota3>
...
```

Exemplo:
```
2
101
João Silva
7.50 8.00 6.50
102
Maria Souza
5.00 4.50 6.00
```

> O arquivo é lido automaticamente ao abrir o programa e regravado ao sair pela opção `0`.

---

## Organização do Código

| Função | Descrição |
|--------|-----------|
| `limparBuffer()` | Limpa o buffer de entrada para evitar leituras indevidas |
| `cadastrarAluno()` | Realoca o array e registra os dados de um novo aluno |
| `calcularMedia()` | Calcula e exibe a média e situação de um aluno |
| `listarAlunos()` | Percorre o array e chama `calcularMedia()` para cada aluno |
| `salvarDados()` | Grava todos os alunos no arquivo `alunos.txt` |
| `carregarDados()` | Lê o arquivo e popula o array dinâmico ao iniciar |
| `main()` | Gerencia o fluxo principal e o menu interativo |

---

## Possíveis Melhorias Futuras

- Busca de aluno por RA ou nome
- Edição e remoção de registros
- Suporte a mais de 3 notas por aluno
- Exportação de relatório em `.csv`
- Validação de entradas duplicadas (RA repetido)

---

## Autor

Desenvolvido como projeto prático de aprendizado em linguagem C, com foco em estruturas de dados, ponteiros e manipulação de arquivos.