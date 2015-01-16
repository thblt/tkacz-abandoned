
# Schémas et modèles de données

Tkacz est conçu selon un modèle de données à deux niveaux : le premier niveau est celui du noyau du logiciel, décrit \autoref{chap:Fondamentaux}. Ce noyau, qui connaît les notions de fiches, taxinomies et relations, est encore insuffisant pour les manipuler effectivement : des modèles de données, extérieurs, décrivent les types de fiches, les taxinomies où elles peuvent entrer et les relations possibles entre elles. Ainsi, c'est le modèle standard, et pas le noyau Tkacz, qui définit les types de fiches «personne» ou «publication».

Du point de vue de l'implémentation, cette distinction est faite de la façon suivante : le noyau du logiciel (écrit en C++) charge des types de données écrits en Python[^why_python] qui représentent la forme générale des données (la forme abstraite des fiches, des taxinomies et des relations), ainsi que leur représentation dans l'interface utilisateur (présentée \autoref{chap:UIModels}). Le modèle de données standard décrit par exemple les types de fiches «personne» (physique ou morale), ou «publication».

[^why_python]: Le choix de Python est principalement dû à deux considérations : ce langage est largement répandu, facile à utiliser et à apprendre ; il dispose de nombreux outils --- y compris des notations --- pour manipuler des ensembles ; il est très facile à interfacer sur du code C/C++. L'implémentation actuelle du système de modèles fait appel à certaines structures très spécifiques de Python (notamment au niveau de la POO), mais pour autant, la dépendance à ce langage précis n'est pas un impératif, et il n'est pas impossible que  d'autres soient interpréteurs soient joints à Tkacz.

Cette conception duelle de Tkacz répond à l'impératif fondamental de ne pas figer le modèle de données : si Tkacz fournit bien un modèle standard, l'utilisateur peut l'étendre à son gré, le modifier, voire en écrire un nouveau[^fromscratch].

[^fromscratch]: L'interface graphique sera sans doute conçue en fonction du modèle standard. Dans ce cas, la conception de nouveaux schémas pourra impliquer de réécrire une partie du code d'interface.

Les modèles de données décrivent :

 1. Des types de données, qui complètent et étendent les types natifs de Tkacz.
 
 2. Des types de fiches.
 
 3. Des types de relations entre ces fiches.
 
 4. Des schémas, composés d'un ensemble de types de données, de fiches et de relations.
 
 5. Des descriptions abstraites d'interface utilisateur pour modifier certains types de données.
 
Ce chapitre présentera les quatre premiers points, le \autoref{chap:UIModels} est consacré à la description des interfaces. 
 
## Notions fondamentales

Les types de données, de fiches ou de relations sont des objets Python qui étendent des classes de base de Tkacz. Ces trois types sont quasiment identiques : la différence entre eux est principalement dans la façon dont le cœur les manipule, pas dans leur structure. Leurs superclasses sont respectivement ```TZDataType```, ```TZCardType``` et ```TZRelationshipType```, dans le paquet ```tkacz```.

Par défaut, aucune taxinomie ni relation n'est disponible, mais Tkacz propose un certain nombre de types primitifs, liés au code du noyau, et qui ne peuvent pas être remplacés. Ces types sont :

+----------------------+-------------------------+
| Nom				   | Description             | 
+======================+=========================+
| ```TZBoolean```      | Booléen : vrai/faux.                
+----------------------+-------------------------+
| ```TZDict```         | Tableau associatif
+----------------------+-------------------------+
| ```TZEnum```         | Énumération
+----------------------+-------------------------+
| ```TZFloat```        | Nombre à virgule flottante
+----------------------+-------------------------+
| ```TZInteger```      | Nombre entier
+----------------------+-------------------------+
| ```TZNumber```       | Nombre
+----------------------+-------------------------+
| ```TZSet```          | Ensemble (éventuellement ordonné)
+----------------------+-------------------------+
| ```TZString```       | Chaîne de caractères
+----------------------+-------------------------+
| ```TZVariant```      | Type variable
+----------------------+-------------------------+

Table: Liste des types primitifs avec leur description


## Types de données

La description d'un type de données se fait en combinant et/ou en étendant des types natifs, sous la forme d'une classe qui étend ```TZDataType``` ou une métaclasse dérivée (*ie*, un autre type de données, y compris un type natif).

La construction d'un type se fait en définissant des attributs typés :

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
~~~

Un type peut avoir, en plus de ses attributs, des *propriétés* : une propriété décrit le comportement de l'instance du type, mais n'est pas en soi une donnée sémantique. Un nom de personne, par exemple, peut être composé de plusieurs parties, c'est à dire d'un prénom, d'un nom de famille, éventuellement d'un second prénom, *etc.* ; ou bien être une unique séquence, comme certains noms non-occidentaux ou les noms des personnes morales. Qu'une fiche représente une personne physique ou une personne morale est un attribut de la fiche, mais pas de son attribut «nom».

Les propriétés se définissent en passant un type d'attribut au constructeur de ```TZProperty```. L'exemple ci-dessous ajoute une propriété de type nombre :

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
	
	myProperty = TZProperty(TZNumber())
~~~

Chaque type (primitif ou dérivé) fournit des évènements, sur lesquels du code peut se brancher. On connecte des méthodes à des attributs ou des propriétés avec le décorateur ```Hook``` :

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString(null=False)
	myNumber = TZNumber()
	myDate 	 = TZDate()
	
	myProperty = TZProperty(TZInteger())
	
	@Hook("myNumber.onChanged")
	def calculate(self):
		pass
~~~

Chaque attribut contient quelques propriétés fondamentales et des évènements standards :

+----------------------+---------+-------------------------------------+
| Propriété			   | Type    | Description                         |
+======================+=========+=====================================+
| ```enabled```        | Booléen | Détermine si l'attribut est activé.
+----------------------+---------+-------------------------------------+
| ```null```           | Booléen | Détermine si l'attribut a une valeur

Table: Propriétés primitives des types de données

+----------------------+-------------------------------------+
| Évènement			   | Description                         |
+======================+=====================================+
| ```onChanged```      | La valeur de l'attribut est modifiée
+----------------------+-------------------------------------+
| ```onEnabled```      | L'attribut est activé
+----------------------+-------------------------------------+
| ```onDisabled```     | L'attribut est désactivé
+----------------------+-------------------------------------+
| ```onCleared```      | L'attribut est remis à zéro
+----------------------+-------------------------------------+
| ```onSet```          | L'attribut qui était ```null``` prend une valeur.

Table: Propriétés primitives des types de données

## Types de fiches

## Types de relations

## Schémas
