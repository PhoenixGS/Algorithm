while true; do
./data > name.in
./name < name.in > name.out
./nameX < name.in > nameX.out
if diff name.out nameX.out; then
echo AC
else
echo WA
break
fi
done
