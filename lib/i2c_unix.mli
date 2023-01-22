(** Library for interacting with I2C devices from the user space *)

type t
(** Type of an opened I2C device. *)

type 'a result = ('a, [ `EUnix of Unix.error ]) Result.t
(** Most API calls can return an Unix error from the underlying
    kernel module. *)

(** {2 Opening and closing} *)

val open_device : string -> int -> t result
(** [open_device name addr] will open the i2c bus [name] at address [addr].
    [name] should be the identifier returned by [i2cdetect -l], for example
    ["i2c-0"] (and {b not} ["/dev/i2c-0"]). *)

val close_device : t -> unit
(** Close a previously opened I2C device. Calling this on an already closed
    device will raise an exception. *)

open Stdint

(** {2 SMBus functions} *)

(** The following functions are simply bindings to C functions provided by the
    SMBus protocol. Refer to their
    {{: https://docs.kernel.org/i2c/smbus-protocol.html}original documentation}.
*)

val read_byte : t -> uint8 result
val write_byte : t -> uint8 -> unit result
val write_quick : t -> uint8 -> unit result
val read_byte_data : t -> uint8 -> uint8 result
val write_byte_data : t -> uint8 -> uint8 -> unit result
val read_word_data : t -> uint8 -> uint16 result
val write_word_data : t -> uint8 -> uint16 -> unit result
val process_call : t -> uint8 -> uint16 -> uint16 result
