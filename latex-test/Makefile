main.pdf: main.tex *.tex *.bib images/*
	pdflatex main
	bibtex main
	pdflatex main
	pdflatex main

clean:
	rm main.aux main.bbl main.blg main.lof main.log main.lot main.out main.toc
