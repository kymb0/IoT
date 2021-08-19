#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/netfilter.h>
#include<linux/netfilter_ipv4.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<linux/hardirq.h>

/* This code will only work with newer kernels > 4.4.0 as the netfilter interface has changed. 
   Should be easy to back port but I have no desire
*/

// defined in netfilter_ipv4.h for userspace?? 
#define NF_IP_PRE_ROUTING 0
#define MAX_IP_LEN      16

#define COVERT_SRC_TCP_PORT     9999
#define COVERT_DST_TCP_PORT     9999
#define MAX_COMMAND_SIZE        512

static unsigned int hooker(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {

        struct iphdr *ip_header;
        struct tcphdr *tcp_header;
        unsigned char *data;
        unsigned char *skb_tail;
        unsigned char covert_command[MAX_COMMAND_SIZE];
        int command_len;

        char src_ip[MAX_IP_LEN];
        char dst_ip[MAX_IP_LEN];


        memset((void *)covert_command, 0, MAX_COMMAND_SIZE);


        if(skb == NULL) {

                pr_info("NULL skb recvd");
        } else {

                ip_header = ip_hdr(skb);

                if(ip_header != NULL && ip_header->protocol == IPPROTO_TCP) {

                        tcp_header = tcp_hdr(skb);

                        if(tcp_header != NULL) { 


                                if(ntohs(tcp_header->source) == COVERT_SRC_TCP_PORT 
                                        && ntohs(tcp_header->dest) == COVERT_DST_TCP_PORT 
                                        && tcp_header->syn 
                                        && tcp_header->rst ) {


                                data = (unsigned char *)((unsigned char *)tcp_header + (tcp_header->doff * 4));

                                skb_tail = skb_tail_pointer(skb);


                                if(skb_tail > data) {

                                        // Yes, there is data! :) 

                                        pr_info("\n*******Covert*****Channel*******\n");

                                        snprintf(src_ip, MAX_IP_LEN, "%pI4", &ip_header->saddr);
                                        snprintf(dst_ip, MAX_IP_LEN, "%pI4", &ip_header->daddr);

                                        pr_info("In device: %s\n",  
                                                        state->in->name);
                                        pr_info("Packet: Src-IP: %s Dst-IP: %s\n", 
                                                        src_ip, dst_ip);

                                        pr_info("Source Port: %d Destination Port: %d\n",
                                                ntohs(tcp_header->source), ntohs(tcp_header->dest));

                                        pr_info("Data ptr: %px Skb tail: %px\n", 
                                                        data, skb_tail);


                                        // Let's parse and get the command! :) 

                                        command_len = (int) (skb_tail - data); 
                                        if (command_len >= MAX_COMMAND_SIZE) command_len = MAX_COMMAND_SIZE-1;

                                        memcpy((void *) covert_command, (void *)data, command_len);

                                        pr_info("Covert Command: %s\n", covert_command);
                                        pr_info("\n****************************\n");
 
                                        return NF_DROP;

                                }


                                }
                        }

                }

        }


        // Accept everything else 
        return NF_ACCEPT;
}

static struct nf_hook_ops outgoing = {
        .hook = hooker,
        .hooknum = NF_IP_PRE_ROUTING,
        .pf = NFPROTO_IPV4,
        .priority = NF_IP_PRI_LAST

};


static int __init my_init(void) {


        pr_info("[covertchannel] Inserting hook!\n");

        nf_register_net_hook(&init_net, &outgoing);

        return 0;

}


static void __exit my_exit(void) {

        pr_info("[covertchannel] Removing and exiting hook ...\n");
        nf_unregister_net_hook(&init_net, &outgoing);

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("VIVEK");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Basic demo of Kernel network montioring");
