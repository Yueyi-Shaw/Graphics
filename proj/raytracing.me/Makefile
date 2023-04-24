SOURCE_PATH := ./src
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cc)
build:
	echo $(SOURCE_FILES);
	gcc $(SOURCE_FILES) -o ./out/main -std=c++11 -lstdc++;

asmfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cc),gcc -S $(var) -o ./out/$(notdir $(var:%.cc=%.asm));)
assembly:
	$(asmfunc)

.PHONY: clean
clean:
	rm ./out
