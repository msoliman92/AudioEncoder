# AudioEncoder
C++ application to convert wav audio files to mp3 using LAME lib
Audio Converter from wav to mp3 using lame open source library.
Lame is statically compiled in exe file.
For windows it can be run under cygwin and lame installation.
For unix it's normally working.
For windows it's tested under win 10 64 bit.
For Unix it's tested under ubuntu 20.04 LTS.

For compilation open cmd in makefile path and type "make" for compilation and "make clean" to clean binaries

Binaries will be in ./bin/
win bin is AudioEncoder_WIN64.exe 
unix bin is AudioEncoder_UNIX

Object files are generated also to validate that lame is statically compiled.

To run the program
in ./bin/ path open the cmd
for windows: AudioEncoder_WIN64.exe ///path to wav folder////
for unix: ./AudioEncoder_UNIX /mnt////path to wave folder/////
