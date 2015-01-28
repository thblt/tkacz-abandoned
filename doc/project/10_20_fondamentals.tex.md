
# Principes fondamentaux {#chap:Fondamentaux}

Tkacz manipule trois types d'entités fondamentaux : des *fiches*, liées entre elles par un mécanisme de *relations*, et organisées dans des *taxinomies*. Tkacz manipule ces données sous la forme d'un graphe.

## Fiches {#sec:Fond:Fiches}

La fiche est l'unité fondamentale de Tkacz. Une fiche peut représenter n'importe quoi, bien qu'elle soit pensée pour modéliser une (et une seule) entité objective. Une fiche a un *type*, qui est le type d'entité qu'elle représente :  : une personne, une publication, un évènement, *etc*. Ces types sont définis par le schéma en cours d'utilisation (cf. \autoref{chap:DataModels}). Une fiche contient deux grandes séries de données :

 1. des métadonnées structurées qui décrivent l'entité qu'elle représente (dans le cas d'une fiche personne, il s'agira par exemple de son nom, son prénom, sa date de naissance, *etc*.). Ces métadonnées peuvent être obtenue automatiquement dans certains cas : l'importation d'une référence bibliographique peut se faire depuis une base de données externe, un script étant chargé de la conversion.
 
 	La structure des métadonnées fait que la plupart des fiches n'ont pas de titre explicitement attribué : celui-ci est calculé à partir des métadonnées (une fiche représentant une personne ou une publication n'a pas besoin de titre : le nom de cette personne ou le titre, les auteurs et la date de cette publication représentent son contenu). Ainsi, une fiche d'entrée bibliographique produit son titre automatiquement (mais de façon configurable) par rapport aux données structurées qu'elle contient. Un tel titre est uniquement destiné à rendre la fiche aisément identifiable par l'utilisateur, en interne, il lui est attribué un identifiant numérique.

 2. des notes de forme libre. Il peut y avoir autant de notes que nécessaires sur une fiche. Ces notes peuvent elles-mêmes décrire des métadonnées (voir plus bas).
  
Il est possible de lier à une fiche des fichiers externes (par exemple, pour un article décrit dans une fiche référence bibliographique, l'artice lui-même en PDF). Les associations à ces fichiers sont gérées comme des métadonnées, et les fichiers sont stockés dans le dépôt Tkacz.

### Fragments

Les *fragments* sont des fiches qui peuvent être incluses dans les notes d'autres fiches, et ne sont pas *a priori* des fiches autonomes. Les images ou les citations sont des fragments. Ils se distinguent des fiches ordinaires par quelques propriétés :

 1. Ils sont généralement créés à la volée en prenant des notes : inclure une image ou copier une citation, c'est créér un fragment.

 2. Ils ont obligatoirement un contenu. Contrairement à une fiche qui peut se contenter de faire référence à une entité, un fragment la contient. Il peut exister un type de fiche tableau qui décrit un tableau, mais un fragment de type image n'a de sens que s'il contient effectivement une image.

 3. Ils peuvent être intrinsèquement liés à (au moins) une fiche : par exemple, une citation n'est jamais déconnectée de la référence dont elle est extraite. Ils peuvent être liés à plusieurs, comme dans le cas d'une citation qui apparaît à l'identique dans plusieurs éditions d'un même texte. Ils peuvent aussi être autonome (une image n'est pas forcément liée à une fiche).

 4. Ils peuvent être inclus dans d'autres fiches que celle de laquelle ils dépendent, sans perdre leur lien initial (une citation peut être citée ailleurs).
 
 5. Comme une fiche ordinaire, ils peuvent être organisés dans des taxinomies (cf. \autoref{sec:Fond:Taxinomies}).
 
 6. Ils n'apparaissent pas dans les vues standards.
 
## Relations {#sec:Fond:Relations}

Une fonction fondamentale et originale de Tkacz est sa capacité à décrire des relations complexes entre des fiches, des métadonnées et d'autres entités. Ces relations sont sémantiques, et font d'un dépôt Tkacz une sorte de graphe. Les relations entre fiches ont quelques propriétés importantes :

 1. Elles peuvent être fixées dans les métadonnées (attribution d'un auteur, par exemple) ou directement dans les notes. Ce ne sont généralement pas les mêmes relations qui sont décrites de l'une ou de l'autre façon.
 
 2. Elles sont nettement plus complexes qu'une simple relation au sens de ce terme dans un SGBDR. Une relation contient elle-même des métadonnées, et elle peut être annotée. Au sens strict, *une relation est elle-même une fiche d'un type particulier*.

Les relations les plus simples sont fixées dans les métadonnées : par exemple, l'auteur d'une publication n'est pas une chaîne de caractères, comme «W. V. O. Quine» : c'est une personne, qui est donc représentée par sa propre fiche. La métadonnée «auteur» est donc une relation vers une (ou des) fiches de type «personne». S'il n'existe pas de fiche pour cet auteur, elle est créée à la volée.

Mais même une relation comme «être auteur de» peut-être plus complexe qu'un lien simple entre deux fiches, comme on pourrait le concevoir dans un SGBDR : il n'est pas rare par exemple de trouver une publication sous pseudonyme, ou dont l'attribution est douteuse. La fiche cible peut bien contenir le(s) pseudonyme(s) en plus du nom légal (ou *des* noms légaux). Mais c'est le modèle de la relation «auteur» qui prévoit qu'elle puisse non seulement pointer sur la fiche cible, mais aussi préciser quel nom est utilisé (ou quelle graphie, ou même avec quelle faute il est copié). Ce modèle permet aussi de préciser que l'attribution est douteuse, ou bien fausse. On peut même modéliser une situation telle que «publié sous le pseudonyme qui peut correspondre à telle personne ou telle autre personne»). Dans la mesure où le modèle de données de Tkacz est extensible par l'utilisateur (cf. \autoref{chap:DataModels}), une relation permet en fait de préciser potentiellement n'importe quoi.

Qu'une relation soit une fiche est ici un avantage considérable : il peut être très utile, dans les cas d'attribution douteuse par exemple, de prendre des notes sur l'attribution elle-même (qui prétend que c'est *x*, qui prétend que c'est *y*, *etc.*)

Une relation peut aussi exister entre des données qui ne sont pas des fiches. Différents noms d'une même personne peuvent être en relation l'un avec l'autre : «FBI» est l'acronyme de «Federal Bureau of Investigation» (et par corollaire, celui-ci est la forme développée de celui-là). Ce type de relation permet, lors de l'emploi des références comme citations dans un document (par exemple en exportant la bibliographie en Bib\TeX), d'attribuer convenablement les champs ```Author``` et ```Shortauthor```.

### Corollaires

Une relation peut avoir un *corollaire*, c'est-à-dire que la relation de A et B implique une relation (de même nature ou d'une autre nature) de B vers A. Dans l'exemple de l'auteur, le lien «a pour auteur» a pour corollaire «est auteur de». Un corollaire est toujours attribué automatiquement, puisqu'il est une conséquence logique de la relation dont il est le corollaire : $Ax,y \iff Bx,y$.

Une relation est un pur corollaire lorsqu'elle ne peut pas être assignée directement : «est l'auteur de» est un exemple de pur corollaire, qui ne peut être affecté à une fiche personne, mais dérive de l'affectation de la relation «auteur» d'une fiche document à une fiche personne.

Une relation dont le corollaire est la même relation de la cible vers la source est dite *réciproque* ou *symétrique* : $Ax,y \iff By,x$
 
## Taxinomies {#sec:Fond:Taxinomies}

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
