#include <pieces.h>
#include <numbers.h>
#include <typedefs.h>
#include <globals.h>

void main(void)
{
    int MoveRow, MoveCol;
    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // first store the address in the  back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = (int) *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer
	int colour = 0; //0 White 1 Black
    setupMouse();
    setupInterrupts();
    while (1)
    {   
        //draw board
		clear_screen();
        drawBoard();
        drawPieces();
        drawMouse();
        if(mousePressed) {
            getMove(&MoveRow, &MoveCol);
            checkMove(MoveRow,MoveCol,Colour,MoveValid);
            if(MoveValid) {
                colour = (colour == 1)? 0:  1;
            }
        }//make sure to enable interrupts for mouse after

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
		pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
    	
	}
}
