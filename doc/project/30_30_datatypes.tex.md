
# Types de données

La description d'un type de données se fait en combinant et/ou en étendant des types natifs, sous la forme d'une classe qui étend ```TZDataType``` ou une métaclasse dérivée (*ie*, un autre type de données, y compris un type natif).

La construction d'un type se fait en définissant des attributs typés :

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
~~~

Un type peut avoir, en plus de ses attributs, des *propriétés* : une propriété décrit le comportement de l'instance du type, mais n'est pas en soi une donnée sémantique. 

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
	
	myProperty = TZProperty(TZInteger())
~~~

Enfin, chaque type fournit des évènements, sur lesquels du code peut se brancher. 

~~~ {.python .numberLines}
from tkacz import *

class MyDataType(TZDataType):

	myString = TZString()
	myNumber = TZNumber()
	myDate 	 = TZDate()
	
	myProperty = TZProperty(TZInteger())
	
	@hook("myNumber.onChanged")
	def calculate(self):
		pass
~~~

## Types natifs

Tkacz fournit un ensemble de types «natifs». Ces types sont liés au code C++ et sont les seuls éléments qui ne peuvent être remplacés. Du point de vue de Python, il sont des métaclasses.

Ces types sont ```TZBoolean```,
```TZDict```,
```TZEnum```,
```TZFloat```,
```TZInteger```,
```TZNumber```,
```TZSet```, 
```TZString```, 
```TZVariant```

## Extension des types natifs