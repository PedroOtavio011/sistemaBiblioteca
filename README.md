Sistema de Gestão de Biblioteca

Aplicação em modo texto para cadastrar e consultar livros, fazer exclusão lógica de registros e exportar os livros ativos para um arquivo de texto. O projeto foi desenvolvido para a Atividade Avaliativa da disciplina de Programação Estruturada.

## Funcionalidades

- **Cadastrar livros:** registra ID, título, autor e ano de publicação em `biblioteca.dat`.
- **Consultar por ID:** exibe os dados de um livro ativo.
- **Excluir livro:** realiza uma exclusão lógica, marcando o registro como inativo. O registro permanece no arquivo binário.
- **Exportar para TXT:** cria `livros_exportados.txt` com os dados dos livros ativos.
- **Contar livros ativos:** mostra no menu quantos livros estão cadastrados e ativos.
- **Validar entradas:** verifica campos obrigatórios e evita IDs ativos duplicados.

## Como executar no Dev-C++

1. Instale e abra o **Dev-C++** (ou outra IDE que ofereça suporte a C).
2. Crie um projeto de console ou abra um novo arquivo-fonte.
3. Copie o código do arquivo `trabalho.cpp` para o projeto e salve-o em uma pasta de sua preferência.
4. Compile e execute pelo próprio Dev-C++.
5. Use as opções apresentadas no menu para gerenciar os livros.

Os arquivos de dados são criados automaticamente quando necessários. `biblioteca.dat` é criado ao cadastrar o primeiro livro, e `livros_exportados.txt` é criado ao usar a opção de exportação. Eles ficam no diretório de execução do programa, que normalmente é a pasta do projeto. Para manter os dados juntos do código, execute o projeto a partir dessa pasta.

> **Observação:** apesar da extensão `.cpp` do arquivo, o código usa a biblioteca padrão de C e pode ser compilado em modo C. Se necessário, salve-o como `trabalho.c` para que a IDE o reconheça como um programa em C.

## Dados armazenados

- `biblioteca.dat`: arquivo binário com os registros dos livros, inclusive os que foram marcados como inativos.
- `livros_exportados.txt`: relatório legível dos livros ativos, gerado pela opção de exportação.

Esses arquivos são criados durante a execução; não é necessário montá-los manualmente.

