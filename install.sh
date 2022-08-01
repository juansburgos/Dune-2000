#!/bin/bash
if (($EUID != 0))
    then echo "Please run as root"
    exit
fi

# compilation
rm -rf build
mkdir -p build
cd build
cmake ..
make

# Resources
cd ..
mkdir /usr/local/share/Dune -p
cp -r assets /usr/local/share/Dune/
cp -r maps /usr/local/share/Dune/
cp assets.yaml /usr/local/share/Dune/

# Binaries
mkdir /usr/local/share/Dune/bin -p
cp build/dune_client /usr/local/share/Dune/bin/
cp build/dune_server /usr/local/share/Dune/bin/
cp build/editor /usr/local/share/Dune/bin/

cp installer/dune_client /usr/local/bin/dune_client
cp installer/dune_server /usr/local/bin/dune_server
cp installer/dune_editor /usr/local/bin/dune_editor

chmod +x /usr/local/bin/dune_client
chmod +x /usr/local/bin/dune_server
chmod +x /usr/local/bin/dune_editor

rm -rf build