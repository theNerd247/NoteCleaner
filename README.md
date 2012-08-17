NoteCleaner
===========

converts a formatted text document of notes to markdown format. Eventually will convert to html as well. 

##Dependencies 
NoteCleaner requires you to have [Markdown][http://daringfireball.net/projects/markdown/] and the
standard C++ libraries installed.

##Usage
NoteCleaner is a very simple program that parses formatted text documents to html via markdown. In otherwords it parses the given
text file and outputs a markdown file. It then uses the Markdown program to convert that to html. 

###How to format your notes
This program was developed with speed typing in mind, and heirchial not taking. This makes notetaking faster and simpler - and you can leave this
program to do the formatting. 

####Headings and Notes
To start headings are organized by index. An index of level one would be equivalent to the top level of a heirarchy. 
In your notes text file, to add a level 1 heading you simply type in the text of that heading. 
For example: 
    THIS IS A HEADING
Will produce
    <h1>THIS IS A HEADING</h1>
in html. 
To increase the index to level 2 simply type in a tab character
    	This is heading level 2
and that will output 
    <h2>This is heading level 2</h2>

Notes are created by putting a "-" in front of the notes, but after the tabs (if the notes are for a heading that is greater than 2).
So for a heading level 1 note: 
    This is a heading level 1
    -this is a note
and for a higher index: 
    	-	This is a heading level 3
    	-	-this a note for that heading 

To put it simply an index is increased using a tab character followed by a hyphen (for notes) or the text of the heading (for a heading).

####Lists and Definitions
Unlike a normal list in a text file, lists are on a single line (it would be a good idea to turn off word wrap). To start a list simply type the title 
of the list and then a colon afterwords. for example: 
    -title oflist: list item 1; list item2;
As you can see an item of a list simply follows after the colon and is delimited by a ; after each item (including the last item)

Definitions are the same as lists, however there are no list items, and there for are no ; delimiters. For example
    -word: definition. 
Below are examples:

    	-	-a list title: item 1; item 2;
    	-	-a word: definition of a word
####CODE 

##Installation
###Linux
To install on a Linux Box download the NoteCleaner.cpp, the Makefile, and the NoteCleaner.sh file.
simply run `make` and then `make install` inside the directory you downloaded the above files to install. 
This will make a directory called "NoteCleaner" inside /usr/bin
Makefile and NoteCleaner.cpp are then copied to ~/.NoteCleaner and NoteCleaner.sh and NoteCleaner are copied to /usr/bin/NoteCleaner

####Uninstall 
To uninstall NoteCleaner simply cd to the directory containing the Makefile (~/.NoteCleaner) and then run `make uninstall`. 
