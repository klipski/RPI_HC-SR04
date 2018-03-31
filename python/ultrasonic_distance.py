#-*- coding: utf-8 -*-

import RPi.GPIO as GPIO
import time

# set pin numbering mode to BOARD
# and disable warnings
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

# receiver pin
ECHO_PIN = 31
# sender pin
TRIGGER_PIN = 29

# set trigger pin as output
GPIO.setup(TRIGGER_PIN, GPIO.OUT)
# set echo pin as input
GPIO.setup(ECHO_PIN, GPIO.IN)

GPIO.output(TRIGGER_PIN, True)
time.sleep(0.00001)
GPIO.output(TRIGGER_PIN, False)

# wait for high state
while GPIO.input(ECHO_PIN) == 0:
    start = time.time()
# sensor response
while GPIO.input(ECHO_PIN) == 1:
    end = time.time()

# calculate result
measure = (end - start) * 17150.0

print (measure)
