#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pci.h>

#define PCI_VENDOR_ID 0x1af4
#define PCI_DEVICE_ID 0x1000
#define DRV_NAME "MyPCI"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PCI DRIVER");

static int major;
static int port_addr;

static struct pci_device_id pci_tbl[] = {
    { PCI_DEVICE(PCI_VENDOR_ID, PCI_DEVICE_ID) },
    { 0, },
}; 
MODULE_DEVICE_TABLE (pci, pci_tbl);


int probe(struct pci_dev *dev, const struct pci_device_id *id) {
    //port_addr = pci_resource_start(dev,0);
  //  major = register_chrdev(0, DRV_NAME, &rtl8139_pci_driver);
    printk(KERN_INFO "PROBE");
    //printk(KERN_INFO "Load driver PCI %d\n",major); 
    return 0;
};

void remove(struct pci_dev *dev) { 
    printk(KERN_INFO "REMOVE");
    unregister_chrdev(major, DRV_NAME); 
};

static struct pci_driver pci_driver = { 
    .name = DRV_NAME, 
    .id_table = pci_tbl, 
    .probe = probe, 
    .remove = remove,
};


int init_module (void) { 
    printk(KERN_INFO "INIT_MODULE");
    return pci_register_driver(&pci_driver); 
};

void cleanup_module(void) { 
    printk(KERN_INFO "CLEANUP_MODULE");
    pci_unregister_driver(&pci_driver); 
};

