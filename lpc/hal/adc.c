/* adc set configtuation to ADxCR 
 * start by ADC | 1 << 24
 * wait till ADxGDR & 0x80000000 BECOMES 1
 * res = (ADxDR1 >> 6 ) & (0X3ff) 
 */
