SECTION TEXT
INPUT OLD_DATA
LOAD OLD_DATA
L1: DIV NEW_DATA + 1
L1: DIV NEW_DATA + OLD_DATA
STORE LAIS
MULT DOIS
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA , OLD_DATA
LOAD OLD_DATA
DIV NEW_DATA
OUTPUT OLD_DATA
JMPP L1
STOP
SECTION DATA
DOIS: CONST 2
OLD_DATA: CONST 2
NEW_DATA: CONST 0
TMP_DATA: CONST 3 
