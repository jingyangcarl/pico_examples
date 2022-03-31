from machine import Pin, Timer

def tik(timer):
    global led
    led.toggle()

# reference: https://docs.micropython.org/en/latest/library/machine.Pin.html
led = Pin(25, Pin.OUT)
timer = Timer()

timer.init(freq=2.5, mode=Timer.PERIODIC, callback=tik)