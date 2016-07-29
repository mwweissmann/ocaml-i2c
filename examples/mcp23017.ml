let gpioa_conf = Stdint.Uint8.of_int 0
let gpiob_conf = Stdint.Uint8.of_int 1

let gpioa_addr = Stdint.Uint8.of_int 0x12
let gpiob_addr = Stdint.Uint8.of_int 0x13

let get_ok = function
  | Result.Ok x -> x
  | _ -> failwith "oops"

let _ =
  let () = print_endline "configure as output" in
  let i2c =
    let fd = Unix.(openfile "/dev/i2c-1" [O_RDWR] 0o644) in
    get_ok (I2c.set_address fd 0x20)
  in

  (* configure bank A and B as output *)
  let () = get_ok (I2c.write_word_data i2c gpioa_conf (Stdint.Uint16.of_int 0x0000)) in
  let () = get_ok (I2c.write_word_data i2c gpiob_conf (Stdint.Uint16.of_int 0x0000)) in

  (* write to bank A and B *)
  let rec loop () =
    let () = print_endline "setting bank A to all 1, all B to all 0" in
    let () = get_ok (I2c.write_word_data i2c gpioa_addr (Stdint.Uint16.of_int 0xFFFF)) in
    let () = get_ok (I2c.write_word_data i2c gpiob_addr (Stdint.Uint16.of_int 0x0000)) in
    let () = Unix.sleep 1 in
    let () = print_endline "setting bank A to all 0, all B to all 1" in
    let () = get_ok (I2c.write_word_data i2c gpioa_addr (Stdint.Uint16.of_int 0x0000)) in
    let () = get_ok (I2c.write_word_data i2c gpiob_addr (Stdint.Uint16.of_int 0xFFFF)) in
    let () = Unix.sleep 1 in
    loop ()
  in
  loop ()

