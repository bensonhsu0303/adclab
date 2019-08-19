CFLAGS = -Wall

ups-parse: ups-parse.c
	gcc ups-parse.c $(CFLAGS) -o ups-parse

.PHONY: clean install

clean:
	rm -rf ups-parse

install:
	sudo yum install -y nut-client
	sudo mkdir -p /etc/ups-parse/
	sudo cp ups-parse /etc/ups-parse/ups-parse
	sudo cp ups-parse.config /etc/ups-parse/ups-parse.config
	sudo cp ups-parse.service /etc/systemd/system/ups-parse.service

