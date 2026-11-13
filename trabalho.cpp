#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define ARQUIVO_BIN "biblioteca.dat"
#define ARQUIVO_TXT "livros_exportados.txt"

struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int ano;
    int ativo;
};

void limparLinha();
int lerInteiro(int &numero);
int lerTexto(char texto[], int tamanho);
int temNumero(char texto[]);
int idJaExiste(int id);
int contarLivrosAtivos();
void cadastrarLivro();
void consultarPorCodigo();
void excluirLivro();
void exportarParaTXT();

int main() {
    int opcao;

    do {
        cout << "\n=========================================\n";
        cout << "     SISTEMA DE GESTAO DE BIBLIOTECA\n";
        cout << "=========================================\n";
        cout << "Livros ativos: " << contarLivrosAtivos() << "\n";
        cout << "-----------------------------------------\n";
        cout << "1. Cadastrar livro\n";
        cout << "2. Consultar livro por ID\n";
        cout << "3. Excluir livro\n";
        cout << "4. Exportar registros para TXT\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";

        if (lerInteiro(opcao) == 0) {
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                cadastrarLivro();
                break;
            case 2:
                consultarPorCodigo();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                exportarParaTXT();
                break;
            case 0:
                cout << "Encerrando o programa. Ate logo!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}

// Descarta o restante do que foi digitado na linha.
void limparLinha() {
    cin.ignore(1000, '\n');
}

// Lê um número inteiro.
// Retorna 1 se conseguiu ler e 0 se houve erro.
int lerInteiro(int &numero) {
    cin >> numero;

    if (cin.fail()) {
        cin.clear();
        limparLinha();
        return 0;
    }

    limparLinha();
    return 1;
}

// Lê um texto.
// Retorna 1 se o texto for válido e 0 se estiver vazio ou for longo demais.
int lerTexto(char texto[], int tamanho) {
    cin.getline(texto, tamanho);

    if (cin.fail()) {
        cin.clear();
        limparLinha();
        return 0;
    }

    if (strlen(texto) == 0) {
        return 0;
    }

    return 1;
}

// Retorna 1 se encontrar um número no texto e 0 se não encontrar.
int temNumero(char texto[]) {
    int i = 0;

    while (texto[i] != '\0') {
        if (texto[i] >= '0' && texto[i] <= '9') {
            return 1;
        }

        i++;
    }

    return 0;
}

// Retorna 1 se o ID já existir em um livro ativo.
int idJaExiste(int id) {
    FILE *arquivo;
    Livro livro;

    arquivo = fopen(ARQUIVO_BIN, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.id == id && livro.ativo == 1) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Cadastra um livro.
void cadastrarLivro() {
    Livro livro;
    FILE *arquivo;
    int correto;

    livro.ativo = 1;

    cout << "\n--- CADASTRAR LIVRO ---\n";

    do {
        cout << "Digite o ID positivo do livro: ";

        if (lerInteiro(livro.id) == 0 || livro.id <= 0) {
            cout << "ID invalido. Digite um numero positivo.\n";
            correto = 0;
        } else if (idJaExiste(livro.id) == 1) {
            cout << "Esse ID ja esta cadastrado. Digite outro.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    do {
        cout << "Digite o titulo: ";

        if (lerTexto(livro.titulo, 100) == 0) {
            cout << "Titulo vazio ou muito longo. Tente novamente.\n";
            correto = 0;
        } else if (temNumero(livro.titulo) == 1) {
            cout << "O titulo nao pode conter numeros. Tente novamente.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    do {
        cout << "Digite o nome do autor: ";

        if (lerTexto(livro.autor, 100) == 0) {
            cout << "Autor vazio ou muito longo. Tente novamente.\n";
            correto = 0;
        } else if (temNumero(livro.autor) == 1) {
            cout << "O nome do autor nao pode conter numeros. Tente novamente.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    do {
        cout << "Digite o ano de publicacao: ";

        if (lerInteiro(livro.ano) == 0 || livro.ano <= 0) {
            cout << "Ano invalido. Digite um ano positivo.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    arquivo = fopen(ARQUIVO_BIN, "ab");

    if (arquivo == NULL) {
        cout << "Erro ao abrir o arquivo de livros.\n";
        return;
    }

    fwrite(&livro, sizeof(Livro), 1, arquivo);
    fclose(arquivo);

    cout << "Livro cadastrado com sucesso!\n";
}

// Consulta um livro pelo ID.
void consultarPorCodigo() {
    FILE *arquivo;
    Livro livro;
    int id;
    int encontrado = 0;
    int correto;

    arquivo = fopen(ARQUIVO_BIN, "rb");

    if (arquivo == NULL) {
        cout << "Ainda nao ha livros cadastrados.\n";
        return;
    }

    do {
        cout << "Digite o ID do livro: ";

        if (lerInteiro(id) == 0) {
            cout << "ID invalido. Digite apenas numeros.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.id == id && livro.ativo == 1) {
            cout << "\nID: " << livro.id << "\n";
            cout << "Titulo: " << livro.titulo << "\n";
            cout << "Autor: " << livro.autor << "\n";
            cout << "Ano: " << livro.ano << "\n";
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        cout << "Nao foi encontrado livro ativo com esse ID.\n";
    }

    fclose(arquivo);
}

// Marca o livro como excluído
void excluirLivro() {
    FILE *arquivo;
    Livro livro;
    int id;
    int encontrado = 0;
    int correto;
    long posicao;

    arquivo = fopen(ARQUIVO_BIN, "rb+");

    if (arquivo == NULL) {
        cout << "Ainda nao ha livros cadastrados.\n";
        return;
    }

    do {
        cout << "Digite o ID do livro que deseja excluir: ";

        if (lerInteiro(id) == 0) {
            cout << "ID invalido. Digite apenas numeros.\n";
            correto = 0;
        } else {
            correto = 1;
        }
    } while (correto == 0);

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.id == id && livro.ativo == 1) {
            livro.ativo = 0;

            posicao = ftell(arquivo) - sizeof(Livro);
            fseek(arquivo, posicao, SEEK_SET);
            fwrite(&livro, sizeof(Livro), 1, arquivo);

            cout << "Livro excluido com sucesso.\n";
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        cout << "Nao foi encontrado livro ativo com esse ID.\n";
    }

    fclose(arquivo);
}

// Exporta os livros ativos para um arquivo de texto.
void exportarParaTXT() {
    FILE *arquivo;
    FILE *texto;
    Livro livro;
    int total = 0;

    arquivo = fopen(ARQUIVO_BIN, "rb");

    if (arquivo == NULL) {
        cout << "Ainda nao ha livros para exportar.\n";
        return;
    }

    texto = fopen(ARQUIVO_TXT, "w");

    if (texto == NULL) {
        cout << "Erro ao criar o arquivo TXT.\n";
        fclose(arquivo);
        return;
    }

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.ativo == 1) {
            fprintf(texto, "ID: %d\n", livro.id);
            fprintf(texto, "Titulo: %s\n", livro.titulo);
            fprintf(texto, "Autor: %s\n", livro.autor);
            fprintf(texto, "Ano: %d\n\n", livro.ano);
            total++;
        }
    }

    fclose(arquivo);
    fclose(texto);

    cout << total << " livro(s) exportado(s) para "
         << ARQUIVO_TXT << ".\n";
}

// Conta quantos livros estão ativos.
int contarLivrosAtivos() {
    FILE *arquivo;
    Livro livro;
    int total = 0;

    arquivo = fopen(ARQUIVO_BIN, "rb");

    if (arquivo == NULL) {
        return 0;
    }

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.ativo == 1) {
            total++;
        }
    }

    fclose(arquivo);
    return total;
}
