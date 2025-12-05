/*first pinsel
 * then set UxLCR with word-len, stop-bit, parit, dlab set to 1 to edit clocks
 * set DLM = 0, and baud = PCLK/ (16*DLL) , then calc DLL
 * UxLCR dlab set to 0
 */
