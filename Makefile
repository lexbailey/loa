
all: loa

loa: loa.c
	gcc $^ -o $@ --std=c99

checkPossible: loa.c
	cbmc $^ --function testRandomBoard --unwind 5 -DASSERT_CBMC | tee cbmc.log

showLoops: loa.c
	cbmc $^ --show-loops

.PHONY: checkPossible showLoops
	
