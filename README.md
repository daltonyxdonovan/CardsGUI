# CardsGUI
## use the issue tracker for bugs
# Due to security restrictions in windows 11

in order to use this, it has to remain in the exact folder configuration provided. the
MainTech Cards executable requires itself to be in the same folder as the includes folder,
and the csv to be used is required to be in the folder with it. you can remove and replace
the csv at will. you are more than welcome to make a shortcut to it, but the csv still has
to be in the MainTech Cards folder. this is a requirement so it can work on anyone's pc
with little fuss. I personally keep it in a folder on the desktop, because it's the easiest
workaround to the tight restrictions on file access.

## TO USE

i'm not personally well-versed in anything maintech, all i know is that you download a
strictly non-filtered .tab file from the maintech website, and you put the file in the
same location as the executable. right outside the 'includes' folder

## CONTROLS

the mouse can check off a card to dismiss it, or to choose a color theme from the paintbrush
in the top right corner.

the escape button exits the program

## NOTES

note: in the spirit of open source, and so there are no thoughts of viruses or anything, i've
left the source code included. feel free to pick apart my spaghetti code

# FAQ
## MISSING REDIST
if you encounter an error along the lines of "missing redistributable MSVC-xxxxxxxx", you are 
missing a redistributable package from the microsoft website. super easy fix. just plug the 
MSVC number in to google and go to the top microsoft website result and install the package.

## BLANK COLORED SCREEN ON START
if you encounter this, that means the files are either not in a place the application is
allowed to touch, or they are in the wrong order. make a folder on your desktop, put the
Cards.exe and the entire 'includes' folder *inside* that folder. put your .tab *inside*
that folder, run the application. that's all (:
