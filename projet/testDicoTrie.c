#include <time.h>
#include "../td8/trie.h"
#include "../td3/mystring.h"
#include "utils.h"

int main(int ac, char**av) {
	clock_t debut,fin,debut1,fin1;

	if (ac!=2 && ac!=3) { printf("Usage : %s ficher_dico fichier_a_verifier\n",av[0]); exit(EXIT_FAILURE);}

	// Nombre de mots du dico
	int nbDicoWords=0;
	int nbTextWords=0;
	FILE* f=fopen(av[1],"r");
	char mot[512];
	while (lecture(f,mot)) nbDicoWords++;
	fclose(f);
	printf("Number of words in the dictionary: %d\n", nbDicoWords);

	f=fopen(av[2],"r");
	while (lecture(f,mot)) nbTextWords++;
	fclose(f);
	printf("Number of words in the file to verify: %d\n", nbTextWords);

	FILE* ftemps=fopen("temps.dat","w");
	for (int k=nbDicoWords; k>1; k-=nbDicoWords/100) {
		// int k=nbDicoWords;
		tree_t tree=trie_new();
		f=fopen(av[1],"r");

		/*
		   Lecture du dictionnaire : uniquement les skip premiers mots.
		   On fait 100 mesures sur le dico.
		 */
		debut=clock();
		for (int i=0; i<k; i++) {
			lecture(f,mot);
			trie_insert(strdup(mot),tree);
			// printf("%s\n",mot);
		}
		fin=clock();
		fclose(f);

		printf("Time to read the dictionary with %d words: %lf\n", k, ((double)fin-debut)/CLOCKS_PER_SEC);

		// taille = /* un double qui est la taille réelle du dictionnaire en Moctets. A calculer ici */
		double taille = trie_memory_usage(tree);


		printf("Taille du dictionnaire with %d words: %lf\n", k, taille);

		int noFound=0;
		f=fopen(av[2],"r");
		debut1=clock();
		// Verification du fichier
		while (lecture(f,mot)) {
			if (mot[0] != 0) {
				if (trie_lookup(mot,tree) == 0) {
					noFound++;
					// printf("Erreur : %s n'est pas dans le dictionnaire\n",mot);
				}
			}

		}
		fin1=clock();
		fclose(f);
		printf("Time to verify the file with dictionary with %d words: %lf\n", k, ((double)fin1-debut1)/
		       CLOCKS_PER_SEC);
		printf("Number of words not found in the dictionary: %d\n", noFound);

		/*
		   On ecrit dans le fichier les données de nombre de mots du dico, taille mémoire réelle, et temps CPU de la vérification
		 */
		fprintf(ftemps,"%d %lf %lf\n",k,taille,((double)fin1-debut1)/CLOCKS_PER_SEC);

		/* Liberation dictionnaire */
		tree=trie_delete(tree);
		free(tree);
	}
	fclose(ftemps);
	/*
	   Trace avec gnuplot des données enregistrée dans le fichier
	   f(x) est la fonction théorique de taille mémoire en fonction du nombre de mots
	   g(x) celle de la complexité
	 */

	system("gnuplot -p -e \"f(x) = a * (x) + b ; fit f(x) 'temps.dat' u 1:2 via a,b;"
	       "set y2range [0:100];set y2tics nomirror;"
	       "plot 'temps.dat' u 1:2 with line lt 4 axis x1y2 title 'Taille', a * (x) + b  with line lt 6 axis x1y2 title 'Fit Taille';"
	       "g(x) = c * (x) + d ;fit g(x) 'temps.dat' u 1:3 via c,d;"
	       "replot 'temps.dat' u 1:3 with line lt 2 title 'Recherchep', g(x)  with line lt 8 title 'Fit Recherche'; quit\"");

}