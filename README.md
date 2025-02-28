# kernel_module_parametrs_example

A simple Linux kernel module that prints messages to the kernel log based on a module parameter. The parameter `mp_print_level` controls the verbosity of the output.

## Building

1. Ensure you have the kernel headers and build tools installed:
   ```bash
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```
2. Build the module:
   ```bash
   make
   ```

## Usage

- Load the module with a specified print level:
  ```bash
  sudo insmod parametrized_module.ko mp_print_level=1
  ```
- Check the kernel logs for insert output:
  ```bash
  dmesg | tail
  ```
  
- Update print level:
  ```bash
  echo 2 | sudo tee /sys/module/parametrized_module/parameters/mp_print_level
  ```

- Unload the module:
  ```bash
  sudo rmmod parametrized_module
  ```

- Check the kernel logs for remove output:
  ```bash
  dmesg | tail
  ```

## License

Dual MIT/GPL
