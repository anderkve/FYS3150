echo 
echo "Building integrand1.cpp as a shared library."

g++ integrand1.cpp -O2 -fPIC -shared -o libintegrand1.so


echo 
echo "Building integrand2.cpp as a shared library."

g++ integrand2.cpp -O2 -fPIC -shared -o libintegrand2.so


echo 
echo "Building the main executable."

g++ main.cpp -O2 -o main

echo 
echo "Done."
echo 
