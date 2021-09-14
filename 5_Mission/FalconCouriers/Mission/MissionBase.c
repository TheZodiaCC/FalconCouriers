modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
				case 1129142: {
					menu = new CourierMenu;
					break;
				}
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}