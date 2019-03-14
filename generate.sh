echo "Enter a number"
read n
count=0
echo "Series:"
while [ $count -lt $n ]
do
count=$((count+1))
echo $count
done