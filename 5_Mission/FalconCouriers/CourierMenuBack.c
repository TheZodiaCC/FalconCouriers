class CourierMenuBack
{
	void CourierMenuBack()
	{
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierNameS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesTakesDetailsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesGivesDetailsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "givePackageS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "takePackageS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCouriersLocationsS", this, SingeplayerExecutionType.Server );
	}
	
	private void getCourierNameS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (data.param1)
			{
				int courierId = data.param1;
				
				FalconCourierCharacterData courierData = FalconCouriersUtils.getCouriersDataById(courierId);
			
				GetRPCManager().SendRPC( "FalconCouriers", "getCourierNameC", new Param1<string>(courierData.getCourierName()), true, sender );
			}	
       	 }
    }
	
	void getCourierName(int courierId) {		
		GetRPCManager().SendRPC( "FalconCouriers", "getCourierNameS", new Param1<int>(courierId) );
	}
	
	private void getCourierPackagesS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1)
			{
				int courierId = data.param1;
				
				array<string> givePackages = new array<string>();
				array<string> takePackages = new array<string>();
			
				FalconCourierCharacterData courierData = FalconCouriersUtils.getCouriersDataById(courierId);
				
				givePackages = courierData.getGivesPackages();
				takePackages = courierData.getTakesPackages();
				
				CourierPackagesRPCPackage package = new CourierPackagesRPCPackage(takePackages, givePackages);
				
				GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesC", new Param1<CourierPackagesRPCPackage>(package), true, sender );
			}
       	 }
    }
	
	void getCourierPackages(int courierId) {		
		GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesS", new Param1<int>(courierId) );
	}
	
	private void getCourierPackagesTakesDetailsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1)
			{
				FCouriersPackage packageDetails;
				
				packageDetails = FalconCouriersUtils.getCouriersPackagesDetailsByName(data.param1);
				
				GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesTakesDetailsC", new Param1<FCouriersPackage>(packageDetails), true, sender );
			}
       	 }
    }
	
	void getCourierPackagesTakesDetails(string packageName) {		
		GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesTakesDetailsS", new Param1<string>(packageName) );
	}
	
	private void getCourierPackagesGivesDetailsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1)
			{
				FCouriersPackage packageDetails;
				
				packageDetails = FalconCouriersUtils.getCouriersPackagesDetailsByName(data.param1);
				
				GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesGivesDetailsC", new Param1<FCouriersPackage>(packageDetails), true, sender );
			}
       	 }
    }
	
	void getCourierPackagesGivesDetails(string packageName) {		
		GetRPCManager().SendRPC( "FalconCouriers", "getCourierPackagesGivesDetailsS", new Param1<string>(packageName) );
	}
	
	private void givePackageS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1 != "")
			{
				string packageName = data.param1;
				PlayerBase player = FalconCouriersUtils.getPlayerByIdentity(sender);
				
				ItemBase item = FalconCouriersUtils.getPackageFromInventory(player, packageName);
				
				if (item)
				{
					if (!item.IsRuined())
					{
						FCouriersPackage package = FalconCouriersUtils.getCouriersPackagesDetailsByName(packageName);
						int sellPrice = package.getSellPrice();
						
						GetGame().ObjectDelete(item);
						
						item = null;
						
						if (item == null)
						{
							FalconCouriersUtils.addMoney(player, sellPrice);
						}
					}
					else
					{
						CouriersMessagesUtils.messageClient(CouriersMessagesConsts.CANT_SELL_RUINED_ITEM, player);
					}
				}
				else
				{
					CouriersMessagesUtils.messageClient(CouriersMessagesConsts.ITEM_NOT_IN_INVENTORY, player);
				}
			}
       	}
    }
	
	void givePackage(string packageName) {		
		GetRPCManager().SendRPC( "FalconCouriers", "givePackageS", new Param1<string>(packageName) );
	}
	
	private void takePackageS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1 != "")
			{
				string packageName = data.param1;
				PlayerBase player = FalconCouriersUtils.getPlayerByIdentity(sender);
				
				FCouriersPackage package = FalconCouriersUtils.getCouriersPackagesDetailsByName(packageName);
				int buyPrice = package.getBuyPrice();
				
				if (FalconCouriersUtils.getPlayerMoneyBalance(player) >= buyPrice)
				{
					ItemBase item = ItemBase.Cast(player.GetInventory().CreateInInventory(packageName));
					
					if (item)
					{
						FalconCouriersUtils.takeMoney(player, buyPrice);
					}
				}
				else
				{
					CouriersMessagesUtils.messageClient(CouriersMessagesConsts.NOT_ENOUGHT_MONEY_TO_BUY, player);
				}
			}
       	}
    }
	
	void takePackage(string packageName) {		
		GetRPCManager().SendRPC( "FalconCouriers", "takePackageS", new Param1<string>(packageName) );
	}
	
	private void getCouriersLocationsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1 != "")
			{
				string packageName = data.param1;
				
				array<ref CourierLocation> locations = new array<ref CourierLocation>();
				
				locations = FalconCouriersUtils.getBuyerCouriersLocations(packageName);
				
				GetRPCManager().SendRPC("FalconCouriers", "getCouriersLocationsC", new Param1<array<ref CourierLocation>>(locations), true,  sender);
			}
       	}
    }
	
	void getCouriersLocations(string packageName) {		
		GetRPCManager().SendRPC( "FalconCouriers", "getCouriersLocationsS", new Param1<string>(packageName) );
	}
}