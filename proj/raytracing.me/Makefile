SOURCE_PATH := ./src
OUT_DIR := ./out
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cc)

build:
	if [ -d $(OUT_DIR) ]; then \
		echo "Check  $(OUT_DIR) exists" ;\
	else \
		echo " $(OUT_DIR) not exists, mkdir" ;\
		mkdir $(OUT_DIR);\
	fi
	gcc $(SOURCE_FILES) -o ./out/main -std=c++11 -lstdc++;


asmfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cc),gcc -S $(var) -o ./out/$(notdir $(var:%.cc=%.asm));)
assembly:
	$(asmfunc)

.PHONY: clean
clean:
	rm ./out
