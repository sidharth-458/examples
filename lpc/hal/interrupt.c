/**
 * FIQ Setup
 */
void fiq_set(uint32_t bitmap){
	VICIntSelect = bitmap;
	VICIntEnable = bitmap;
}
/**
 * handler fiq
 */
__fiq void FIQ_Handler(void){
	
	EXTINT = 0x2;
}
/**irq setup example*/
void irq_set(){
	VICVectCntl0 = 0x0000002F; //select a line
	VICVectAddr0 = (unsigned)EXTINTVectoredIRQ; //select isr
	VICIntEnable = 0x00008000; 
	while(1); 
}
void EXTINTVectoredIRQ (void) __irq{
	VICVectAddr = 0x00000000; //Dummy write to end
}
