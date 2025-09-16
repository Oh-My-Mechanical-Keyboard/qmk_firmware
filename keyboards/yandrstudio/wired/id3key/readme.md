# id3key
===

A 3 keys keyboard.

- Keyboard Maintainer: https://idobao.net/
- Hardware Supported: https://github.com/Oh-My-Mechanical-Keyboard
- Hardware Availability: https://idobao.net/

Make example for this keyboard (after setting up your build environment):

    make yandrstudio/wired/id3key:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard.
* **Physical reset pins**: Press the `reset` pin twich on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (`RESET`) if it is available.
