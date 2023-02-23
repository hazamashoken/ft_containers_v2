all:
	@ make -C tests
	$(MAKE) terminator

terminator:
	@ if [ ! -d "../terminator" ]; then \
		git clone https://github.com/Mikastiv/ft_containers-terminator.git ../terminator; \
	fi
	@ cd ../terminator && ./test_containers.sh

vector:
	@ make vector -C tests

stack:
	@ make stack -C tests

map:
	@ make map -C tests

set:
	@ make set -C tests

.PHONY: vector stack map set clean terminator
