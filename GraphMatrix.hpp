#ifndef GRAPHMATRIX_HPP_INCLUDED
#define GRPAHMATRIX_HPP_INCLUDED

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

class GraphMatrix
{
	public:

	GraphMatrix(std::ifstream &i) : m_size(0), m_matrix(nullptr)
	{
		std::string tmp;
		bool read(true);
		unsigned int arrete(0);
		char tampon[128];

		while(read)
		{
			i >> tmp;

			if(tmp == "c")
			{
				i.getline(tampon, 128);
			}
			else if(tmp == "p")
			{
				i >> tmp >> m_size >> arrete;

				m_matrix = new bool*[m_size];

				for(unsigned int j(0); j < m_size; j++)
				{
					m_matrix[j] = new bool[m_size];
				}

				for(unsigned int j(0); j < arrete; j++)
				{
					i >> tmp;
					if(tmp == "c")
					{
						i.getline(tampon, 128);
						j--;
					}
					else if(tmp == "e")
					{
						unsigned int a,b;
						i >> a >> b;

						m_matrix[a-1][b-1] = true;
						m_matrix[b-1][a-1] = true;
					}
				}

				read = false;
			}
		}
	}

	~GraphMatrix()
	{
		for(unsigned int i(0); i < m_size; i++)
		{
			delete[] m_matrix[i];
		}

		delete[]m_matrix;
	}

	std::vector<unsigned int> glouton()
	{
		std::vector<int> v;
		std::vector<unsigned int> rep;
		unsigned int nbColor(1);

		for(unsigned int i(0); i < m_size; i++)
		{
			v.push_back(i);
			rep.push_back(0);
		}

		std::random_shuffle(v.begin(), v.end());

		for(unsigned int i(0); i < m_size; i++)
		{
			unsigned int couleur(1);
			while(!rep[v[i]])
			{
				bool can(true);
				for(unsigned int j(0); j < m_size; j++)
				{
					if(m_matrix[v[i]][j])
					{
						if(rep[j] == couleur)
						{
							can = false;
						}
					}
				}

				if(can)
				{
					rep[v[i]] = couleur;
				}
				else
				{
					couleur++;
					if(couleur > nbColor)
					{
						nbColor++;
					}
				}
			}
		}

		for(auto& x : rep)
		{
			x--;
		}

		return rep;
	}

	std::vector<unsigned int> nbCouleur(unsigned int it)
	{
		std::vector<unsigned int> rep(glouton());
		unsigned int nbColor(0);

		for(auto& x : rep)
		{
			if(nbColor < x)
			{
				nbColor = x;
			}
		}

		for(unsigned int i(0); i < it; i++)
		{
			unsigned int sommet(rand()%m_size);
			unsigned int couleur((rand()%(nbColor)));

			bool can(true);
			for(unsigned int j(0); j < m_size; j++)
			{
				if(m_matrix[sommet][j])
				{
					if(rep[j] == couleur)
					{
						can = false;
					}
				}
			}

			if(can)
			{
				unsigned int tmp(rep[sommet]);
				rep[sommet] = couleur;

				bool isColorEnd(true);

				for(unsigned int j(0); j < m_size; j++)
				{
					if(rep[j] == tmp)
					{
						isColorEnd = false;
					}
				}

				if(isColorEnd)
				{
					for(unsigned int j(0); j < m_size; j++)
					{
						if(rep[j] == nbColor)
						{
							rep[j] = tmp;
						}
					}
					nbColor--;
				}
			}
		}

		return rep;
	}

	private:

	unsigned int m_size;
	bool **m_matrix;
};

#endif