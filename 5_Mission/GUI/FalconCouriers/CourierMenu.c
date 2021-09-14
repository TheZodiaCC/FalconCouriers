class CourierMenu extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;
	
	private int courierId;

	private TextWidget courierNameTEXT;
	
	private TextWidget priceTEXT;
	private TextWidget rewardTEXT; 
	
	private MultilineTextWidget packageDescriptionTEXT;
	private MapWidget couriersMAP;
	
	private TextListboxWidget takesPackagesLIST;
	private TextListboxWidget givesPackagesLIST;
	
	private ButtonWidget giveBUTTON;
	private ButtonWidget takeBUTTON;
	
	private ref Timer buttonsTimer = new Timer(CALL_CATEGORY_SYSTEM);

	ref CourierMenuBack courierMenuBack;
	
	//Constructor
	void CourierMenu() {	
		courierMenuBack = new ref CourierMenuBack();
		
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierNameC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesTakesDetailsC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCourierPackagesGivesDetailsC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconCouriers", "getCouriersLocationsC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~CourierMenu() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );

		delete courierMenuBack;
		
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconCouriers/GUI/Layouts/CourierMonitor.layout");
			
			couriersMAP = MapWidget.Cast(widgetRoot.FindAnyWidget("CouriersMAP"));
			
			courierNameTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("CourierNameTEXT"));
			packageDescriptionTEXT = MultilineTextWidget.Cast(widgetRoot.FindAnyWidget("PackageDescriptionTEXT"));
			
			packageDescriptionTEXT.SetTextExactSize(5);
			
			priceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("PriceTEXT"));
			rewardTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("RewardTEXT"));
			
			takesPackagesLIST = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("TakesPackagesLIST"));
			givesPackagesLIST = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("GivesPackagesLIST"));
			
			giveBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("GiveBUTTON")); 
			takeBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("TakeBUTTON")); 
			
			WidgetEventHandler.GetInstance().RegisterOnClick( takesPackagesLIST, this, "selectTakesPackage" );
			WidgetEventHandler.GetInstance().RegisterOnClick( givesPackagesLIST, this, "selectGivesPackage" );
			WidgetEventHandler.GetInstance().RegisterOnClick( takeBUTTON, this, "takePackage" );
			WidgetEventHandler.GetInstance().RegisterOnClick( giveBUTTON, this, "givePackage" );
			
			widgetRoot.Show(false);
			
			isInitialized = true;
		}
		
		return widgetRoot;		
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0.5);
		lockControls();
		initWidgets();
    }
	
	private void initWidgets() {
		courierNameTEXT.SetText("");
		priceTEXT.SetText("");
		rewardTEXT.SetText("");
		packageDescriptionTEXT.SetText("");
		takesPackagesLIST.ClearItems();
		givesPackagesLIST.ClearItems();
		
		updatePackages();
	}
	
	private void updatePackages()
	{
		takesPackagesLIST.ClearItems();
		givesPackagesLIST.ClearItems();
		couriersMAP.ClearUserMarks();	
		
		getCourierName(courierId);
		getCourierPackages(courierId);
		
		markOwnedPackages();
	}
	
	void setCourierId(int value) {
        courierId = value;
    }
	
	int getCourierId() {
        return courierId;
    }
	
	void setMenuOpened(bool state) {
        isMenuOpen = state;
        if (isMenuOpen)
		{
			PPEffects.SetBlurMenu(0.5);
		}
        else
		{
			PPEffects.SetBlurMenu(0);
		}
    }
	
	bool isMenuOpened() {
        return isMenuOpen;
    }
	
	private void lockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void unlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
	
	private void markOwnedPackages()
	{
		array<string> givesPackages = new array<string>();
		array<string> takesPackages = new array<string>();
		string tmp;
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		ItemBase package;
		
		for (int i = 0; i < takesPackagesLIST.GetNumItems(); i++)
		{
			takesPackagesLIST.GetItemText(i, 0, tmp);
			takesPackages.Insert(tmp);
		}
		
		for (int k = 0; k < givesPackagesLIST.GetNumItems(); k++)
		{
			givesPackagesLIST.GetItemText(k, 0, tmp);
			givesPackages.Insert(tmp);
		}
		
		for (int j = 0; j < takesPackages.Count(); j++)
		{
			package = FalconCouriersUtils.getPackageFromInventory(player, takesPackages[j]);
			
			if (package)
			{
				takesPackagesLIST.SetItemColor(j, 0, ARGB(255, 0, 255, 0));
			}
			else
			{
				takesPackagesLIST.SetItemColor(j, 0, ARGB(255, 255, 255, 255));
			}
		}
		
		for (int c = 0; c < givesPackages.Count(); c++)
		{
			package = FalconCouriersUtils.getPackageFromInventory(player, givesPackages[c]);
			
			if (package)
			{
				givesPackagesLIST.SetItemColor(c, 0, ARGB(255, 0, 255, 0));
			}
			else
			{
				givesPackagesLIST.SetItemColor(c, 0, ARGB(255, 255, 255, 255));
			}
		}
	}
	
	private void setPackageDescription(ItemBase package)
	{
		packageDescriptionTEXT.SetText(package.GetTooltip());
	}
	
	private void getCourierNameC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				courierNameTEXT.SetText(data.param1);
			}
		}
	}
	
	private void getCourierName(int courierId) {
		courierMenuBack.getCourierName(courierId);
	}
	
	private void getCourierPackagesC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<CourierPackagesRPCPackage> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				CourierPackagesRPCPackage package = data.param1;
				
				array<string> givesPackages = new array<string>();
				array<string> takesPackages = new array<string>();
				
				givesPackages = package.givesPackages;
				takesPackages = package.takesPackages;
				
				for (int i = 0; i < givesPackages.Count(); i++)
				{
					givesPackagesLIST.AddItem(givesPackages[i], null, 0);
				}
				
				for (int j = 0; j < takesPackages.Count(); j++)
				{
					takesPackagesLIST.AddItem(takesPackages[j], null, 0);
				}
				
				markOwnedPackages();
			}
		}
	}
	
	private void getCourierPackages(int courierId) {
		courierMenuBack.getCourierPackages(courierId);
	}
	
	private void getCourierPackagesTakesDetailsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<FCouriersPackage> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				FCouriersPackage package = data.param1;
				
				priceTEXT.SetText(package.getSellPrice().ToString());
				
				ItemBase item = ItemBase.Cast(GetGame().CreateObject(package.getName(), vector.Zero, true, false));
	
				if (item)
				{
					setPackageDescription(item);
				} 
			}
		}
	}
	
	private void getCourierPackagesTakesDetails(string packageName) {
		courierMenuBack.getCourierPackagesTakesDetails(packageName);
	}
	
	private void getCourierPackagesGivesDetailsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<FCouriersPackage> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				FCouriersPackage package = data.param1;
				
				rewardTEXT.SetText(package.getBuyPrice().ToString());
				
				ItemBase item = ItemBase.Cast(GetGame().CreateObject(package.getName(), vector.Zero, true, false));
	
				if (item)
				{
					setPackageDescription(item);
				}
			}
		}
	}
	
	private void getCourierPackagesGivesDetails(string packageName) {
		courierMenuBack.getCourierPackagesGivesDetails(packageName);
	}
	
	private void getCouriersLocationsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<array<ref CourierLocation>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				array<ref CourierLocation> locations = new array<ref CourierLocation>();
				locations = data.param1;
				
				for (int i = 0; i < locations.Count(); i++)
				{
					couriersMAP.AddUserMark( locations[i].courierPos, locations[i].courierName, ARGB( 255, 230, 20, 20 ), "gui\textures\dot.paa" );
				}
			}
		}
	}
	
	private void getCouriersLocations(string packageName) {
		courierMenuBack.getCouriersLocations(packageName);
	}
	
	private void selectTakesPackage() {
		int ind = takesPackagesLIST.GetSelectedRow();
		
		if (ind >= 0)
		{
			string packageName;
			
			takesPackagesLIST.GetItemText(ind, 0, packageName);
			
			getCourierPackagesTakesDetails(packageName);	
		}
	}
	
	private void selectGivesPackage() {
		int ind = givesPackagesLIST.GetSelectedRow();
		
		if (ind >= 0)
		{
			string packageName;
		
			givesPackagesLIST.GetItemText(ind, 0, packageName);
			
			getCourierPackagesGivesDetails(packageName);
			
			couriersMAP.ClearUserMarks();
			getCouriersLocations(packageName);
		}
	}
	
	private void takePackage() {
		if (!buttonsTimer.IsRunning())
		{
			int ind = givesPackagesLIST.GetSelectedRow();
			
			if (ind >= 0)
			{
				string packageName;
				givesPackagesLIST.GetItemText(ind, 0, packageName);
				
				courierMenuBack.takePackage(packageName);
		
				updatePackages();
			
				startButtonsTimer();
			}
		}
	}
	
	private void givePackage() {
		if (!buttonsTimer.IsRunning())
		{
			int ind = takesPackagesLIST.GetSelectedRow();
			
			if (ind >= 0)
			{
				string packageName;
				takesPackagesLIST.GetItemText(ind, 0, packageName);
				
				courierMenuBack.givePackage(packageName);
			
				updatePackages();
				
				startButtonsTimer();
			}
		}
	}
	
	void startButtonsTimer()
	{
		buttonsTimer.Run(1, null, "");
	}
}
	
	
