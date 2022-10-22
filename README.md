# tagprint.c
<pre>
Tag parser and printer. Takes HTML like TAGS and converts colors to ANSI color codes.
Examples:

"<green>this is a test</green><br>"

will print the string "this is a test" in the color green and then print a line break.

Supports the following ANSI colors: 

black, red, green, yellow, blue, magenta, cyan, white.

supports the following HTML equivilant tags:
<br>   line feed.


