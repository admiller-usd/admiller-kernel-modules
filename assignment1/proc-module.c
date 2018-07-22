/*******************************************************
 *                Cyber 570: Assignment 1
 *                 Author: Austin Miller
 *
 ******************************************************/
// Include Libraries
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

// Define constants
#define BUFFER_SIZE 128
#define PROC_NAME "hello"

// Prototyping 
ssize_t proc_read(struct file *file, char __user *usr_buf, 
		size_t count, loff_t *pos);

// Struct (kind of like an object)
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

// Module entrypoint 
int init_module(void)
{
    // Prints when module gets loaded into Kernel
    printk(KERN_INFO "Proc Module Inserted.\n");

    // Creates the /proc/hello entry 
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	
    return 0;
}

// Module exit 
void cleanup_module(void)
{
    // removes the /proc/hello entry
    remove_proc_entry(PROC_NAME, NULL);

    // Message when module removed from Kernel
    printk(KERN_INFO "Proc Module Removed.\n");
}

/* This function is called each time /proc/hello is read */
ssize_t proc_read(struct file *file, char __user *usr_buf, 
		size_t count, loff_t *pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE]; // size defined from const
    static int completed = 0;

    // Won't this always be false? 
    if (completed) {
    completed = 0;
    return 0;
    }

    completed = 1;
    rv = sprintf(buffer, "Hello World∖n"); // store string in buffer

    // copies kernel space buffer to user space usr_buf
    raw_copy_to_user(usr_buf, buffer, rv);
    return rv;
}

// Macros to declare license and author
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Austin Miller");
