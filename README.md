# i2c-unix

This library provides bindings to the `i2c-dev` module of the Linux kernel to
access the I2C bus from user space.

It is partly inspired by the older [ocaml-i2c](https://github.com/mwweissmann/ocaml-i2c) library by Markus Weissmann, aiming to use more modern tools.

Its API is very straightforward and documented [online](FIXME).

## Installation

> Run `opam install i2c-unix`

You will have to have the SMBus i2c headers available on your system for the
package to build, provided by `i2c-tools` on Arch Linux or `libi2c-dev` on
Debian.

## Usage

For the library to work, ensure:
- the `i2c_dev` kernel module is loaded (`lsmod | grep i2c_dev`)
- you have an I2C bus attached to the system (`i2cdetect -l`)

Then you can use this library, with the name of the device returned by
`i2cdetect` (usually of the form `i2c-X`):

```ocaml
(* This snippet reads a byte from the bus at address 0x20 *)
let (let*) = Result.bind

let i2c =
  let* t = I2c_unix.open_device "i2c-1" 0x20 in
  let* b : Stdint.uint8 = I2c_unix.read_byte t in
  (* do something with b *)
  I2c_unix.close_device t
```  
