run:
	cd ./app && docker compose up -d

stop:
	cd ./app && docker compose down

cm=update
push:
	git add --all
	git commit -m "$(cm)"
	git push
