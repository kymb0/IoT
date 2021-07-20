to find services running we just nmap all ports

Interact with RabbitMQ http api to pull info: 
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/overview | python -m json.tool`
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/cluster-name`  
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/vhosts`  
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/vhosts | python -m json.tool | grep name`  
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/exchanges/%2F/amq.topic | python -m json.tool`  
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/exchanges | python -m json.tool | grep name | wc -l`  
`curl -q -XGET http://guest:guest@192.68.208.3:15672/api/queues | python -m json.tool | grep name`
`curl -q -XGET
http://guest:guest@192.68.208.3:15672/api/exchanges/%2F/amq.topic | python -m json.tool`  
Further enumerate by running amqp script against ports:  
`nmap --script amqp-info -p 5672 192.161.129.3`  
Retrieve messages from queue:  
save below script:  
```
#!/bin/bash
read line
echo $line
```  
Then run `amqp-consume --url amqp://guest:guest@192.161.129.3 -q sensors ./get.sh`
