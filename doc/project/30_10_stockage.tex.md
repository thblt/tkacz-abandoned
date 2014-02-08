# Format de stockage

Un dépôt Tkacz est un répertoire du système de fichiers, qui n'est pas destiné à être manipulé par l'utilisateur. Il peut être présenté comme un bundle (sur OS X) ou stocké zippé (sur les autres systèmes) pour empêcher toute manipulation destructrice. 

## Format d'un dépôt

Un dépôt combine un dépôt git[^depot] et une base de données SQLite qui sert de cache. Un dépôt vide a donc la structure suivante:

\begin{figure}[H]
\dirtree{%
.0 \hspace{-1.2em}/. % Dirty dirtree hack 
%                      to align correctly 
%                      to left edge.
.1 .git.
.2 ….
.1 .tkacz.
.2 db\DTcomment{Fichiers SQLite}.
.3 ….
.2 manifest\DTcomment{Déclarations Tkacz de base (Yaml)}.
}
\end{figure}

[^depot]: Dans ce document, le mot «dépôt» seul fait *toujours* référence à un dépôt Tkacz.

Le fichier \directory{.tkacz / manifest} est une représentation JSON
de la structure détaillée ci-dessous. évidemment 

~~~ json
{
    "tkacz": {
        "frameworkVersion": [0,1,0],
        "formatVersion":    [0,1,0],
        "schemaId":         "core",
        "schemaVersion":    [0,1,0]
    },
    "repository": {
        "uuid":             "03095EEF-6C87-430B-A00E-440616196C31",
        "name":             "As set by the user"
    },
    "core": {}
}
~~~

Les clés ```tkacz```, ```repository``` et ```core``` (options du schéma standard) et de façon générale toutes les clés racines vérifiant ```[a-zA-Z]+[a-zA-Z0-9_]*` sont réservées, les extensions ou les schémas tiers peuvent inscrire leur paramétrage dans des clés au format ```com.domaine.nom``` (à la Java).

## Stockage des fiches

Les fiches sont sauvegardées comme des fichiers gérés par Git, dans des dossiers correspondant à leurs types, par exemple \directory{person / collective}. Leur nom est un numéro attribué séquentiellement pour le dépôt entier (indépendemment du type donc). Tous les noms vérifiant ```[0-9]+``` sont donc réservés pour les fiches au niveau du suivi des versions. 

Le dépôt n'utilise qu'une seule branche, ```master```.

L'usage de Git fait ici est assez particulier: chaque message de commit décrit l'état des références, c'est à dire la fiche qui sert de source et la position dans cette fiche. 

Quand Tkacz contrôle l'éditeur de texte, il commite automatiquement les changements, sans contrôle possible de l'utilisateur, dans les situations suivantes:

 1. La saisie ou l'effacement se poursuit, mais la position du curseur a changé.
 
 2. L'utilisateur commence à saisir du texte après en avoir effacé.
 
 3. L'utilisateur commence à effacer du texte après en avoir saisi.
 
 4. La référence ou l'emplacement dans la référence a changé.
 
 5. L'utilisateur coupe du texte.
 
 6. L'utilisateur colle du texte.
 
Si un éditeur externe est utilisé, un commit est réalisé à chaque modification du fichier[^edext]. 

[^edext]: Il est plausible qu'il soit en fait impossible d'utiliser un éditeur pour lequel Tkacz ne puisse pas suivre chaque modification. En effet, la fonctionnalité fondamentale de suivi des ajouts et modifications et de leur rattachement à des emplacements précis des sources nécessite un suivi extrêment précis des modifications. Autrement dit, seul peut sans doute être utilisé un éditeur qui sauvegarde à chaque caractère modifié.

### Format des messages de commit

#### Commits sur modification

Le format d'un message de commit en cours d'édition est une représentation JSON (minimisée) de la structure:

~~~ json
{
    "operation": 1
    "using":     234,
    "position": {
        "page": "x"
    }
}
~~~

```operation``` décrit l'action de l'utilisateur qui justifie le commit. Le numéro correspond à l'énumération ci-dessus.

Avec cette réserve que le format de  ```position```, s'il est obligatoirement un dictionnaire, n'est pas déterminé par avance, et dépend du type de fiche. En imaginant des notes prises à la volée sur un enregistrement audio, ```position``` pourrait avoir un format exprimé en heures:minutes:secondes :

~~~ json
{
    "position": {
        "time": [0, 12, 34]
    }
}
~~~


Si une fiche est modifiée sans référence ouverte, le message de commit est un arbre JSON vide : ```{}```

#### Commits vides

Des messages supplémentaires sont produits à l'ouverture et à la fermeture d'une ressource, avec des commit vide:

~~~ json
{
    "opening": 123
}
~~~

et:

~~~ json
{
    "closing": 123
}
~~~

Un dernier type de message permet d'associer une donnée déjà saisie à une autre ressource:

~~~ json
{
    "link": 72,
    "from": [132, 21],
    "to":   [135, 12]
}
~~~

```from``` et ```to``` sont ici des paires ligne/colonne.

### Calcul des diffs, suivi de l'origine et déplacement de paragraphes

Le *déplacement* de blocs de texte est un problème sérieux que les diff classiques ne permettent pas de résoudre. Or, un bloc déplacé doit continuer à être associé à son origine. Plusieurs solutions semblent possibles:

 * Commit automatique à chaque opération couper/copier/coller.
 
 * “Lester” les copies/coupes avec les informations d'origine de la source et les porter dans le commit lors du collage. *Cette option exclut absolument d'utiliser un autre éditeur de texte que celui de Tkacz*.

## Structure du cache

La totalité des données utiles se trouve dans les fiches elle-même, ce qui signifie que seul le dépôt git doit être copié pour cloner entièrement 