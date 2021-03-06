#!/bin/bash

# for use with Learn C The Hard Way ex17.c

# man 1 documents shell commands, man 3 documents library calls
# man 1 printf
# http://stackoverflow.com/questions/18920539/how-can-i-get-in-linux-the-man-page-for-c-functions-and-not-the-man-with-bash-co
printf "connect to database file. If it doesn't exist, create it.\n"
./ex17 db.dat c

printf "add records\n"
# add record with id 1
./ex17 db.dat s 1 zed zed@zedshaw.com
# add record with id 2
./ex17 db.dat s 2 frank frank@zedshaw.com
./ex17 db.dat s 3 joe joe@zedshaw.com

printf "list database\n"
# Example output
# 1 zed zed@zedshaw.com
# 2 frank frank@zedshaw.com
# 3 joe joe@zedshaw.com
./ex17 db.dat l

printf "delete record id 3\n"
# Example output
# 1 zed zed@zedshaw.com
# 2 frank frank@zedshaw.com
./ex17 db.dat d 3

printf "list database\n"
./ex17 db.dat l

printf "get record id 2\n"
# Example output
# 2 frank frank@zedshaw.com
./ex17 db.dat g 2

