# Introduction to git

## What is git?

*git* is a version control software, or as the developers themselves call it, a *stupid content tracker*. What it *does* is track changes in a system of files to make collaboration among developers on a code project easy. It provides a rich set of tools to ensure that several programmers can work on the same project in a non-linear way. Several programmers can even work on the exact same file.

## What is GitHub?

GitHub is a service that provides hosting and storage for software development and version control using git as its underlying version control software. It also offers services that goes beyond the functionality of git.

For our purposes, they host *repositories*, or *repos* for short, that essentially are copies of specific local computer directories at certain timestamps. We use git to manage these and store copies on a server hosted by GitHub.

## The structure of a repo and typical workflow

A repo usually consists of many branches, each of which contains some version of the repo. There's a *main* branch that contains the main project. Then there's branches we create to protect the main project during development where we tweak, modify or add new code to the project. At the point of creation, these branches are exact copies of the main branch. During development, these branches can be thought of as an experimental version of the repo. Once the work on a separate branch is tested and verified, it's *merged* with main branch. Any new code that is developed thus becomes part of the main project. Any project is practically this on repeat.

This will all make more sense once you've worked with git.
