
# Schémas et modèles de données {#chap:DataModels}

Tkacz est conçu selon un modèle de données à deux niveaux : le premier niveau est celui du noyau du logiciel, décrit \autoref{chap:Fondamentaux}. Ce noyau, qui connaît les notions de fiches, taxinomies et relations, est encore insuffisant pour les manipuler effectivement : des modèles de données, extérieurs, décrivent les types de fiches, les taxinomies où elles peuvent entrer et les relations possibles entre elles. Ainsi, c'est le modèle standard, et pas le noyau Tkacz, qui définit les types de fiches «personne» ou «publication».

Du point de vue de l'implémentation, cette distinction est faite de la façon suivante : le noyau du logiciel (écrit en C++) charge des types de données décrits en XML[^why_xml] et Python[^why_python] qui représentent la forme générale des données (la forme abstraite des fiches, des taxinomies et des relations), ainsi que leur représentation dans l'interface utilisateur (présentée \autoref{chap:UIModels}). Le modèle de données standard décrit par exemple les types de fiches «personne» (physique ou morale), ou «publication».

[^why_xml]: Rien n'interdit par ailleurs d'utiliser un autre langage de balisage, mais l'implémentation initiale se restreint à XML. 

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

Les types de données, de fiches, de relations ou de taxinomies sont des descriptions XML qui peuvent être étendues par du code Python. À un type correspondent généralement deux fichiers, un fichier ```.xml``` qui décrit la structure de données, et un ```.py``` qui contient le code exécutable.

L'utilisateur peut étendre le modèle de données en ajoutant des attributs ou du code. Utiliser deux langages distincts répond à un impératif de sécurité : dans la mesure où l'essentiel des extensions utilisateurs peuvent se représenter en XML, on évite de rajouter du code exécutable au sein des \glspl{depot}.

Par défaut, aucune taxinomie ni relation n'est disponible, mais Tkacz propose un certain nombre de types primitifs, liés au code du noyau, et qui ne peuvent pas être remplacés. Ces types sont :

+----------------------+-------------------------+
| Nom				   | Description             | 
+======================+=========================+
| ```array```          | Tableau
+----------------------+-------------------------+
| ```bool```           | Booléen : vrai/faux.                
+----------------------+-------------------------+
| ```dict```           | Tableau associatif
+----------------------+-------------------------+
| ```enum```           | Énumération
+----------------------+-------------------------+
| ```number```         | Nombre
+----------------------+-------------------------+
| ```set```            | Ensemble
+----------------------+-------------------------+
| ```string```         | Chaîne de caractères
+----------------------+-------------------------+
| ```variant```        | Type variable
+----------------------+-------------------------+

Table: Liste des types primitifs avec leur description

## Types de données

Le format des types de données est à peu près le même que celui des types de fiches ou de relations. Par conséquent, cette exposition va être relativement longue, mais couvrira l'essentiel de ce qui est nécessaire pour décrire n'importe quel modèle Tkacz.

Un type de données est en gros l'équivalent d'un ```struct``` en C (ou d'une classe, s'il contient du code). Tkacz gère l'héritage et le polymorphisme : un type de données peut en étendre un autre et un attribut peut être d'un type abstrait. Dans ce cas, les différents types non abstraits qui l'étendent sont proposés pour fixer la valeur de l'attribut.

### Le modèle XML

La construction d'un type se fait en définissant des attributs typés

~~~ {.xml .numberLines}
<?xml version="1.0" encoding="UTF-8"?>
<model id="myModel" version="1.0.0" xmlns="http://tkacz.thb.lt/ns/model/">

	<datatype id="myType" />

</model>
~~~

Ce code définit un type ```myType``` vide. Le paramètre ```id``` définit le nom interne du type. Il est obligatoire. Le nom interne complet est constitué de la concaténation du nom du type et de la totalité des noms de ses parents: ici, il sera ```myModel.myType```.

Ce type vide n'est pas très intéressant. Ajoutons-y des attributs :

~~~ {.xml .numberLines}
<?xml version="1.0" encoding="UTF-8"?>
<model id="myModel" version="1.0.0" xmlns="http://tkacz.thb.lt/ns/model/">

	<datatype id="myType">
		<attr type="string" id="myString" />
		<attr type="number" id="myNumber" />
	</datatype>

</model>
~~~

Les types standards disposent chacun d'un raccourci de création d'attribut. Ainsi, on peut aussi écrire :

~~~ {.xml .numberLines startFrom=5}
		<string id="myString" />
		<number id="myNumber" />
~~~

Un type peut avoir, en plus de ses attributs, des *propriétés* : une propriété décrit le comportement de l'instance du type, mais n'est pas en soi une donnée sémantique. Un nom de personne, par exemple, peut être composé de plusieurs parties, c'est à dire d'un prénom, d'un nom de famille, éventuellement d'un second prénom, *etc.* ; ou bien être une unique séquence, comme certains noms non-occidentaux ou les noms des personnes morales. Qu'une fiche représente une personne physique ou une personne morale est un attribut de la fiche, mais pas de son attribut «nom».

