[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/license/gpl-3-0/)


# Simplersync

Simple remote sync service.


## Build/Installation

Clone and build with gcc

### Install GCC: 

#### Ubuntu
```bash
sudo apt install build-essential
```

#### Arch
```bash
sudo pacman -S gcc
```

 
### Install dependencies: 

 
#### Ubuntu
```bash
sudo apt install libjansson-dev zlib1g-dev
```

#### Arch
```bash
sudo pacman -S zlib jansson
```

### Compile: 
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
[Unit]
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

### Remote Key:

Generate and copy ssh key over to remote computer, 
which also needs to have sshd running.

### Install sshd on remote computer:

#### Ubuntu
```bash
sudo apt install openssh-server
sudo systemctl start sshd
```

#### Arch
```bash
sudo pacman -S openssh
sudo systemctl start sshd
```

### Generate and copy key:

```bash
ssh-keygen
ssh-copy-id username@x.x.x.x
``` 

## Usage

Start service.

```bash
sudo systemctl start simplersync
sudo systemctl enable simplersync
```

## To-Do:
- handle multiple remote computers,
- rewriting zip function and del function.
