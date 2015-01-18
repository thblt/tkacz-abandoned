
# Principes fondamentaux {#chap:Fondamentaux}

Tkacz manipule trois types d'entités fondamentaux : des *fiches*, liées entre elles par un mécanisme de *relations*, et organisées dans des *taxinomies*.

## Fiches {#sec:Fiches}

La fiche est l'unité atomique de Tkacz. Une fiche peut représenter n'importe quoi, bien qu'elle représente en général une (et une seule) entité objective. Une fiche a un *type*, qui est le type d'entité qu'elle représente :  : une personne, une publication, un évènement, *etc*. Ces types sont définis par le schéma en cours d'utilisation (cf. \autoref{chap:DataModels}). Chaque fiche a un *titre*, ainsi généralement que d'autres métadonnées, et peut contenir des *notes*. Les métadonnées exactes qui peuvent être contenues dans une fiche sont déterminées par son type. 

Les *notes* liées à une fiche sont celles que prend l'utilisateur sur l'objet représenté par la fiche. Leur forme est libre, leur syntaxe est inspirée de Markdown. La syntaxe des notes est exposée \autoref{chap:CardsSyntax}.

Les métadonnées d'une fiche décrivent l'entité qu'elles représentent. Le titre est un de ces métadonnées, même si la plupart des types n'ont pas *stricto sensu* de titre[^emptypage] : celui-ci est calculé à partir des métadonnées (une fiche représentant une personne ou une publication n'a pas besoin de titre : le nom de cette personne ou le titre, les auteurs et la date de cette publication représentent son contenu). Ainsi, une fiche d'entrée bibliographique produit son titre automatiquement (mais de façon configurable) par rapport aux données structurées qu'elle contient. Un tel titre peut prendre la forme:

\tzcard{\textbf{The efficacy of AZT in the treatment of patients with AIDS…}\hfill1987

\textsc{\uline{Fischl}}, \textsc{\uline{Richman}}, \textsc{\uline{Grieco}} \textit{et \uline{al}}.\hfill \uline{N Engl J Med}}

Automatiquement calculée à partir des noms des auteurs, de l'année et du titre (éventuellement, comme ici, abrégé) d'une entrée bibliographique. Le titre d'une fiche personne prendra une forme du type:

\tzcard{\textbf{FOUCAULT, Michel}\hfill1926--1984}
 
[^emptypage]: Il existe un type «page blanche», qui a bien une métadonnée titre, et aucune autre. Mais ce type est une exception.


## Relations

Une fonction fondamentale et originale de Tkacz est sa capacité à décrire des relations complexes entre des fiches. Ces relations sont sémantiques, et font d'un dépôt Tkacz une sorte de graphe. Les relations entre fiches ont quelques propriétés importantes :

 1. Elles peuvent être fixées dans les métadonnées (attribution d'un auteur, par exemple) ou directement dans les notes. Ce ne sont généralement pas les mêmes relations qui sont décrites de l'une ou de l'autre façon.
 
 2. Elles sont nettement plus complexes qu'une simple relation au sens de ce terme dans un SGBDR. Une relation contient elle-même des métadonnées, et elle peut être annotée. Au sens strict, *une relation est elle-même une fiche d'un type particulier*.

Les relations les plus simples sont fixées dans les métadonnées : par exemple, l'auteur d'une publication n'est pas une chaîne de caractères, comme «W. V. O. Quine» : c'est une personne, qui est donc représentée par sa propre fiche. La métadonnée «auteur» est donc une relation vers une (ou des) fiches de type «personne». S'il n'existe pas de fiche pour cet auteur, elle est créée à la volée.

Mais même une relation comme «être auteur de» peut-être plus complexe qu'un lien simple entre deux fiches, comme on pourrait le concevoir dans un SGBDR : il n'est pas rare par exemple de trouver une publication sous pseudonyme. La fiche cible peut bien contenir le(s) pseudonyme(s) en plus du nom légal (voire des noms légaux). Mais c'est le modèle de la relation «auteur» qui prévoit qu'elle puisse non seulement pointer sur la fiche cible, mais aussi préciser quel nom est utilisé (ou quelle graphie, ou même avec quelle faute il est copié). Ce modèle permet aussi de préciser que l'attribution est douteuse, ou bien fausse. On peut même modéliser une situation telle que «publié sous le pseudonyme qui peut correspondre à telle personne ou telle autre personne»). Dans la mesure où le modèle de données de Tkacz est extensible par l'utilisateur (cf. \autoref{chap:DataModels}), une relation permet en fait de préciser potentiellement n'importe quoi.

Qu'une relation soit une fiche est ici un avantage considérable : il peut être très utile, dans les cas d'attribution douteuse par exemple, de prendre des notes sur l'attribution elle-même (qui prétend que c'est *x*, qui prétend que c'est *y*, *etc.*)

### Corollaires, corollaires purs et relations symétriques

Une relation peut avoir un *corollaire*, c'est-à-dire que la relation de A et B implique une relation (de même nature ou d'une autre nature) de B vers A. Dans l'exemple de l'auteur, le lien «a pour auteur» a pour corollaire «est auteur de». Un corollaire est toujours attribué automatiquement, puisqu'il est comme une conséquence logique de la relation dont le corollaire : $Ax,y \iff Bx,y$. 

Une relation est un pur corollaire lorsqu'elle ne peut pas être assignée directement : «est l'auteur de» est un pur corollaire, qui ne peut être affecté à une fiche personne, mais dérive de l'affectation de la relation «auteur» d'une fiche document à une fiche personne.

Une relation dont le corollaire est la même relation dans l'autre sens est une relation symétrique. 
 
## Taxinomies

Cette organisation se fait sous la forme de **taxinomies**. Une
taxinomie est une structure hiérarchique, comparable à un système
de fichiers, dans les entrées duquel les fiches prennent place. Contrairement
à un système de fichiers, par définition unique, plusieurs taxinomies
peuvent cohabiter, aucune fiche ne réside nécessairement dans une
taxinomie quelconque, et une fiche peut se trouver associée à plusieurs
taxons.

Une taxinomie peut être créee manuellement ou automatiquement. Les
types de fiche sont eux-mêmes des taxons, et créent une taxinomie
automatique et non modifiable (ie, associer une fiche à un type revient
à la faire rentrer dans une taxinomie)

### Construction des taxinomies

La création des taxinomies peut être automatique ou manuelle. La création automatique se fait par du code Python fourni par le schéma ou l'utilisateur, la création automatique est faite par l'utilisateur.

### Affectations des fiches aux taxons

#### Principes généraux

L'affectation peut-être manuelle (chaque fiche est ajoutée par l'utilisateur), automatique (le taxon contient certaines fiches selon certaines propriétés) ou hybride : l'affectation est automatique par défaut, mais peut être forcée. Par exemple, une taxonomie des acteurs d'un champ par activité professionnelle privilégiera une affection manuelle des fiches ; une taxonomie des publications par décennie sera automatique et l'affectation se fera en fonction de la première publication.

