import streams
import hcsr04

streams.serial()

sens = hcsr04.hcsr04(D23, D22)

while True:
    cm = sens.get_distance_cm()
    
    print("Distance: %.2f" % cm)
    
    sleep(60)