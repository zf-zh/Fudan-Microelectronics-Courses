awk '
NR % 2 == 0 {print NR, NF, $0; n += 1 }
END  {printf "N = %d\n", n}' <file
