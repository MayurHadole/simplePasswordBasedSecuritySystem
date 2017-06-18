/*  FILE          : simplePasswordBasedSecuritySystem.ino
    PROJECT       : PROG8125-16S
    PROGRAMMER    : Mayur Hadole (5783)
    FIRST VERSION : 2016-06-12
    DESCRIPTION   :
       This program takes input(i.e passcode of 4 digit/character
    or combilnation of both ) from user through serial port and
    if it matches to one of the 10 existing passcodes stored in
    an array, the serial port shows "Access Granted".If not
    serial port will show "Access Denied".
        As a feedback for access granted, green LED will be ON,
    speaker will beep once and LCD will Display "ACCESS GRANTED".
        For feedback of access denied, red LED will be OFF,
    speaker will beep twice and LCD will Display "ACCESS GRANTED".
        if entered passcode is more the 4 digits long, Serial port
    will show "Password is of 4 digits, Plese enter again" and will
    show "access denied" on serial port and LCD


         This code is tested on Teensy 3.1 board
*/
