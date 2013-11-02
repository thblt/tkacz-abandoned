**Tkacz is unstable, unfinished software. The notes below are for reference only, and no description of anything which would actually work.**

**This readme is partially deprecated**

# Tkacz

The idea of writing Tkacz came to me when writing a masters thesis on the historical epistemology of sex. I wanted a way to organize numerous notes about various things (people, historical events, publications, and so on), to keep them ordered but also to keep have them easy to write, to find and to organize. Tkacz aims at:

  * Providing an environment for taking structured and unstructured notes following different templates.
  * Organize these notes in a multi-level, hierarchical category tree, which should be:
    * Partially automated: some categories are obvious, and should be generated automatically.
    * Exhaustive: a page may be in numerous categories.
    * Searchable: categories are the primary way to search for contents.
           
## What do all the words mean?
           
 * A **repository** is a Tkacz file. It stores pages, collections, rules, and so on.
 
 * (Unsure) An **object** is a page without any contents. A book about which nothing exists as an object. 

 * A **page** is a note in Tkacz. Page is used in the same meaning as in, say, Wikipedia. Pages may have templates, or types: a template determines the kind of data stored in a page, and provides ways to formally define them. Internally, a page is a XML document associated to an object. 
 
 * A **collection** is a set of (optionally) pages and (optionally) other collections. Collections are a hierarchical tree. They come in three flavors:
 
   * *Standard* or *static*
   : These collections collect objects which are added manually to them. These are created by the user.
   * *Dynamic* or *smart*: These collections collect pages by following rules, and are dynamically updated. The user can create, edit and delete them, too.
   * *Magic*: These ones can't be edited or modified (but can be made invisible). They are created, updated and maintened by the engine itself, usually by the page templates.

# How to use it ?
              
### Write a note.
              
After creating or opening a Repository, select `File > New note` (Ctrl-N) or `New note of type...` (Ctrl-Shift-N). The editor opens, with a new untitled note. Some types have simple titles, but most titles use fields to compute a properly formatted title. If the title is editable, you may set it directly.  The Publication type doesn't allow for title editing, instead, it requires fields to be completed in order to generate a title. The title format itself may be configured in the Repository settings. 

#### Editing a generic (untyped) note

When seeing the note in the browser, select `Edition > Edit mode` to start modifying the note. The Editor then behaves just like any structured text editor. It allows to create paragraphs, emphasis, enumerations and so on.

#### Editing or creating a templated note.

When creating or editing a note of type Publication, the title area looks slightly different: It comes with fields, most being automatically picked up. The first field of a Publication is the type of this publication. Then it usually requests an Auhor, maybe more, a title, and depending on type, more fields. Just type the value for each field Tkacz will suggest values as you type depending on field type. Tab to go to the next field or Ctrl-Tab to repeat the field (when possible). If the selected field type is wrong, just use the arrow button next to its name or type Ctrl-T to change it. When leaving the title area, the fields will be replaced by a correctly formated title. 

You may then start to edit notes on this Publication. Publication notes allow for a few more types of data within them : quote (which expects pagination information to be provided), links to other Publications as cited, and so on. 

#### Is this really useful ?

The ability to easily give structure to notes is Tkacz's key strength. It will automatically provide the citations as standalone notes, and if you say that your Publication cites another, you may be able to find it from the other one as well. 

It also makes exporting to other formats a breeze : your publication data will be easy to convert to BibTeX or similar formats.

### Search for notes

Searching uses the collections logic to select notes. Collections may be thought of as sets of records. Search syntax is as follows: 

` Publications & Michel Foucault << & date < 3 jan 1950 `

Page and collection titles are identified on the fly and displayed as non-modifiable objects,
so no quote marks are required. They're reserved for full-text search.
 
#### Operators

 * Binary operators: 
   * `*` intersection. This is the implicit operator. `A x B` means pages both in A and B.
   * `+` union. `A + B` means pages in category A, B or both
   * `-` difference. `A - B` means all pages in A but not in B.
 * Unary operators:
 * `::[selector]` : Pages which links to `[selector]`. The selector may be litteral (ie a page name) or a formula, eg. : links(A - B). `>>` is used implicitly when page names are used in a search expression without a unary operator. Where P is a page, `P` = `::P`
 * `[selector]::` : Pages linked from `[selector]`. This operator must be used explicitly. 

Operators priorities are as follow : intersection, union, then difference. Parentheses can be used.


# Dependencies
 * PyQt4 and Qt 4.8.4 (PyQt 4.10 is broken with Qt 5.0.1: the code generated from ui files which contains unicode characters is crashy; furthermore Qt 5.0.1 leaves out the cool unified title and toolbar on OSX — but brings cool Lion Fullscreen.

# Building
## Mac .app bundle

1. python3 setup.py py2app
2. macdeployqt dist/Tkacz.app
	 (Ignore the long “WARNING: Could not find any external (...) before trying again.”
3. cp /Developer/Applications/Qt/plugins/imageformats/libqsvg.dylib dist/Tkacz.app/Contents/PlugIns/imageformats/
4. macdeployqt dist/Tkacz.app (Yes, again. That's because I haven't found a way to make it aware of the need to embed the SVG lib, but the app crashes after manual embedding. The second run seems to fix that.