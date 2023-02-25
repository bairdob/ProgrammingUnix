#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/fs.h> 
#include <asm/uaccess.h> /* для put_user */

MODULE_LICENSE("GPL");
/* 
 * Прототипы 
 */ 

int init_module(void); 
void cleanup_module(void); 
static int device_open(struct inode *, struct file *); 
static int device_release(struct inode *, struct file *); 
static ssize_t device_read(struct file *, char *, size_t, loff_t *); 
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0 
#define DEVICE_NAME "chardev" /* Имя устройства добаляемое в /proc/devices */
#define BUF_LEN 1024 /* Максимальная длина сообщения в устройстве */

/*
 * Глобальные переменные, декларированные как static, глобальные внутри файла. 
 */

static int Major; /* Major-номер, для нашего устройства */ 
static int Device_Open = 0; /* Is device open? Используется, чтобы ограничить 
			     * множественный доступ к устройству */ 
static char msg[BUF_LEN]; /* The msg the device will give when asked */ 
static char *msg_rPtr;
static char *msg_wPtr;
static struct file_operations fops = { 
	.read = device_read, 
	.write = device_write, 
	.open = device_open, 
	.release = device_release 
};

/*
 * Эта функция вызывается, когда модуль загружается. 
 */
int init_module(void) { 
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) { 
		printk(KERN_ALERT "Регистрация симв. устройства failed для %d\n", Major); 
	return Major; 
	}

	printk(KERN_INFO "Был присвоен major-номер %d.\n", Major); 
	printk(KERN_INFO "To talk to the driver, create a dev file with\n"); 
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major); 
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n"); 
	printk(KERN_INFO "the device file.\n"); 
	printk(KERN_INFO "Remove the device file and module when done.\n");
	sprintf(msg, "Some msg!\n");

	return SUCCESS;
}

/* 
 * Эта функция вызывается, когда модуль выгружается. 
 */ 
void cleanup_module(void) {
	/* 
	 * Unregister the device 
	 */
	unregister_chrdev(Major, DEVICE_NAME); 
}

/* 
 * Методы:
 * Вызывается, когда процесс открывает файл устройства, подобно: 
 * "cat /dev/mycharfile" */ 
static int device_open(struct inode *inode, struct file *file) { 
	static int counter = 0;

	if (Device_Open) 
		return -EBUSY;

	Device_Open++; 
	printk("Я уже сообщил тебе %d раз Hello world!\n", counter++); 
	printk("Opening /dev/chardev process name is %s\n", current->comm);
	msg_rPtr = msg; 
	msg_wPtr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

/* 
 * Вызывается, когда процесс закрывает файл устройства.
 */ 
static int device_release(struct inode *inode, struct file *file) { 
	Device_Open--; /* Мы теперь готовы для следующего вызова */

	/* 
	 * Decrement the usage count, or else once you opened the file, you'll 
	 * never get get rid of the module.
	 */ 
	module_put(THIS_MODULE);

	return 0;
}

/* 
 * Вызывается, когда процесс, который уже открыл файл устройства, 
 * пытается читать из него.
 */ 
static ssize_t device_read(struct file *filp, /* смотри include/linux/fs.h */
			   char *buffer, /* буфер для данных */ 
			   size_t length, /* длина буфера */ 
			   loff_t * offset) /* смещение */ {


	/* 
	 * Число байт, реально записанных в буфер 
	 */

	int bytes_read = 0;

	/* 
	 * Если конец сообщения, то
	 * return 0, обозначая конец файла 
	 */ 
	if (*msg_rPtr == 0) 
		return 0;

	/* 
	 * Фактическая посылка данных в буфер 
	 */ 
	while (length && *msg_rPtr) {

		/* 
		 * Буфер находится в user data segment, not the kernel 
		 * segment so "*" assignment won't work. Мы можем использовать 
		 * put_user, которая копирует данные из сегмента данных ядра в 
		 * сегмент данных пользователя.
		 */ 
		put_user(*(msg_rPtr++), buffer++);

		length--; 
		bytes_read++;

	}

	/* 
	 * Большинство функций чтения возвращают число байт, посланных в буфер 
	 */ 
	return bytes_read;
}


static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off) {
    int i;
    for(i=0; i<len && i<BUF_LEN; i++)
    get_user(msg[i], buff+i);
    msg_wPtr = msg;
    return i;
}
