# Liens des modèles de données à l'interface d'utilisateur {#chap:UIModels}

Voici la description de l'interface de saisie d'un nom de personne :

~~~ {.xml .numberLines}
<block>
<if propname="simple">
	<lineinput bind="name" />
<else>
	<lineinput bind="name" />
	<hr />
	<lineinput bind="prefix" class="small" />
	<lineinput bind="firstName" class="small" />
	<lineinput bind="middleName" class="small" />
	<lineinput bind="vonPart" class="small" />
	<lineinput bind="lastName" class="small" />
	<lineinput bind="suffix" class="small" />
</else></if>
</block>
<checkbox bind="simple" />
~~~