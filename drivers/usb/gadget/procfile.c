







/*
 * Processing for UI of USB event
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/***********************************************************************/
/* Modified by                                                         */
/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
/***********************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/proc_fs.h>	
#include <asm/uaccess.h>	

#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"usb_eut"





static struct proc_dir_entry *Our_Proc_File;





static char procfs_buffer[PROCFS_MAX_SIZE];





static unsigned long procfs_buffer_size = 0;





static int 
procfile_read(char *buffer,
	      char **buffer_location,
	      off_t offset, int buffer_length, int *eof, void *data)
{
	int ret;
	
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME);
	
	if (offset > 0) {
		
		ret  = 0;
	} else {
		
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}

	return ret;
}





static int procfile_write(struct file *file, const char *buffer,
                   unsigned long count, void *data)
{
	
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	
	
	if ( copy_from_user(procfs_buffer, buffer, procfs_buffer_size) ) {
		return -EFAULT;
	}
	
	return procfs_buffer_size;
}





int procfile_init(void)
{
	printk(KERN_INFO "procfile_init\n");

	if (Our_Proc_File) {
		printk(KERN_INFO "not call create_proc_entry\n");
		return 0;
	}

	
	Our_Proc_File = create_proc_entry(PROCFS_NAME, S_IFREG | S_IRUGO | S_IWUGO, NULL);
	
	if (Our_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
			PROCFS_NAME);
		Our_Proc_File = NULL;
		return -ENOMEM;
	}

	Our_Proc_File->read_proc  = procfile_read;
	Our_Proc_File->write_proc = procfile_write;

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);	
	return 0;
}




void procfile_fin(void)
{
	printk(KERN_INFO "procfile_fin\n");
	remove_proc_entry(PROCFS_NAME, NULL);
	Our_Proc_File = NULL;
	printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}








