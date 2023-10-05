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


## Templates

### Template for projects 1 and 2: problem sets

We've prepared a template for you to use in the two first projects. We have both the source code found in a `.tex` and a rendered file in `.pdf` format.

- The [tex file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/oppgave_mal.tex)
- The [pdf file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/oppgave_mal.pdf)

The above `.tex` example tries to include a figure file `rel_err.pdf` from a subdirectory `imgs`. If you want to compile this example yourself, you can get the figure file [here](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/imgs/rel_err.pdf).


### Template for projects 3, 4 and 5: scientific reports

Here's a template you can use when writing the scientific reports for projects 3, 4 and 5. We recommend taking the time to read through all the text in the template, as it contains a lot of useful information on how to structure a scientific report, as well as some LaTeX tips and tricks.

- The [tex file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/report_example.tex)
- The [pdf file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/report_example.pdf)
- The [BibTex references file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/ref.bib)

To easily view the template "in action", you can access it as a read-only Overleaf project [here](https://www.overleaf.com/read/ykjsqvchkhyz).

If you want to compile the template report yourself, you'll need a figure file `rel_err.pdf` in a subdirectory `imgs`. (Just like for the template for projects 1 and 2.) You can get the figure file [here](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/imgs/rel_err.pdf).

To build the template along with the reference list, you need to run `pdflatex` and `bibtex` a few times over. Here's a single-line command that should do the trick:

```sh
pdflatex report_example.tex && bibtex report_example.aux && pdflatex report_example.tex && pdflatex report_example.tex
```


### Example report

An example of a very good student report from a few years back can be found [here](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/example_report.pdf).



## LaTeX resources

Here are some LaTeX resources that might come in handy:

- Overleaf's [beginner's guide](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes) to LaTeX
- Overleaf's [documentation pages](https://www.overleaf.com/learn) have info on all aspects of LaTeX that you will need for this course
- Don't know the TeX command for a mathematical symbol? Try drawing the symbol in [Detexify](https://detexify.kirelabs.org/classify.html)...
- ...or look for it in [this](https://ctan.uib.no/info/symbols/comprehensive/symbols-a4.pdf) document of 18150 symbols and corresponding LaTeX commands

