#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Dados da PGM
struct PGM
{

    string tipo;
    int largura;
    int altura;
    int vmax;
    unsigned char *pixels;

    PGM()
    {
        pixels = nullptr;
        largura = 0;
        altura = 0;
        vmax = 255;
        tipo = "";
    }
};

// Descarta os dados alocados de uma PGM
void destruir(PGM *pgm)
{
    if (pgm->pixels)
        delete pgm->pixels;

    pgm->pixels = nullptr;
    pgm->largura = 0;
    pgm->altura = 0;
    pgm->tipo = "";
    pgm->vmax = 255;
}

// Imprime os dados de uma PGM
void imprimir(PGM *pgm)
{
    cout << "\n * PGM * \n";
    cout << "Tipo: " << pgm->tipo << endl;
    cout << "Dimensao: " << pgm->largura << "x" << pgm->altura << endl;
    cout << "vMax: " << pgm->vmax << endl;

    if (pgm->pixels)
        cout << "Vetor de pixels: " << &(pgm->pixels) << endl;
    else
        cout << "Vetor de pixels: NULL\n";
}

// Cria uma nova PGM com todos os pixels na cor preto (0), caso a PGM não exista
void criar(PGM *pgm, int altura, int largura)
{
    if (pgm->pixels)
        delete pgm->pixels;

    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->largura = largura;
    pgm->altura = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = 0;
}

// Grava na memória uma PGM de acordo com o caminho recebido
bool gravar(PGM *pgm, string caminho)
{
    if (!pgm->pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "Erro ao gravar a PGM: caminho do arquivo invalido\n";
        return false;
    }

    arq << pgm->tipo << endl;
    arq << pgm->largura << " " << pgm->altura << endl;
    arq << 255 << endl;

    int tam = pgm->largura * pgm->altura;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)pgm->pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}

// Lê a linha de um arquivo que contém a PGM, ignorando espaços em branco e comentários
string lerLinha(std::ifstream &arq)
{
    string linha = "", dadoLido = "";
    while (!arq.eof())
    {
        linha = "";
        std::getline(arq, linha);
        if (linha.size() > 0 && linha[0] != '#')
            return linha;
    }

    return linha;
}

// Lê um arquivo contendo uma PGM, utilizando a função lerLinha como auxiliar
bool ler(PGM *pgm, string caminho)
{
    ifstream arq;
    string dado;
    stringstream str;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "Erro ao abrir o arquivo: endereco do arquivo invalido!\n";
        return false;
    }

    dado = lerLinha(arq);
    if (dado == "P2")
        pgm->tipo = dado;
    else
    {
        cout << "Erro ao ler o tipo da imagem\n";
        return false;
    }

    dado = lerLinha(arq);
    str = stringstream(dado);
    if (!(str >> pgm->largura))
    {
        cout << "Erro ao ler a largura\n";
        return false;
    }

    if (!(str >> pgm->altura))
    {
        cout << "Erro ao ler a largura\n";
        return false;
    }

    dado = lerLinha(arq);
    str = stringstream(dado);
    if (!(str >> pgm->vmax))
    {
        cout << "Erro ao ler vMax\n";
        return false;
    }

    if (pgm->pixels)
        delete pgm->pixels;

    int tam = pgm->largura * pgm->altura;

    pgm->pixels = new unsigned char[tam];

    int i = 0, p;
    while (!arq.eof())
    {
        if (arq >> p)
        {
            if (i < tam)
                pgm->pixels[i] = (unsigned char)p;
            i++;
        }
        else
            break;
    }

    if (i != tam)
    {
        cout << "Erro ao ler os pixels!\n";
        return false;
    }

    arq.close();

    return true;
}

// Retorna a cor de um pixel encontrado com a coordenada (x,y) recebida
unsigned char getPixel(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return 0;

    return pgm->pixels[y * pgm->largura + x];
}

