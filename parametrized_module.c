/*
 * parametrized_module.c
 ****************************************************************
 * Brief Description:
 * A very simple module which prints messages to logs dependently of passed
 *  parameters.
 *
 * Modules parameters are passed as key value pairs during `insmod` or
 *  `modprobe` execution. For example:
        sudo insmod parametrized_module.ko mp_print_level=2
 *
 * Parameters can be seen via `modinfo` utility:
         modinfo -p ./parametrized_module.ko
 *
 */

#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("KubaTaba1uga");
MODULE_DESCRIPTION("a simple LKM showing passing parameters feature");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

// mp stands for module parameter. It is not required but it is good practice.
static int mp_print_level;
// Here real magic happends. We are telling kernel to treat our mp_print_level
//  as module parameter of type int. kernel automatically initializes ints to 0
//  and create file in /sys/module/parametrized_module/parameters/mp_print_level
//  which user can use to controll the parameter during runetime. That's why we
//  are passing 0660 as third arg to module_param. Third arg stands for
//  permissions to the file automatically created for us. If third arg is set to
//  0 file is not created.
module_param(mp_print_level, int, 0660);
// This is just description for module param. We can see it when using `modinfo`
//  utility. This is standard way of telling user what params are available and
//  what they actually do.
MODULE_PARM_DESC(mp_print_level, "Print level [0-2]");

static int __init parameters_init(void) {
  int i;

  for (i = 0; i < 5; i++) {
    switch (mp_print_level) {
    case 0:
      pr_info("Inserted: i=%d\n", i);
      break;
    case 1:
      pr_info("Inserted: i=%d, max=%d\n", i, 5);
      break;
    case 2:
      pr_info("Inserted: i=%d, max=%d, mp_print_level=%d\n", i, 5,
              mp_print_level);
      break;
    default:
      pr_err("Unrecognized print level: %d", mp_print_level);
      return 1;
    }
  }

  return 0;
}

static void __exit parameters_exit(void) {
  pr_info("Removed: mp_print_level=%d\n", mp_print_level);
}

module_init(parameters_init);
module_exit(parameters_exit);
