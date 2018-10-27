#!/usr/bin/env sh

g++ lingang.cpp
if [ $? -ne 0 ]; then
	echo "compile error!"
else
	./a.out
fi
exit $?

