#!/bin/bash
./install.sh -f -i multisite_drupal_standard $1
for (( i=1; i<=3; i++ ))
do
  subsite_name=$2$i
  ./install_subsite.sh $1 $subsite_name
done


