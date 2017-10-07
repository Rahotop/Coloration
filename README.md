# Coloration

L’algorithme se décompose en deux parties.
La première est un glouton :
-On mélange les sommets.
-Pour chaque sommet :
	-On attribue la couleur la plus petite possible.

Cette coloration est peu efficace mais nous permet d’avoir une première coloration pour commencer à travailler.

La deuxième partie est une méthode basée sur le hasard qui ressemble à une recherche locale à descente simple :
-Pour un nombre d’itérations donné :
	-On choisit un sommet.
	-On choisit une couleur [0, la couleur la plus grande utilisée[
	-On vérifie que la couleur est applicable. 
	-Si elle l’est :
		-On applique la couleur sur le sommet.
		-On vérifie que la couleur précédente du sommet est toujours active.
		-Si elle ne l’est pas :
			-On bascule tous les sommets de la couleur maximale vers la couleur vide.
