pandoc *.tex.md --template template.tex -o document.tex --to latex

pdflatex document
pdflatex -interaction=nonstopmode document