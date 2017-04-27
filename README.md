# LLSIF-JsonBinary-CC

After unpacking the `AppAssets.zip` within the LoveLive! School Idol Festival package, even [decoding](https://github.com/MikuAuahDark/HonokaMiku) them cannot make some of the `.json` files directly readable by normal text editors or normal programs, this is because [KLab](https://github.com/KLab) uses a [proprietary binary format](https://github.com/KLab/PlaygroundOSS/blob/master/Doc/Documentation_Libraries.md) to encode json.

The purpose of this project, is to restore the binary JSON to its orignal text format.

## How to Use?

The program now take the name of the binary (or normal) JSON file as its only argument, and split normal JSON text to console's standard output. If the input file is a normal JSON file, this program will just beautify it.

Example:

```bash
$ jbcc-dump example.json
```

## How to Compile?

I wrote and compile this program using Microsoft Visual Studio 2015. Since this program taking advantage of no more than some STL facilities, it should compile and run with no problem on any other platform.

## KLab's YAJL

The difference between KLab's YAJL and the original one is that, it

>  Added code to check the first bytes of the stream to decode and decide to switch to other parser that perform the same callback to user code as YAJL, as an end result, we can send different stream formats but the user parser implementing the callbacks from YAJL will stay the same.

as stated in [this](https://github.com/KLab/PlaygroundOSS/blob/master/Doc/Documentation_Libraries.md#note1) document.

## Acknowledgements

This program make use of the KLab [modified](https://github.com/KLab/PlaygroundOSS) version of [YAJL](https://github.com/lloyd/yajl) (Yet Another JSON Library). I personally refer to KLab's original code and the YAJL's original reformat program [example](https://lloyd.github.io/yajl/) to understand how the YAJL library works.