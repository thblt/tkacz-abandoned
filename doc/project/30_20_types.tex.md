
# Le système de types

Le mécanisme de types de Tkacz repose sur une correspondance terme
à terme entre une hiérarchie de types et une hiérarchie d'objets instantiables.
Ces deux hiérarchies sont définies comme suit:

\begin{tabular*}{1\columnwidth}{@{\extracolsep{\fill}}|c|c||c|c|}
\multicolumn{2}{c}{Types} & \multicolumn{2}{c}{Objets}\tabularnewline
\hline 
\multicolumn{2}{|c||}{Template (virtual)} & \multicolumn{2}{c|}{Node}\tabularnewline
\hline 
EntityTemplate & PrimitiveTemplate<T> & — & —\tabularnewline
\hline 
 & IntegerTemplate, StringTemplate… & Card & \tabularnewline
\hline 
\end{tabular*}

À chaque instance d'un descendant d'Object correspond un objet
Template du type correspondant (à une Primitive correspond
un PrimitiveTemplate, etc.). L'objet Template:

 -  Initialise la structure de données de l'Object.