~~~ {.xml .numberLines startFrom=5}
		<string id="myString" />
		<number id="myNumber" />

		<property type="string" id="myProperty" />
~~~

Les champs et les propriétés ne sont pas limités aux types standards, n'importe quel type personnalisé peut être utilisé. Créons un second type qui utilise le premier :

~~~ {.xml .numberLines}
<?xml version="1.0" encoding="UTF-8"?>
<model id="myModel" version="1.0.0" xmlns="http://tkacz.thb.lt/ns/model/">

	<datatype id="myType">
		<string id="myString" />
		<number id="myNumber" />

		<property type="string" id="myProperty" />
	</datatype>
	
	<datatype id="myOtherType">
		<attr type="..myType" id="myTypeAttrA" />
		<attr type="..myType" id="myTypeAttrB" />
		
		<property type="string" id="myStringProperty" />
	</datatype>
	
</model>
~~~

Les deux points avant ```myType``` indiquent de chercher le type un niveau plus bas dans l'arbre hiérarchique. Comme ```myOtherType``` a pour identifiant complet ```myModel.myOtherType```, ```..myType``` désigne donc ```myModel.myType```. Un seul point aurait désigné ```myModel.myOtherType.myType```. Sans point initial, le nom est supposé complet: il aurait alors fallu écrire ```myModel.myType```.

Un type peut contenir un autre type: cela est utile si le type secondaire n'est utilisé que localement. Dans ce cas, on peut écrire :

~~~ {.xml .numberLines}
<?xml version="1.0" encoding="UTF-8"?>
<model id="myModel" version="1.0.0" xmlns="http://tkacz.thb.lt/ns/model/">
	
	<datatype id="myOtherType">
		<datatype id="myInternalType">
			<string id="myString" />
			<number id="myNumber" />

			<property type="string" id="myProperty" />
		</datatype>
	
		<attr type=".myInternalType" id="myTypeAttrA" />
		<attr type=".myInternalType" id="myTypeAttrB" />
		
		<property type="string" id="myStringProperty" />
	</datatype>
	
</model>
~~~

Un type défini à l'intérieur d'un autre type peut être utilisé par n'importe quel autre type, y compris dans un autre modèle.

Si un type n'est utilisé qu'une seule fois, il n'y a même pas besoin de le définir à part ni de le nommer :

~~~ {.xml .numberLines}
<?xml version="1.0" encoding="UTF-8"?>
<model id="myModel" version="1.0.0" xmlns="http://tkacz.thb.lt/ns/model/">
	
	<datatype id="myOtherType">
		<attr id="myTypeAttrA">
			<string id="myString" />
			<number id="myNumber" />
		
			<property type="string" id="myProperty" />
		</attr>
		
		<property type="string" id="myStringProperty" />
	</datatype>
	
</model>
~~~

De manière générale, 

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

#### Extension des types primitifs

S'il étend un type primitif (par exemple ```<datatype id="myStringType" extends="string" />```{.xml}), il a en plus une valeur de base : il continue d'être une chaîne avec d'autres propriétés, ce qui permet d'écrire quelque chose comme : 

~~~ {.python .numberLines}
myObject.myTypeInstance = "une chaîne"
myObject.myTypeInstance.myAttribute = true
~~~

### Code Python

## Types de fiches, types de relations, types de taxons

Décrire un type de fiche ou de relation est quasiment la même chose que décrire un type de données, à ceci près que l'élément racine ne sera pas ```datatype``` mais respectivement ```cardtype``` et ```reltype```. 

## Exemples

### La relation «attribution d'une source»

La relation d'attribution d'une source à une information se fait entre n'importe quoi et une publication. Elle contient une propriété supplémentaire, qui est un emplacement dans la publication. Cet emplacement peut s'exprimer de différentes manières : si en général il s'agit d'un numéro de page, d'une section (*L'archéologie du savoir*, III, II, d), d'une pagination spécifique (*Théétète*, 142c), ou de plusieurs paginations combinées (*Critique de la raison pure*, A20/B34)

Le type abstrait «référence bibliographique» prévoit un attribut pagination, qui décrit comment le document est paginé. Cet attribut est défini comme suit :

~~~ {.xml .numberLines}
…
<attr id="pagination">
	<datatype extends="enum" id="sectioning">
		<super>
			<extensible>true</extensible>
			<ordered>true</ordered>
			<option id="volume" />
			<option id="tome" />
			<option id="book" />
			<option id="chapter" />
			<option id="section" />
			<option id="subsection" />
			<option id="subsubsection" />
			<option id="paragraph" />
			<option id="subparagraph" />
			<option id="subsubparagraph" />
		</super>
	</datatype>
	
	<datatype id="sectionFormatting">
		<attr type="..sectioning" id="level" />
		<attr type="core.numberFormat" id="format" />
		<python>
			@bind(".level.onChange")
			def disableFormat(target, *args, **kwargs):
				target.format.enabled = target.level != "unpaginated"
		</python>
		
	</datatype>
	
</attr>
myObject.myTypeInstance.myAttribute = true
…
~~~
