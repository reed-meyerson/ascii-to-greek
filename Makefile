current_dir = $(shell pwd)
bin_dir = $(current_dir)/bin
CFLAGS = -Wall -O2

togreek: togreek.c letters.h
	cc togreek.c $(CFLAGS) -o togreek
	mkdir -p bin
	mv $@ bin/$@
	@echo "Cleaning Up"
	rm -f accent.db
	rm -f letter.db
	rm -f breath.db
	rm -f isubs.db
	@echo "Compilation Finished"
	@echo 'add' $(bin_dir) 'to your $$PATH' with
	@echo 'export PATH=$$PATH:$(bin_dir)'

letters.h: make_header.sh
	@echo "Generating header from alphabet.csv"
	cat alphabet.csv | ./label.sh | sort | cut -c 13- | sed 's/ /,/g' | sed 's/^/	GREEK(/g' | sed 's/$$/),/g' | sed '$$ s/.$$//' > greek.tmp 
	./make_header.sh > letters.h
	rm -f greek.tmp

clean:
	rm -rf bin
	rm -f letters.h
