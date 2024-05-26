# User Notes

> Author: Dr Zeeshan Mujawar

## Introduction
This file contains notes and logs of the progress and plans with the custom  firmware that I am experimenting with for the keychron Q3 Pro. 

Most of the code is applied to the MacOS layer as I am primarily using the keyboard with MacOS and do not have the inclination to copy over the code to the `WIN` layer. People who are looking to use this code on Windows based machines, would benefit from swapping the layers for Windows.

## To-Do List 
- [X] Dynamic Macros
- [ ] Mouse Keys
- [X] Custom RGB
- [X] Custom Macros
- [X] Dynamic Custom Encoder with Indicator
- [X] MO Layer selection with Encoder (VIAL Adaptation)
- [X] Caps Lock to Backspace. Caps Lock option on FN Layer
- [ ] Mod Tap
- [ ] WPM Implementation
- [X] CAPS Idicator on CAPS LOCK key
- [X] Clipboard manager and copy set on M4 key
- [X] Backspace custom toggle on Backspace key on FN layer

## Complex
- [ ] OS level HID App
- [ ] RAW_HID
- [ ] Custom XAP Protocol
- [ ] KB Document
- [ ] Encoder Callback Fucntions
- [ ] ALT Tab Complex Macro (Previously implemented in the K8 Pro)

### Encoder Callback
```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
    }
    return false;
}
```

## Custom Keycode List


| Code      | Macro Name | Function |
|-----------|------------|----------|
| MRO_1| CMD+LEFT | Move MacOS Space Left|
|MRO_2| CMD+RIGHT | Move MacOS Space Right|
|MRO_3| CMD+SPACE| Show CommandBar MacOS|
|MRO_4 | Clipboard: Copy | Copy Command |
|MRO_5| Clipboard: Paste | Opens Paste Manager| 
|MRO_6| Text Input| Text Input for Password|
|MRO_BKSPC| Dynamic Bakcspace| Based on the Toggle Switches between regular backspace and ALT+BACKSPACE to delete whole word. Useful when typing out long documents. CAPS will still function as a regular backspace|
|MRO_BKSPC_TOGGLE| Dynamic Bakcspace Switch| Toggle between regular Backspace and the Whole word backspace. Set to FN+BACKSPACE|
|MRO_ENC_U| Encoder: Function Increment| Moves up to the next encoder function|
|MRO_ENC_D| Encoder: Fucntion Decrement| Moves down to the previous encoder function|
|MRO_ENC_CCW| Encoder: CCW Function| CCW macro based on the selected function code|
|MRO_ENC_CW| Encoder: CW Function| CW macro based on the selected function code|


## NEW TODO

- [ ] Leader Keys
- [ ] Dynamic Encoder
- [ ] Caps Word
- [ ] Backspace


