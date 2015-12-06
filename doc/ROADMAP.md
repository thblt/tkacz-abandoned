# Roadmap

Current version is 0.0.1 alpha, aka “Unfinished Unstable Buggy Thing”.

## Version 0.1 — *Something that works.*

### Basic pages mechanism
Create, edit and delete plain text pages, with little or no formatting.

Builtin collections can be hidden but not deleted, and can be restored from “Repository settings”.

Pages can have types, but these types are only markers. The following types will exist:

* (Standard page)
* Publication (abstract)
    * Book
    * Article
    * Manuscript
* Entities
    * Person (natural)
    * Organization or other legal or informal (collective or not) entity. 

No creation of custom types.

Pages can be added to categories.

### Basic collections mechanism
Create, modify and delete static collections.

Some builtin collections available, at least `Pages by type/*`.

All collections are static except `Pages by type/$` which is magic.

No other magical collections, no relationships, no dynamic collections.

### GUI
Sidebar prepopulated with the `Pages by type/*` collections. 

Sidebar configurable

Location bar **disabled for now**.

"Organize collections" view in mainwindow, similar to an orthodox file manager.

Menu bar changes depending on current view, *à la* Autodesk Maya.

## Version 0.2 — *Look for things*

### Categories search mechanism
 Location bar implemented with basic features, ie select pages by collections using sets operators  (union, intersection, difference).
 
Search pages by name only.
 
Location bar is somehow aware of categories hierarchy and of children subsets. 

* Searching for a category of which children are subsets return pages in children as well.
* Searching for a category of which children aren't subsets doesn't return these children.
 
No search on properties and links, which doesn't exist yet.

## Version 0.3 — *Zero point two and one*

### Categories management
Enable logical "relationships" between categories.

### Pages editing
Allow free links to be created between pages.
Some links have types, e.g : source.

## Version 0.4 — *Types, properties, links*

### Pages types, pages ≠ objects, introducing objects.
Implementing page types. A *type* is the definition of a set of properties which characterizes an object.  

A *property* is the association of a name and another type. Types may be primitive (a string, an integer, a floating-point number) or types as defined above. In the latter case, the type's value is a link to another *object*, in the former, it is a literal constant.

Eg. a page of type Book will link to one or more pages of type Person, which will be authors or editors of the book, have a property of type String for the title, date for the year, and so on.

An *object* is a **typed** page with or without a body, ie with or without any associated text. The publisher of a book is probably an organization, and thus will be a link and not a string literal. But this organization may never be used as a page, because there's nothing to say about it. The difference between page and object is technically quite small, but is meaningul in terms of user interaction, because nobody wants a bunch of random publishers to pollute their hand-crafted collection of notecard on their research.

Note some objects are more meaningful than others, and should be treated as pages even if they aren't. Books are.

Typed pages don't have titles the way standard pages do, because their title is usually generated. The title of a book is something like “FOUCAULT, Michel, *The Order of Things*, 1966”. You don't need to enter it twice.

All linked pages are generated on the fly if needed. 

The type handlers may translate a common string into the different fields needed to define their type, as, eg,  BibTeX can understand a full name as first, middle, last, suffix, and so on. 

There always remains the possibility to create typeless pages. 

## Version 0.5 — *Objects in pages*

**Objects backlinks** — Objects link other objects as the value of their *properties*. Linked objects now show these links in their pages when this has any meaning. For example, a `person` object which is linked as `author` of a `book` will see this book appear in its page, in a section matching the type name or the magic collection "pages by type" name (Here, Publications > Books)

**Objects creation in page** — If type `B` has a property `p` whose type is `A`, `B` objects can be created while editing `A` pages, where `p` will default to the page being edited. If `B` also has properties `q`, `r`... of type `A`, the user will just have to pick a dropdown menu and select the relevant property. Eg, when editing a `person`, it is now possible to create publications objects directly in its page. Publications will have a *default field for each object type*: `author` for type `person`. 
 
# Other features

Not in this roadmap, but they may be added some day.

## Structured text editor.

This must be improved and extended. 

Common block and character formats introduced.

Export to other formats, mostly xhtml and LaTeX. 

Distraction-free mode.

Zen mode (distraction-free + dark background)

## Exporting

See above. The whole repository should also be exportable as a webpage, a PDFLaTeX document…

BibTEX and bibliographic export. This is important. Somewhere around 0.6.

## Importing / Creating objects and pages from remote sources.

Bibliography search and import. The usual suspects : Google scholar, BnF and so on.

Wikipedia import

Other ?

## GUI functions

Editing multiple pages simultaneously (on a grid)

Quick invoke: a system-wide shortcut to invoke a Tkacz search box and quickly obtain information about something.

## Pages

Pages can be anything, and not only structured text. This include graphes, media, and other file formats, eg Asymptote files, images…

## File format

