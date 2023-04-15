#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/pci_regs.h>
#include <linux/init.h>
#include <linux/etherdevice.h>

#define PCI_VENDOR_ID 0x10ec
#define PCI_DEVICE_ID 0x8168
#define DRV_NAME "MyPCI"
#define ETH_ALEN 6

MODULE_LICENSE("GPL");

unsigned char mac_addr[ETH_ALEN];

static struct pci_device_id ids[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID, PCI_DEVICE_ID) },
	{ 0, }
};

int get_mac_address(struct pci_dev *pdev, unsigned char *mac_addr) {
    void __iomem *mmio_addr;
    u8 *mac_ptr;

    // Map the PCI device memory into kernel space
    mmio_addr = ioremap(pci_resource_start(pdev, 0), pci_resource_len(pdev, 0));
    if (!mmio_addr) {
        return -ENOMEM;
    }

    // Read the MAC address from the memory-mapped region
    mac_ptr = (u8 *)(mmio_addr + 0x0000);
    memcpy(mac_addr, mac_ptr, ETH_ALEN);

    // Unmap the memory region
    iounmap(mmio_addr);

    return 0;
}

/* kernel builds a table during build time in
   /lib/modules/<kern>modules.pcimap that which
   driver is supported for particular pci_vendor
 */
// MODULE_DEVICE_TABLE(pci,pci_tbl);

/*  1. 	Probe is called if a matching device in pci_tbl is found in the
 *  	the  System ,Called once for each matching device .if already called
 *  	another module , probe will not be called.
 *  2. 	when in Sysfs bind and new_id macthcing id found then Also probe is called
 */
static int my_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	
	printk(KERN_INFO "*** inside probe  *** \n");
	
	// Get the MAC address for the device
	if (get_mac_address(dev, mac_addr)) {
		printk(KERN_ERR "Unable to get MAC address\n");
		return -EINVAL;
	}

	printk(KERN_INFO "MAC address: %pM\n", mac_addr);

	return 0;
}

static void my_remove(struct pci_dev *dev)
{
	/* clean up done here */
}

/*pci driver operation */
static struct pci_driver pci_driver = {
	.name = DRV_NAME,
	.id_table = ids,
	.probe = my_probe,
	.remove = my_remove,
};

/*called while loading driver*/
int init_module(void)
{
	/*register the pci_driver structure with pci subsystem*/
	printk(KERN_INFO "*** inside init  *** \n");
	return pci_register_driver(&pci_driver);
}

/*called while rmmod or unbind from sysfs*/
void cleanup_module(void)
{
	printk(KERN_INFO "*** inside exit *** \n");
	pci_unregister_driver(&pci_driver);
}

