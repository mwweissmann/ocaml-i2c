module Types (F : Ctypes.TYPE) = struct
  open F

  let type_out (type t) (module I : Stdint.Int with type t = t) =
    view ~read:I.of_int32 ~write:I.to_int32 int32_t

  let type_in (type t1 t2) (module I1 : Unsigned.S with type t = t1)
      (module I2 : Stdint.Int with type t = t2) t =
    view t
      ~read:(fun x -> I1.to_int x |> I2.of_int)
      ~write:(fun x -> I2.to_int x |> I1.of_int)

  let not_implemented _ = assert false
  let ignore_t t = view ~read:ignore ~write:not_implemented t
  let void32 = ignore_t int32_t
  let t : Unix.file_descr typ = view ~read:Obj.magic ~write:Obj.magic int

  open Stdint

  let uint8_out = type_out (module Uint8)
  let uint16_out = type_out (module Uint16)
  let uint8_in = type_in (module Unsigned.UInt8) (module Uint8) uint8_t
  let uint16_in = type_in (module Unsigned.UInt16) (module Uint16) uint16_t
end
