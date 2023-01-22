(*
type t = private Unix.file_descr

external i2c_initialize : unit -> unit = "i2c_initialize"
let () = i2c_initialize ()

external set_address : Unix.file_descr -> int ->
    (t, [> `EUnix of Unix.error ]) Result.result = "i2c_address"

external write_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_block_data"
external write_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 list -> (unit, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_write_i2c_block_data"
external read_block_data : t -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_block_data"
external read_i2c_block_data : t -> Stdint.uint8 -> Stdint.uint8 -> Stdint.uint8 -> (Stdint.uint8 list, [> `EUnix of Unix.error ]) Result.result = "wrap_i2c_smbus_read_i2c_block_data"
*)

type t = Unix.file_descr
type 'a result = ('a, [ `EUnix of Unix.error ]) Result.t

let wrap_error (x, errno) : 'a result =
  let errno = Signed.SInt.to_int errno in
  if errno = 0 then Result.ok x else Result.error (`EUnix (Obj.magic errno))

let wr1 f x = wrap_error (f x)
let wr2 f x y = wrap_error (f x y)
let wr3 f x y z = wrap_error (f x y z)

open Stdint
open Ctypes
module F = C.Function

let write_quick = wr2 F.write_quick
let read_byte = wr1 F.read_byte
let write_byte = wr2 F.write_byte
let read_byte_data = wr2 F.read_byte_data
let write_byte_data = wr3 F.write_byte_data
let read_word_data = wr2 F.read_word_data
let write_word_data = wr3 F.write_word_data
let process_call = wr3 F.process_call
let set_address = wr2 F.set_address

let open_device name address =
  let name = "/dev/" ^ name in
  let fd = Unix.(openfile name [ O_RDWR ] 0o644) in
  Result.map (fun () -> fd) (set_address fd address)

let close_device t = Unix.close t
