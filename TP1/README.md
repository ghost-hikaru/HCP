# TP1 sur la découverte d'OpenMP 

## Introduction 
OpenMP, qui signifie "Open Multi-Processing," est une API (Interface de Programmation Applicative) utilisée principalement en programmation parallèle pour exploiter efficacement la puissance de calcul des processeurs multi-cœurs. Conçue pour les langages de programmation tels que le C, C++, et Fortran, OpenMP offre un moyen pratique d'ajouter des éléments de parallélisme à vos applications. 

Avec OpenMP, les développeurs peuvent spécifier des régions de code parallèles, où plusieurs threads peuvent travailler simultanément pour accélérer l'exécution des tâches. Ces threads partagent souvent des données, mais OpenMP gère la gestion des threads et la synchronisation, ce qui facilite grandement le développement de logiciels parallèles. OpenMP utilise des directives pragmatiques et des fonctions de bibliothèque pour créer et gérer les threads, répartir le travail entre eux, et synchroniser leur exécution. Cela permet aux programmeurs de tirer parti des architectures multi-cœurs sans avoir à se soucier des détails complexes de la programmation parallèle.

Dans le cadre de ce TP en C sur OpenMP, nous avons utilisé des directives et fonctions pour exploiter la puissance de calcul parallèle du processeur. Cela vous a permis d'améliorer les performances faisant fonctionner plus efficacement le programme sur des systèmes multi-cœurs.

## Installer le sujet
Le [Sujet](https://github.com/ghost-hikaru/HCP/blob/main/Instruction/openmpbeginners.gz) est disponible sur le git. 

## Compiler le sujet et exécuter le sujet 
Pour compiler le sujet ou sa correction, il faut entrer la commande suivante sur Windows: 
```Compiler le sujet
gcc -o executable OpenMPbeginners.c -fopenmp
```

```Exécuter le sujet
./executable
```

## Explication de la solution
Dans le premier exercice, il fallait implémenter une fonction prenant en paramètre une chaîne de caractères ainsi que sa taille, devant renvoyer le caractère apparaissant le plus souvent. En utilisant une directive OpenMP parallel for, une boucle for parallèle est créée, où chaque thread traite une portion du tableau clist. Chaque thread parcourt les caractères du tableau, et avec #pragma omp atomic, ils mettent à jour les compteurs counts de manière sécurisée en s'assurant que les modifications sont atomiques pour éviter les conflits de données. Une fois la boucle parallèle terminée, un autre passage à travers le tableau counts est effectué pour trouver le caractère avec le compte le plus élevé. Le caractère correspondant est stocké dans la variable result, et le nombre maximal d'occurrences est stocké dans maxCount.

Dans le deuxième exercice, la fonction à implémenter, nommée matrix_by_vector, effectue une multiplication matrice-vecteur en utilisant la programmation parallèle OpenMP. Une boucle est créée avec la directive OpenMP parallel for, où chaque thread traite une portion des lignes de la matrice A. À l'intérieur de la boucle, une variable value est initialisée à zéro. Cette variable stockera la somme des produits des éléments de la ligne de la matrice A par le vecteur b. Une deuxième boucle est créée avec la directive OpenMP parallel for pour parcourir les colonnes de la matrice A. Cette parallélisation permet de répartir le calcul sur les colonnes entre plusieurs threads. À l'intérieur de la boucle interne, la variable value est mise à jour en accumulant les produits des éléments de la ligne de A par les éléments correspondants du vecteur b. Une fois la boucle interne terminée, la variable value contient la somme des produits des éléments de la ligne i de A par le vecteur b, et cette somme est stockée dans le vecteur c à l'indice i.

Dans le troisième exercice, la fonction implémentée vise à déterminer si tous les éléments d'un vecteur sont égaux en utilisant OpenMP pour paralléliser la vérification. La première valeur du vecteur v est stockée dans la variable firstValue, ce qui servira de référence pour la comparaison ultérieure. Une variable booléenne retour est initialisée à true, supposant initialement que tous les éléments du vecteur sont égaux. Une boucle for est créée avec la directive OpenMP parallel for. Chaque thread traite une portion du vecteur v. Cela permet de vérifier simultanément plusieurs éléments du vecteur. À l'intérieur de la boucle, chaque élément du vecteur est comparé à la valeur stockée dans firstValue. Si un élément est différent, la variable retour est définie sur false. Une fois que la boucle a vérifié tous les éléments, la méthode renvoie la valeur de la variable retour, qui indique si tous les éléments du vecteur sont égaux ou non.

Le dernier exercice permet de résoudre le problème des philosophes. Un tableau forks d'objets de verrouillage OpenMP est créé pour représenter les fourchettes. Chaque philosophe a besoin de deux fourchettes (à gauche et à droite) pour manger. Ces verrous sont initialisés avec omp_init_lock. Une boucle for est utilisée pour initialiser les verrous pour chaque fourchette. Ensuite, une section parallèle est créée avec #pragma omp parallel num_threads(NTHREADS). Chaque thread dans cette section représente un philosophe. Dans la section parallèle, chaque philosophe est identifié par son numéro de thread (id) obtenu avec omp_get_thread_num(). Ils ont également deux variables, right_fork et left_fork, qui représentent l'indice des fourchettes à leur droite et à leur gauche. Il y a une logique pour garantir que les fourchettes sont prises dans un ordre spécifique pour éviter les interblocages. En fonction de leur numéro, un philosophe prendra d'abord la fourchette de droite, puis la fourchette de gauche (ou l'inverse). Lorsqu'un philosophe a les deux fourchettes, il imprime un message indiquant qu'il a deux fourchettes et peut commencer à manger. Une fois qu'il a terminé de manger, il pose les fourchettes en utilisant omp_unset_lock, ce qui les rend disponibles pour d'autres philosophes. La boucle parallèle se termine lorsque chaque philosophe a fini de manger.

Enfin, les verrous sont détruits avec omp_destroy_lock, et la mémoire allouée pour le tableau forks est libérée avec free.
## Conclusion
Nous avons pu, à travers ce TP, voir comment fonctionne OpenMP notamment en C afin de mettre en pratique du multithreading dans de multiple situation basique. Nous avons également pu l'utiliser afin de résoudre le problème des philosophes.

## 🙇 Author
#### Mathurin Melvin
- Github: [@Melvin](https://github.com/ghost-hikaru)
- Adresse mail : [melvin.mathurin@etudiant.univ-rennes.f](melvin.mathurin@etudiant.univ-rennes.fr)
#### Voisin Enzo
- Github: [@Enzo](https://github.com/Slonev0)
- Adresse mail : [enzo.voisin@etudiant.univ-rennes.fr](enzo.voisin@etudiant.univ-rennes.fr)
