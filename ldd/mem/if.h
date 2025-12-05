struct region{
	int num;
	char data[512];
};
struct w_hd{
	int key;
	off_t offset;
};

extern int vblock_backup_to_file(const char *path);
#define MAGIC 0x44
#define VBLOCK_LOCK_REGION _IOW(MAGIC,1,char)
#define VBLOCK_UNLOCK_REGION _IOW(MAGIC,2,char)
#define VBLOCK_READ_REGION _IOWR(MAGIC,3,struct readregion *)
#define VBLOCK_ERASE_REGION _IOW(MAGIC,4,char)
#define VBLOCK_GET_INFO	_IOR(MAGIC,5,unsigned char *)
