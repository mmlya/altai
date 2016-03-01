#!/bin/bash

echo this scenario tests 10 times
echo the whole chain of periodically asymmetrically compromized reproductive barrier
echo between two species of variabile sizes

for i in {1..10};
do 
    echo $i
    ./mlya
    phyml -i sample.phy -m JC69 --quiet
    phyml -i samplAA.phy -d aa --quiet
    mv sample.phy_phyml_tree.txt tree.tre
    ./dst.py
    echo Done!
done