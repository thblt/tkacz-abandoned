cat header.tex > document.tex
pandoc *.tex.md --from markdown --to latex >> document.tex
cat footer.tex >> document.tex

pdflatex document
pdflatex -interaction=nonstopmode document