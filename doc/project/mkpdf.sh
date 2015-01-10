pandoc *.tex.md --chapters --template template.tex -o document.out.tex --to latex

pdflatex document.out
if pdflatex -interaction=nonstopmode document.out
	then
	rm document.out.aux document.out.log document.out.out document.out.toc document.out.tex
fi
