import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
led=21

GPIO.setup(led,GPIO.OUT)

try:
	while True:
    	  GPIO.output(led,True)
    	  time.sleep(1)
    	  GPIO.output(led,False)
    	  time.sleep(1)
finally:
   GPIO.cleanup()
