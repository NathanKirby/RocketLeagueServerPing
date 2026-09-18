# Rocket League Region Pinger

A multi-threaded tool that correctly pings all Rocket League matchmaking regions using real ICMP instead of the game's broken internal pinger.

## The Problem

Rocket League's region pinger frequently fails. Typical log output:

```
[0019.96] ScriptLog: RegionPinger_X_0 PingRegions ("15.240.66.181:15006","16.162.44.0:15028","35.79.104.14:15009",...)
[0021.72] Matchmaking: All Regions Pinged: USE (1.0000),USC (1.0000),USW (1.0000),EU (1.0000),...
[0021.72] Matchmaking: Failed to ping 'USE'. Using cached ping '0.1131'
[0021.72] Matchmaking: Failed to ping 'USC'. Using cached ping '0.1199'
[0021.72] Matchmaking: Failed to ping 'USW'. Using cached ping '0.0657'
...
```

Even though the game reports every region as successfully pinged (`1.0000`), it immediately falls back to stale cached values for **every** region. This causes incorrect region selection and higher latency than necessary.

## The Fix

This tool bypasses Rocket League's pinger entirely and performs real ICMP pings directly to the server IPs. Results include the correct region code and physical location.

### Servers

| Region | IP              | Location                  |
|--------|-----------------|---------------------------|
| SAF    | 15.240.66.181   | Cape Town, South Africa   |
| ASC    | 16.162.44.0     | Hong Kong                 |
| JPN    | 35.79.104.14    | Tokyo, Japan              |
| IND    | 15.207.126.110  | Mumbai, India             |
| ASM    | 13.212.141.113  | Singapore                 |
| OCE    | 3.26.124.153    | Sydney, Australia         |
| EU     | 18.157.34.74    | Frankfurt, Germany        |
| EU1    | 13.60.90.86     | Stockholm, Sweden         |
| EU3    | 52.208.27.33    | Dublin, Ireland           |
| EU5    | 18.133.98.200   | London, England           |
| EU7    | 35.180.227.57   | Paris, France             |
| ME     | 34.18.71.245    | Doha, Qatar               |
| ME1    | 34.165.88.11    | Tel Aviv, Israel          |
| SAM    | 15.228.137.173  | São Paulo, Brazil         |
| USE    | 3.237.167.92    | Ashburn, Virginia         |
| USC    | 3.144.61.165    | Columbus, Ohio            |
| USC1   | 18.88.9.98      | Dallas, Texas             |
| USW    | 3.101.179.49    | San Francisco, California |
| USW1   | 52.12.91.222    | Portland, Oregon          |

## Building

**MinGW / g++**
```bash
g++ -std=c++17 -O2 -pthread ping_regions.cpp -o ping_regions.exe
```

**MSVC**
```bash
cl /EHsc /std:c++17 ping_regions.cpp
```

## Usage

```bash
./ping_regions.exe
```

All 19 regions are pinged concurrently. Output shows the region code, physical location, IP address, and the raw Windows `ping` results.
