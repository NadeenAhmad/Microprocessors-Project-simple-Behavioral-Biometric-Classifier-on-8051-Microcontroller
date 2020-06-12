# Microprocessors Project
## A Simple Behavioral Biometric Classifier on 8051-Microcontroller
* The program code is written in C & the software used to compile the code is Keil
* In this project we were asked to implement a simple Behavioral
Biometric Classifier on 8051 Microcontroller.
* The first thing our program does is receive input through peripheral port 0 after deciphering the value of this port the program detects which user is entering the training password “.tie5Ronal” if user A we create a profile for him/ her and save his/her data which will be explained in details later . 
* After that the program starts saving the time between each keystroke ending up with 9 features (time between 10 key strokes, 10 is the number of characters in the train password). 
* Since we were asked to provide a train data set of size five to our classifier each user will enter the train password 5 times. We then
calculate an average for each feature.
* Then the program enters the  test phase where it expects the train password once from unknown user to perform a simple classifying algorithm to effectively and efficiently guess the test user. 
* This classifying algorithm is a simplified Euclidean equation that compares the 9 features in the test vector to the 9 features in average user A vector and average user B vector. Then a decision is made to choose which user to output according to the Euclidean equation if user A the LED will flash one time else if user B the LED will flash multiple times. 
*  The code configures the UART of the C51 to get each time the user hits a key, identify
the key and check if it matches the training password “.tie5Ronal” if not
notify the user that he/she entered a wrong password by printing in the
UART a warning message. 
* The code reads input from a peripheral port (port 0) the
implementation relied mainly on reading the value and making a branching
decision upon this reading example: if port 0 reads value 0x0A means we
are in the training phase and user A will enter the password 5 times and the
timings will be saved in his/her profile else if port 0 reads 0x0B means we
are in the training phase and user B will enter the password 5 times and the
timings will be saved in his/her profile else if port 0 reads 0x0C means we
are in the test phase and an anonymous user will enter the training
password once. 
* Timers were used to track the interrupt
flag that keeps track of overflow to get the 9 features required (time
between 10 key strokes (5 times for each user) and one time for the test
user. 
* The program finds the average of each feature in each user’s profile which was achieved by
traversing each profile and dividing each feature by 5 (password was
entered 5 times). Then they implemented a simple function mimicking the
Euclidean equation that created a variable   
Da = [(featureTest0-featureA0)*
(featureTest0-featureA0)] +………. + [(featureTest8-featureA8)*
(featureTest8-featureA8)]   
and another variable   
Db = [(featureTest0-
featureB0)* (featureTest0-featureB0)] +………. + [(featureTest8-featureB8)*
(featureTest8-featureB8)].   
Comparing these two variables will give an
insight of how close the test vector is to average vector of user A or average
vector of user B. If (Da < Db) this indicates that test vector obtained results
closer to user’s A profile therefore user A is chosen so to notify the user 
with the output. The program sends 0s and 1s
with delays to peripheral port 1 & 2 to simulate flashing of the LEDs now
we can rest assured that the program performs correctly if the LEDs flash
once on port 1 this indicates user A was guessed else if the LEDs on port 2
flash multiple times this indicates user B was guessed. 
* A user guide including a full simulation example step-by-step with
snapshots for the training and the test phase.
- **Step #1:**
- First you need to build the code using f7 on the keyboard or the build
icon labeled in the screenshot as 1
- Second you need to debug the code using the debug icon labeled in
the screenshot a 2  
<img src="https://i.ibb.co/X51yZF3/test.jpg" width="500">  
<br>
- **Step#2:**  
In the debugging phase:  
- As mentioned before we need a switch to indicate whether we are in
training phase or test phase , also to know if we are in the training
which user is saving in his profile A or B , we will mimic the switch
using peripheral ports (Port 0 for input) : 0x0A -> train A , 0x0B->
train B , 0x0C -> test unknown .  
- We need another 2 ports to display the output so port 1 will be used
to flash once if user A is detected and port 2 will flash multiple times
to simulate the behavior of the LED if user B is detected therefore we
need to view Ports 1 & 2
- Password must be entered through a UART and a warning message
notifying the user that he/she entered an incorrect character
therefore we must view UART#1
Please see the screenshots below!! 
<img src="https://i.ibb.co/xjF7m9f/test2.jpg" width="500">
