awk '
NF > 3 {printf "%s -> %s\n", $0, $2;} ' <file
