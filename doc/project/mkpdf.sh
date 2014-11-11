pandoc *.tex.md --chapters --template template.tex -o document.tex --to latex

pdflatex document
if pdflatex -interaction=nonstopmode document
	then
	rm document.aux document.log document.out document.toc document.tex
fi
