AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

yadqt_SOURCES = $(COMMONSRC)

yadqt_CFLAGS = -O3
yadqt_CXXFLAGS = -O3

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

scriptfilesdir = $(pkgdatadir)/scripts
scriptfiles_SCRIPTS = ../resources/scripts/README

desktopfilesdir =  ${datadir}/applications
desktopfiles_SCRIPTS = ../resources/applications/*

bin_PROGRAMS = yadqt

man1_MANS = ../resources/man/yadqt.1

install-exec-hook:
	install -D ../resources/pixmaps/YadQt.png $(DESTDIR)${prefix}/share/pixmaps/YadQt.png
	install -D ../resources/pixmaps/YadQt.desktop $(DESTDIR)${prefix}/share/applications/YadQt.desktop
	strip --strip-all $(DESTDIR)${bindir}/yadqt

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/YadQt.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/YadQt.png
	rm -fr $(pkgdatadir)

all:
	strip --strip-all yadqt
	