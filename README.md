# Adventure Text Limit Break
 This mod disables all text limitations on text edit fields found in Spore's Adventure Editor, allowing you to be as verbose as you want to be. It does not extend the amount of text bubbles total in each act, goal and creation, but at least now you will no longer be restricted by the 192 character limit imposed on you previously.

### Latest release can be found [here](https://github.com/Liskomato/Spore-AdventureTextLimitBreak/releases/latest).

![](TextLimitsBroken.png) 

 If you encounter any issues, please don't hesitate to contact me about this! 

 ### **Requires [Spore ModAPI Launcher Kit](http://davoonline.com/sporemodder/rob55rod/ModAPI/Public/).**

## FAQ
### Is this shareable?
Yes, it is indeed a shareable adventure mod. In fact, one of my previous mods, [Adventure Localizer](https://github.com/Liskomato/Spore-AdventureLocalizer), proved that text strings exceeding 192 characters were possible to share online to Spore.com, discounting some small hiccups with the sharing process itself. The Localizer mod was how I managed personally to share adventures with overlong text before I made this mod, but now some of the long process that was previously there (in editing text fields manually outside of Spore itself) can now be skipped entirely.

### What happens if I remove the mod and loaded an adventure where I used this mod?
Same thing if you were to use the Localizer before for this purpose: The text itself will cease to exist if you try to edit it, but it will persist in the adventure's data itself for as long as it is unmodified. For this reason, the adventures now made with this are entirely shareable, and if you have used the Localizer before, *now you can actually display your long text strings in-game.*

### Anything else I should take note of?
If you encounter any issues with sharing your own adventures to the online Sporepedia (i. e. the "Adventure was not successfully shared" error), try doing one or more of the following things, with priority from first to last:
1. Trim the adventure's win, lose and intro texts to less than 192 characters each.
2. Remove extra images from the adventure in question in the editor until only the "saved" preview images and the thumbnail remain. You will know if they are "saved" if they appear as the first image in their respective frames. 
    * If this doesn't work, remove the 3 preview thumbnails as well so there's only one preview image (the first one, which will become the adventure's PNG icon).
3. If you know how to use SporeModder FX, try compressing your PNG thumbnails with a compression algorithm like [zopfli](https://github.com/google/zopfli), and manually place them again into your EditorSaves package.

If none of these work for you, remove the text limit break mod as well and rewrite every missing dialogue box in your adventure, using also the three above solutions available to you until you get it to share. And if possible, figure out which one of these options worked for you specifically and note it down somewhere for your future adventures.

I plan on also updating the [Creation ZIP Porter](https://github.com/Liskomato/Spore-CreationZIP-Porter) mod with a feature in the ``adventureExport`` cheat where it only exports the adventure's own files and its thumbnails, allowing you to create a "duplicate" adventure with its own custom thumbnails which you can then try sharing, making option 3 more viable as a result.

 ## Credits
 - Liskomato - Main developer 
