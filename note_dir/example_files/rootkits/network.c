#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/netfilter.h>
#include<linux/netfilter_ipv4.h>
#include<linux/ip.h>

/* This code will only work with newer kernels > 4.4.0 as the netfilter interface has changed. 
   Should be easy to back port but I have no desire
*/

// defined in netfilter_ipv4.h for userspace?? 
#define NF_IP_LOCAL_OUT 3
#define NF_IP_PRE_ROUTING 0
#define MAX_IP_LEN      16

static void print_protocol(uint8_t proto) {


        switch(proto) {

                case IPPROTO_UDP: pr_info("UDP: "); break;
                case IPPROTO_TCP: pr_info("TCP: "); break;
                default: pr_info("Unknown(%d): ", proto);


        }


}


static unsigned int hooker(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {

        struct iphdr *ip_header;
        char src_ip[MAX_IP_LEN];
        char dst_ip[MAX_IP_LEN];

        // check for sk_buff null

        pr_info("Hook called! ");
        if(skb == NULL) {

                pr_info("NULL skb recvd");
        } else {

                ip_header = ip_hdr(skb);

                if(ip_header != NULL) {

                        snprintf(src_ip, MAX_IP_LEN, "%pI4", &ip_header->saddr);
                        snprintf(dst_ip, MAX_IP_LEN, "%pI4", &ip_header->daddr);

                        print_protocol(ip_header->protocol);
                        pr_info("In device: %s Out device: %s\n",  state->in->name, state->out->name);
                        pr_info("Packet: Src-IP: %s Dst-IP: %s\n", src_ip, dst_ip);
 
                }

        }


        // Accept everything as we are just monitoring 
        return NF_ACCEPT;
}

static struct nf_hook_ops outgoing = {
        .hook = hooker,
        .hooknum = NF_IP_LOCAL_OUT,
        .pf = NFPROTO_IPV4,
        .priority = NF_IP_PRI_LAST

};



static int __init my_init(void) {

        nf_register_net_hook(&init_net, &outgoing);

        return 0;

}


static void __exit my_exit(void) {

        nf_unregister_net_hook(&init_net, &outgoing);

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("VIVEK");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Basic demo of Kernel network montioring");