Les modes d'affectation automatique sont les suivants

#### Relations entre taxons

Les taxons peuvent se voir associés un certain nombre de règles d'affectation:

 -  un taxon peut contenir la totalité du contenu (ie, les fiches) de
ses enfants. Comme dans une taxinomie biologique, toutes les sous-classes
de mammifères (theria et prototheria) *sont* des mammifères ;
ou au contraire ne contenir que ce qui y est explicitement ajouté.

 -  Un taxon peut être incompatible avec un autre, ie la présence d'une
fiche dans ce taxon rend impossible sa présence dans un autre. Par
exemple, un mammifère ne peut pas être un poisson ; ou au contraire
un taxon peut en impliquer automatiquement un ou plusieurs autres. 

Un taxon peut fixer des règles pour lui-même et/ou ses enfants à un
niveau *n* ou aux niveaux *n *à *m*.

*Le lien d'une fiche à un taxon est lui-même une fiche, qui peut donc être commenté.*

Le fait qu'une taxinomie est forcément hiérarchique n'implique pas
nécessairement qu'elle soit manipulée comme telle. Il est possible
de créer des taxinomies de \og tags \fg{} ou tous les tags sont
au même niveau.

Les taxinomies ne sont pas fortement indépendantes ; elles sont gérées
en interne comme un unique arbre hiérarchique. 

## Synthèse

Tout est fiche.