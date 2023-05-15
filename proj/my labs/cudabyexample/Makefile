SOURCE_PATH := ./src
OUT_DIR := ./out
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cu)

OSFLAG :=
ifeq ($(OS),Windows_NT)
	OSFLAG += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		OSFLAG += -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		OSFLAG += -D IA32
	endif
	LIB = -Llib ./lib/glut64.lib
# set your own cl.exe path here
# company pc
	CC =  -ccbin "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\Hostx64\x64"
# home pc
#	CC =  -ccbin "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\bin\Hostx64\x64"
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG += -D LINUX
		LIB = -lglut
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG += -D OSX
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		OSFLAG += -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	OSFLAG += -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		OSFLAG += -D ARM
	endif
endif

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
ifneq (,$(wildcard $(proj).result))
	rm $(OUT_DIR)/$(proj).result
endif

	$(OUT_DIR)/$(proj).out > $(OUT_DIR)/$(proj).result

build:
	if [ -d $(OUT_DIR) ]; then \
		echo "Check  $(OUT_DIR) exists" ;\
	else \
		echo " $(OUT_DIR) not exists, mkdir" ;\
		mkdir $(OUT_DIR);\
	fi
	nvcc $(SOURCE_PATH)/$(proj).cu -o $(OUT_DIR)/$(notdir $(proj)).out $(LIB) $(CC)
	rm $(OUT_DIR)/*.exp
	rm $(OUT_DIR)/*.lib

.PHONY: clean
clean:
	rm ./out
