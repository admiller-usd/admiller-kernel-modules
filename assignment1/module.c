/*******************************************************
 *                Cyber 570: Assignment 1
 *                 Author: Austin Miller
 *
 ******************************************************/
// Include Libraries
#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>
#include <linux/proc fs.h>
#include <asm/uaccess.h>

// Define constants
#define BUFFER_SIZE 128
#define PROC_NAME "hello"

// Prototyping 
ssize_t proc_read(struct file *file, char __user *usr_buf, 
		size_t count, loff_t *pos);

// Struct (kind of like an object)
static struct file_operations proc_ops = {
	.owner = THIS MODULE,
	.read = proc read,
};

int init_module(void)
{
	printk(KERN_INFO "Proc Module Inserted.\n");
	
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Proc Module Removed.\n");
}

// Macros to declare license and author
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Austin Miller");
