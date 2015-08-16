#include "Exploradoras.h"
#include <iostream>
#include <algorithm>

static std::tuple<int, string> Exploradoras::backtracking(texto) {
	int minFriendship = -1;
	char res[];
	char girls[] = {'a', 'b', 'c', 'd', 'e'};

	int n = leer primera linea;

	for (int i = 0; i < n!; i++) {
		//complejidad e!
		int minFriendshipAux = 0;
		for(int j = 0; j < n; j++) {
			//recorro toda la lista y voy sumando en la salida parcial cuando encuentro amigas de j
			//complejidad e
			char friends[] = leer amigas de j en girls[j];
			int lower = j - 1;
			int upper = j + 1;
			int distance = 1;

			while (lower >= 0 || upper < n) {
				//complejidad e
				if (lower >= 0 && girls[lower] in friends[j]) {
					//complejidad a
					minFriendshipAux = minFriendshipAux + distance;
				}
				if (upper < n && girls[upper] in friends[j]) {
					//complejidad a
					minFriendshipAux = minFriendshipAux + distance;
				}
				lower = lower - 1;
				upper++;
				distance++;
			}
		}
		if (minFriendship == -1 || minFriendshipAux < minFriendship) {
			minFriendship = minFriendshipAux;
			res = girls;
		}

	//hago la siguiente permutación 
	//complejidad e
	std::next_permutation(girls, girls + girls.count());

	}

	return std::make_pair(minFriendship, res);

}

/*
COMPLEJIDAD TOTAL:
e! . (e . e . a  + e) = e!. e2.a + e
*/

/*
esto imprime todas las permutaciones, tengo que retocarlo 
para que devuelva la siguiente, y despues pasar a iterativo.
da para sacar el next_permutation por nuestra version de esto.
*/
void permute(char *a, int l, int r) {
   int i;
   if (l == r)
     printf("%s\n", a);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); //backtrack
       }

   }
}
