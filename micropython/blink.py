from machine import Pin, Timer

def tik(timer):
    global led
    led.toggle()

# reference: https://docs.micropython.org/en/latest/library/machine.Pin.html
led = Pin(25, Pin.OUT)
timer = Timer()

timer.init(freq=2.5, mode=Timer.PERIODIC, callback=tik)

# difference in resistors? 1/8W vs. 1/4W
# reference: reddit.com/r/arduino/comments/6s4ca6/difference_in_resistors_18_vs_14/
# For example if you're putting 20mA through a resistor to drive a (1.7v) red LED from a 5v supply, it's gonna dissipate (5v-1.7v)*0.02mA = 66mW so a 1/16W or larger resistor would be fine - basically anything.