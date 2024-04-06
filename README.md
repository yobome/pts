# PTS
PTS is a trading system written in C++.

## Getting Started

### Prequisites
- xmake
- gcc-10

### Installation
```shell
$ cd pts && xmake -y
$ xmake install -o [TARGET_DIR]
```

### Usage
```shell
$ cd [TARGET_DIR] 
# edit config/config.toml
$ ./bin/pts -c config/config.toml
```