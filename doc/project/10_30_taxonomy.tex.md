
# Organisation en arbre : la taxinomie

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

## Construction des taxinomies

La création des taxinomies peut être automatique ou manuelle. La création automatique se fait par du code Python fourni par le schéma ou l'utilisateur, la création automatique est faite par l'utilisateur.

## Affectations des fiches aux taxons

### Principes généraux

L'affectation peut-être manuelle (chaque fiche est ajoutée par l'utilisateur), automatique (le taxon contient certaines fiches selon certaines propriétés) ou hybride : l'affectation est automatique par défaut, mais peut être forcée. Par exemple, une taxonomie des acteurs d'un champ par activité professionnelle privilégiera une affection manuelle des fiches ; une taxonomie des publications par décennie sera automatique et l'affectation se fera en fonction de la première publication.

Les modes d'affectation automatique sont les suivants

### Relations entre taxons

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
