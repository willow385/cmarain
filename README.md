## CMarain

![Screenshot of the test program](./example.png)

To render the Marain string "orhO orayu kabo wugE marAnva." do the following:
```sh
make
./render-string-test.x86 "orhO orayu kabo wugE marAnva."
```

Don't use the standard romanization, use the font mapping (e.g. use "LAyu" not "llayyuh").

This repository also comes with a set of CLI tools for converting between Marain encoding
and ASCII. To make these tools, do `make converters`, which will produce two binaries named
`ascii2marain` and `marain2ascii`. If you run `ascii2marain` on `ascii_example.txt`, you should
get a binary file whose contents are equivalent to `marain_example.mar`; likewise, running
`marain2ascii` on `marain_example.mar` should produce a file equivalent to `ascii_example.txt`.
