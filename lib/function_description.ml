module Types = Types_generated

module Functions (F : Ctypes.FOREIGN) = struct
  open Ctypes
  open F
  open Types

  let set_address = foreign "set_address" (t @-> int @-> returning void32)

  let write_quick =
    foreign "i2c_smbus_write_quick" (t @-> uint8_in @-> returning void32)

  let read_byte = foreign "i2c_smbus_read_byte" (t @-> returning uint8_out)

  let write_byte =
    foreign "i2c_smbus_write_byte" (t @-> uint8_in @-> returning void32)

  let read_byte_data =
    foreign "i2c_smbus_read_byte_data" (t @-> uint8_in @-> returning uint8_out)

  let write_byte_data =
    foreign "i2c_smbus_write_byte_data"
      (t @-> uint8_in @-> uint8_in @-> returning void32)

  let read_word_data =
    foreign "i2c_smbus_read_word_data" (t @-> uint8_in @-> returning uint16_out)

  let write_word_data =
    foreign "i2c_smbus_write_word_data"
      (t @-> uint8_in @-> uint16_in @-> returning void32)

  let process_call =
    foreign "i2c_smbus_process_call"
      (t @-> uint8_in @-> uint16_in @-> returning uint16_out)

  (*
external read_block_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_block_data"
external write_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_block_data"

external read_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_i2c_block_data"
external write_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_i2c_block_data"

external block_process_call : t -> Stdint.uint8 -> Stdint.uint8 list -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_block_process_call"
     *)
end
