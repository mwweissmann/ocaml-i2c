(lang dune 3.4)
(using ctypes 0.2)

(generate_opam_files true)

(name i2c-unix)
(version 0.2.0)
(source (github Firobe/ocaml-i2c))
(license MIT)
(authors "Markus W. Weissmann <markus.weissmann@in.tum.de>" "Virgile Robles")
(maintainers "Markus W. Weissmann <markus.weissmann@in.tum.de>" "virgile.robles@pm.me")

(package
  (name i2c-unix)
  (synopsis "Bindings to i2c-dev, the Linux i2c bus interface")
  (description "Bindings to i2c-dev, the Linux i2c bus interface")
  (depends base-unix stdint))
