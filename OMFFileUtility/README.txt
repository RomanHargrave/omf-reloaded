One Must Fall: 2097 File Format Utility

OBJECTIVE: Make a program that allows you to edit every file
of OMF without dificult.

DONE:
· Read and edit Fonts (8 bytes fonts and 6 bytes fonts).
· Read and edit Sprite headers.

TODO:
· Read and edit HARs (.AF). 
· Read and edit backgrounds (.BK).
· Finish reverse engineer the rest of the files.

HOW TO's:

· COMPILE:
	You can use code::blocks to compile the proyect without to much 
	complication. Or you can compile by hand every single file.
	You don't need to link any library, as this is written in
	pure C.

· USE:
	This program is CLI (Comand Line Input). So, you need to 
	execute this program with the use of the terminal (linux)
	or console (windows). Just follow the help. For instance:

	program -iGRAPHCHR.DAT -tfont8 

	Will init the program for editting the big font of the game.

· USE THE set COMMAND:
	The "set" command is one of the most important commands. It 
	allows you to edit by hand any value of the file. You use:

	set kind offset value

	For instance:

	set sbyte 4A -2

	Will edit the byte at 0x04A and change it value to -2. 
	The kind of value you can choose is:

	byte 	- just a unsigned byte
	sbyte 	- a signed byte
	word	- a 16 bits unsigned word
	sword	- a signed word
	dword	- 32 bits double word

FAQ's:

