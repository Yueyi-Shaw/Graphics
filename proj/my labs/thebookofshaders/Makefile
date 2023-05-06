SOURCE_PATH := ./src
OUT_PATH := ./out

target=hello.frag
run:
	glslViewer $(SOURCE_PATH)/$(target)


cm=update
push:
	git add --all
	git commit -m "$(cm)"
	git push


.PHONY: clean
clean:
	rm ./out
