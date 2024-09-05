#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h> //copy_to/from_user()

#define DEVICE_MAJOR 227
#define DEVICE_NAME "adxl345"

#define I2C_ADDRESS 0x53       // I2C 設備位置
#define BUF_SIZE 6             // 讀取的數據大小
#define DATA_REG 0x32          // 資料存放位置
#define DATA_FORMAT_REG 0x31   // 資料格式設定位置
#define DATA_FORMAT_VALUE 0x0B // 資料格式設定內容
#define POWER_CTL_REG 0x2D     // 電源模式設定位置
#define POWER_CTL_VALUE 0x08   // 電源模式設定內容

static struct i2c_client *my_i2c_client;

static unsigned char buf[BUF_SIZE];

static void position_read_data(void) {
  // 讀取長度6的資料
  if (i2c_smbus_read_i2c_block_data(my_i2c_client, DATA_REG, 6, buf) < 0) {
    printk(KERN_ERR "i2c_smbus_read_i2c_block_data");
    return;
  }
}

static ssize_t position_read(struct file *file, char *buffer, size_t size,
                             loff_t *off) {
  int ret;

  // 讀取資料
  position_read_data();

  // 檢查請求大小是否符合
  if (size < sizeof(buf)) {
    return -EINVAL;
  }

  // 複製數據到user space
  ret = copy_to_user(buffer, buf, sizeof(buf));
  if (ret != 0) {
    printk(KERN_ERR "Failed to copy data to user space\n");
    return -EFAULT;
  }

  printk(KERN_INFO "Read %d bytes: ", BUF_SIZE);
  for (int i = 0; i < BUF_SIZE; i++) {
    printk("%02X ", buf[i]);
  }
  printk("\n");

  return sizeof(buf);
}

static int position_open(struct inode *inode, struct file *file) {
  printk(KERN_INFO "Device opened\n");
  return 0;
}

static int position_release(struct inode *inode, struct file *file) {
  printk(KERN_INFO "Device released\n");
  return 0;
}

static struct file_operations position_dev_fops = {
    .owner = THIS_MODULE,
    .open = position_open,
    .read = position_read,
    .release = position_release,
};

static struct class *adxl_class;

static void init_adxl345(void) {
  int ret;

  // 設定感測器
  // 設定測量範圍(+-16)
  ret = i2c_smbus_write_byte_data(my_i2c_client, DATA_FORMAT_REG,
                                  DATA_FORMAT_VALUE);
  if (ret < 0) {
    printk(KERN_ERR "Failed to initialize ADXL345 DATA_FORMAT register\n");
  }

  // 設定電源模式
  ret =
      i2c_smbus_write_byte_data(my_i2c_client, POWER_CTL_REG, POWER_CTL_VALUE);
  if (ret < 0) {
    printk(KERN_ERR "Failed to initialize ADXL345 POWER_CTL register\n");
  }
}

static int __init position_dev_init(void) {
  int ret;
  struct i2c_adapter *adapter;
  struct i2c_board_info info = {
      I2C_BOARD_INFO("adxl345", I2C_ADDRESS),
  };

  ret = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &position_dev_fops);
  if (ret < 0) {
    printk(KERN_ERR "Failed to register character device\n");
    return ret;
  }
  printk(KERN_INFO "ADXL345 driver registered successfully\n");

  adxl_class = class_create(THIS_MODULE, "adxl345");
  if (IS_ERR(adxl_class)) {
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_ERR "Failed to create class\n");
    return PTR_ERR(adxl_class);
  }

  if (IS_ERR(device_create(adxl_class, NULL, MKDEV(DEVICE_MAJOR, 0), NULL,
                           DEVICE_NAME))) {
    class_destroy(adxl_class);
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_ERR "Failed to create device\n");
    return -1;
  }

  adapter = i2c_get_adapter(1);
  if (!adapter) {
    class_destroy(adxl_class);
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_ERR "Failed to get I2C adapter\n");
    return -ENODEV;
  }

  my_i2c_client = i2c_new_client_device(adapter, &info);
  i2c_put_adapter(adapter);
  if (!my_i2c_client) {
    class_destroy(adxl_class);
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_ERR "Failed to create I2C client\n");
    return -ENODEV;
  }

  init_adxl345();
  printk(KERN_INFO "ADXL345 driver initialized successfully\n");

  return 0;
}

static void __exit position_dev_exit(void) {
  if (my_i2c_client) {
    i2c_unregister_device(my_i2c_client);
  }

  device_destroy(adxl_class, MKDEV(DEVICE_MAJOR, 0));
  class_destroy(adxl_class);
  unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);

  printk(KERN_INFO "ADXL345 driver exited\n");
}

module_init(position_dev_init);
module_exit(position_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WWW");
MODULE_DESCRIPTION("ADXL345 Accelerometer Driver");
