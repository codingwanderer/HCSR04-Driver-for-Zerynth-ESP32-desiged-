class hcsr04:
    
    @c_native("read_hcsr04_raw", ["read_hcsr04.c"], [])
    def _get_distance_raw(trig, echo):
        pass
    
    def get_distance_raw(self):
        return hcsr04._get_distance_raw(self.trigger, self.echo)
    
    def get_distance_cm(self):
        return self.get_distance_raw() / 58
    
    def get_distance_inch(self):
        return self.get_distance_raw() / 148
    
    def __init__(self, trigger, echo):
        self.trigger = trigger
        self.echo = echo
        
        pinMode(self.trigger, OUTPUT)
        pinMode(self.echo, INPUT)