SOURCE_PATH := ./src
OUT_DIR := ./out
SOURCE_FILES := $(wildcard $(SOURCE_PATH)/*.cu)
# HEADER_FILES := $(wildcard $(SOURCE_PATH)/*.h)

buildfunc := $(foreach var,$(wildcard $(SOURCE_PATH)/*.cu),nvcc $(var) -o ./out/$(notdir $(var:%.cu=%.out));)
build:
	if [ -d $(OUT_DIR) ]; then \
		echo "Check  $(OUT_DIR) exists" ;\
	else \
		echo " $(OUT_DIR) not exists, mkdir" ;\
		mkdir $(OUT_DIR);\
	fi
	$(buildfunc)

cm=update
git-push:
	git add --all
	git commit -m "$(cm)"
	git push

.PHONY: clean
clean:
	rm ./out
