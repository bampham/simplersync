[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/license/gpl-3-0/)


# Simplersync

Simple remote sync service.


## Build/Installation

Clone and build with gcc

Install the zlib and jansson libraries.

### Ubuntu
```bash
sudo apt install libjansson-dev
sudo apt install zlib1g-dev
```
### Arch
```bash
sudo pacman -S zlib
sudo pacman -S jansson
```
### Compile
```bash
  git clone https://github.com/bampham/simplersync
  cd simplersync
  sudo ./build && sudo ./install

```


## Configure

Config in /etc/simplersync/config.json
```json
{
  "username": "root",
  "remoteHost": "192.168.x.x",
  "remoteDirectory": "/path/to/remote/dir",
  "destinationDirectory": "/path/to/backup/dest",
  "backupFrequencyHours": 24
}
``` 

Choose desired user in /etc/systemd/system/simplersync.service

```service
Unit]
Description=SimpleRsync Backup Service
After=network.target

[Service]
ExecStart=/usr/local/bin/simplersync
Restart=always
User=root
RestartSec=60

[Install]
WantedBy=default.target
```


## Usage

Start service.

```bash
sudo systemctl start simplersync
sudo systemctl enable simplersync
```
