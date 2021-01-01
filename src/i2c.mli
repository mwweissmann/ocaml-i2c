type t = private Unix.file_descr

val set_address : Unix.file_descr -> int -> (t, [> `EUnix of Unix.error ]) Result.result
val write_quick : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_byte : t -> (Stdint.uint8, [> `EUnix of Unix.error ]) Result.result
val write_byte : t -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_byte_data : t -> Stdint.uint8 -> (Stdint.uint8, [> `EUnix of Unix.error ]) Result.result
val write_byte_data : t -> Stdint.uint8 -> Stdint.uint8 -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_word_data : t -> Stdint.uint8 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result
val write_word_data : t -> Stdint.uint8 -> Stdint.uint16 -> (unit, [> `EUnix of Unix.error ]) Result.result
val process_call : t -> Stdint.uint8 -> Stdint.uint16 -> (Stdint.uint16, [> `EUnix of Unix.error ]) Result.result
val read_block_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result
val read_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result
val write_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result
val block_process_call : t -> Stdint.uint8 -> Stdint.uint8 list -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result

