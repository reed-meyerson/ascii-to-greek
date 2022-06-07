#!/bin/sh

echo "#ifndef LETTERS_H"
echo "#define LETTERS_H"
echo ""
echo "#define GREEK(c,b,a,i,m,l,u) ((c << 24) | b | a | i | m | l | u)"
echo ""
echo "enum Modifier {"
echo "	Last	= (1 << 16),"
echo "	Macron	= (1 << 17),"
echo "	ISub	= (1 << 18),"
echo "	Acute	= (1 << 19),"
echo "	Grave	= (1 << 20),"
echo "	Circ	= (1 << 21),"
echo "	Smooth	= (1 << 22),"
echo "	Rough	= (1 << 23)"
echo "};"
echo ""
echo "const uint32_t letters[] = {"
cat greek.tmp
numletters=$(cat greek.tmp | wc -l)
echo "};"
echo ""
echo "#define NUM_LETTERS" $numletters
echo ""
echo "#endif"
