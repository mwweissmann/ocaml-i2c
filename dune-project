(lang dune 3.0)

(generate_opam_files true)

(name i2c)
(version 0.1.3)
(source (github Firobe/ocaml-i2c))
(license MIT)
(authors "Markus W. Weissmann <markus.weissmann@in.tum.de>" "Virgile Robles")
(maintainers "Markus W. Weissmann <markus.weissmann@in.tum.de>" "virgile.robles@pm.me")

(package
  (name i2c)
  (synopsis "Bindings to i2c-dev, the Linux i2c bus interface")
  (description "Bindings to i2c-dev, the Linux i2c bus interface")
  (depends base-unix result stdint))
