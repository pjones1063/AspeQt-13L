;@com.wudsn.ide.asm.hardware=ATARI8BIT

;  This program is free software; you can redistribute it and/or modify
;  it under the terms of the GNU General Public License as published by
;  the Free Software Foundation; either version 2 of the License, or
;  (at your option) any later version.
;
;  This program is distributed in the hope that it will be useful,
;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;  GNU General Public License for more details.
;
;  You should have received a copy of the GNU General Public License
;  along with this program; if not, write to the Free Software
;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
;


	icl "menu_1.asm"
	
	org $4000
Start
	jsr printf
	.byte 125,155,'AspeQT              Version 5.13l ',155
	.byte         '------               13leader.net  ',155,155,155,0
		
 	icl 'menu_2.asm'    
 	
    icl 'printf.asm'      
		
SelectB
	.byte 0 	
ArgFlag
	.byte 0
CreateFlag
	.byte 0
Slot
	.byte 0
Drive
	.byte 0
DriveID1
	.byte 0
DriveID2
	.byte 0
Path 
	.ds 22
Filename
	.ds 16		
IOBuf
	.ds 253
IOLc   
    .ds   1	
IOLp
    .ds   1    			
InputBuf
	.ds 255

	
	run Start
	