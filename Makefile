NoteCleaner: NoteCleaner.cpp
	g++ -o NoteCleaner NoteCleaner.cpp 
debug:
	g++ -g -fpermissive NoteCleaner.cpp -o NoteCleaner
clean:
	rm NoteCleaner
install: NoteCleaner
	sudo mkdir /usr/bin/NoteCleaner
	sudo cp NoteCleaner /usr/bin/NoteCleaner/
	sudo cp NoteCleaner.sh /usr/bin/NoteCleaner
	echo 'alias NoteCleaner="/usr/bin/NoteCleaner/NoteCleaner.sh"' >> $(HOME)/.bash_aliases
	. ~/.bashrc
uninstall: /usr/bin/NoteCleaner/
	sudo rm -rf /usr/bin/NoteCleaner
	cat $(HOME)/.bash_aliases | grep -v 'alias NoteCleaner="/usr/bin/NoteCleaner/NoteCleaner.sh"' > temp ; cat temp > $(HOME)/.bash_aliases ; rm temp
	. ~/.bashrc
update: /usr/bin/NoteCleaner/
	make uninstall
	make install
