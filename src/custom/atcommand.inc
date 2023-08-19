// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}

/*==========================================
 *------------------------------------------*/
ACMD_FUNC(hideview)
{
	int val = 0, view = 0;
	char type[CHAT_SIZE_MAX];
	
	nullpo_retr(-1, sd);
	memset(atcmd_output, '\0', sizeof(atcmd_output));
	
	parent_cmd = atcommand_alias_db.checkAlias(command+1);
	
	if( strcmp(parent_cmd, "hideview") == 0 ){
		if((sscanf(message, "%s %11d", &type, &view)) < 1 || (view > 15 || view < 1)){
			clif_displaymessage(fd, "วิธีใช้: @hideview {<ประเภท>} {<ตำแหน่ง>}");
			clif_displaymessage(fd, "ประเภท: all - ผู้เล่นทุกคน {<ตำแหน่ง>} view | other - ผู้เล่นอื่น {<ตำแหน่ง>} view");
			clif_displaymessage(fd, "ตำแหน่ง: 1 - หัว | 2 - หู | 4 - ปาก | 8 - ผ้าคลุม");
			clif_displaymessage(fd, "ตัวอย่าง: \"@hideview other 7\"  \nคือ ( 1 + 2 + 4 = 7 จะซ่อนของสวมใส่ในส่วน หัว,หู,ปาก ของผู้เล่นอื่น)");
			return -1;
		}
		if((strncmp(type, "all", 3) == 0))
			val += 16;

		if(view&1) val += 1;
		if(view&2) val += 2;
		if(view&4) val += 4;
		if(view&8) val += 8;
		
		sd->state.hideview = val;
		clif_refresh(sd);
		if((strncmp(message, "others", 3) == 0) || (val&16)){
			clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_TOP,sd->status.head_top,SELF);
			clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_MID,sd->status.head_mid,SELF);
			clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_BOTTOM,sd->status.head_bottom,SELF);
			clif_refreshlook(&sd->bl,sd->bl.id,LOOK_ROBE,sd->status.robe,SELF);
		}
		if(val&16){
			if(val&1) clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_TOP,0,SELF);
			if(val&2) clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_MID,0,SELF);
			if(val&4) clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_BOTTOM,0,SELF);
			if(val&8) clif_refreshlook(&sd->bl,sd->bl.id,LOOK_ROBE,0,SELF);
		}
		sprintf(atcmd_output, "อุปกรณ์สวมใส่ของผู้เล่น %s ถูกซ่อนแล้ว",(strncmp(type, "others", 3)) ? "อื่น":"มั้งหมด");
		clif_displaymessage(fd, atcmd_output);
		clif_displaymessage(fd, "ใช้คำสั่ง @showview เพื่อแสดงอุปกรณ์สวมใส่ทั้งหมด");
	} else if(strcmp(parent_cmd, "showview") == 0){
		sd->state.hideview = 0;
		clif_displaymessage(fd, "อุปกรณ์สวมใส่ของผู้เล่นทั้งหมดถูกแสดงแล้ว.)");
		clif_refresh(sd);
		clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_TOP,sd->status.head_top,SELF);
		clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_MID,sd->status.head_mid,SELF);
		clif_refreshlook(&sd->bl,sd->bl.id,LOOK_HEAD_BOTTOM,sd->status.head_bottom,SELF);
		clif_refreshlook(&sd->bl,sd->bl.id,LOOK_ROBE,sd->status.robe,SELF);
	}
	
	return 0;
}

