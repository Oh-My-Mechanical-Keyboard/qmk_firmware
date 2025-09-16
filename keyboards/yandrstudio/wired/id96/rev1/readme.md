# ID96

A 96% keys keyboard with rgb (keys).
This keyboard use 16mhz HSE and APM32F103 (or STM32F103) as MCU.

- Keyboard Maintainer: https://github.com/jiaxin96
- Hardware Supported: id96
- Hardware Availability: https://github.com/Oh-My-Mechanical-Keyboard 

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/wired/id96/rev1/f103:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available.
