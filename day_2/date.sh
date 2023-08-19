#!/bin/bash
echo "Do you want to print date and time? (y/n)"
read answer
if [ $answer = y ]; then
	echo $(date +'%F %H:%M')
else
	echo "Sorry, in that case I'm useless."
	exit 1
fi
