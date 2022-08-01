#!/bin/bash
if (($EUID != 0))
    then echo "Please run as root"
    exit
fi

rm -rf /usr/local/share/Dune
rm /usr/local/bin/dune_client
rm /usr/local/bin/dune_server
rm /usr/local/bin/dune_editor