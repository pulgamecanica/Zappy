<center>
<h1>ZappyWeb 42</h1>
</center>

***

<center>

![lofi night](https://i.pinimg.com/originals/75/28/7e/75287e12c273a005251757fc60c3b444.gif)

</center>

***

## Intro

This current Directory contains 3 different programs: Client, GraphicalInterface & the main program (The server)

The Client & GraphicalInterface directories (programs) are just for testing, they are not relevant.

***

### Server

The Zappy server is a Game engine where you can run the Trantor World!
Trantorians must survive and you can build a bot to play and get to the last elevation level.

#### Running the server:

You can just compile the project and run with the default configuration (conf.toml)

```bash
make all
./Zappy
```

Optionally if you want you can run the project in debug mode (this will generate aditional debug information on the server side and clients will receive more information)
When DEBUG mode is on Clients will receive more information about the command they execute, if they fail and why.
To run in debug mode you can generate an executable like this:

```bash
make debug
./Zappy
``` 

##### Options

You can change almost all the server configurations. You have the following options available:

Mandatory OPTIONS (For now disabled until later because it's not convenient to write all this info every time you want to run the server)

    -c <#clients>       number of players allowed per team
    -n team <team2> ... teams, this is, the teams that will exist on trantor
    -x <width>          refers to the initial horizontal size of trantor (width > 10)
    -y <height>         refers to the initial vertical size of trantor (height > 10)

Other OPTIONS]:
  
    -f <file>    set the configuration file (TOML format)
                 by default `./conf.toml` is used
    -t <ms>      set the time unit divider, it's 100 by default (100 frames per second)
                 the higher this number, the faster the world will be (ms > 0)
    -T <ms>      set the connection timeout, if a player doesn't join a team after ms
                 doesn't apply to spectators (default to 1min (60000ms)
    -l <acronym> default Zappy language <must be present on the conf.file>
    -P <port>    set the players port to something else than 4242
    -S <port>    set the spectators port to something else than 2121
    -h           help

#### Configuration

The configuration is managed on the configuration file (conf.toml by default)

On the configuration file you can add new languages (for now)
In the future I will implement the port(s), address, single port mode; etc

<center>

<h3> Table of commands </h3>

<h4>Graphical Client</h4>

| CMD Request | CMD Response | Details | Example |
| ----------- | ------------ | ------- | ------- |
||
| `msz` | `msz X Y\n` | Map Size, returns the map size<br>`X` width<br>`Y` height | <details> <summary>Example</summary><a href="/images/SpectatorImg.png" referer="no-referer" target="auto"><img src="/images/SpectatorImg.png" alt="Spectator"></a></details> |
||
| `bct X Y` | `bct X Y q q q q q q q\n` | Box Content Tile, returns all the resources of a tile in order<hr>Params:<br>`X` tile 'x' coordinate<br>`Y` tile 'y' coordinate<hr>Resources (`q q q q q q q`):<br>Each `q` represents the amount of a resource, the list is ordered<br><details style="text-align: left;"> <summary>See More</summary>`q q q q q q q`<br>`│ │ │ │ │ │ └` Thystame [7]<br>`│ │ │ │ │ └─` Phiras [6]<br>`│ │ │ │ └───` Mendiane [5]<br>`│ │ │ └─────` Sibur [4]<br>`│ │ └───────` Deraumère [3]<br>`│ └─────────` Linemate [2]<br>`└───────────` Food [1]<br></details><hr>Errors:<br>When '[x, y]' is not found on the map: `Tile [20 20] is not in the map`| <div class="shields">![Static Badge](https://img.shields.io/badge/map-yellow?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPCFET0NUWVBFIHN2ZyBQVUJMSUMgIi0vL1czQy8vRFREIFNWRyAxLjEvL0VOIiAiaHR0cDovL3d3dy53My5vcmcvR3JhcGhpY3MvU1ZHLzEuMS9EVEQvc3ZnMTEuZHRkIj4KPCEtLSBVcGxvYWRlZCB0bzogU1ZHIFJlcG8sIHd3dy5zdmdyZXBvLmNvbSwgVHJhbnNmb3JtZWQgYnk6IFNWRyBSZXBvIE1peGVyIFRvb2xzIC0tPgo8c3ZnIHdpZHRoPSI4MDBweCIgaGVpZ2h0PSI4MDBweCIgdmlld0JveD0iMCAwIDEwMCAxMDAiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIGFyaWEtaGlkZGVuPSJ0cnVlIiByb2xlPSJpbWciIGNsYXNzPSJpY29uaWZ5IGljb25pZnktLWdpcyIgcHJlc2VydmVBc3BlY3RSYXRpbz0ieE1pZFlNaWQgbWVldCIgZmlsbD0iI2ZmZmZmZiI%2BCjxnIGlkPSJTVkdSZXBvX2JnQ2FycmllciIgc3Ryb2tlLXdpZHRoPSIwIi8%2BCjxnIGlkPSJTVkdSZXBvX3RyYWNlckNhcnJpZXIiIHN0cm9rZS1saW5lY2FwPSJyb3VuZCIgc3Ryb2tlLWxpbmVqb2luPSJyb3VuZCIvPgo8ZyBpZD0iU1ZHUmVwb19pY29uQ2FycmllciI%2BCjxwYXRoIGQ9Ik0zMi40MjUuMjg0QzE4LjQ4MiA1LjggMTAuMjU3IDIyLjQ1MiAxNi4wNzUgNDYuMjI0Yy41MDEgMi4xMDcgNC4zMTMgNS4xMTYgNC42MTQgNy4xMjJjLjIgMi4wMDctMy4yMSAzLjAxLTMuMzEgNC44MTVjMCAzLjYxMS0uNjAyIDYuODIxLTEuMzA0IDkuNzNsLTcuMTIyLTEuNzA1Yy0yLjUwOCAyLjkwOS00LjgxNSA1LjYxNy02LjAxOSA4LjUyNmMtLjgwMiAyLjEwNi0xLjMwNCA0LjYxNC0uMiA3LjAyMmMxOS4zNiAxMi4xMzcgNTIuMTYgMTguMDU1IDcxLjYyIDE4LjI1NmMyLjkwOC4xIDMuOTExLS41MDIgNC45MTUtMi42MDhjLjMtLjcwMy43MDItMS43MDYgMS4xMDMtMi45MWMuOTAzLTIuNDA3IDEuODA1LTUuNzE3IDIuNjA4LTkuODNjLjcwMi00LjAxMiAxLjIwNC04LjgyNyAxLjAwMy0xMy44NDJjMC0yLjYwOC02LjUyLTQuNTE0LTYuMzItNy4yMjJjLjEwMS0yLjAwNiA1LjQxNy00LjgxNSAzLjUxMS04LjcyN2MtNC41MTMtOS4yMjgtMy4yMS0xNi4yNS0uNTAxLTIxLjg2N2MyLjYwOC01LjcxOCA3LjkyNC0xMC42MzMgMTUuODQ4LTE1Ljk0OWMyLjMwOC0xLjYwNSAxLjYwNS01LjIxNi0xLjIwMy01LjcxN0wzNC4xMy4wODNjLS42MDItLjItMS4yMDQgMC0xLjcwNS4yem0xLjcwNSA2LjIxOWw1My4yNjMgOS43M2MtNS4zMTYgNC4yMTMtOS45MyA4LjYyNi0xMi40MzggMTQuMDQzYy0zLjQxIDcuMzIyLTMuNDEgMTQuODQ1LjMwMSAyNS4zNzhjLjgwMyAyLjQwNy01LjgxOCA2LjMxOS01LjQxNiA4LjYyNmMuNCAyLjQwNyA3LjUyMyA1LjYxNyA3LjYyMyA3LjkyNGMuMSA0LjUxNCAwIDcuNjI0LS43MDIgMTEuMzM1Yy0uNjAyIDMuNzExLTEuMzA0IDYuODIxLTIuMzA3IDguOTI3Yy0uOTAzIDEuNTA1LTMuNDEuMjAxLTQuMzEzLTMuMDA5Yy0xLjAwNC0zLjkxMi0uNTAyLTYuMDE4IDEuNzA1LTkuMDI3Yy0xNi41NTEtMS40MDUtMzMuMTAyLTQuODE1LTQ5LjY1Mi0xMS4wMzRjLjkwMi0zLjExIDEuNTA0LTQuOTE1IDEuNjA0LTkuMDI4YzAtMi4wMDYgMy40MS0yLjIwNyAzLjExLTQuNTE0Yy0uMi0yLjQwNy00LjExMy04LjUyNi00LjcxNC0xMS4xMzRjLTUuMzE3LTIxLjM2NiAxLjYwNC0zMy43MDMgMTEuOTM2LTM4LjIxN3ptNi40MiAyLjEwNmwtNC44MTUgNC4wMTNjLTIuMDA2IDAtMy45MTIgMS4wMDMtNS4yMTYgMi41MDdsLTQuMzEzIDEuMDAzbDIuNzA4IDIuODA5Yy0uMyAyLjIwNy40MDEgNC41MTQgMi4xMDcgNi4wMThsLS41MDIgNi4wMTlsNC4zMTMtNC4zMTNjMi4yMDcuMSA0LjQxNC0uODAzIDUuODE4LTIuNTA4bDMuNzEyLS41MDJsLTIuMDA3LTMuMzFjLjIwMS0yLjIwNy0uNTAxLTQuNTE0LTIuMTA2LTYuMDE4em0tNC41MTQgOC4yMjVjLjIgMCAuNTAyIDAgLjcwMi4xYzEuNTA1LjcwMyAxLjkwNiAyLjcxIDEuMTA0IDQuMDEzYy0uNzAzIDEuNDA0LTIuNjA4IDIuMTA3LTMuODEyIDEuMTAzYy0xLjUwNS0xLjEwMy0xLjMwNC0zLjQxIDAtNC41MTNjLjUwMS0uNTAyIDEuMzA0LS44MDMgMi4wMDYtLjcwM3ptMTkuMTU5IDguNzI3bC0zLjUxMSAyLjIwN2wzLjAxIDQuOTE1bC00LjUxNSAyLjMwN2wxLjkwNiAzLjcxMmw0LjcxNS0yLjQwOGwzLjgxMSA2LjExOWwzLjUxMS0yLjIwN2wtMy41MS01LjgxOGw1LjcxNy0yLjkwOWwtMS45MDYtMy43MTFsLTYuMDE4IDMuMDF6bS05LjYzIDguNDI2bC0yLjAwNi40MDFjLTIuMzA3LjcwMi00LjYxNCAxLjkwNi02LjQyIDMuNjExbDIuODA5IDMuMTFjMS44MDYtMS43MDUgNC4xMTMtMi43MDggNi41Mi0zLjExek0zNC4yMyA0MS44MTFsLS45MDIgMS42MDVhNTEuODI3IDUxLjgyNyAwIDAgMC0xLjQwNSA0LjIxM2wtLjMgMi45MDlsNC4yMTIuNDAxYy4xLTEuNjA1LjMwMS0zLjIxLjkwMy00LjcxNGMuMi0uOTAzLjcwMi0xLjYwNSAxLjEwNC0yLjMwN3ptMS44MDYgMTIuNTM5bC00LjAxMiAxLjEwM2MuNTAxIDEuNzA1LjkwMiAzLjUxIDEuOTA2IDUuMDE1Yy41MDEgMS4yMDQgMS4yMDMgMi4yMDcgMS45MDUgMy4yMWwzLjQxLTIuNTA4Yy0xLjAwMi0xLjQwNC0xLjkwNS0yLjkwOC0yLjUwNy00LjYxNHptNS43MTggOS4zMjhsLTIuNTA4IDMuNDFjMi4zMDcgMS44MDYgNS4xMTYgMy4xMSA3LjgyNCA0LjExM2wxLjYwNS0zLjgxMWMtMi41MDgtMS4wMDQtNC45MTUtMi4wMDctNi45MjEtMy43MTJ6bTEwLjgzMyA1LjMxNmwtMS43MDUgMy44MTJjMi4xMDYgMS4wMDMgNC4yMTIgMi4zMDcgNS41MTYgNC40MTRsMy41MTEtMi4zMDdjLS44MDItMS4zMDQtMS44MDUtMi4zMDctMy4wMDktMy4zMWEyMy41MDYgMjMuNTA2IDAgMCAwLTQuMzEzLTIuNjA5eiIgZmlsbD0iI0RGRjBEOCIgZmlsbC1ydWxlPSJldmVub2RkIi8%2BCjwvZz4KPC9zdmc%2B) ![Static Badge](https://img.shields.io/badge/params-green)</div><details> <summary>Example</summary><a href="/images/bct.png" referer="no-referer" target="auto"><img src="/images/bct.png" alt="Block Content Tile"></a></details> |
||
| `mct` | `bct X Y q q q q q q q\n` <br>(for each tile) | Map Content Tiles, executes the `bct` command for all the tiles in the map, followed by an empty new line (end of message) | <details> <summary>Example</summary><a href="/images/mct.png" referer="no-referer" target="auto"><img src="/images/mct.png" alt="Map Contents Tiles"></a></details> |
||
| `tna` | `tna N\n` <br>(for each team) | Team names, returns all the teams names<br>`N` team's name followed by an empty new line (end of message) | <details> <summary>Example</summary> </details> |
||
| - | `pnw #n X Y O L N\n` | Player New, notification when a Player connects and joins a team<br>`X` x coordinate<br>`Y` y coordinate<br>`O` orientation<br>`L` level<br>`N` team's name | <details> <summary>Example</summary> </details> |
||
| `ppo #n` | `ppo #n X Y O\n` | Player Position, returns the position of player #n<hr>Params:<br>`#n` player's id<hr>`X` x coordinate<br>`Y` y coordinate<br>`O` orientation<hr>Errors:<br>When the id is not found: `Player not found`<br> | <details> <summary>Example</summary></details>|
||
| `plv #n` | `plv #n L\n` | Player Level, returns the level of player #n <hr>Params:<br>`#n` player's id<hr>`L` level<hr>Errors:<br>When the id is not found: `Player not found`<br> | <details> <summary>Example</summary></details>|
||
| `pin #n` | `pin #n X Y q q q q q q q\n`| Player inventory, get the inventory of player #n<hr>Params:<br>`#n` player's id<hr>`X` x coordinate<br>`Y` y coordinate<br>`q` amount of the resource<hr>Errors:<br>When the id is not found: `Player not found`<br> | <details> <summary>Example</summary></details>|
||
| `players` | `player #n X Y O L N q q q q q q q\n` (for each player) | Players, get all the players information, as described on the Player New and Player inventory, followed by an empty new line (end of message) | <details> <summary>Example</summary></details>|
||

<h6 style="text-align:left;">
NOTE:<br>
All parameters given to a command should be separated by spaces<br>
The commands which take no parameters ignore any parameters if executed with parameters<br>
Commands which require parameters should receive only the parameters which are allowed or they will fallback to `sbp` (server bad params)<br>
All commands not found will fallback to `scu` (server command unknown)<br>
When DEBUG mode is ON, the `suc` & `sbp` will display more information on the reason of the failure
</h6>
</center>

***
