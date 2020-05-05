#define ZERYNTH_PRINTF

#include "zerynth.h"

#define TicksPerMicros  (_system_frequency / 1000000)

void pseudoSleepForMicros(uint32_t micros){
    uint32_t startTicks = *vosTicks();
    
    while (*vosTicks() - startTicks < (TicksPerMicros * micros));
}

uint32_t pseudoICU(int pin, int mode, uint32_t timeout){
    uint32_t start_ticks = *vosTicks();
    
    while (*vosTicks() - start_ticks < (TicksPerMicros * timeout))
        if(!!vhalPinRead(pin) != !!mode)
            break;
    
    return (*vosTicks() - start_ticks) / TicksPerMicros;
}

C_NATIVE(read_hcsr04_raw) {
    C_NATIVE_UNWARN();
    
    int32_t triggerPin, echoPin;
    if (parse_py_args("ii", nargs, args, &triggerPin, &echoPin) != 2)
        return ERR_TYPE_EXC;
    
    vosSysLock();
    vhalPinWrite(triggerPin, 0);
    vhalPinWrite(triggerPin, 1);
    pseudoSleepForMicros(10);
    vhalPinWrite(triggerPin, 0);
    
    uint32_t start_ticks = *vosTicks();
    
    while(!vhalPinRead(echoPin));
    
    *res = PSMALLINT_NEW(pseudo_ICU(echoPin, 1, 35000));
    
    vosSysUnlock();
    
    return ERR_OK;
}