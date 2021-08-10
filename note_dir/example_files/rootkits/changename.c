#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/oom.h>
#include<linux/string.h>

static int process_pid = -1;
static char *new_name = "new_name_defval";

static int __init my_init(void) {

        struct task_struct *p;

        pr_info("[namechanger] Module init-ed ....\n");

        if(process_pid == -1) {

                pr_info("[namechanger] No PID given as input? Run modinfo for options\n");
                return -1;

        }

        for_each_process(p) {

                if(p->pid == process_pid) {

                        pr_info("[namechanger] Found the process with PID: %d (Current Name: %s)\n", 
                                        process_pid, p->comm);

                        memset((void *)p->comm, 0, TASK_COMM_LEN);

                        strncpy((char *)p->comm, new_name, TASK_COMM_LEN -1);

                        pr_info("[namechanger] Changed the name to %s\n", p->comm); 

                }

        }

        return 0;

}


static void __exit my_exit(void) {

        pr_info("[namechanger] Module exiting!\n");

}

module_init(my_init);
module_exit(my_exit);

module_param(process_pid, int, S_IRUGO);
MODULE_PARM_DESC(process_pid, "Target process PID");

module_param(new_name, charp, S_IRUGO);
MODULE_PARM_DESC(new_name, "New name for the target process");



MODULE_AUTHOR("VIVEK");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renaming running processes like Neo would");
