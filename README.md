# Poliman
Poliman is inspired by the Pac-Man game developed by Japanese firm Namco in 1980. In this case, the player's goal is to get through all the college stages without getting caught by the teachers. This project was created as part of an assignment to design an educational platform incorporating Pac-Man based gamification elements ("Fostering the Transversal Digital Competences in Higher Education" Ref. Project: 2022-1-ES01-KA220-HED-000089861).

## Gameplay
### Goal
There are 3 levels: the dorm, the campus and the classroom. Your goal is to avoid being caught by the professors. If they catch you, you'll have to answer a question. Get three questions wrong and you'll fail the exam!

<img width="864" alt="image" src="https://github.com/user-attachments/assets/28672df8-3ce2-4ca4-8218-ae11a7eec776" />

### Controls
- WASD - move the character

## Compiling
There are pre-compiled binaries in the [Releases](https://github.com/Edward205/poliman/releases) section.

You can compile the game yourself on Windows, Linux and Mac OS. Download and install the prerequesites:
- https://mesonbuild.com/Getting-meson.html
- https://ninja-build.org/

Execute these commands to build:
- `meson setup builddir`
- `cd builddir`
- `meson compile`

## Credits
- Sprites & art: https://github.com/EnescuDianaCristina
- Level design, testing & bug fixes: https://github.com/darianski143
