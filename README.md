# Huffman Coding
This project was designed to compress a text file using the Huffman algorithm without losing any data. In the sample file, the algorithm could compress a text file with 9.5 MB into a file with only 6.9 MB(25% reduced). The de-compressed file is identical to the original file. The compression effect depends on the content of the file. With the same size, the compression effect would be better for files with more repeated characters. The specialty about this project is that on certain occasions, the compression effect could even be better than the zip compression technique we normally use in our computer.

The Huffman Coding could be used in compressing image, mp3 or text file in real life.

# Three Files
"huff.c", Platform: Xcode, Language: C : 
The program will accept one command line argument, which will be the name of an input file and then write out the compressed output to a file that has the same name as the input file with a “.huff.txt” appended to it. 

"unhuff.c", Platform: Xcode, Language: C : 
The program will accept one command line argument, which will be the name of an input file and then write out the de-compressed output to a file that has the same name as the input file with a “.unhuff.txt” appended to it. 

"test file", Platform: Xcode, Language: C : 
The file included the file for testing and the sample output for compressed file and de-compressed file.
