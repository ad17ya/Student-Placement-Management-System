#!/bin/sh

echo "Creating dynamic libraries"

g++ -fPIC -shared College.cpp Company.cpp Date.cpp Eligibility.cpp Offer.cpp Student.cpp  -o lib_dynamic_SPMS.so

echo "Dynamic libraries created"
