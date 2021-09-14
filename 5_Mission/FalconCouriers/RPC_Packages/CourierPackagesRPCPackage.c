class CourierPackagesRPCPackage
{
	ref array<string> takesPackages = new array<string>();
	ref array<string> givesPackages = new array<string>();
	
	
	void CourierPackagesRPCPackage(array<string> takesPackages, array<string> givesPackages)
	{
		this.takesPackages = takesPackages;
		this.givesPackages = givesPackages;
	}
}