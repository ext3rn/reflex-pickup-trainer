# reflex-pickup-trainer
reflex-pickup-trainer is a simple command line program that helps train your pickup timing skills in Reflex Arena. The program first "spawns" a random pickup item at a random game time. The user then has to perform simple arithmetic and enter the correct time at which the item spawns again.

In addition, you can manually configure the item list to support other arena FPS such as Quake Live.

## Installation
### Linux
Clone this repo:
```
git clone https://github.com/ext3rn/reflex-pickup-trainer.git
```
Enter the directory and compile the executable:
```
cd reflex-pickup-trainer
make
```

## Usage
For Linux:
- Run the executable in a terminal, e.g. `./pickuptrainer`

To answer, enter a number in the format `XX`, where XX is the time (in seconds) at which the item spawns again.

For example, if the Red Armor spawns at 55, the correct answer would be `20`.

To quit, enter `q`. Alternatively, you can also enter the EOF character (Ctrl-D on Linux).

## Configuration
Item list is stored in the file `config`, located in the same directory as the executable.
`config` follows the following format:
```
; Lines that start with a semicolon are comments
; Item Name = XX    where XX is the spawn duration
Red Armor = 25
Yellow Armor = 25
Mega Health = 30
```

## License
GPLv3
