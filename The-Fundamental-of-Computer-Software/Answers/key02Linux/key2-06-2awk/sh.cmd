echo "#### awk '{printf "mv %s %s\n", $2, $1}' file"
awk '{printf "mv %s %s\n", $2, $1}' file
