# Introduction to LaTeX


## What is LaTeX

Taken from the [LaTeX-projects website](https://www.latex-project.org/),

*LaTeX is a high-quality typesetting system; it includes features designed for the production of technical and scientific documentation. LaTeX is the de facto standard for the communication and publication of scientific documents.*

## How to use it?

A LaTeX document is compiled from a `.tex` file with the text and LaTeX code for your document. Typically, the compiler renders a `.pdf` file from the LaTeX code and creates a document with a specific format. To compile a `.tex` file directly from the terminal, you can use `pdflatex`:

```sh
pdflatex your_latex_file.tex
```

You often need to run this command twice for all changes to be displayed correctly.

Since this course typically involves collaborating with others on a single document, a simple solution is to use [Overleaf](https://www.overleaf.com/project) for the writing and compilation process. 

```{note}
  Many people can work simultaneously on the same Overleaf document, even when using the free version of Overleaf, as mentioned [here](https://www.overleaf.com/learn/how-to/Is_Overleaf_free_to_use%3F). Just use the **link sharing** option when you share the document with your collaborators. 
```

However, you can of course also just use your git repository to collaborate on a `.tex` file, like you would for any code file. Use whatever solution works best for you and your collaborators.


## LaTeX resources

Here are some LaTeX resources that might come in handy:

- Overleaf's [beginner's guide](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes) to LaTeX
- Overleaf's [documentation pages](https://www.overleaf.com/learn) have info on all aspects of LaTeX that you will need for this course
- Don't know the TeX command for a mathematical symbol? Try drawing the symbol in [Detexify](https://detexify.kirelabs.org/classify.html)...
- ...or look for it in [this](https://ctan.uib.no/info/symbols/comprehensive/symbols-a4.pdf) document of 18150 symbols and corresponding LaTeX commands

