# ocaml-i2c
ocaml-i2c provides an interface to the i2c bus via the Linux i2c-dev module.

## API
```ocaml
type t = private Unix.file_descr

val set_address : Unix.file_descr -> int -> (t, [> `EUnix of Unix.error ]) Result.result

val write_quick : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_byte : t -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_byte : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_byte_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_byte_data : t -> Stdint.uint8 -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_word_data : t -> Stdint.uint8 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result
val write_word_data : t -> Stdint.uint8 -> Stdint.uint16 -> (unit, [> `EUnix of Unix.error ]) Result.result
val process_call : t -> Stdint.uint8 -> Stdint.uint16 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result
val read_block_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result
val block_process_call : t -> Stdint.uint8 -> Stdint.uint8 list -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
```                                                                                                
## Usage
First make sure you have loaded the ```i2c-dev``` module and there is a ```/dev/i2c-0``` device.
In OCaml you then can open this device-file:
```ocaml
let i2c =
  let i2c_address = 0x20 in
  let fd = Unix.(openfile "/dev/i2c-0" [O_RDWR] 0x644) in
  match I2c.set_address fd i2c_address with
  | Result.Ok x -> x
  | Result.Error _ -> failwith "oops"
```  

You can now use the read/write functions to read/write from/to your device at address ```0x20```


The source code of ocaml-i2c is available under the MIT license; the included Linux header file is under GPL2.

This library is originally written by [Markus Weissmann](http://www.mweissmann.de/)
