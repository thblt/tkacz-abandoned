
# Schémas et types de données

Le modèle de données de Tkacz n'est pas codé en dur dans le noyau du logiciel. Ce noyau, écrit en C++, fournit principalement l'abstraction du stockage, les interfaces utilisateurs et la forme générale de données (la forme abstraite des fiches, des taxinomies et des relations). La description des types de données manipulées par dépôt donné se fait à l'aide de modèles écrits en Python[^why_python].

[^why_python]: Le choix de Python est principalement dû à deux considérations : ce langage est largement répandu, facile à utiliser et à apprendre ; il dispose de nombreux outils --- y compris des notations --- pour manipuler des ensembles ; il est très facile à interfacer sur du code C/C++. L'implémentation actuelle du système de modèles fait appel à certaines structures très spécifiques de Python (notamment au niveau de la POO), mais pour autant, la dépendance à ce langage précis n'est pas un impératif, et il n'est pas impossible que  d'autres soient interpréteurs soient joints à Tkacz.

Grossièrement, le cœur fournit un gestionnaire de données sémantiques et les modèles décrivent la structure sémantique de ces données. Jusqu'à ce point de ce document, les mécanismes de stockage et les types de données et de relations présentés (fiches, taxonomies, relations) relevaient du cœur du logiciel ; mais les exemples (types de fiches, taxinomies, exemples de relations) ne dépendaient que des modèles.

Cette conception duelle de Tkacz répond à l'impératif fondamental de ne pas figer le modèle de données : si Tkacz fournit bien un modèle standard, l'utilisateur peut l'étendre à son gré, le modifier, voire en écrire un nouveau[^fromscratch].

[^fromscratch]: L'interface graphique sera sans doute conçue en fonction du modèle standard. Dans ce cas, la conception de nouveaux schémas pourra impliquer de réécrire une partie du code d'interface.

Les modèles de données décrivent :

 * Des types de données, qui complètent et étendent les types natifs de Tkacz.
 
 * Des types de fiches.
 
 * Des types de relations entre ces fiches.
 
 * Des schémas, composés d'un ensemble de types de données, de fiches et de relations.
 
 * Des descriptions abstraites d'interface graphique pour modifier certains types de données.
 
## Notions fondamentales

Les types de données, de fiches ou de relations sont des objets Python qui étendent des classes de base de Tkacz. Ces trois types sont extrêmement proches : la différence entre eux est dans la façon dont le cœur les manipule, pas dans leur structure. Leurs superclasses sont respectivement ```TZDataType```, ```TZCardType``` et ```TZRelationshipType```, dans le paquet ```tkacz```.

Les éléments d'interface graphiques sont décrits en XML. Ils sont présentés  \autoref{sec:UIModels}.

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

Un type peut avoir, en plus de ses attributs, des *propriétés* : une propriété décrit le comportement de l'instance du type, mais n'est pas en soi une donnée sémantique. 

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
	
	myProperty = TZProperty(TZInteger())
~~~

Chaque type (primitif ou dérivé) fournit des évènements, sur lesquels du code peut se brancher. 

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


### Types primitifs

Tkacz fournit un ensemble de types «natifs». Ces types peuvent être surchargés, mais pas remplacés.

Ces types sont :

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

### Extension des types natifs

## Types de fiches

## Types de relations

## Schémas

## Interface utilisateur {#sec:UIModels}

Voici la description de l'interface de saisie d'un nom de personne :

~~~ {.xml .numberLines}
<block>
<if propname="simple">
	<lineinput bind="name" />
<else>
	<lineinput bind="name" />
	<hr />
	<lineinput bind="prefix" class="small" />
	<lineinput bind="firstName" class="small" />
	<lineinput bind="middleName" class="small" />
	<lineinput bind="vonPart" class="small" />
	<lineinput bind="lastName" class="small" />
	<lineinput bind="suffix" class="small" />
</else></if>
</block>
<checkbox bind="simple" />
~~~