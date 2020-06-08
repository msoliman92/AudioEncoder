all:
ifeq ($(OS),Windows_NT)
			g++ -v -static AudioEncoder.cpp MultiThreadHandler.cpp -o bin/AudioEncoder_WIN64  -L./lame_static/win64 -lpthread -lmp3lame  --verbose
			objdump -D bin/AudioEncoder_WIN64 > obj/AudioEncoder_WIN64
else
			g++ -v AudioEncoder.cpp MultiThreadHandler.cpp -lpthread -L./lame_static/unix/ -Wl,-Bstatic -lmp3lame -Wl,-Bdynamic  -o bin/AudioEncoder_UNIX
			objdump -D bin/AudioEncoder_UNIX > obj/AudioEncoder_UNIX
endif
clean:
	rm -rf ./obj/* ./bin/*.exe ./bin/*_UNIX