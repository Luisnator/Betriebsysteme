#!/bin/bash

div = $1

shift

mult = 1

while [ $# ]; do
	mult = $mult * $1
	shift
done

echo "$mult"

