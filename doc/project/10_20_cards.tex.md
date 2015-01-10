# L'objet fondamental : la fiche

## L'objet fiche

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

## Attributs et liens

Une fiche, à l'exception du type minimal (qui modélise réellement
une feuille blanche avec un titre), contient un certain nombre d'attributs,
qui sont les données sémantiques, et de relations.

### Attributs {#par:attributs}

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

### Liens et relations

Il y a deux façons de lier une fiche à une autre : le lien simple
et l'expression d'une relation.


### Le lien simple 

est un \og pointeur \fg{} vers la fiche cible. L'auteur d'un document,
par exemple, est un lien vers une fiche personne, et pas une simple
séquence de caractères. Le lien peut avoir un **corollaire**,
c'est-à-dire que la liaison de A et B implique une relation d'une
autre nature de B vers A. Dans l'exemple de l'auteur, le lien \og a
pour auteur \fg{} a pour corollaire \og est auteur de \fg{}. 

Le corollaire est généralement implicite. Il peut n'être fixable que
depuis un seul des membres de la relation possible. Le lien d'auteur,
par exemple, n'est manipulable que depuis la chose dont *x* est
l'auteur, et pas depuis *x*. 


### La relation

est un attribut complexe, qui permet de lier des fiches entre elles
de façon moins formelle et plus fine. Une relation a une **nature**,
qui est l'équivalent du type d'une fiche. Dans certains cas, un lien
peut être remplacé par une relation. Par exemple, dans un document
historique, l'attribution de l'auteur peut être douteuse — \og auteur
probable \fg{} est une relation, car le lien simple ne suffit pas
— il faut sans doute préciser la nature du doute, les différentes
sources, etc.

Une relation peut aussi décrire des relations entre entités : \og membre
de \fg{} ou \og ami de \fg{}, \og frère de \fg{}, etc.

Une relation peut être réciproque ou non. Dans l'exemple qui précède,
les deux dernières sont nécessairement réciproques. Une relation peut
aussi avoir un **corollaire**. La relation ```A est membre de B```
(dans cet exemple, B est par exemple une personne morale) a pour corollaire
\og B a comme membre A \fg{}

Une relation est de type \og cite \fg{} ou \og évoque \fg{}, qui
permet de commenter un livre en le liant à ce qui fait son objet. 


## La notion de type {#sub:Type}


## Les types de fiche standards {#sub:Types}

La description formelle de ces types est donnée en \vref{CoreSchema}.


### Simple

Il s'agit d'une fiche a minima : titre et notes.


### Référence bibliographique

Ce type de fiche peut représenter différents types d'objets entrant
dans une bibliographie, qu'il s'agisse de sources primaires ou de
sources secondaires, de supports imprimés ou audiovisuels. 


### Personne (physique ou morale)
