SOURCE_PATH := ./src
OUT_DIR := ./out
#SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cu)
# HEADER_FILES := $(wildcard $(SOURCE_PATH)/*.h)

#buildfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cu),nvcc $(var) -o ./out/$(notdir $(var:%.cu=%.out)) $(LIB);)
# build:
# 	if [ -d $(OUT_DIR) ]; then \
# 		echo "Check  $(OUT_DIR) exists" ;\
# 	else \
# 		echo " $(OUT_DIR) not exists, mkdir" ;\
# 		mkdir $(OUT_DIR);\
# 	fi
# 	$(buildfunc)

cm=update
push:
	git add --all
	git commit -m "$(cm)"
	git push


proj=
run:
	$(OUT_DIR)/$(proj).out


.PHONY: clean
clean:
	rm ./out
