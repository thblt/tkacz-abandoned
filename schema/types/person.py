#                                                                 [licblock]
# This file is part of Tkacz. 
# Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#                                                                [/licblock]

from tkacz import *

class Person (TZTemplate):
	name = TZString()
	firstName = TZString()
	middleName = TZString()
	vonPart = TZString()
	lastName = TZString()
	suffix = TZString()

@hook_option("person/name/simple")
def option_simple(entity, new_value):
    if new_value:
        entity["name"].set(person_name_format(entity))
    else:
        entity["last_name"].set(entity["name"])
    
    entity["surname"].enabled = not new_value
    entity["middle_name"].enabled = not new_value
    entity["von_part"].enabled = not new_value
    entity["last_name"].enabled = not new_value
    entity["suffix"].enabled = not new_value
    entity["name"].enabled = new_value
