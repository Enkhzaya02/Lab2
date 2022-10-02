#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

/* insmod rmmod dmesg -wH */

/* Birtday Structure zarlaj baina */
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

/* list.h dotorh LIST_HEAD-g ashiglan linked list uusgej baina */
static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
static int simple_init(void) {
    struct birthday *person;
    int i;
	printk(KERN_INFO "Loading Module\n");
    for (i = 0; i < 5; i++) {
		/* slab.h dotorh kmalloc-g ashiglan sanah oi nuutsluv */
		/* GFP_KERNEL gdg n engiin kerneliin ram nuutslunu */
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = 2 + i;
        person->month = 8 + i;
        person->year = 1995 + i;

        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    /* list_for_each_entry ni list.h dotor todorhoilogddog buguud ugsun turliin listeer davtdag */
    list_for_each_entry(person, &birthday_list, list) {
        printk(KERN_INFO "Created birthday: %d-%d-%d", person->year, person->month, person->day );
    }

    printk(KERN_INFO "Linked listiig amjilttai uusgelee\n");
    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {
    int i = 1;
    struct birthday *ptr, *next;
	printk(KERN_INFO "Removing Module\n");
	/* Kerneliin sanah oigoos linked list-g ustgah */
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
        printk(KERN_INFO "%d birthday amjilttai ustgagdlaa",i++);
    }
	
	printk(KERN_INFO "Listuudiig ustgaj duuslaa \n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
