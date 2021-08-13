#include<linux/module.h>
#include<linux/init.h>
#include <linux/kallsyms.h>
#include<linux/syscalls.h>
#include<linux/delay.h>
#include<linux/sched.h>

/*

        System-wide Monitor all attempts to kill processes

*/


static unsigned long **sys_call_table;
static char *process_name = NULL;


asmlinkage long (*real_sys_kill)(pid_t pid, int sig);

asmlinkage long new_sys_kill(pid_t pid, int sig)
{

        struct task_struct *p;

        /*  Let's find more about this process */

        for_each_process(p) {

                if(p->pid == pid) {

                        pr_info("[killmonitor] Kill attempt on %s (PID: %d) by %s (PID: %d) \n", 
                                p->comm, p->pid, current->comm, current->pid);

                        if(strstr(p->comm, process_name)) {

                                pr_info("[killmonitor] Disallowing kill ...\n");
                                return -1;
                        } else {

                                pr_info("[killmonitor] Not on protected list, allowing kill\n");
                                return real_sys_kill(pid, sig);
                        }


                }

        }

        return real_sys_kill(pid, sig);

}



static int __init my_init(void) {


        pr_info("[killmonitor] Starting module ...\n"); 

        if(process_name == NULL) {

                pr_info("[killmonitor] No file to protect? exiting\n");
                return -1;
        }

        // Only works with newer kernels. For older ones memory search is 
        // required. This code tested on 4.15.1
 
        sys_call_table = (void *) kallsyms_lookup_name("sys_call_table");


        // Assuming kernel data set to rw -- else we need to change page to rw
        // before this step 
        real_sys_kill = (void *)sys_call_table[__NR_kill];

        sys_call_table[__NR_kill] = (void *) &new_sys_kill;

        return 0;

}


static void __exit my_exit(void) {


        pr_info("[killmonitor] Exiting ... \n");

        sys_call_table[__NR_kill] = (unsigned long *)real_sys_kill;

        /* Sleep is needed to ensure that no running operations try to get back to the 
           old reference as the kernel will oops. This is required for high frequency 
           calls such as sys_open but we can keep it for others as well.
        */

        msleep(1000);

}

module_init(my_init);
module_exit(my_exit);

module_param(process_name, charp, S_IRUGO);
MODULE_PARM_DESC(process_name, "name of the process to protect");


MODULE_AUTHOR("Vivek");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Disallow killing a process by name");
