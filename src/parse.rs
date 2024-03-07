use serde::{Serialize, Deserialize}; 
use serde_json::Result;
use std::fs::File;
use std::io::prelude::*;

#[derive(Serialize, Deserialize)]
pub struct Config {
    username: String,
    remote_host: String,
    remote_directory: String,
    destination_directory: String,
    frequency: usize,
}

impl Config {
    pub fn new(username: String, remote_host: String,
        remote_directory: String, destination_directory: String,
        frequency: usize) -> Self {
        Self {username, remote_host, remote_directory, destination_directory, frequency}
    }
}

pub fn serialize(config: Config, file_name: &str) -> std::io::Result<()> {
    let mut file = File::create(file_name)?;
    let serialized_config: String = serde_json::to_string(&config)?;
    write!(file, "{}", serialized_config)?;
    Ok(())
}


