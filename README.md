# Google-T-Rex-Game
Introduction: We developed the Google T-Rex Game which could be played using our customized circuit board. The T-Rex need to overcome the obstacles by jumping accross the cactus or dodging the upcoming crow to keep itself alive. The project could be seperated into three parts, main game program, sound generation and hardware development. In order to display the User Interface, we developed our own library to cooperate with the two screen Graphic LCD (64+64)x64. It should be noted that STM32f051r8t6 has relative small memories(64 Kbyte flash memory and 8 Kbyte of SRAM), so we mainly use for loop and bit map to reduce the memory usage.

For the main game part, we used our own algorithm to randomly produce three different characters: single cactus, cactus cluster and crow with random distances, which is a significant specialty of this project. By using non-visible simple squares to record characters' position, we could track if the T-Rec touch the cactus or crow and determine if it is Game Over. At last, we added the bit map of each characters on the non-visible simple square to finish the User Interface. 

For the sound generation, we used the concept of Digital to Analog Conversion, Timer and Direct Memory Access to generate certain voltage ouput. By generating a wave form using the analog ouput and calculate each note's frequency, we could then produce sound wave of notes from C, D, E to A and B. 

Last but not least, the customized printed circuit board is another specialty of this project. The development board is also acceptable for this project, but the wiring is really a pain in the ass, so we developed the circuit board and soldered the STM32f051r8t6 ourselves. The wiring map and PCB are all provided in the above file.

# Project Video Demostration
https://www.youtube.com/watch?v=Yxi9itDUQOI
