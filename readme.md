# About the author and purpose
I am a Software Engineering student in the Netherlands and this project is the final assignment of a course I am doing to learn how to write proper applications in C. The project's goal is to create 3 functionalities, encoding, channeling, and decoding, to be able to simulate message/file exchange between 2 computers using the internet or an Ethernet cable.
[Note: The channel only flips 1 random bit for each character in the file] 

# Usage steps
1. encoder [text-file-name] [output-file-name]
2. channel [output-file-of-encoder] [output-file-name]
3. decoder [output-file-of-encoder] [output-file-name]

# Files Description
* encoder - Used to create parity bits for each character that can be found inside of the provided text file, further saved onto a file with the specified by the user name.
* channel - Used to simulate interference from outside sources onto the file/message when being transmitted. This method uses srandom(time(NULL)) method to make sure that the output is always different.
* decoder - Used to remove the parity bits, check for and fix errors occurred when the file/message was in transition. The output of this script should be the message/file that was originally sent!