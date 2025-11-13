# Checklist for reports

Writing a good scientific report is difficult and requires attention to a lot of details. On this page, we will collect some of the things that are useful to check before handing in a report. Note that this list is not meant to be exhaustive --- it's just a convenient reminder for some of the more common problems.


- **Try to be specific:** When you can make a statement specific, it's usually a good thing to do so. For instance, if you are describing a harmonic motion, it is more specific to use the precise term "harmonic" than to use a more general term like "periodic". Or if you are comparing two methods, it is better to try to give some quantitative statements about their relative performance ("the error in method A is a factor ~5 smaller compared to the error in method B") rather than just using general descriptions like "method A performs much better than method B").

- **Try to be concise:** This can help shorten your sentences and make the report more readable. For example, say you have used two algorithms A and B to solve problem X. Consider the following sentence: "We have made use of algorithms for solving problem X, such as A and B." A more concise version would be to simply write "To solve problem X we have used algorithms A and B." 

- **Units:** Check that all the numbers and plot axes that should have units actually have units. 

- **Axis ranges:** Make sure all plots have reasonable axis ranges. (If your code deals with numbers that are not incredibly small or large, but you end up with plot axes with a scale of e.g. $10^{20}$ or $10^{-20}$, then this is often a sign that something has gone wrong in your code.) A useful rule is to *always* set the axis ranges "manually" (e.g. with `plt.xlim(...)` and `plt.ylim(...)`) for all plots you produce, since this forces you to pay attention to the axis ranges.

- **Text in figures:** Keep an eye on the font size for the text appearing in figures (axis labels, legends, etc.) compared to the other text in the document. Text in figures should generally be of similar size to the main text in the document. (It's not at all important to be exact here, just avoid huge differences.)

- **Grammar:** Read through your report to remove as many grammatical mistakes as you can. Some common mistakes to look out for are:

  - Wrong/missing capitalization (*Wrong:* "penning trap", "Penning Trap". *Correct:* "Penning trap".)

  - Singular versus plural forms (e.g. when to use "is" and when to use "are")

  - The use of "a" versus "an"

  - Switching between "we" and "I"

  - Incomplete sentences (*Wrong:* "Derivation in Appendix A." *Correct:* "The derivation is given in Appendix A".)


- **Avoid empty lines after equations:** Avoid empty lines after equations in your .tex file, unless you actually want to start a new paragraph in your text. (LaTeX will indent the text following an empty line.) If you just want some "air" surrounding the equations in your .tex file, use empty comment lines.

- **Equations are part of sentences:** Grammatically, equations should be regarded as part of the sentence they appear in. This means that equations typically should be followed by a comma or a period, depending on whether you are continuing the sentence after the equation or starting a new one. (For examples, see the project report template.)


- **Quotation marks:** To get correct quotation marks, you should use LaTeX code like this

  ```
  Writing a report is ``fun''.
  ```

  not like this

  ```
  Writing a report is "fun".
  ```

- **Consistent mathematical notation:** Make sure the mathematical notation is consistent. For instance, check that all vector quantities are typeset like `\mathbf{x}` or `\vec{x}`.

- **Explain all mathematical symbols:** The first time a new symbol appears in an equation, the surrounding text should specify what it means.

- **Use of italics for math:** 

  - When referring to mathematical symbols, function names, etc. in the text, use inline math mode, e.g. `the function $f(x)$` or `the result $x = 10$.`

  - One exception is units -- they are typically not written in italics. Example: `$f = 10\,\text{Hz}$`.

- **Text in math mode:** Regular words that appear in mathematical expressions (i.e. in math mode in LaTeX) should be typeset with `\text{}`. *Correct:* `y_{\text{analytical}}`. *Wrong:* `y_{analytical}`

- **Explicitly refer to all figures/tables:** All figures/tables you include in your report should be explicitly mentioned in the main text. 

- **Explicitly cite all references:** All references you include in your reference list should be explicitly cited in the main text. If you don't cite it, remove it.

- **Explicitly mention appendices:** Have you added any appendices? If so you must refer to them at the relevant point(s) in the main text.

- **Consistent use of either British English or American English spelling:** If you have some time to really polish your report, try to be consistently British or consistently American in how you spell English words. Some common differences are the use of **ou** (British) versus **o** (American) in words like **colour**/**color**, and the use of **ise** (British) versus **ize** (American) in words like **analyse**/**analyze** and **discretise**/**discretize**.
