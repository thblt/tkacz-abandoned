# Sélection et recherche

La sélection et la recherche utilisent le mécanisme de la taxinomie
pour rechercher des notes. Chaque taxon peut être conçu comme un ensemble
de fiches. Les expressions de recherche prennent la forme suivante:

\texttt{{[}Publications{]} 'Michel Foucault' date < \{3 jan 1950\}}

La recherche répond à une logique globalement ensembliste ; les opérations
fondamentales de la théorie des ensembles (intersection, union, différence,
différence symétrique) forment les opérateurs principaux du mécanisme
de recherche. 

À terme, il est prévu de faciliter l'usage de ce mécanisme de recherche
par une interface graphique d'élaboration des requêtes et/ou une formulation
des requêtes dans un langage formalisé proche du langage naturel.

## Syntaxe

La totalité des opérateurs peuvent manipuler quatre types de propriétés,
soit les trois types d'ensembles :

```set```
:   Un ensemble de fiches ou de taxons (c'est pareil, un taxon n'est qu'un ensemble de fiches)

```strset``` 
:   Un ensemble de chaînes.

```attrset```
:   Un ensemble de noms d'attributs ou de relations.

Et un type complexe, repéré par les accolades, spécifiques à certain
type d'attributs, par exemple les dates.

Il n'existe pas de type « fiche unique » ou « chaîne \fg{}
: tout est un ensemble, qui peut ne contenir qu'un élément.


## Opérateurs de groupement

```[ ]```
:   Sélectionne un taxon par son nom : ```[str]```.

Les ambiguités peuvent être résolues en donnant un parent du taxon
au format ```[parent/taxon]```, un parent plus lointain ```[parent/.../taxon]```
ou le nom de la taxinomie ```[@taxinomie: parent/taxon]``` ou une combinaison:
```[@taxinomie: parent//taxon]```.

```" "```
:   Sélectionne une fiche par son nom. 

Une fiche peut être aussi sélectionnée directement par son numéro.

Ces deux premiers opérateurs utilisent la virgule comme séparateur.
```[taxon1, taxon2]``` est un ensemble de taxons, et donc renvoie une
valeur de type ```set```.

```()```

:   Les parenthèses augmentent la priorité d'une expression (cf. \vref{OperateursPriorite}). Rien de très original. L'expression ```A+B*C``` sera évaluée implicitement comme l'union de ```A``` et de l'intersection de ```B``` et ```C```. Avec des parenthèses telles que ```(A+B)*C```, elle renverra l'intersection de ```C``` et de l'union de ```A``` et ```B```.

## Opérateurs binaires

```:```

:   ```attribut:set``` ou ```attribut:str``` retourne l'ensemble des fiches dont l'attribut ```a``` a au moins une valeur dans ```expr```. 



```::```
:   ```a::expr``` retourne l'ensemble des fiches dont l'attribut ```a``` a toutes ses valeurs dans expr.



```<```
:   Strictement inférieur à, pour les attributs où cela à un sens.



```<=```
:   Inférieur ou égal où, pour les attributs où cela à un sens.


 
```>```
:   Strictement supérieur à, pour les attributs où cela à un sens.
 
 
 
```>=```
:   Supérieur ou égal où, pour les attributs où cela à un sens.
 
 
 
```&```
:   intersection ($\cap$). c'est l'opérateur implicite. ```A&B``` ou ```AB``` retournent l'intersection des taxons ```A``` et ```B```. L'intersection est symétrique; ```A&B = B&A``` 



```|```
:   union ($\cup$). ```A|B``` retourne l'ensemble des fiches de ```A``` et de ```B```. L'union est symétrique; ```A|B = B|A```



```-```
:   différence ($\backslash$). ```A-B``` renvoie l'ensemble ```A``` moins l'ensemble ```B```. La différence n'est pas symétrique (l'intersection de ```A-B``` et ```B-A``` est vide : $(A\backslash B)\cap(B\backslash A)=\emptyset$.)


```^```
:   différence symétrique ($\bigtriangleup$). ```A^B``` renvoie la totalité des fiches de ```A``` ou ```B``` mais pas les deux. ```A^B = (A+B)-(B*A)```. 


## Opérateurs unaires

```-``` 
:   Inverse. ```-expr``` renvoie la totalité des fiches non contenues dans ```expr```. ```-expr = {*```-expr}

```:``` 
:   équivalent approximatif de ```:``` sans spécifier le nom de l'attribut : ```*:expr``` renvoie toutes les fiches liées à expr. ```* :expr``` doit être un ensemble.

```:*```
:   ```expr``` 


## Autres termes

```*```
:   L'ensemble des fiches du dépôt. 

```[ ]```
:   Délimite une construction complexe spécifique à un type de données, par exemple une date.

```" "```
:   Délimite une chaîne pour la recherche en plein texte.
Isolé, il renvoie l'ensemble des fiches dans lesquelles ce texte a
été trouvé ; sinon il peut être utilisé pour la recherche par attributs (```:```, ```::```)

```\```
:    Caractère d'échappement.


## Priorité {#OperateursPriorite}

Les expressions sont évaluées avec les priorités suivantes. (1) et
(2) précisent qu'il s'agit, respectivement, de la version unaire ou
binaire d'un opérateur.

+----------+------------+
| Priorité | Opérateurs |
+============+==========+
| 1        | Opérateurs de groupement
+----------+------------+
| 2        | Opérateurs unaires
+----------+------------+
| 3        | &
+----------+------------+
| 4        | - (binaire)
+----------+------------+
| 5        | /

Table: Priorité des opérateurs de recherche



## Synonymie

Pour des raisons de clarté, les opérateurs natifs ont les synonymes
suivants:

+------------+-----------+
| Opérateurs | Synonymes |
+============+===========+
| :          | in
+------------+-----------+
| ::         | 
+------------+-----------+
| &          | and 
+------------+-----------+
| |          | or
+------------+-----------+
| -          | andnot
+------------+-----------+
| \          | xor
+------------+-----------+
| *          | all
+------------+-----------+

Table: Synonymes des opérateurs de recherche

Les versions localisées pourraient implémenter ces synonymes dans
leur langue.

