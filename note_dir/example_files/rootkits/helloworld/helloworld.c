#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/oom.h>


static int __init my_init(void) {

        pr_info("Hello Cruel World of Kernel Programming!\n");

        return 0;

}


static void __exit my_exit(void) {

        pr_info("Wow! You exited early\n");

}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("VIVEK");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A Hello World Module");
