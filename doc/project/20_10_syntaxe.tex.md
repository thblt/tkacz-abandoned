
# Syntaxe des fiches

La syntaxe est dérivée de Markdown et d'autres langages de formatage rapide. Il y a néanmoins quelques différences dans le comportement standard du parser:

 * Tkacz utilise les \__tirets de soulignement\__ pour la mise en italiques, et \***une seule étoile**\* pour le gras. 
 
 * Un paragraphe indenté de quatre espaces ou plus n'est pas traité comme un bloc de code, mais est simplement indenté d'un niveau. Les blocs de code utilisent exclusivement la syntaxe «grillagée», en encadrant le bloc de ```~~~``` et en indiquant éventuellement le langage après la première série de tildes.

 * La syntaxe des liens est supprimée.

 * La syntaxe des blocs de description est modifiée.
 
 * Le format des citations permet d'en préciser l'origine.
 
 * Tkacz pourrait gèrer plusieurs tables des matières dans un seul document.
 
De plus, un certain nombre d'extensions spécifiques sont ajoutées.


## Association clé-valeur

Toute fiche commence généralement par un préambule qui expose formellement son contenu. Ce préambule prend la forme 

~~~ tkacz
:name 
    :first Michel
    :middle Paul :unused
    :last Foucault

:name Fuchs :aka
    Dans [Guibert 1980]
    
:birth 15 octobre 1926 @ Poitiers
:death 25 juin 1984 @ Paris
~~~

## Liens et relations

~~~ tkacz
<> friend [Didier.Éribon]
<> founder GIP.
~~~