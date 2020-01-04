#!/usr/bin/env bash

BASE_PATH="src/"

printf "Problem name: "
read PROB_NAME 

if [ -e "$BASE_PATH$PROB_NAME" ]; then
  printf "Found problem $PROB_NAME.\n
fi

exit 0
