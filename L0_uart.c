/*************************************************************************************************/
/* filename:  L0_uart.c
 *
 * content:   Functions to communicate via UART
 *
 * CREATED
 * date:      12.02.2015
 * version:   1.1
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/
 
 #include "config.h"
 
 uint8_t pixel[6] = {0, 0, 0, 0, 0, 0};
 uint8_t pixelbuffer[MATRIX_WIDTH][MATRIX_HEIGHT][3];
 
 // get a UART packet and update framebuffer
 // if clear panel command is received -> clear frame buffer
 // if start streaming command is received -> receive full image and update frame buffer
 void getPixelsFromUART(void)
 {
		if(XMC_USIC_CH_RXFIFO_IsEmpty(XMC_UART0_CH0) == false && XMC_USIC_CH_RXFIFO_GetLevel(XMC_UART0_CH0) >= 5)
		{				
				pixel[0] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // x
				pixel[1] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // y
				pixel[2] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // R
				pixel[3] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // G
				pixel[4] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // B
									
				if(!(pixel[0] == 253 && pixel[1] == 253))		// if condition is true -> drawing pixel is 
				{																					 // received, no streaming of complete image
							pixel[5] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);    // CS is read only if no 
																										// start/stop streaming command is received
							
						// synchronization -> until the checksum is correct, to find the correct x, y, R, G, B 
						// values for the particular pixel
						while(pixel[5] != (pixel[0] ^ pixel[1] ^ pixel[2] ^ pixel[3] ^ pixel[4]) && XMC_USIC_CH_RXFIFO_IsEmpty(XMC_UART0_CH0) == false)
						{
							pixel[0] = pixel[1];    // x = y
							pixel[1] = pixel[2];    // y = R
							pixel[2] = pixel[3];    // R = G
							pixel[3] = pixel[4];    // G = B
							pixel[4] = pixel[5];    // B = CS
							pixel[5] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);			
						}
						
						// clear panel if "clear panel" command is received	
						if(pixel[0] == 254 && pixel[1] == 254)
							initEmptyPanel();		
						
						// update single pixels in the framebuffer if no "start streaming" command was received
						else if(pixel[5] == (pixel[0] ^ pixel[1] ^ pixel[2] ^ pixel[3] ^ pixel[4]))
							framebuffer_update_1px(pixel[0], pixel[1], pixel[2], pixel[3], pixel[4]);		
				}							
				
				// start streaming (filling the framebuffer) if "start streaming" command is received				
				else if (pixel[0] == 253 && pixel[1] == 253)		
				{		
						OE_H;	// disable LED panel while receiving data
					
						while(pixel[0] != 252 && pixel[1] != 252)		// store the received pixel RGB values 
						{																						// in the pixelbuffer
							if(XMC_USIC_CH_RXFIFO_GetLevel(XMC_UART0_CH0) >= 5)
							{
								pixel[0] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);
								pixel[1] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);
								if(pixel[0] < 32 && pixel[1] < 32)
								{
								pixelbuffer[pixel[0]][pixel[1]][0] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);	// R
								pixelbuffer[pixel[0]][pixel[1]][1] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);	// G
								pixelbuffer[pixel[0]][pixel[1]][2] = XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);	// B
								}
							}
						}
						
						// Clear FIFO Buffer after stop streaming command was received
						while(XMC_USIC_CH_RXFIFO_IsEmpty(XMC_UART0_CH0) == false)
						{
							XMC_USIC_CH_RXFIFO_GetData(XMC_UART0_CH0);
						}
						
						// after the streaming has finished - update framebuffer out of the filled pixelbuffer
						for(int x=0;x<MATRIX_WIDTH;x++) {		
								for(int y=0;y<MATRIX_HEIGHT;y++) {
									framebuffer_update_1px(x, y, pixelbuffer[x][y][0], pixelbuffer[x][y][1], pixelbuffer[x][y][2]);							 
								}
						}
						OE_L;	// enable LED panel when data is received and framebuffer updated
				}
		}
}
