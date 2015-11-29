### Lines of action deadlock finder

This is a program that checks if a board configuration for a game of lines of action is valid and is a deadlock position.

The program contains assertions for CBMC to be able to find a counterexample for the theroy that no such deadlock exists.

The makefile contains a rule for initiating a CBMC run to check the current configuration of loa.c

