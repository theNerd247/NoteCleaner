#!/bin/bash

if [[ -z $1 ]] ; then 
	echo "usage: NoteCleaner [options -f] [path to text file]"
	echo "     -f: also exports a flash card text file to contain definitions"
	exit 1
fi

NAME=$1
/usr/bin/NoteCleaner/NoteCleaner $1 $2 
if [[ -n $2 ]] ; then
	NAME=$2	
fi
Markdown.pl --html4tags $NAME.mkdn > $NAME.html
rm $NAME.mkdn
