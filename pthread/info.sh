#!/bin/sh

while [ true ]
do
    clear
    ps -efL | head -n 1 && ps -efL | grep $1 | grep -v 'grep' | grep -v 'test.sh'
    sleep 1
done
