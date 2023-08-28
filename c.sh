#!/bin/bash bash

for i in {1..5000}
do
   echo $i >> g.txt
   git add .
   git commit -m "security: security check #$i"
done

gh
git push
