all:
	@ make -C tests

vector:
	@ make vector -C tests

stack:
	@ make stack -C tests

map:
	@ make map -C tests

set:
	@ make set -C tests

.PHONY: vector stack map set
