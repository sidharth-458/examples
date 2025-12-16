struct ts{
	atomic_t tmp;
	atomic_t high;
	atomic_t low;
	atomic_t alrtcnt;
	wait_queue_head_t alrtwq;
};
enum{
	NO_ALERT,
	TOO_HIGH,
	TOO_LOW,
};
#define MAGIC 0x44
#define LD_SET_TMP		_IOW(MAGIC,2,int)
#define LD_SET_HIGH		_IOW(MAGIC,3,int)
#define LD_SET_LOW		_IOW(MAGIC,4,int)
#define LD_GET_HIST		_IOR(MAGIC,5,int *)
#define LD_GET_ALRT		_IOR(MAGIC,6,int)

