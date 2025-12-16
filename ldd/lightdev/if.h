struct ld_state{
	atomic_t brt;
	atomic_t tmp;
	atomic_t on;
	atomic_t usrs;
};
#define MAGIC 0x44
#define LD_SET_ON		_IO(MAGIC,1)
#define LD_SET_OFF		_IO(MAGIC,2)
#define LD_SET_BRT		_IOW(MAGIC,3,int)
#define LD_SET_TMP		_IOW(MAGIC,4,int)
#define LD_GET_STATE		_IOR(MAGIC,5,struct ld_state*)

