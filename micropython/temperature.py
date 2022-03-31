import machine
import utime

# reference: https://docs.micropython.org/en/latest/library/machine.ADC.html
# reference: https://lemariva.com/blog/2018/12/micropython-visual-studio-code-as-ide
sensor = machine.ADC(4)
conversion_factor = 3.3 / (65535)

while True:
    reading_u16 = sensor.read_u16() * conversion_factor
    
    # The temperature sensor measures the Vbe voltage of a biased bipolar diode, connected to the fifth ADC channel
    # Typically, Vbe  0.706V at 27 degree C, with a slope of -1.721mV (0.001721) per degree
    temperature = 27 - (reading_u16 - 0.706) / 0.001721
    print(temperature)
    utime.sleep(2)