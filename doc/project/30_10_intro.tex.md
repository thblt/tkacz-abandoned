
# Le système de schémas

\newglossaryentry{schema}{name=schéma,plural=schémas,description={}}

Le modèle de données de Tkacz n'est pas codé en dur dans le noyau du logiciel. Ce noyau, écrit en C++, fournit principalement l'abstraction du stockage, les interfaces utilisateurs et la forme générale de données (la forme abstraite des fiches, des taxinomies et des relations). La description des types de données manipulées par dépôt donné se fait à l'aide de modèles écrits en Python[^why_python].

[^why_python]: Le choix de Python est principalement dû à deux considérations : ce langage est largement répandu, facile à utiliser et à apprendre ; il dispose de nombreux outils --- y compris des notations --- pour manipuler des ensembles ; il est très facile à interfacer sur du code C/C++. Pour autant, la dépendance à ce langage précis n'est pas un impératif, et il n'est pas absurde d'imaginer joindre d'autres interpréteurs à Tkacz.

Grossièrement, le cœur fournit un gestionnaire de données sémantiques et les modèles décrivent la structure sémantique de ces données. Jusqu'à ce point de ce document, les mécanismes de stockage et les types de données et de relations présentés (fiches, taxonomies, relations) relevaient du cœur du logiciel ; mais les exemples (types de fiches, taxinomies, exemples de relations) ne dépendaient que des modèles.

Cette conception duelle de Tkacz répond à l'impératif fondamental de ne pas figer le modèle de données : si Tkacz fournit bien un modèle standard, l'utilisateur peut l'étendre à son gré, le modifier, voire en écrire un nouveau[^fromscratch].

[^fromscratch]: L'interface graphique sera sans doute conçue en fonction du modèle standard. Dans ce cas, la conception de nouveaux schémas pourra impliquer de réécrire une partie du code d'interface.

Les modèles de données décrivent :

 * Des types de données, qui complètent les types natifs de Tkacz.
 
 * Des types de fiches.
 
 * Des types de relations entre ces fiches.
 
 * Des schémas, composés d'un ensemble de types de données, de fiches et de relations.
 
 * Des descriptions abstraites d'interface graphique pour modifier certains types de données.
 
# Fondamentaux

Les types de données, de fiches ou de relations sont des objets Python qui étendent une méta-classe fournie par Tkacz. Ces trois types sont extrêmement proches : la différence entre eux est dans la façon dont le cœur les manipule, et pas dans leur structure.