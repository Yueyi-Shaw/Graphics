SOURCE_PATH := ./src
OUT_DIR := ./out
IMG_DIR :=./img
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cc)
HEADER_FILES := $(wildcard $(SOURCE_PATH)/*.h)
# Overrides command line arguments
# override lesson = 0, on wsl we don't need override keyword
lesson = 0

run:
	if [ -d $(IMG_DIR) ]; then \
		echo "Check  $(IMG_DIR) exists" ;\
	else \
		echo " $(IMG_DIR) not exists, mkdir" ;\
		mkdir $(IMG_DIR);\
	fi
ifeq ($(lesson),0)
	echo param lesson is illegal : $(lesson)
else
	$(OUT_DIR)/main $(lesson) > $(IMG_DIR)/$(lesson).ppm
endif

build:
	if [ -d $(OUT_DIR) ]; then \
		echo "Check  $(OUT_DIR) exists" ;\
	else \
		echo " $(OUT_DIR) not exists, mkdir" ;\
		mkdir $(OUT_DIR);\
	fi
	gcc $(SOURCE_FILES) -o ./out/main -std=c++11 -lstdc++;


asmfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cc),gcc -S $(var) -o ./out/$(notdir $(var:%.cc=%.s));)
assembly:
	$(asmfunc)

dasm:
	objdump -d -M intel -s -j .text $(OUT_DIR)/main > $(OUT_DIR)/main.asm

git-push:
	git add --all
	git commit -m "update"
	git push

.PHONY: clean
clean:
	rm ./out
