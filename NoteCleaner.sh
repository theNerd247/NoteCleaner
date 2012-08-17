#!/bin/bash

if [[ -z $1 ]] ; then 
	echo "usage: NoteCleaner [path to text file]"
	exit 1
fi

/usr/bin/NoteCleaner/NoteCleaner $1
Markdown.pl --html4tags $1.mkdn > $1.html
rm $1.mkdn
