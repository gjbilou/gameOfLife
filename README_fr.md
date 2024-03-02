
# Jeu de la Vie

## Vue d'ensemble du projet

Le Jeu de la Vie, est un automate cellulaire conçu par le mathématicien britannique John Horton Conway en 1970. C'est un jeu sans joueur, ce qui signifie que son évolution est déterminée par son état initial, sans nécessiter d'intervention supplémentaire de la part des joueurs humains. On interagit avec le Jeu de la Vie en créant une configuration initiale et en observant comment elle évolue.

## Règles du jeu

Le jeu se déroule sur une grille infinie bidimensionnelle de cellules carrées, chacune pouvant être dans l'un des deux états possibles, vivante ou morte. Pour chaque cellule, son état dans la génération suivante est déterminé par un ensemble de règles relatives aux états des cellules voisines :

1. **Naissance :** Une cellule morte avec exactement trois voisins vivants devient une cellule vivante (comme par reproduction).
2. **Survie :** Une cellule vivante avec deux ou trois voisins vivants reste en vie pour la génération suivante.
3. **Mort :** Une cellule vivante avec moins de deux voisins vivants meurt de sous-population, et une cellule vivante avec plus de trois voisins vivants meurt de surpopulation. De même, une cellule morte avec un nombre quelconque de voisins vivants autre que trois reste morte.

Ces règles simples conduisent à une grande variété de résultats, certains motifs initiaux menant à une croissance infinie, à des oscillations ou à une mort éventuelle.

## Objectif du projet

Cette reconstitution en langage C vise à implémenter les fonctionnalités de base du Jeu de la Vie, permettant aux utilisateurs de saisir des configurations initiales et d'observer l'évolution du système selon les règles de Conway.

## Instructions de configuration

### Prérequis

- Assurez-vous que les utilitaires **gcc** et **make** sont installés sur votre système.
- Téléchargez la [bibliothèque GUI Cairo](https://www.cairographics.org/).

### Compilation du programme

Après avoir cloné le dépôt, utilisez la commande **make** pour compiler le code source.

### Configuration de votre jeu initial

Vous pouvez configurer votre configuration initiale pour une simulation donnée dans un fichier texte. Ce fichier déterminera quelles cellules sont vivantes lorsque la simulation commence. Suivez ces étapes pour créer votre fichier de configuration :

#### 1. Choisissez votre taille de grille

La première ligne de votre fichier de configuration doit spécifier la taille de la grille. Entrez deux nombres séparés par un espace : le premier nombre pour le nombre de lignes, et le deuxième pour le nombre de colonnes.

Par exemple, pour créer une grille de 10x12, écrivez :
```
10 12
```

#### 2. Spécifiez les cellules vivantes

Après avoir défini la taille de la grille, listez les coordonnées des cellules que vous souhaitez démarrer comme vivantes. Chaque cellule est spécifiée par une paire de nombres sur une nouvelle ligne, représentant sa ligne et sa colonne. Le coin supérieur gauche de la grille est considéré comme l'origine, aux coordonnées (1, 1).

Si vous souhaitez qu'une cellule en ligne 5, colonne 5 soit vivante, ajoutez cette ligne ensuite :
```
5 5
```

Répétez cette étape pour chaque cellule que vous souhaitez démarrer vivante. Si vous avez plusieurs cellules, listez chacune sur une nouvelle ligne.

#### 3. Indiquez la fin de votre configuration

Après avoir listé toutes vos cellules vivantes, ajoutez un seul `0` sur une nouvelle ligne. Cela signale la fin de votre configuration.

Par exemple, si vous souhaitez initialiser un petit motif, votre fichier de configuration pourrait ressembler à ceci :
```
10 12

5 5
6 5
7 5

0
```

Cette configuration crée une grille 10x12 avec trois cellules en ligne verticale commençant à partir de (5, 5).

#### Notes finales

- Assurez-vous qu'il n'y a pas d'espaces supplémentaires ou de lignes après le dernier `0`.
- Enregistrez votre fichier avec une extension `.txt`.

### Exécution du programme

Avec le fichier de configuration initiale écrit, vous pouvez maintenant exécuter le programme avec le fichier de configuration dit.

```bash
./bin/final <config_file.txt>
```

### Comment jouer

- Utilisez le bouton gauche de la souris pour faire avancer le jeu.
- Activez les fonctionnalités supplémentaires affichées sous la grille en appuyant sur les boutons spécifiés sur votre clavier.
