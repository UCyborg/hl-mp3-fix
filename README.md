# Half-Life 1.1.1.0 MP3 Fix

Small ASI plugin that fixes the issue with not playing correct MP3 files when playing expansion packs/mods with the old pre-Steam version of Half-Life.
For example, you would always hear the Half-Life soundtrack even if playing Half-Life: Opposing Force.

It also fixes the issue with the MP3 file associated with the last track not playing.

Ability to play MP3 files as a substitute for playing soundtrack from CD first appeared with patch 1.1.0.9. It's an undocumented feature that only
became official with Steam version of Half-Life. Refer to the following list to see how to name MP3 files after ripping them from Half-Life CD:

1. <data track, ignore it>
2. Half-Life01.mp3
3. Prospero01.mp3
4. Half-Life12.mp3
5. Half-Life07.mp3
6. Half-Life10.mp3
7. Suspense01.mp3
8. Suspense03.mp3
9. Half-Life09.mp3
10. Half-Life02.mp3
11. Half-Life13.mp3
12. Half-Life04.mp3
13. Half-Life15.mp3
14. Half-Life14.mp3
15. Half-Life16.mp3
16. Suspense02.mp3
17. Half-Life03.mp3
18. Half-Life08.mp3
19. Prospero02.mp3
20. Half-Life05.mp3
21. Prospero04.mp3
22. Half-Life11.mp3
23. Half-Life06.mp3
24. Prospero03.mp3
25. Half-Life17.mp3
26. Prospero05.mp3
27. Suspense05.mp3
28. Suspense07.mp3

**Important:** The MP3 decoder used in the old version of Half-Life doesn't understand ID3v2 tags commonly added by CD ripping software and such MP3s
won't be played. Make sure your ripping software offers ability to use ID3v1 tags instead. They may also be omitted entirely.

The files go into following folders. The above list can be used when ripping CDs of the expansion packs, the only difference is they have less tracks.

### Half-Life

\Half-Life\valve\media

### Half-Life: Opposing Force

\Half-Life\gearbox\media

### Half-Life: Blue Shift

\Half-Life\bshift_unlocked\media (use [Blue Shift: Unlocked v1.1](https://www.moddb.com/games/half-life-blue-shift/downloads/blue-shift-unlocked-v112) to convert your BS installation to HL mod)
