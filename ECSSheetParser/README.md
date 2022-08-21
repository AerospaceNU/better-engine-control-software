## ECS Python Sheet Parser

This folder contains our Python parser, which reads spreadsheets downloaded as `csv` files from the prop team
and translates that data into C++ object definitions/declarations that we can directly paste into
our files

Currently, we generate our `ECSState` and `IRedline` objects from this script

The expected format for the sheets is detailed at 
[this link](https://docs.google.com/spreadsheets/d/1KS2zOC6Fd0i-oO3xj4y0no6LlENIi-kr_QfeziOjQnU/edit#gid=0)


NOTE: The code is kinda spaghetti rn, so I'll have to work on making it better - Kevin
