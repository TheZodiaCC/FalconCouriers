class FalconCouriersUtils
{	
	const static string couriersDataPath = CouriersConsts.COURIERS_DATA_DIR_PATH;
	const static string couriersPackagesDetailsPath = CouriersConsts.COURIERS_PACKAGES_DATA_PATH;
	const static string coinName = CouriersConsts.COIN_ITEM_NAME;
	
	
	static ref array<ref FalconCourierCharacterData> getCouriersData() 
	{
		ref array<ref FalconCourierCharacterData> couriersData = new ref array<ref FalconCourierCharacterData>();
		
		JsonFileLoader<ref array<ref FalconCourierCharacterData>>.JsonLoadFile(couriersDataPath, couriersData);
		
		return couriersData;
	}
	
	static ref array<ref FCouriersPackage> getCourierPackagesDetails() {
		ref array<ref FCouriersPackage> courierPackagesDetails = new ref array<ref FCouriersPackage>();
		
		JsonFileLoader<ref array<ref FCouriersPackage>>.JsonLoadFile(couriersPackagesDetailsPath, courierPackagesDetails);
		
		return courierPackagesDetails;
	}
	
	static FCouriersPackage getCouriersPackagesDetailsByName(string packageName) 
	{
		ref array<ref FCouriersPackage> courierPackagesDetails = new ref array<ref FCouriersPackage>();
		FCouriersPackage package;
		
		courierPackagesDetails = getCourierPackagesDetails();
		
		for (int i = 0; i < courierPackagesDetails.Count(); i++)
		{
			if (courierPackagesDetails[i].getName() == packageName)
			{
				package = courierPackagesDetails[i];
			}
		}
		
		return package;
	}
	
	static array<string> getCourierGivesPackages(int courierId) 
	{
		array<string> packages = new array<string>();
		
		FalconCourierCharacterData courierData = getCouriersDataById(courierId);
		
		packages = courierData.getGivesPackages();
		
		return packages;
	}
	
	static array<string> getCourierTakesPackages(int courierId) 
	{
		array<string> packages = new array<string>();
		
		FalconCourierCharacterData courierData = getCouriersDataById(courierId);
		
		packages = courierData.getTakesPackages();
		
		return packages;
	}
	
	static FalconCourierCharacterData getCouriersDataById(int courierId) {
		ref array<ref FalconCourierCharacterData> couriersData = new ref array<ref FalconCourierCharacterData>();
		
		couriersData = getCouriersData();
		
		FalconCourierCharacterData courierData;
		
		for (int i = 0; i < couriersData.Count(); i++)
		{
			if (courierId == couriersData[i].getCourierId())
			{
				courierData = couriersData[i];
				break;
			}	
		}
		
		return courierData;
	}
	
	static void initCouriers() 
	{
		ref array<ref FalconCourierCharacterData> couriersData = new ref array<ref FalconCourierCharacterData>();
		
		couriersData = getCouriersData();
		
		for (int i = 0; i < couriersData.Count(); i++)
		{
			FalconCourier courier = FalconCourier.Cast(GetGame().CreateObject(couriersData[i].getCourierType(), couriersData[i].getCourierSpawnPoint().ToVector(), false, false));
			
			courier.SetDirection(couriersData[i].getCourierDirection().ToVector());
			courier.SetAllowDamage(false);
			courier.setCourierId(couriersData[i].getCourierId());
			
			courier.setMaxHumanity(couriersData[i].getMaxHumanity());
			courier.setMinHumanity(couriersData[i].getMinHumanity());
			
			courier.GetInventory().CreateInInventory(couriersData[i].getCourierHead());
			courier.GetInventory().CreateInInventory(couriersData[i].getCourierBody());
			courier.GetInventory().CreateInInventory(couriersData[i].getCourierPants());
			courier.GetInventory().CreateInInventory(couriersData[i].getCourierBoots());
		}
	}
	
	static PlayerBase getPlayerByIdentity(PlayerIdentity identity)
	{
	    int highBits, lowBits;
	
	    if (!GetGame().IsMultiplayer())
	        return PlayerBase.Cast(GetGame().GetPlayer());
	
	    if (identity == null)
	        return null;
	
	    GetGame().GetPlayerNetworkIDByIdentityID(identity.GetPlayerId(), lowBits, highBits);
			
	    return PlayerBase.Cast(GetGame().GetObjectByNetworkId(lowBits, highBits));
	}
	
	private static array<string> getBodyParts()
	{
		array<string> bodyParts = new array<string>();
		
		bodyParts.Insert("Body");
		bodyParts.Insert("Back");
		bodyParts.Insert("Vest");
		bodyParts.Insert("Legs");
		
		return bodyParts;
	}
	
	static int getPlayerMoneyBalance(PlayerBase player)
	{
		int moneyBalance = 0;
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					//Getting Goldcoin class name from var doesnt work, dunno why
					if (item.ClassName() == "Goldcoin")
					{
						moneyBalance += item.GetQuantity();
					}
				}
			}
		}
		
		return moneyBalance;
	}
	
	static ItemBase getPackageFromInventory(PlayerBase player, string packageName)
	{
		ItemBase bodyPart;
		ItemBase package;
		array<string> bodyParts = new array<string>();
		array<string> emptyBodyParts = new array<string>();
		
		package = ItemBase.Cast(player.GetItemInHands());
		
		if (package)
		{			
			if (package.ClassName() == packageName)
			{
				return package;
			}
		}
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{				
					package = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (package)
					{
						if (package.ClassName() == packageName)
						{
							return package;
						}
					}
				}
			}
		}
		
		return null;
	}
	
	private static array<ItemBase> getItemsFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		array<ItemBase> items = new array<ItemBase>();
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item.ClassName() == itemName)
					{
						items.Insert(item);
					}
				}
			}
		}
		
		return items;
	}
	
	static void addMoney(PlayerBase player, int sellPrice)
	{
		int maxMoneyQuantity = (ItemBase.Cast(GetGame().CreateObject(coinName, vector.Zero, true, false))).GetQuantityMax();
		int restMoney = sellPrice;
		ItemBase money;
		
		if (restMoney < maxMoneyQuantity)
		{
			money = ItemBase.Cast(player.GetInventory().CreateInInventory(coinName));
			money.SetQuantity(restMoney);
		}
		else
		{
			while (restMoney > 0)
			{
				money = ItemBase.Cast(player.GetInventory().CreateInInventory(coinName));
				money.SetQuantity(restMoney);
				
				restMoney -= maxMoneyQuantity;
			}
		}
	}
	
	static void takeMoney(PlayerBase player, int buyPrice)
	{
		array<ItemBase> moneyItems = new array<ItemBase>();
		moneyItems = getItemsFromInventory(player, coinName);
		int restMoney = buyPrice;
		
		int maxMoneyQuantity = (ItemBase.Cast(GetGame().CreateObject(coinName, vector.Zero, true, false))).GetQuantityMax();
		int moneyQuantity;
		
		while (restMoney > 0)
		{
			for (int i = 0; i < moneyItems.Count(); i++)
			{
				moneyQuantity = moneyItems[i].GetQuantity();
				
				if (restMoney >= moneyQuantity)
				{
					moneyItems[i].SetQuantity(0);
					
					restMoney -= moneyQuantity; 
				}
				else
				{
					moneyItems[i].SetQuantity(moneyQuantity - restMoney);
					
					restMoney = 0;
				}
			}
		}
	}
	
	static array<ref CourierLocation> getBuyerCouriersLocations(string packageName)
	{
		array<ref CourierLocation> locations = new array<ref CourierLocation>();
		array<ref FalconCourierCharacterData> couriersData = new array<ref FalconCourierCharacterData>();
		
		couriersData = getCouriersData();
		
		for (int i = 0; i < couriersData.Count(); i++)
		{
			if (checkIfCourierHasPackage(couriersData[i], packageName))
			{
				locations.Insert(new CourierLocation(couriersData[i].getCourierName(), couriersData[i].getCourierSpawnPoint().ToVector()));
			}
		}
		
		return locations;
	}
	
	private static bool checkIfCourierHasPackage(FalconCourierCharacterData courierData, string packageName)
	{
		array<string> packages = new array<string>();
		
		packages = courierData.getTakesPackages();
		
		for (int i = 0; i < packages.Count(); i++)
		{
			if (packages[i] == packageName)
			{
				return true;
			}
		}
		
		return false;
	}
}