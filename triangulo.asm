SECTION data
	B:		SPACE
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2
	TRIANGULO EQU 0
SECTION TEXT
		INPUT		B
		INPUT		H
		LOAD		B
		MULT		H
		IF TRIANGULO
		DIV		DOIS
		STORE		R
		OUTPUT	R
		STOP

