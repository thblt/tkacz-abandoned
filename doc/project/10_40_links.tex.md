# Organisation en graphe : liens et relations

Une fonction fondamentale et originale de Tkacz est sa capacité à décrire des relations complexes entre des fiches. Ces relations sont sémantiques, et organisent un dépôt Tkacz sous la forme d'un graphe. 

Au plus simple, une relation est un simple pointeur d'une fiche vers une fiche cible. L'auteur d'un document, par exemple, est un lien vers une fiche personne, et pas une chaîne de caractères. Certaines relations sont plus élaborées : un texte publié sous pseudonyme verra l'auteur attribué par un lien vers la fiche de personne, mais ce lien stockera aussi le pseudonyme retenu. Une attribution d'auteur peut-être douteuse, ou au contraire certaine pour un texte publié anonymement. Ces informations sont stockées au niveau de la relation.



## Le lien simple 


Le corollaire est généralement implicite. Il peut n'être fixable que
depuis un seul des membres de la relation possible. Le lien d'auteur,
par exemple, n'est manipulable que depuis la chose dont *x* est
l'auteur, et pas depuis *x*. 


## La relation

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

## Corollaires et relations symétriques

Une relation peut avoir un **corollaire**, c'est-à-dire que la liaison de A et B implique une relation (de même nature ou d'une autre nature) de B vers A. Dans l'exemple de l'auteur, le lien «a pour auteur» a pour corollaire «est auteur de». Une relation dont le corollaire est la même relation dans l'autre sens est une relation symétrique.