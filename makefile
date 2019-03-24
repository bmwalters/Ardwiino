all:

micro:
	$(MAKE) -C src/micro avrdude

clean:
	$(MAKE) -C src/micro clean

build:
	$(MAKE) -C src/micro
