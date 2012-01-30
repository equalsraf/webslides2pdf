
## Introduction

webslides2pdf is a tool to convert web pages into pdf files.

Its behaviour can be described as follows:

> Imagine you open a browser, take a screenshot, and press page-down
> and take another screenshot, and so on.
> You them grab all screenshots and generate a pdf where each
> one is a single page.
> That's what this application does for you.

I did this to be able generate pdf files from web based presentations.
However there are some downsides:

+ The pdf will not be perfect, it wont have ToC or other accessibility features
+ Some web pages react badly to certain page dimensions you can try using the size parameter (see bellow)
+ While the result is a pdf, these wont be high quality vector drawings - they are bitmaps embedded in a pdf

## Usage

Just call
    
    $ ./webslides2pdf <location> <num_pages>

Where locations is either a local file path or URL of a presentation,
and num_pages is the number of slides.

There is an optional third argument, to specify the size in pixels of the
slides. For example, this command

    $ ./webslides2pdf file.html 10 1920x1080


would generate a pdf with 10 pages and size 1920x1080 pixels
from the file.html file.


## Compiling

The only requirement is Qt along with its development tools,
running:

    $ qmake
    $ make 

should build the webslides2pdf binary.




