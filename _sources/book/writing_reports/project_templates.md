# Project templates

## Template for projects 1 and 2: problem sets

We have prepared a template for you to use in the two first projects. Below you find both the `.tex` file and the corresponding generated `.pdf` file.

- The [tex file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/oppgave_mal.tex)
- The [pdf file](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/oppgave_mal.pdf)

The above `.tex` example tries to include a figure file `rel_err.pdf` from a subdirectory `imgs`. If you want to compile this example yourself, you can get the figure file [here](https://github.com/anderkve/FYS3150/blob/master/book/writing_reports/tex_mal/imgs/rel_err.pdf).


## Template for projects 3, 4 and 5: scientific reports

Below is the template you should use when writing the scientific reports for projects 3, 4 and 5. We recommend taking the time to read through all the text in the template, as it contains a lot of useful information on how to structure a scientific report, as well as some LaTeX tips and tricks.

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
