class CfgPatches
{
	class FalconCouriers
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};
};

class CfgMods
{
	class FalconCouriers
	{
	    dir = FalconCouriers
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconCouriers
	    credits = "";
	    author = "zNitche";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "Mission" };

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconCouriers/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconCouriers/5_Mission"};
			};
		};
	};
};

class CfgVehicles
{
	class SurvivorMale_Base;

	class FalconCourierTaki: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "MaleTaikiHead";
		emptyBody = "MaleTaikiTorso";
		emptyLegs = "MaleTaikiLegs";
		emptyFeet = "MaleTaikiFeet";
		emptyGloves = "MaleTaikiHands";
		faceType = "MaleTaikiHead";
		decayedTexture = "\DZ\characters\heads\data\m_Taiki\hhl_m_Taiki_body_shaved_decayed_co.paa";
		class BloodyHands
		{
			mat_normal = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat";
			mat_blood = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bloodyhands.rvmat";
		};
		class Lifespan
		{
			class Beard
			{
				mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard_ca.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard.rvmat"};
			};
		};
		class Wounds
		{
			tex[] = {};
			mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury2.rvmat"};
		};
		voiceType = 2;
	};

	class Inventory_Base;
	class NormalPackage: Inventory_Base
	{
		scope = 2;
		displayName = "Normal Package";
		descriptionShort = "Lorem Ipsum";
		model="\dz\gear\containers\Protector_Case.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class SmallPackage: Inventory_Base
	{
		scope = 2;
		displayName = "Small Package";
		descriptionShort = "Lorem Ipsum";
		model="\dz\gear\containers\Protector_Case.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class HeavyPackage: Inventory_Base
	{
		scope = 2;
		displayName = "Heavy Package";
		descriptionShort = "Lorem Ipsum";
		model="\dz\gear\containers\Protector_Case.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};
};
