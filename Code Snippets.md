# Overview
This document contains snippets of code that have been removed from the main program during development. Some of these (e.g. *Auto* function) should be kept, most should probably be discarded eventually.

## Bright Mode Switch Switching
```
  /* Set Bright Mode Controller
  if (lightModeCurrent == 1) {  // If on auto, read bright status from steering wheel stalk switch
    brightSelector = HIGH_BEAM_CAR;
  }
  else if (lightModeCurrent == 2) { // If on manual, read bright status from button
    brightSelector = HIGH_BEAM_DRIVER;
  }
  */
```

## Auto Mode
### Different Brights Control Criteria
```/*
  else if (lightModeCurrent == 2 && digitalRead(brightSelector) == HIGH) {
    delay(50);
    brightModeCurrent++;
    changeBrights();
  }
  */

  /*
  if (brightModeCurrent != 0 && digitalRead(brightSelector) == HIGH) {
    delay(50);
    brightModeCurrent = 0;
    changeBrights();
  }
  */
```

### Additional lightsOnOff Code
```  // For Auto Mode, not currently in use
  /*
  if (lightModeCurrent == 1 && digitalRead(CAR_LIGHTS) == HIGH) {
    digitalWrite(RELAY_L, LOW);
  }
  */
```

