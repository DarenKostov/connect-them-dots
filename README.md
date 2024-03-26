# Connect them dots!
![](https://github.com/DarenKostov/connect-them-dots/blob/master/demo.gif)

## How to install:
```
git clone https://github.com/DarenKostov/connect-them-dots.git
cd connect-them-dots
make -j
sudo make install
```
#### How to run
```
connect-them-dots
```


## How it works
1. Left click, and hold, on the center of the orange circle
2. Drag, while holding, to the cyan circle
3. Release the button when the center of the cyan circle is reached
4. Repeat, while trying to take the shortest path

Should work on touch screen if the touchscreen outputs left click when pressing

## Data
When the program is closed it will create a `datapoints-{UNIX TIME IN SECONDS}.csv` file.

The file contains information about each successful attempt of connecting 2 dots.


## Flags
`-h`, `--help`: prints help information

`-l`, `--licence`: prints the licence

`-v`, `--version`: prints the version

