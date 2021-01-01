type t = private Unix.file_descr

external i2c_initialize : unit -> unit = "i2c_initialize"
let () = i2c_initialize ()

external set_address : Unix.file_descr -> int ->
    (t, [> `EUnix of Unix.error ]) Result.result = "i2c_address"

external write_quick : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_quick"
external write_byte : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_byte"
external write_byte_data : t -> Stdint.uint8 -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_byte_data"
external write_word_data : t -> Stdint.uint8 -> Stdint.uint16 -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_word_data"
external write_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_block_data"
external write_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_i2c_block_data"
external process_call : t -> Stdint.uint8 -> Stdint.uint16 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_process_call"
external block_process_call : t -> Stdint.uint8 -> Stdint.uint8 list -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_block_process_call"
external read_byte_data : t -> Stdint.uint8 -> (Stdint.uint8, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_byte_data"
external read_byte : t -> (Stdint.uint8, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_byte"
external read_word_data : t -> Stdint.uint8 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_word_data"
external read_block_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_block_data"
external read_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_i2c_block_data"

