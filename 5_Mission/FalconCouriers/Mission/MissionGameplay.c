modded class MissionGameplay {

	ref CourierMenu courierMenu;
	
	
	void MissionGameplay() {
		GetRPCManager().AddRPC( "FalconCouriers", "openCourierMenuC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "FCmessagePlayerC", this, SingeplayerExecutionType.Server );
	}
	
	private void FCmessagePlayerC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) 
		{
			string message = data.param1;
			
			if (message)
			{
				string finalMessage = "[FalconCouriers]: " + message;
			
				GetGame().Chat(finalMessage, "colorAction");
			}
       	}
    }
	
	private void openCourierMenuC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (data.param1)
			{
				int courierId = data.param1;
				
				if (courierMenu) 
				{						
					if (!courierMenu.isMenuOpened()) 
					{
						courierMenu.setCourierId(courierId);
						
	                    openCourierMenu();
	               	}
            	} 
				else if (!courierMenu) 
				{
					courierMenu = CourierMenu.Cast(GetUIManager().EnterScriptedMenu(1129142, null));
					
					courierMenu.setCourierId(courierId);
					
	                openCourierMenu();
	            }
			}
        }
	}
	
	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		if (key == KeyCode.KC_ESCAPE) 
		{
			if (courierMenu) 
			{
                if (courierMenu.isMenuOpened()) 
				{
                    closeCourierMenu();
                } 
            } 
		}
	}
	
	private void openCourierMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(courierMenu, NULL);
        courierMenu.setMenuOpened(true);
	}
	
	private void closeCourierMenu()
	{
		courierMenu.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(courierMenu);
	}
}