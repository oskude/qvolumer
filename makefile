.PHONY: all build clean install uninstall archlinux

PREFIX ?= /usr/local

all: build

build:
	mkdir -p build
	cd build; \
		qmake ../qvolumer.pro; \
		make
	mv build/qvolumer .

clean:
	rm -f qvolumer
	rm -rf build
	rm -rf distro/archlinux/pkg
	rm -rf distro/archlinux/src
	rm -rf distro/archlinux/qvolumer
	rm -f *.pkg.tar.*

install:
	install -D -m755 qvolumer "$(DESTDIR)$(PREFIX)/bin/qvolumer"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/qvolumer"

archlinux:
	cd distro/archlinux; \
		makepkg -f
	mv distro/archlinux/*.pkg.tar.* .
