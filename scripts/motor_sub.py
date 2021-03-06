#!/usr/bin/env python3
import RPi.GPIO as GPIO
import time
import rospy
from ros_raspi_motor_control.msg import raspi_servo

global servo
global first

def callback(data):
    global first
    global servo
    if first:
        first = False
        motor_pin_pwm = data.pinNumber 
        GPIO.setup(motor_pin_pwm, GPIO.OUT)
        servo = GPIO.PWM(motor_pin_pwm, 50)
        servo.start(0)
        duty_cycle =(2.5 + (( 12.0 - 2.5 ) / 180.0) * ( 0 + 90.0 ))
        servo.ChangeDutyCycle(duty_cycle)
        time.sleep(0.5)
        servo.ChangeDutyCycle(0.0)
    else:
        duty_cycle =(2.5 + (( 12.0 - 2.5 ) / 180.0) * ( data.degree + 90.0 ))
        servo.ChangeDutyCycle(duty_cycle)
        time.sleep(0.4)
        servo.ChangeDutyCycle(0.0)

def sub():

    rospy.init_node('motor_sub', anonymous=True)

    rospy.Subscriber("RASPI_MOTOR/move_servo", raspi_servo, callback)

    rospy.spin()


        
if __name__ == '__main__':
    GPIO.setmode(GPIO.BCM)
    global first 
    first = True



    sub()

    servo.stop()
    GPIO.cleanup()
