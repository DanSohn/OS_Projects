suffix=$1 #set suffix to be the first argument
number=$2 #set number to be second argument
find . -type f -name "*$suffix" -printf '%p %s\n' | sort -t " " -k 2 -n -r | head "-$number" | awk '{total += $2; print $1 " " $2} END {print "Total size: " total }' 
#echo "arg1: $1"
#echo "arg1 var: $suffix"
