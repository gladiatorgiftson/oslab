echo "Enter the number"
read num
temp=$(($num%2))
if [ $temp -eq 0 ]
then
echo "even"
else
echo "odd"
fi