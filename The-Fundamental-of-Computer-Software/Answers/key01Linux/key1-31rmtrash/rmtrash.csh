#! /bin/csh
# File: rmtrash.csh
# Func:  remove trash files such as "core" and "*.tmp"
# Usage: rmtrash.csh
set trash = $$.$$ 
echo "** Remove trash started. …"
find $HOME -name "*.tmp" -print	>$trash
find $HOME -name core -print	>>$trash
foreach i ( `cat $trash` )
	if ( ! -d $i ) then
#		rm $i
		echo $i
	endif
end
rm -f $trash
echo "** Remove trash finished."
