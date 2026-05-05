#! /bin/csh 
# File:	makec.csh 
# Func:	compile C source files
# Usage: makec name1 name2 …
# Files to be compiled: file = name.c
if ($# == 0) then
	echo Usage: makec name1 name2 …
	exit
endif
echo There are $# files to be compiled.
while ( $# > 0 )
	cc -c $1.c 2>$1.err
	if ( -e $1.err ) then
		echo See error report in file $1.err
	else
		echo $1.c is OK!
	endif
	shift
end
