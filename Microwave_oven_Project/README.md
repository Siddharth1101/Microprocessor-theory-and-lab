# Microcontroller of a Microwave Oven
This repository contains our prototype of the Microcontroller of a Microwave Oven written in AVR Atmega32, as per the course project requirement of EE2016: Microporcessor Theory and Lab at IIT Madras, Fall 2019.

<ul>
<li> In our model, we provide user with 10 buttons, 9 LEDs, an LCD and a buzzer. </li>
<li> Two buttons are provided to select one of the two Modes: microwave and grill. Three buttons are provided to increment the timer by 10s, 1min and 10min respectively.</li> 
<li> A clear/stop button is provided to reset the timer while setting the time. This button is also used to pause the timer count down when the microwave oven is in the ON condition. </li>
<li> Once the grill/microwave mode is pressed and the 600W/800W is set, the timer is set. </li>
<li> Two buttons are provided to select one of the two power levels: 600W and 800W. After pressing start button, timer starts decreasing with the LCD of selected mode glowing. This button is also used to resume the timer in-case the user has paused the timer to open the oven and check the status of food. </li>
<li> When the timer reaches 0, power gets off and a green LED glows for 12 seconds to indicate that the job is done, along with a buzzer long beep. A toggle switch is used to model an accidental door opening. A red LED glows and the buzzer beeps when door is opened accidentally. </li>
<li> Low frequency beep from the buzzer indicates that door is open while in configuration mode. A high frequency beep indicates “Danger” that door is opened while cooking.</li>
</ul>

<b>The Main Flowchart of the working of the microwave oven is given below:
![Main Flowchart](https://github.com/Siddharth1101/Microprocessor-theory-and-lab/blob/master/Microwave_oven_Project/Main%20Flowchart.jpg "Title")

The Bread-board implementation using the AVR Atmega32 Chip is given below:
![Our bread-board picture](https://github.com/Siddharth1101/Microprocessor-theory-and-lab/blob/master/Microwave_oven_Project/Oven_Board.jpg "Title")

Alternatively, our video description and the final functioning of the project is given in this YouTube link:</b> https://www.youtube.com/watch?v=MudgaewhIiQ&feature=youtu.be
