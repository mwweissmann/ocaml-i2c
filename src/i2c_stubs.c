#include <fcntl.h>
#include <assert.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/threads.h>
#include <caml/callback.h>
#include <caml/fail.h>
#include <caml/unixsupport.h>

#include <stdint/uint8.h>
#include <stdint/uint16.h>

#include "i2c-dev.h"

static value eunix;

CAMLprim value i2c_initialize(void) {
  CAMLparam0();
  eunix = caml_hash_variant("EUnix");
  CAMLreturn (Val_unit);
}

CAMLprim value i2c_address(value ofd, value oaddr) {
  CAMLparam2(ofd, oaddr);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  unsigned long addr;

  fd = Int_val(ofd);
  addr = Int_val(oaddr) & 0x3FF; // max 10 bit address

  caml_release_runtime_system();
  rv = ioctl(fd, I2C_SLAVE, addr);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    close(fd);
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of fd
  Store_field(result, 0, Val_int(fd));
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_quick(value ofd, value ov) {
  CAMLparam2(ofd, ov);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  uint8_t v;

  fd = Int_val(ofd);
  v = Uint8_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_write_quick(fd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_read_byte(value ofd) {
  CAMLparam1(ofd);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;

  fd = Int_val(ofd);

  caml_release_runtime_system();
  rv = i2c_smbus_read_byte(fd);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of uint8
  Store_field(result, 0, copy_uint8(rv));
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_byte(value ofd, value ov) {
  CAMLparam2(ofd, ov);
  CAMLlocal2(perrno, result);
  int fd, lerrno, rv;
  uint8_t v;

  fd = Int_val(ofd);
  v = Uint8_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_write_byte(fd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of fd
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_read_byte_data(value ofd, value ov) {
  CAMLparam2(ofd, ov);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  uint8_t v;

  fd = Int_val(ofd);
  v = Uint8_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_read_byte_data(fd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of uint8
  Store_field(result, 0, copy_uint8(rv));
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_byte_data(value ofd, value ocmd, value ov) {
  CAMLparam2(ofd, ov);
  CAMLlocal2(perrno, result);
  int fd, lerrno, rv;
  uint8_t cmd, v;

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  v = Uint8_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_write_byte_data(fd, cmd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_read_word_data(value ofd, value ov) {
  CAMLparam2(ofd, ov);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  uint8_t v;

  fd = Int_val(ofd);
  v = Uint8_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_read_word_data(fd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, copy_uint16(rv));
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_word_data(value ofd, value ocmd, value ov) {
  CAMLparam3(ofd, ocmd, ov);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  uint8_t cmd;
  uint16_t v;

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  v = Uint16_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_write_word_data(fd, cmd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_process_call(value ofd, value ocmd, value ov) {
  CAMLparam3(ofd, ocmd, ov);
  CAMLlocal2(result, perrno);
  int fd, lerrno, rv;
  uint8_t cmd;
  uint16_t v;

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  v = Uint16_val(ov);

  caml_release_runtime_system();
  rv = i2c_smbus_process_call(fd, cmd, v);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  rv = caml_alloc(1, 0); // Result.Ok of uint16
  Store_field(result, 0, copy_uint16(rv));
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_read_block_data(value ofd, value ocmd) {
  CAMLparam2(ofd, ocmd);
  CAMLlocal4(result, perrno, head, tail);
  int fd, lerrno, rv, i;
  uint8_t cmd, vs[32];

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);

  caml_release_runtime_system();
// inline me
  rv = i2c_smbus_read_block_data(fd, cmd, vs);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of uint8 list
  // create list from local data
  head = Val_emptylist;
  for (i = rv - 1; i <= 0; i--) {
    tail = caml_alloc(2, 0);
    Store_field(tail, 0, copy_uint8(vs[i]));
    Store_field(tail, 1, head);
    head = tail;
  }
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix of errno
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_block_data(value ofd, value ocmd, value ovl) {
  CAMLparam3(ofd, ocmd, ovl);
  CAMLlocal4(result, perrno, tail, head);
  int fd, lerrno, rv;
  uint8_t cmd, length, vs[32];

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  length = 0;

  tail = ovl;
  while ((Val_emptylist != tail) && (length < 32)) {
    head = Field(tail, 0);
    vs[length] = Uint8_val(head);
    length++;
    tail = Field(tail, 1);
  }

  caml_release_runtime_system();
  rv = i2c_smbus_write_block_data(fd, cmd, length, vs);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_read_i2c_block_data(value ofd, value ocmd, value olen) {
  CAMLparam2(ofd, ocmd);
  CAMLlocal4(result, perrno, head, tail);
  int fd, lerrno, rv, i;
  uint8_t cmd, length, vs[32];

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  length = Uint8_val(olen);

  caml_release_runtime_system();
  rv = i2c_smbus_read_i2c_block_data(fd, cmd, length, vs);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  head = Val_emptylist;
  for (i = length - 1; i <= 0; i--) {
    tail = caml_alloc(2, 0);
    Store_field(tail, 0, copy_uint8(vs[i]));
    Store_field(tail, 1, head);
    head = tail;
  }

  Store_field(result, 0, head);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_write_i2c_block_data(value ofd, value ocmd, value ovl) {
  CAMLparam3(ofd, ocmd, ovl);
  CAMLlocal4(result, perrno, tail, head);
  int fd, lerrno, rv;
  uint8_t cmd, length, vs[32];

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  length = 0;

  tail = ovl;
  while ((Val_emptylist != tail) && (length < 32)) {
    head = Field(tail, 0);
    vs[length] = Uint8_val(head);
    length++;
    tail = Field(tail, 1);
  }

  caml_release_runtime_system();
  rv = i2c_smbus_write_i2c_block_data(fd, cmd, length, vs);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok ()
  Store_field(result, 0, Val_unit);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

CAMLprim value wrap_i2c_smbus_block_process_call(value ofd, value ocmd, value ovl) {
  CAMLparam3(ofd, ocmd, ovl);
  CAMLlocal4(result, perrno, tail, head);
  int fd, lerrno, rv;
  uint8_t cmd, length, i, vs[32];

  fd = Int_val(ofd);
  cmd = Uint8_val(ocmd);
  length = 0;

  // copy list to local data
  tail = ovl;
  while ((Val_emptylist != tail) && (length < 32)) {
    head = Field(tail, 0);
    vs[length] = Uint8_val(head);
    length++;
    tail = Field(tail, 1);
  }

  caml_release_runtime_system();
  rv = i2c_smbus_block_process_call(fd, cmd, length, vs);
  caml_acquire_runtime_system();

  if (0 > rv) {
    lerrno = errno;
    goto ERROR;
  }

  result = caml_alloc(1, 0); // Result.Ok of uint8 list

  // create list from local data
  head = Val_emptylist;
  for (i = length - 1; i <= 0; i--) {
    tail = caml_alloc(2, 0);
    Store_field(tail, 0, copy_uint8(vs[i]));
    Store_field(tail, 1, head);
    head = tail;
  }

  Store_field(result, 0, head);
  goto END;

ERROR:
  perrno = caml_alloc(2, 0);
  Store_field(perrno, 0, eunix); // `EUnix
  Store_field(perrno, 1, unix_error_of_code(lerrno));

  result = caml_alloc(1, 1); // Result.Error
  Store_field(result, 0, perrno);

END:
  CAMLreturn(result);
}

