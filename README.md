# mas_listdialog

[![sampctl](https://img.shields.io/badge/sampctl-mas_listdialog-2f2f2f.svg?style=for-the-badge)](https://github.com/MassonNN/mas_listdialog)


ListDialogs is a simple library for dialogs with lists


## Installation

Simply install to your project:

```bash
sampctl package install MassonNN/mas_listdialog
```

Include in your code and begin using the library:

```pawn
#include <mas_listdialog>
```

## Usage


ShowListDialog(playerid, func[], caption[], info[], listitems[], button1[], button2[] = "")

playerid - id of player to show list dialog
func - function that is executed when the dialog box responds
caption - dialog caption
info - dialog text 
listitems - an array of listitems
button1 - first button (Yes)
button2 - second button (No)

Example of usage:


public OnPlayerConnect(playerid) {
	new string[256];
	new addnum;
	new listitems[64];
	new name[MAX_PLAYER_NAME];
	for(new i; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i)) {
			listitems[addnum] = i;
			addnum++;
			GetPlayerName(i, name, MAX_PLAYER_NAME);
			strcat(string, name);
			strcat(string, "\n");
		}
	}
	ShowListDialog(playerid, LIST:TestDialog, "Players online", string, "Send hi", "Close", listitems);
	return 1;
}

LISTDIALOG:TestDialog(playerid, response, value) {
	if(!response) return 1;
	SendClientMessage(value, 0x00FF00FF, "Hi!");
	return 1;
}