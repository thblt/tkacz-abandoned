from tkacz import Tkacz

tkacz = Tkacz( "~/Temporaire/tkacz", create=True )
card = tkacz.makeCard( "tkacz_schemas.types.person.Person" )
card2 = tkacz.makeCard( "tkacz_schemas.types.person.Person" )

card.notes = 32
card2.notes = 39

card.names.name = "Polge, Jr., Thibault J."
card.names.name = "Jean-- Baptiste Polge"

#print(card.serialize(True))

