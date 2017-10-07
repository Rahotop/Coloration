#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include "GraphMatrix.hpp"

int main(int argc, char **argv)
{
	if(argc >= 2)
	{
		std::string nomOut(argv[1]);
		nomOut += ".out";
		std::ofstream out(nomOut.c_str());

		std::srand(unsigned(std::time(0)));

		std::ifstream txt(argv[1]);

		GraphMatrix graph(txt);

		std::vector<unsigned int> rep(graph.nbCouleur(atoi(argv[2])));

		unsigned int nbCouleur(0);

		for(auto& x : rep)
		{
			if(x > nbCouleur)
			{
				nbCouleur = x;
			}
		}

		out << nbCouleur << std::endl;

		for(auto& x : rep)
			out << x << " ";
	}
	else
	{
		std::cout << "Veuillez preciser en argument le chemin du fichier et le nombre d'iteration a effectuer" << std::endl;
	}

	return 0;
}