// Altera a cor de um pixel encontrado com a coordenada (x,y) recebida
void setPixel(PGM *pgm, int x, int y, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    pgm->pixels[y * pgm->largura + x] = cor;
}

/*
Exercício 4:
Crie uma função para criar uma imagem. A função deve conter os seguintes parâmetros:
*/
void criar(PGM *pgm, int largura, int altura, unsigned char corFundo)
{
    if (pgm->pixels)
        delete pgm->pixels;

    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->largura = largura;
    pgm->altura = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = corFundo;
}

/*
Exercício 5:
Crie uma função para preencher uma determinada linha de uma imagem PGM com uma
cor específica (branco, cinza ou preto).
*/
void setLinha(PGM *pgm, int linha, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    if (linha >= pgm->altura)
        return;

    for (int x = 0; x < pgm->largura; x++)
        pgm->pixels[linha * pgm->largura + x] = cor;
}

/*
Exercício 6:
Crie uma função para verificar se as coordenadas de um pixel passadas por parâmetro
são válidas.
*/
bool coordValida(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return false;

    if (x >= 0 && y >= 0 && x < pgm->largura && y < pgm->altura)
        return true;

    return false;
}

/*
Exercício 7:
Crie uma função para preencher uma região de uma imagem PGM com uma
determinada cor (branco, cinza ou preto). A região é definida pelas coordenadas P1(x1,
y1) e P2(x2,y2).
Observação: preencher a região somente das coordenadas válidas (utilize a função
criada no exercício 6).
*/
void preencherRegiao(PGM *pgm, int x1, int y1, int x2, int y2, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    for (int y = y1; y < y2; y++) {

        for (int x = x1; x < x2; x++) {

            if (coordValida(pgm, x1, y1) && coordValida(pgm, x2, y2))
                pgm->pixels[y * pgm->largura + x] = cor;

        }

    }
}

/*
Exercício 8:
Crie uma imagem PGM de 500x500 pixels com fundo preto (colocar o valor zero para
todos os pixels). Em seguida, defina uma linha branca a cada 50 linhas da imagem.
*/
void pintarListras(PGM *pgm)
{
    if (!pgm->pixels)
        return;
    
    for (int y = 0; y < pgm->altura; y += 50)
    {

        for (int x = 0; x < pgm->largura; x++)
            pgm->pixels[y * pgm->largura + x] = 255;

    }
}

/*
Exercício 9:
Crie um método para inverter a imagem verticalmente (flip).
*/
void flipImagem(PGM *pgm)
{
    if (!pgm->pixels)
        return;

    int aux;
    for (int y = 0; y < pgm->altura / 2; y++)
    {

        for (int x = 0; x < pgm->largura; x++)
        {

            aux = pgm->pixels[y * pgm->largura + x];
            setPixel(pgm, x, y, pgm->pixels[(pgm->altura - y - 1) * pgm->largura + x]);
            setPixel(pgm, x, (pgm->altura - y - 1), aux);
            
        }

    }
}

/*
Exercício 10:
Considere uma imagem PGM de entrada e uma região definida pelas coordenadas P1(x1,
y1) e P2(x2,y2). Desenvolva uma função para criar uma imagem de saída, a qual possui a
mesma dimensão da imagem de entrada e a cor de todos os pixels é preta. Em seguida,
copie a região definida na imagem de entrada para a imagem de saída.
*/
void copiaSelecaoRegiao(PGM *pgm_1, PGM *pgm_2, int x1, int y1, int x2, int y2)
{
    if (!pgm_1->pixels)
        return;

	criar(pgm_2, pgm_1->altura, pgm_1->largura);
	imprimir(pgm_2);

    for (int y = y1; y < y2; y++) {

        for (int x = x1; x < x2; x++) {

            if (coordValida(pgm_1, x1, y1) && coordValida(pgm_2, x2, y2))
            {
                unsigned char pixel = getPixel(pgm_1, x, y);
                setPixel(pgm_2, x, y, pixel);
            }

        }

    }
}

#endif