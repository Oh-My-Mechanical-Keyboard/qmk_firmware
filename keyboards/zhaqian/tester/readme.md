# tester

A test keyboard with rgb and different mcus.

Note: The source code for this keyboard has only been tested in this repository[[zhaqian](https://github.com/zhaqian12/qmk_firmware/tree/zhaqian)]!

* Keyboard Maintainer: [zhaqian](https://github.com/zhaqian12)
* Hardware Supported: tester
* Hardware Availability: [zq-kb](https://github.com/zhaqian12/ZQ-Keyboard)

Make example for this keyboard (after setting up your build environment):

* MCU:at90usb1286
    ```
    make zhaqian/tester/at90usb1286:default
    make zhaqian/tester/at90usb1286:via
    ```

* MCU:atmega32u4
    ```
    make zhaqian/tester/atmega32u4:default
    make zhaqian/tester/atmega32u4:via
    ```

* MCU:stm32f103/apm32f103/cks32f103/gd32f103/gd32f303
    ```
    make zhaqian/tester/f103:default
    make zhaqian/tester/f103:via
    ```

* MCU:stm32f401
    ```
    make zhaqian/tester/f401:default
    make zhaqian/tester/f401:via
    ```

* MCU:stm32f411
    ```
    make zhaqian/tester/f411:default
    make zhaqian/tester/f411:via
    ```
    
* MCU:gd32vf103
    ```
    make zhaqian/tester/gd32vf103:default
    make zhaqian/tester/gd32vf103:via
    ```
    
* MCU:stm32l433
    ```
    make zhaqian/tester/l433:default
    make zhaqian/tester/l433:via
    ```
    
 * MCU:air32f103xB/xC
    ```
    make zhaqian/tester/air32f103:default
    make zhaqian/tester/air32f103:via
    ```
    
 * MCU:stm32f407
    ```
    make zhaqian/tester/f407:default
    make zhaqian/tester/f407:via
    ```

 * MCU:stm32g431
    ```
    make zhaqian/tester/g431:default
    make zhaqian/tester/g431:via
    ```
    
 * MCU:at32f415
    ```
    make zhaqian/tester/at32f415:default
    make zhaqian/tester/at32f415:via
    ```
    
 * MCU:at32f413
    ```
    make zhaqian/tester/at32f413:default
    make zhaqian/tester/at32f413:via
    ```
    
 * MCU:at32f403a
    ```
    make zhaqian/tester/at32f403a:default
    make zhaqian/tester/at32f403a:via
    ```
    
 * MCU:at32f407
    ```
    make zhaqian/tester/at32f407:default
    make zhaqian/tester/at32f407:via
    ```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
 ## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
