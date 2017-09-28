###############################################################################
# Makefile
###############################################################################

SHELL = /bin/bash # for ubuntu

###############################################################################

SRC = $(wildcard *.c *.cc)
EXE = $(basename $(SRC))
ATT = $(EXE:=.att)
DAT = $(EXE:=.dat)
PNG = $(DAT:.dat=.png)
SVG = $(DAT:.dat=.svg)

###############################################################################

CFLAGS = -fno-omit-frame-pointer -m32 -mpopcnt -O3 -Wall -g
CXXFLAGS = $(CFLAGS) -std=c++0x

###############################################################################

default: $(EXE)

all: default $(ATT) $(PNG)

clean:
	$(RM) -rfv $(ATT) $(DAT) $(EXE) $(PNG) $(SVG) core.* *~

###############################################################################

%.att: %
	objdump -C -d $< > $@

%.dat: %
	./$< | tee $@

%.png: %.svg
	convert $< $@

%.svg: %.dat Makefile
	gnuplot <<< "\
		set terminal svg; \
		set output '$@'; \
		set key; \
		set grid; \
		set ylabel 'time (ms)'; \
		set y2label 'cpu cycles'; \
		set xtics rotate; \
		set ytics; \
		set y2tics; \
		set y2tics nomirror; \
		set style fill solid 0.10 border; \
		set boxwidth 0.80; \
		plot '$<' u 5:xtic(1) w boxes axes x1y1 title 'time', \
		     '$<' u 3:xtic(1) w lp pt 7 axes x1y2 title 'cycles'"

###############################################################################

.PHONY: all clean default
.PRECIOUS: $(DAT) $(PNG) $(SVG)

###############################################################################

