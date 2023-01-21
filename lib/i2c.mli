type t
type 'a result = ('a, [ `EUnix of Unix.error ]) Result.t

val open_device : string -> int -> t result

open Stdint

val read_byte : t -> uint8 result
val write_byte : t -> uint8 -> unit result
val write_quick : t -> uint8 -> unit result
val read_byte_data : t -> uint8 -> uint8 result
val write_byte_data : t -> uint8 -> uint8 -> unit result
val read_word_data : t -> uint8 -> uint16 result
val write_word_data : t -> uint8 -> uint16 -> unit result
val process_call : t -> uint8 -> uint16 -> uint16 result
