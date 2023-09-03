import RPi.GPIO as GPIO
from time import sleep

ledPin = 4            # GPIO Pin Number, where LED is connected

GPIO.setmode(GPIO.BCM)        # Broadcom pin-numbering scheme (GPIO)
#GPIO.setmode(GPIO.BOARD)        # Board pin-numbers

GPIO.setup(ledPin, GPIO.OUT)     # LED pin set as output

GPIO.output(ledPin, GPIO.HIGH)     # Turn the LED on
sleep(1)                        # Sleep for 1 sec
GPIO.output(ledPin, GPIO.LOW)   # Turn the LED off
GPIO.cleanup()                  # Clean up at the end of the program
