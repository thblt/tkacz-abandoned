pandoc *.tex.md --template template.tex -o document.tex --to latex

pdflatex document
if pdflatex -interaction=nonstopmode document
	rm document.aux document.log document.out document.toc document.tex
fi