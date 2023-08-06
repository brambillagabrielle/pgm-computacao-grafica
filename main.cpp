#include <iostream>
#include "PGM.hpp"

using namespace std;

int main(void)
{
	// Exercício 4
	PGM ex4;
	criar(&ex4, 10, 10, 125);
	imprimir(&ex4);
	gravar(&ex4, "imagens/exercicio4.pgm");
	destruir(&ex4);

	// Exercício 5
	PGM ex5;
	criar(&ex5, 10, 10);
	imprimir(&ex5);
	setLinha(&ex5, 4, 255);
	gravar(&ex5, "imagens/exercicio5.pgm");
	destruir(&ex5);

	// Exercício 6:
	PGM ex6;
	ler(&ex6, "imagens/exercicio5.pgm");
	imprimir(&ex6);

	if (coordValida(&ex6, 10, 10))
		cout<< "\nA coordenada é válida!";
	else
		cout<< "\nA coordenada é inválida!";

	if (coordValida(&ex6, -1, 9))
		cout<< "\nA coordenada é válida!";
	else
		cout<< "\nA coordenada é inválida!";

	if (coordValida(&ex6, 9, 9))
		cout<< "\nA coordenada é válida!";
	else
		cout<< "\nA coordenada é inválida!";

	destruir(&ex6);

	// Exercício 7:
	PGM ex7;
	criar(&ex7, 50, 50);
	imprimir(&ex7);
	preencherRegiao(&ex7, 7, 7, 9, 9, 255);
	gravar(&ex7, "imagens/exercicio7.pgm");
	destruir(&ex7);

	// Exercício 8:
	PGM ex8;
	criar(&ex8, 500, 500);
	imprimir(&ex8);
	pintarListras(&ex8);
	gravar(&ex8, "imagens/exercicio8.pgm");
	destruir(&ex8);

	// Exercício 9:
	PGM ex9;
	ler(&ex9, "imagens/numeros.pgm");
	imprimir(&ex9);
	flipImagem(&ex9);
	gravar(&ex9, "imagens/exercicio9.pgm");
	destruir(&ex9);

	// Exercício 10:
	PGM ex10_1, ex10_2;
	ler(&ex10_1, "imagens/numeros.pgm");
	imprimir(&ex10_1);

	copiaSelecaoRegiao(&ex10_1, &ex10_2, 225, 200, 340, 350);
	gravar(&ex10_2, "imagens/exercicio10.pgm");

	destruir(&ex10_1);
	destruir(&ex10_2);

	cout << "\n\nPressione uma tecla para encerrar o programa\n";
	getchar();
	return EXIT_SUCCESS;
}