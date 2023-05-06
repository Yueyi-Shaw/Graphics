SOURCE_PATH := ./src
OUT_PATH := ./out
MODEL_PATH := ./model
TEXTURE_PATH := ./texture

target=hello.frag
model=Fox
texture=
run:
ifeq ($(texture),)
	# texture is empty
	glslViewer $(SOURCE_PATH)/$(target) $(MODEL_PATH)/$(model).glb
else
	# texture is not empty
	glslViewer $(SOURCE_PATH)/$(target) $(MODEL_PATH)/$(model).glb $(TEXTURE_PATH)/$(texture)
endif

savefile=screenshot
screenshot:
	glslViewer $(SOURCE_PATH)/$(target) $(MODEL_PATH)/$(model).glb  -E screenshot,$(OUT_PATH)/$(savefile).png

cm=update
push:
	git add --all
	git commit -m "$(cm)"
	git push


.PHONY: clean
clean:
	rm ./out
