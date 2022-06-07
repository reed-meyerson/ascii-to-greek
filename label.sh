#!/bin/sh

while IFS=", " read -r symbol hex key breath accent isub macron last
do
	breathnum="00"
	accentnum="000"
	isubnum="0"
	lastnum="0"
	macronnum="0"
	test $breath = "Rough" && breathnum="10";
	test $breath = "Smooth" && breathnum="01";
	test $accent = "Circ" && accentnum="100";
	test $accent = "Grave" && accentnum="010";
	test $accent = "Acute" && accentnum="001";
	test $isub = "ISub" && isubnum="1";
	test $macron = "Macron" && mcaronnum="1";
	test $last = "Last" && lastnum="1";
	keyval=$(printf "%03d" "'$key")
	echo "$keyval$breathnum$accentnum$isubnum$macronnum$lastnum '$key' $breath $accent $isub $macron $last 0x${hex}u"
done
