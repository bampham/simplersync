mod parse;
use std::{net, io::Result, error};

fn main() -> Result<()> {

    let mut config = parse::Config::new("test".to_string(), "test".to_string(), "test".to_string(), "test".to_string(), 24);
    parse::serialize(config, "config.json")?;

    Ok(())
}
