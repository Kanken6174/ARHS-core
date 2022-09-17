packages:
```mermaid
flowchart LR
    main --> hw
    hw --> ui
    ui --> cameras
    ui --> psvr
    ui --> opencv4/imgcodecs
    cameras-->threadweaver
    cameras-->opencv4
    psvr-->ihidapi
    ihidapi-->hidapi
```