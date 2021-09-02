#!/bin/sh

echo "Creating static libraries"

# g++ -c main.cpp -o main.o
g++ -c College.cpp -o College.o
g++ -c Company.cpp -o Company.o
g++ -c Offer.cpp -o Offer.o
g++ -c Eligibility.cpp -o Eligibility.o
g++ -c Date.cpp -o Date.o
g++ -c Student.cpp -o Student.o

ar cr lib_static_SPMS.a College.o Company.o Date.o Eligibility.o Offer.o Student.o

echo "Static libraries created"
