



//			Masson`s list dialog System
//			This include add into your code list dialogs with simple usage

//			Version: 0.2sam
//			Last Release: 22.06.2020

//			Dependencies:
//			- No

//			Compatibility:
//			- mdialog
//			- tdw_dialog
//			- y_dialogs



#if defined MAS_LISTDIALOG_INCLUDED
	#endinput
#else 
	#define MAS_LISTDIALOG_INCLUDED
#endif

#if !defined MAS_DIALOG_ID
	#define MAS_DIALOG_ID	2 // if it used you can change it
#endif

#if !defined MAX_LIST_ITEMS
	#define MAX_LIST_ITEMS	64
#endif

#if !defined MAX_PLAYERS
	#define MAX_PLAYERS	500
#endif

#if !defined 

#define INVALID_LISTITEM	-1
#define MAX_LIST_FUNC_NAME	24
#define MAX_FUNC_NAME		32

#define LISTDIALOG:%0(%1) \
	forward _mas_ld_%0(%1);\
	public _mas_ld_%0(%1)

#define LIST: #


static
	masListDialog[MAX_PLAYERS+1][MAX_FUNC_NAME],
	masListDialogListitems[MAX_PLAYERS+1][MAX_LIST_ITEMS];


stock ShowListDialog(
	const playerid, 
	const func[], 
	const caption[], 
	const info[], 
	const listitems[], 
	const button1[], 
	const button2[] = "",
	const size_listitems = sizeof(listitems),
	const size_func	= sizeof(func)
) {
	if(!IsPlayerConnected(playerid)) return 0;
	if(
		!size_func || size_func >= MAX_LIST_FUNC_NAME
	) return 0;
	if(size_listitems >= MAX_LIST_ITEMS) return 0;

	ListDialogClear(playerid);

	strcat(masListDialog[playerid], "_mas_ld_");
	strcat(masListDialog[playerid], func);

	// Thanks to tnc for awesome advice
	memcpy(masListDialogListitems[playerid], listitems, _, size_listitems * (cellbits / charbits));

	return ShowPlayerDialog(playerid, MAS_DIALOG_ID, DIALOG_STYLE_LIST, caption, info, button1, button2);
}


stock ListDialogClear(playerid) {
	if(!IsPlayerConnected(playerid)) return 0;
	if(strlen(masListDialog[playerid])) masListDialog[playerid][0] = EOS;
	if(strlen(masListDialogListitems[playerid])) masListDialogListitems[playerid] = masListDialogListitems[MAX_PLAYERS];
	return 1;
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {

	if(dialogid == MAS_DIALOG_ID) {
		if( strlen(masListDialog[playerid]) ) {
			CallLocalFunction(masListDialog[playerid], "ddd", playerid, response, masListDialogListitems[playerid][listitem]);	
		}
	}

    #if defined _mas_ld_OnDialogResponse
        _mas_ld_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
    #endif
    return 1;
}

#if    defined    _ALS_OnDialogResponse  
    #undef    OnDialogResponse
#else
    #define    _ALS_OnDialogResponse
#endif
#define    OnDialogResponse    _mas_ld_OnDialogResponse
#if    defined    _mas_ld_OnDialogResponse
forward _mas_ld_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif 




