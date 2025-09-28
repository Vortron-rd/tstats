include config.mk

SRC = tstats.c
OBJ = ${SRC:.c=.o}

all: tstats

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

config.h:
	cp config.def.h $@

tstats: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}
test: ${OBJ}
	${CC} -o $@ ${SRC} ${TESTCFLAGS} ${LDFLAGS} 
clean:
	rm -f test tstats ${OBJ} tstats-${VERSION}.tar.gz ;

dist: clean
	mkdir -p tstats-${VERSION}
	cp -R LICENSE Makefile README.md config.mk\
		 ${SRC} tstats-${VERSION}
	tar -cf tstats-${VERSION}.tar tstats-${VERSION}
	gzip tstats-${VERSION}.tar
	rm -rf tstats-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f tstats ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/tstats
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < tstats.1 > ${DESTDIR}${MANPREFIX}/man1/tstats.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/tstats.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/tstats\
		${DESTDIR}${MANPREFIX}/man1/tstats.1

.PHONY: all clean dist install uninstall
