/*
Sorry about the delay. I was out of the office all last week 
and didn’t have access to my work email.
We just had a group discussion and decided to pass you onto the code challenge. 
Please complete the following task and send it back to us at your discretion:


!!!   Write a linux kernel module to create the device /dev/fibonacci. 
Writing to this device should have no effect, 
however reading at offset k should return the kth fibonacci number.


Once you are done, we will schedule the live portion of your code challenge. 
What to expect from that is you will be given a segment of code, you will 
have to read it, identify what it does, and identify any bugs that might be 
present. If you have any further questions, please let me know!

The Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 
377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 
121393, 196418, 317811

https://tldp.org/LDP/lkmpg/2.6/lkmpg.pdf


ls /lib/modules/$(uname -r)/build
make -C /lib/modules/$(uname -r)/build M=$(pwd)   
sudo lsmod                  //lsmod to see list of modules running
sudo rmmod fibonacci        //to unload module
sudo dmesg                  //to see what we printed


sudo insmod ./fibonacci.ko count=8      //will take 8 for k

*/


#include <linux/init.h>
#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO, printk() */


/*Meta info*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christopher Hovsepian");
MODULE_DESCRIPTION("First LKM, fibonacci");


int count = 1;
module_param(count, int, 0);
MODULE_PARM_DESC(count, "fib");


// Start function
static int my_init(void)
{
    // 8 prioritys.  can use <1> or KERN_ALERT
    printk(KERN_ALERT "fibonacci Start\n");

    if(k == 0){
        printk(KERN_ALERT "fibonacci number at position 0 is 0\n");
        return 0;
    }
    // verify that || means or in a LKM in C
    if(k == 1 || k == 2){
        printk(KERN_ALERT "fibonacci number at position 1 or 2 is 1\n");
        return 0;
        // cant return 1.  0 means ok, other number means error
    }

    int numA =0, numB = 1, numC, i;

    // for(i = 3; i <= k; i++)
    for(i = 2; i < k; i++)
    {
        numC = numA + numB;
        numA = numB;
        numB = numC;
    }
    printk(KERN_ALERT "fibonacci number at position %d is %d\n", k, numC);
    //return numC;

    return  0;
}

// End function
static void my_exit(void)
{
    printk(KERN_ALERT "my_exit started\n");
    return;
}
    
module_init(my_init);
module_exit(my_exit);




/*
What we've seen here is: insmod requires you to pass it the full pathname 
and to insert the modules in the right order, while  modprobe  just takes the 
name, without any extension, and figures out all it needs to know by parsing 

.ko

Note that kernel 2.6 introduces a new file naming convention: kernel modules 
now have a .ko extension (in place of the old .o extension) which easily 
distinguishes them from conventional object files. 








*/
