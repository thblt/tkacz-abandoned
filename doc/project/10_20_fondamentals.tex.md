
# Principes fondamentaux {#chap:Fondamentaux}

Tkacz manipule trois entités fondamentales : des *fiches*, organisées dans des *taxinomies*, et reliées par un système de *relations*.

## Fiches {#sec:Fiches}

### L'objet fiche

La **fiche** est l'unité atomique de Tkacz. Une fiche a un **type**
(cf. \vref{sub:Types}); la liste complète des types n'est pas fixée
*a priori*. Chaque fiche a un **titre**, permet la prise
de notes, et est identifiée par un numéro unique attribué séquententiellement
à la création. 

Le titre devrait être unique et identifie la fiche de façon pour l'utilisateur.
Sa forme est par défaut libre, mais peut être imposée par certains
types. Par exemple, une fiche d'entrée bibliographique produit son
titre automatiquement (mais de façon configurable) par rapport aux
données structurées qu'elle contient. Un tel titre peut prendre la
forme:

\tzcard{\textbf{The efficacy of AZT in the treatment of patients
with AIDS…}\hfill1987

\textsc{\uline{Fischl}}, \textsc{\uline{Richman}}, \textsc{\uline{Grieco}} \textit{et \uline{al}}.\hfill \uline{N
Engl J Med}}

Automatiquement calculée à partir des noms des auteurs, de l'année
et du titre (éventuellement, comme ici, abrégé) d'une entrée bibliographique.
Le titre d'une fiche personne prendra une forme du type:

\tzcard{\textbf{FOUCAULT, Michel}\hfill1926--1984}

Des notes, écrites dans un format inspiré de Markdown.

### Attributs et liens

Une fiche, à l'exception du type minimal (qui modélise réellement
une feuille blanche avec un titre), contient un certain nombre d'attributs,
qui sont les données sémantiques, et de relations.

#### Attributs {#par:attributs}

Les attributs sont les propriétés sémantiques qui décrivent l'objet
modélisé par une fiche. Certains attributs sont des liens vers d'autres
fiches. L'auteur d'un livre (dans une fiche de notice bibliographique)
est manipulé comme un lien vers une fiche personne; si cette fiche
n'existe pas, elle est créée automatiquement avec les valeurs disponibles.

Il existe trois espèces d'attributs:
 -  Il peut être un objet primitif, comme une chaîne, un nombre ou une
date, ou un ensemble d'objets primitifs, comme une liste ou un ensemble.


Dans une entrée de type \og notice bibliographique \fg{}, le numéro
d'édition est un tel attribut. Ils sont relativement rares.

 -  Il peut être d'un type complexe, lui-même composé d'autres attributs
(voir \vref{sub:Types}).


Dans une entrée de type \og personne \fg{}, le nom de la personne
est un type complexe formé de chaînes qui distingue les composants
du nom. Ce type a aussi du code qui lui permet de lire et de mettre
en forme un nom.

 -  Il peut être un **lien** vers une autre fiche d'un type donné. 
 
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

## Relations


Une fonction fondamentale et originale de Tkacz est sa capacité à décrire des relations complexes entre des fiches. Ces relations sont sémantiques, et organisent un dépôt Tkacz sous la forme d'un graphe. 

Au plus simple, une relation est un simple pointeur d'une fiche vers une fiche cible. L'auteur d'un document, par exemple, est un lien vers une fiche personne, et pas une chaîne de caractères. Certaines relations sont plus élaborées : un texte publié sous pseudonyme verra l'auteur attribué par un lien vers la fiche de personne, mais ce lien stockera aussi le pseudonyme retenu. Une attribution d'auteur peut-être douteuse, ou au contraire certaine pour un texte publié anonymement. Ces informations sont stockées au niveau de la relation.



### Le lien simple 


### La relation

est un attribut complexe, qui permet de lier des fiches entre elles
de façon moins formelle et plus fine. Une relation a une **nature**,
qui est l'équivalent du type d'une fiche. Dans certains cas, un lien
peut être remplacé par une relation. Par exemple, dans un document
historique, l'attribution de l'auteur peut être douteuse — «auteur
probable» est une relation, car le lien simple ne suffit pas
— il faut sans doute préciser la nature du doute, les différentes
sources, etc.

Une relation peut aussi décrire des relations entre entités : «membre
de» ou «ami de», «frère de», etc.

Une relation peut être réciproque ou non. Dans l'exemple qui précède,
les deux dernières sont nécessairement réciproques. Une relation peut
aussi avoir un **corollaire**. La relation «A est membre de B»
(dans cet exemple, B est par exemple une personne morale) a pour corollaire
«B a comme membre A»

Une relation est de type «cite»  ou «évoque» , qui
permet de commenter un livre en le liant à ce qui fait son objet. 

Formellement, une relation est toujours un prédicat à deux places et représente un nœud d'un graphe. Lorsque une fiche présente la même relation a plusieurs autres fiches, la relation est assignée autant de fois qu'il y a de fiches cibles.

### Corollaires, corollaires purs et relations symétriques

Une relation peut avoir un *corollaire*, c'est-à-dire que la relation de A et B implique une relation (de même nature ou d'une autre nature) de B vers A. Dans l'exemple de l'auteur, le lien «a pour auteur» a pour corollaire «est auteur de». Un corollaire est toujours attribué automatiquement, puisqu'il est comme une conséquence logique de la relation dont le corollaire : $Ax,y \iff Bx,y$. 

Une relation est un pur corollaire lorsqu'elle ne peut pas être assignée directement : «est l'auteur de» est un pur corollaire, qui ne peut être affecté à une fiche personne, mais dérive de l'affectation de la relation «auteur» d'une fiche document à une fiche personne.

Une relation dont le corollaire est la même relation dans l'autre sens est une relation symétrique. 