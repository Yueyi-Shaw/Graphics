SOURCE_PATH := ./src
OUT_DIR := ./out
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cu)
LIB := -lGL -lglut -lGLEW
# HEADER_FILES := $(wildcard $(SOURCE_PATH)/*.h)

buildfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cu),nvcc $(var) -o $(OUT_DIR)/$(notdir $(var:%.cu=%.out)) $(LIB);)
All:
	if [ -d $(OUT_DIR) ]; then \
		echo "Check  $(OUT_DIR) exists" ;\
	else \
		echo " $(OUT_DIR) not exists, mkdir" ;\
		mkdir $(OUT_DIR);\
	fi
	$(buildfunc)

cm=update
push:
	git add --all
	git commit -m "$(cm)"
	git push


proj=
run:
	$(OUT_DIR)/$(proj).out > $(OUT_DIR)/$(proj).result

build:
	nvcc $(SOURCE_PATH)/$(proj).cu -o $(OUT_DIR)/$(notdir $(proj:%.cu=%.out)) $(LIB)


.PHONY: clean
clean:
	rm ./out
