// Fill out your copyright notice in the Description page of Project Settings.

#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/Public/NexusSampleProjectGlobals.h"
//#include "NexusPrototype.h"
//#include "NexusUnrealSDK.h"
#include "HttpModule.h"
#include "HttpManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNexusUESDKTest, Log, All);
DEFINE_LOG_CATEGORY(LogNexusUESDKTest);

BEGIN_DEFINE_SPEC(FNexusUESDKTestSpec, "Nexus.AutomationTests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

// Add variables here 
//NexusSDK::FOnGetCatFactsComplete OnGetCatFactsComplete;
//NexusSDK::FOnGetCreatorsComplete OnGetCreatorsComplete;

FString PublicApiKey = TEXT("nexus_pk_7784c3faa6e94c1fad8aceab27ab31e6"); // #TODO: REMOVE ME

// PLACEHOLDER VARIABLES // PLACEHOLDER VARIABLES // PLACEHOLDER VARIABLES //
//NexusSDK::FOnGetCreatorsComplete OnGetCreatorsComplete;
//NexusSDK::FGetCreatorByUuidComplete OnGetCreatorsByUuidComplete;
//NexusSDK::FGetPingComplete OnGetPingComplete;
//NexusSDK::FGetReferralInfoByPlayerIdComplete OnGetReferralInfoComplete;
//NexusSDK::FGetReferralInfoByCodeComplete OnGetReferralCodeComplete;
//NexusSDK::FGetPlayerCurrentReferralComplete OnGetReferralInfoByCodeComplete;
//NexusSDK::FOnGetBountyProgressComplete OnGetBountyProgressComplete;
// PLACEHOLDER VARIABLES // PLACEHOLDER VARIABLES // PLACEHOLDER VARIABLES //

float DeltaTime = 0.2f;
// Add variables here 

END_DEFINE_SPEC(FNexusUESDKTestSpec);

void WaitForResponse(bool& Condition, float Timeout, FString InMessage)
{
	float TimeoutCounter = 0;
	
	while (!Condition) 
	{
		if (TimeoutCounter >= Timeout)
		{
			UE_LOG(LogNexusUESDKTest, Error, TEXT("Request timed out!"));
			break;
		}
		
		FPlatformProcess::Sleep(0.2f);
		FHttpModule::Get().GetHttpManager().Tick(0.2f);

		if (!InMessage.IsEmpty())
		{
			UE_LOG(LogNexusUESDKTest, Log, TEXT("%s"), *InMessage);
		}

		TimeoutCounter += 0.2f;
	}
}

void FNexusUESDKTestSpec::Define()
{
	Describe("A_Setup", [this]
	{
		It("A_Should perform setup for automation testing", [this]
		{
			// Add any setup or init here
			return true;
		});
	});

	/*
	Describe("B_Unreal SDK Prototype Tests", [this]
	{
		It("A_'GetCatFacts' Should retrieve cat facts with valid data", [this]
		{
			bool bGetCatFactsDone = false;
			bool bGetCatFactsSuccess = false;
			TArray<FString> FactList;

			NexusSDK::FGetCatFactsRequest GetCatFactsRequest;
			GetCatFactsRequest.MaxLength = 32;
			GetCatFactsRequest.Limit = 32;

			// Bind lambda and assign flags appropriately
			OnGetCatFactsComplete.BindLambda(
				[this, &bGetCatFactsDone, &bGetCatFactsSuccess, &FactList](const NexusSDK::FGetCatFactsResponse& Response)
				{
					FactList = Response.Facts;
					bGetCatFactsSuccess = Response.bSuccess;
					bGetCatFactsDone = true;
				});

			// Request GetCatFacts 
			NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetCatFactsComplete);

			// Wait for response
			WaitForResponse(bGetCatFactsDone, 5.0f, TEXT("Waiting to retrieve cat facts..."));

			// Test success
			TestTrue(TEXT("GetCatFacts response should be successful"), bGetCatFactsSuccess);

			// Test content
			for (FString& Fact : FactList) 
			{
				TestTrue(TEXT("Fact in FactList should not be empty"), !Fact.IsEmpty());
			}

			return true;
		});
	});
	*/

	Describe("C_Nexus Attribution API", [this]
	{
		// https://app.swaggerhub.com/apis-docs/nexus-gg/Attribution/1.5.1#/attribution%20creators/getCreators
		It("A_GetCreators", [this]
		{
			/*
			bool bGetCreatorsDone = false;
			bool bGetCreatorsSuccess = false;
			NexusSDK::FGetCreatorsResponse OutData;
			
			OnGetCreatorsComplete.BindLambda(
				[this, &bGetCreatorsDone, &bGetCreatorsSuccess, &OutData](const NexusSDK::FGetCreatorsResponse& Response)
				{	
					OutData = Response;
					bGetCreatorsSuccess = Response.bSuccess;
					bGetCreatorsDone = true;
				});
			
			NexusSDK::FGetCreatorsRequest GetCreatorsRequest;
			GetCreatorsRequest.GroupId = TEXT("");
			GetCreatorsRequest.Page = 1;
			GetCreatorsRequest.PageSize = 1;
			GetCreatorsRequest.PublicKey = PublicApiKey;

			// Request GetCreators
			NexusSDK::GetCreators(GetCreatorsRequest, OnGetCreatorsComplete);

			// Wait for response
			WaitForResponse(bGetCreatorsDone, 5.0f, TEXT("Waiting to retrieve all creators and their creator details..."));

			// Test success
			TestTrue(TEXT("GetCreators should be successful"), bGetCreatorsSuccess);

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);

			// Test content (creator data)
			for (FCreatorInfo Creator : OutData.Creators) 
			{
				TestTrue(TEXT("Creator Id should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator Name should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator LogoImage should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator NexusURL should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator ProfileImage should not be empty"), !Creator.Id.IsEmpty());
			}
			*/
			return true;
		});

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Attribution/1.5.1#/attribution%20creators/getCreatorByUuid
		It("A_GetCreators by slug or UUID", [this]
		{
			/*
			bool bGetCreatorsDone = false;
			bool bGetCreatorsSuccess = false;
			
			OnGetCreatorsByUuidComplete.BindLambda(
				[this, &bGetCreatorsDone, &bGetCreatorsSuccess](const NexusSDK::FGetCreatorsResponse& Response)
				{
					bGetCreatorsSuccess = Response.bSuccess;
					bGetCreatorsDone = true;
				});
			
			NexusSDK::GetCreatorByUuid GetCreatorsRequest;
			GetCreatorsRequest.Slug = TEXT("");
			GetCreatorsRequest.Id = TEXT("");
			GetCreatorsRequest.Page = 1;
			GetCreatorsRequest.PageSize = 1;
			GetCreatorsRequest.PublicKey = PublicApiKey;

			// Request GetCreators
			NexusSDK::GetCreatorByUuid(GetCreatorsRequest, OnGetCreatorsByUuidComplete);

			// Wait for response
			WaitForResponse(bGetCreatorsDone, 5.0f, TEXT("Waiting to retrieve creator information by slug or UUID..."));

			// Test success
			TestTrue(TEXT("GetCreators should be successful"), bGetCreatorsSuccess);

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);

			// Test content (creator data)
			for (FCreatorInfo Creator : OutData.Creators)
			{
				TestTrue(TEXT("Creator Id should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator Name should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator LogoImage should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator NexusURL should not be empty"), !Creator.Id.IsEmpty());
				TestTrue(TEXT("Creator ProfileImage should not be empty"), !Creator.Id.IsEmpty());
			}
			*/
			return true;
		});

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Attribution/1.5.1#/attribution%20health/get_ping
		It("A_GetPing", [this]
		{
			/*
			bool bGetPingDone = false;
			bool bGetPingSuccess = false;
			int32 OutPingRate = -1;

			OnGetPingComplete.BindLambda(
				[this, &bGetPingDone, &bGetPingSuccess, &OutPingRate](const int32& PingRate, bool bWasSuccessful)
				{
					OutPingRate = PingRate;
					bGetPingSuccess = bWasSuccessful;
					bGetPingDone = true;
				});

			// Request ping
			NexusSDK::GetPing();

			// Wait for response
			WaitForResponse(bGetPingDone, 5.0f, TEXT("Waiting to retrieve ping..."));

			// Test content
			TestTrue(TEXT("Ping should not be -1"), OutPingRate != -1);
			*/
			return true;
		});
	});

	Describe("C_Nexus Referral API", [this]
	{
		// https://app.swaggerhub.com/apis-docs/nexus-gg/Referral/1.0.0#/monitor/getReferralInfoByPlayerId
		It("A_GetReferralInfo by playerId", [this]
		{
			/*
			bool bGetReferralInfoDone = false;
			bool bGetReferralInfoSuccess = false;
			NexusSDK::FGetReferralInfoResponse OutData;

			NexusSDK::FGetReferralInfoByPlayerIdRequest GetReferralInfoRequest;
			GetReferralInfoRequest.PlayerId = TEXT("ABCD1234");

			OnGetReferralInfoComplete.BindLambda(
				[this, &bGetReferralInfoDone, &bGetReferralInfoSuccess, &OutData](const FGetReferralInfoResponse& Response, bool bWasSuccessful)
				{
					OutData = Response;
					bGetReferralInfoSuccess = bWasSuccessful;
					bGetReferralInfoDone = true;
				});
			
			// Request referral info by player id
			NexusSDK::GetReferralInfoByPlayerId(GetReferralInfoRequest, OnGetReferralInfoComplete);

			// Wait for response
			WaitForResponse(bGetReferralInfoDone, 5.0f, TEXT("Waiting to retrieve referral info by Player Id..."));

			// Test success
			TestTrue(TEXT("Get referral info should be successful"), bGetReferralInfoSuccess);

			// Test content (group name and Id)
			TestTrue(TEXT("GroupId should not be empty"), !OutData.GroupId.IsEmpty());
			TestTrue(TEXT("GroupName should not be empty"), !OutData.GroupName.IsEmpty());

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);
			TestTrue(TEXT("TotalCount of referrals should be greater than 0"), OutData.TotalCount > 0);

			// Test content (referral codes)
			for (FReferralCodeInfo ReferralCode : OutData.ReferralCodes) 
			{
				TestTrue(TEXT("ReferralCode should not be empty"), !ReferralCode.Code.IsEmpty());
			}

			// Test content (player info)
			TestTrue(TEXT("PlayerId should not be empty"), !OutData.PlayerId.IsEmpty());

			// Test content (referrals)
			for (FReferralInfo Referral : OutData.Referrals) 
			{
				TestTrue(TEXT("Referral Id should not be empty"), !Referral.Id.IsEmpty());
				TestTrue(TEXT("Referral Code should not be empty"), !Referral.Code.IsEmpty());
				TestTrue(TEXT("Referral PlayerId should not be empty"), !Referral.PlayerId.IsEmpty());
				TestTrue(TEXT("Referral PlayerName should not be empty"), !Referral.PlayerName.IsEmpty());
				TestTrue(TEXT("Referral Date should not be empty"), !Referral.ReferralDate.IsEmpty());
			}
			*/
			return true;
		});

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Referral/1.0.0#/monitor/getReferralInfoByCode
		It("B_GetReferralInfo by code", [this]
		{
			/*
			bool bGetReferralInfoDone = false;
			bool bGetReferralInfoSuccess = false;
			NexusSDK::FGetReferralInfoResponse OutData;

			NexusSDK::FGetReferralInfoByCodeRequest GetReferralInfoByCodeRequest;
			GetReferralInfoByCodeRequest.ReferralCode = TEXT("ABCD1234");

			OnGetReferralInfoByCodeComplete.BindLambda(
				[this, &bGetReferralInfoDone, &bGetReferralInfoSuccess, &OutData](const FGetReferralInfoResponse& Response, bool bWasSuccessful)
				{
					OutData = Response;
					bGetReferralInfoSuccess = bWasSuccessful;
					bGetReferralInfoDone = true;
				});
			
			// Request referral info by creator code
			NexusSDK::GetReferralInfoByCode(GetReferralInfoByCodeRequest, OnGetReferralInfoByCodeComplete);

			// Wait for response
			WaitForResponse(bGetReferralInfoDone, 5.0f, TEXT("Waiting to retrieve referral info by creator code..."));

			// Test success
			TestTrue(TEXT("Get referral info should be successful"), bGetReferralInfoSuccess);

			// Test content (group name and Id)
			TestTrue(TEXT("GroupId should not be empty"), !OutData.GroupId.IsEmpty());
			TestTrue(TEXT("GroupName should not be empty"), !OutData.GroupName.IsEmpty());

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);
			TestTrue(TEXT("TotalCount of referrals should be greater than 0"), OutData.TotalCount > 0);

			// Test content (referral codes)
			for (FReferralCodeInfo ReferralCode : OutData.ReferralCodes) 
			{
				TestTrue(TEXT("ReferralCode should not be empty"), !ReferralCode.Code.IsEmpty());
			}

			// Test content (player info)
			TestTrue(TEXT("PlayerId should not be empty"), !OutData.PlayerId.IsEmpty());

			// Test content (referrals)
			for (FReferralInfo Referral : OutData.Referrals) 
			{
				TestTrue(TEXT("Referral Id should not be empty"), !Referral.Id.IsEmpty());
				TestTrue(TEXT("Referral Code should not be empty"), !Referral.Code.IsEmpty());
				TestTrue(TEXT("Referral PlayerId should not be empty"), !Referral.PlayerId.IsEmpty());
				TestTrue(TEXT("Referral PlayerName should not be empty"), !Referral.PlayerName.IsEmpty());
				TestTrue(TEXT("Referral Date should not be empty"), !Referral.ReferralDate.IsEmpty());
			}
			*/
			return true;
		});

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Referral/1.0.0#/monitor/getPlayerCurrentReferral
		It("C_GetReferralCode used by playerId", [this]
		{
			/*
			bool bGetReferralCodeDone = false;
			bool bGetReferralCodeSuccess = false;
			FString OutReferralCode;

			NexusSDK::FGetPlayerCurrentReferralRequest GetReferralCodeRequest;
			GetReferralCodeRequest.PlayerId = TEXT("ABCD1234");

			OnGetReferralInfoComplete.BindLambda(
				[this, &bGetReferralCodeDone, &bGetReferralCodeSuccess, &OutData](const FString& ReferralCode, bool bWasSuccessful)
				{
					OutReferralCode = ReferralCode;
					bGetReferralCodeSuccess = bWasSuccessful;
					bGetReferralCodeDone = true;
				});
			
			// Request referral code by player id
			NexusSDK::GetPlayerCurrentReferral(GetReferralCodeRequest, OnGetReferralCodeComplete);

			// Wait for response
			WaitForResponse(bGetReferralCodeDone, 5.0f, TEXT("Waiting to retrieve referral code by Player Id..."));

			// Test success
			TestTrue(TEXT("Get referral code should be successful"), bGetReferralCodeSuccess);

			// Test content (code)
			TestTrue(TEXT("Referral code should not be empty"), !OutReferralCode.IsEmpty());
			*/
			return true;
		});
	});

	Describe("C_Nexus Bounty API", [this]
	{
		// https://app.swaggerhub.com/apis-docs/nexus-gg/Bounty/1.0.0#/monitor/getBounties
		It("A_GetBounties", [this]
		{
			/*
			bool bGetBountiesDone = false;
			bool bGetBountiesSuccess = false;
			NexusSDK::FGetBountiesResponse OutData;

			OnGetReferralInfoComplete.BindLambda(
				[this, &bGetBountiesDone, &bGetBountiesSuccess, &OutData](NexusSDK::FGetBountiesResponse Response, bool bWasSuccessful)
				{
					OutData = Response;
					bGetBountiesSuccess = bWasSuccessful;
					bGetBountiesDone = true;
				});
			
			// Get list of bounties
			NexusSDK::GetBounties(NexusSDK::FGetBountiesRequest(), OnGetBountiesComplete);

			// Wait for response
			WaitForResponse(bGetBountiesDone, 5.0f, TEXT("Waiting to retrieve the list of available bounties..."));

			// Test success
			TestTrue(TEXT("Get bounties should be successful"), bGetBountiesSuccess);

			// Test content (group name and Id)
			TestTrue(TEXT("GroupId should not be empty"), !OutData.GroupId.IsEmpty());
			TestTrue(TEXT("GroupName should not be empty"), !OutData.GroupName.IsEmpty());

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);
			TestTrue(TEXT("TotalCount of referrals should be greater than 0"), OutData.TotalCount > 0);

			// Test content (code)
			TestTrue(TEXT("Referral code should not be empty"), !OutReferralCode.IsEmpty());

			// Test bounties
			for (FBountyInfo Bounty : OutData.Bounties)
			{
				TestTrue(TEXT("Bounty Id should not be empty"), !Bounty.Id.IsEmpty());
				TestTrue(TEXT("Bounty name should not be empty"), !Bounty.Name.IsEmpty());
				TestTrue(TEXT("Bounty description should not be empty"), !Bounty.Description.IsEmpty());
				TestTrue(TEXT("Bounty imageSrc not be empty"), !Bounty.ImageSrc.IsEmpty());
				TestTrue(TEXT("Bounty rewardDescription should not be empty"), !Bounty.RewardDescription.IsEmpty());
				TestTrue(TEXT("Bounty limit should be greater than 0"), Bounty.Limit > 0);
				TestTrue(TEXT("Bounty startsAt time should be valid"), Bounty.StartsAt.Parse());
				TestTrue(TEXT("Bounty endsAt time should be valid"), Bounty.EndsAt.Parse());
				TestTrue(TEXT("Bounty lastProgressCheck time should be valid"), Bounty.LastProgressCheck.Parse());

				// Test each Bounty's Objectives
				for (FBountyObjective Objective : Bounty.Objectives)
				{
					TestTrue(TEXT("Bounty's Objective Id should not be empty"), !Objective.Id.IsEmpty());
					TestTrue(TEXT("Bounty's Objective name should not be empty"), !Objective.Name.IsEmpty());
					TestTrue(TEXT("Bounty's Objective type should not be empty"), !Objective.Type.IsEmpty());
					TestTrue(TEXT("Bounty's Objective condition should not be empty"), !Objective.Condition.IsEmpty());
					TestTrue(TEXT("Bounty's Objective count should be greater than 0"), Objective.Count > 0);
					TestTrue(TEXT("Bounty's Objective eventType should not be empty"), !Objective.EventType.IsEmpty());
					TestTrue(TEXT("Bounty's Objective eventCode should not be empty"), !Objective.EventCode.IsEmpty());
					TestTrue(TEXT("Bounty's Objective nexusPurchaseObjectiveType should not be empty"), !Objective.NexusPurchaseObjectiveType.IsEmpty());

					// Test each Bounty Objective's SKUs
					if (Objective.Type == NexusTypeEnum::NexusPurchase && NexusPurchaseObjectiveType::sku)
					{
						for (FNexusSKU Sku : Objective.Skus)
						{
							TestTrue(TEXT("Bounty Objective's Sku Id should not be empty"), !Sku.Id.IsEmpty());
							TestTrue(TEXT("Bounty Objective's Sku name should not be empty"), !Sku.Name.IsEmpty());
							TestTrue(TEXT("Bounty Objective's Sku slug should not be empty"), !Sku.Slug.IsEmpty());
						}
					}
					
					// Test Bounty Objective's category
					TestTrue(TEXT("Bounty's Objective category's id should not be empty"), !Objective.Category.Id.IsEmpty());
					TestTrue(TEXT("Bounty's Objective category's name should not be empty"), !Objective.Category.Name.IsEmpty());
					TestTrue(TEXT("Bounty's Objective category's slug should not be empty"), !Objective.Category.Slug.IsEmpty());

					// Test Bounty Objective's publisher
					TestTrue(TEXT("Bounty's Objective publisher's id should not be empty"), !Objective.Publisher.Id.IsEmpty());
					TestTrue(TEXT("Bounty's Objective publisher's name should not be empty"), !Objective.Publisher.Name.IsEmpty());
				}

				// Test each Bounty's rewards
				for (FBountyReward Reward : Bounty.Rewards) 
				{
					TestTrue(TEXT("Bounty Reward's id should not be empty"), !Reward.Id.IsEmpty());
					TestTrue(TEXT("Bounty Reward's name should not be empty"), !Reward.Name.IsEmpty());
					TestTrue(TEXT("Bounty Reward's type should not be empty"), !Reward.Type.IsEmpty());

					// Test each Bounty Reward's SKUs
					if (Reward.Type == NexusRewardsType::sku)
					{
						TestTrue(TEXT("Bounty Reward's Sku Id should not be empty"), !Reward.Sku.Id.IsEmpty());
						TestTrue(TEXT("Bounty Reward's Sku name should not be empty"), !Reward.Sku.Name.IsEmpty());
						TestTrue(TEXT("Bounty Reward's Sku slug should not be empty"), !Reward.Sku.Slug.IsEmpty());
					}

					TestTrue(TEXT("Bounty Reward's amount of currency should be greater than 0"), !Reward.Amount > 0);
					TestTrue(TEXT("Bounty Reward's currency code should not be empty"), !Reward.Currency.IsEmpty());
					TestTrue(TEXT("Bounty Reward's externalId should not be empty"), !Reward.ExternalId.IsEmpty());
				}

				// Test each Bounty's Dependants
				for (FBountyDependants Dependant : Bounty.Dependants)
				{
					TestTrue(TEXT("Bounty's Dependant's id should not be empty"), !Dependant.Id.IsEmpty());
					TestTrue(TEXT("Bounty's Dependant's name should not be empty"), !Dependant.Name.IsEmpty());
				}

				// Test each Bounty's prerequisites
				for (FBountyDependants Prerequisite : Bounty.Prerequisites)
				{
					TestTrue(TEXT("Bounty's Prerequisite's id should not be empty"), !Prerequisite.Id.IsEmpty());
					TestTrue(TEXT("Bounty's Prerequisite's name should not be empty"), !Prerequisite.Name.IsEmpty());
				}
			}
			*/
			return true;
		});

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Bounty/1.0.0#/monitor/getBounty
		It("A_GetBountyInformation by bountyId", [this]
		{
			/*
			bool bGetBountyInfoDone = false;
			bool bGetBountyInfoSuccess = false;
			NexusSDK::FGetBountyInfoResponse OutData;

			OnGetBountyInfoComplete.BindLambda(
				[this, &bGetBountyInfoDone, &bGetBountyInfoSuccess, &OutData](NexusSDK::FGetBountyInfoResponse Response, bool bWasSuccessful)
				{
					OutData = Response;
					bGetBountyInfoSuccess = bWasSuccessful;
					bGetBountyInfoDone = true;
				});

			NexusSDK::FGetBountyInfoRequest GetBountyInfoRequest;
			GetBountyInfoRequest.BountyId = TEXT("12345");
			
			// Request bounty information
			NexusSDK::GetBountyInfo(GetBountyInfoRequest, OnGetBountiesComplete);

			// Wait for response
			WaitForResponse(bGetBountyInfoDone, 5.0f, TEXT("Waiting to retrieve bounty info by bounty id..."));

			// Test success
			TestTrue(TEXT("Get bounty info should be successful"), bGetBountyInfoSuccess);

			// Test content (group name and Id)
			TestTrue(TEXT("GroupId should not be empty"), !OutData.GroupId.IsEmpty());
			TestTrue(TEXT("GroupName should not be empty"), !OutData.GroupName.IsEmpty());

			// Test bounty
			TestTrue(TEXT("Bounty Id should not be empty"), !OutData.Bounty.Id.IsEmpty());
			TestTrue(TEXT("Bounty name should not be empty"), !OutData.Bounty.Name.IsEmpty());
			TestTrue(TEXT("Bounty description should not be empty"), !OutData.Bounty.Description.IsEmpty());
			TestTrue(TEXT("Bounty imageSrc not be empty"), !OutData.Bounty.ImageSrc.IsEmpty());
			TestTrue(TEXT("Bounty rewardDescription should not be empty"), !OutData.Bounty.RewardDescription.IsEmpty());
			TestTrue(TEXT("Bounty limit should be greater than 0"), OutData.Bounty.Limit > 0);
			TestTrue(TEXT("Bounty startsAt time should be valid"), OutData.Bounty.StartsAt.Parse());
			TestTrue(TEXT("Bounty endsAt time should be valid"), OutData.Bounty.EndsAt.Parse());
			TestTrue(TEXT("Bounty lastProgressCheck time should be valid"), OutData.Bounty.LastProgressCheck.Parse());

			// Test each Bounty's Objectives
			for (FBountyObjective Objective : OutData.Bounty.Objectives)
			{
				TestTrue(TEXT("Bounty's Objective Id should not be empty"), !Objective.Id.IsEmpty());
				TestTrue(TEXT("Bounty's Objective name should not be empty"), !Objective.Name.IsEmpty());
				TestTrue(TEXT("Bounty's Objective type should not be empty"), !Objective.Type.IsEmpty());
				TestTrue(TEXT("Bounty's Objective condition should not be empty"), !Objective.Condition.IsEmpty());
				TestTrue(TEXT("Bounty's Objective count should be greater than 0"), Objective.Count > 0);
				TestTrue(TEXT("Bounty's Objective eventType should not be empty"), !Objective.EventType.IsEmpty());
				TestTrue(TEXT("Bounty's Objective eventCode should not be empty"), !Objective.EventCode.IsEmpty());
				TestTrue(TEXT("Bounty's Objective nexusPurchaseObjectiveType should not be empty"), !Objective.NexusPurchaseObjectiveType.IsEmpty());

				// Test each Bounty Objective's SKUs
				if (Objective.Type == NexusTypeEnum::NexusPurchase && NexusPurchaseObjectiveType::sku)
				{
					for (FNexusSKU Sku : Objective.Skus)
					{
						TestTrue(TEXT("Bounty Objective's Sku Id should not be empty"), !Sku.Id.IsEmpty());
						TestTrue(TEXT("Bounty Objective's Sku name should not be empty"), !Sku.Name.IsEmpty());
						TestTrue(TEXT("Bounty Objective's Sku slug should not be empty"), !Sku.Slug.IsEmpty());
					}
				}

				// Test Bounty Objective's category
				TestTrue(TEXT("Bounty's Objective category's id should not be empty"), !Objective.Category.Id.IsEmpty());
				TestTrue(TEXT("Bounty's Objective category's name should not be empty"), !Objective.Category.Name.IsEmpty());
				TestTrue(TEXT("Bounty's Objective category's slug should not be empty"), !Objective.Category.Slug.IsEmpty());

				// Test Bounty Objective's publisher
				TestTrue(TEXT("Bounty's Objective publisher's id should not be empty"), !Objective.Publisher.Id.IsEmpty());
				TestTrue(TEXT("Bounty's Objective publisher's name should not be empty"), !Objective.Publisher.Name.IsEmpty());
			}

			// Test each Bounty's rewards
			for (FBountyReward Reward : OutData.Bounty.Rewards)
			{
				TestTrue(TEXT("Bounty Reward's id should not be empty"), !Reward.Id.IsEmpty());
				TestTrue(TEXT("Bounty Reward's name should not be empty"), !Reward.Name.IsEmpty());
				TestTrue(TEXT("Bounty Reward's type should not be empty"), !Reward.Type.IsEmpty());

				// Test each Bounty Reward's SKUs
				if (Reward.Type == NexusRewardsType::sku)
				{
					TestTrue(TEXT("Bounty Reward's Sku Id should not be empty"), !Reward.Sku.Id.IsEmpty());
					TestTrue(TEXT("Bounty Reward's Sku name should not be empty"), !Reward.Sku.Name.IsEmpty());
					TestTrue(TEXT("Bounty Reward's Sku slug should not be empty"), !Reward.Sku.Slug.IsEmpty());
				}

				TestTrue(TEXT("Bounty Reward's amount of currency should be greater than 0"), Reward.Amount > 0);
				TestTrue(TEXT("Bounty Reward's currency code should not be empty"), !Reward.Currency.IsEmpty());
				TestTrue(TEXT("Bounty Reward's externalId should not be empty"), !Reward.ExternalId.IsEmpty());
			}

			// Test each Bounty's Dependants
			for (FBountyDependants Dependant : OutData.Bounty.Dependants)
			{
				TestTrue(TEXT("Bounty's Dependant's id should not be empty"), !Dependant.Id.IsEmpty());
				TestTrue(TEXT("Bounty's Dependant's name should not be empty"), !Dependant.Name.IsEmpty());
			}

			// Test each Bounty's prerequisites
			for (FBountyDependants Prerequisite : OutData.Bounty.Prerequisites)
			{
				TestTrue(TEXT("Bounty's Prerequisite's id should not be empty"), !Prerequisite.Id.IsEmpty());
				TestTrue(TEXT("Bounty's Prerequisite's name should not be empty"), !Prerequisite.Name.IsEmpty());
			}
			// ~End Test bounty

			// Test Bounty's progress
			TestTrue(TEXT("Bounty progress' currentPage should be greater than 0"), OutData.Progress.CurrentPage > 0);
			TestTrue(TEXT("Bounty progress' currentPageSize should be greater than 0"), OutData.Progress.CurrentPageSize > 0);
			TestTrue(TEXT("Bounty progress' totalCount should be greater than 0"), OutData.Progress.TotalCount > 0);

			// Test Bounty progress' data
			for (FBountyProgressData DataEntry : OutData.Progress.Data)
			{
				TestTrue(TEXT("Bounty progress data entry's id should not be empty"), !DataEntry.Id.IsEmpty());
				// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry's completed value should be valid"), DataEntry.Completed);
				TestTrue(TEXT("Bounty progress data entry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);
				TestTrue(TEXT("Bounty progress data entry's lastProgressCheck should not be empty"), !DataEntry.LastProgressCheck.IsEmpty());
				TestTrue(TEXT("Bounty progress data entry's currentObjectiveGroupId should not be empty"), !DataEntry.CurrentObjectiveGroupId.IsEmpty());

				// Test Bounty progress data's currentObjectives
				for (FBountyObjectiveProgress ObjProgressEntry : DataEntry.CurrentObjectives)
				{
					TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's id should not be empty"), !ObjProgressEntry.Id.IsEmpty());
					// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completed value count should be valid"), ObjProgressEntry.Completed);
					TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);

					// Test Bounty progress data currentObjectives' objective
					TestTrue(TEXT("Bounty progress data currentObjectives objective's id should not be empty"), !ObjProgressEntry.Objective.Id.IsEmpty());
					TestTrue(TEXT("Bounty progress data currentObjectives objective's name should not be empty"), !ObjProgressEntry.Objective.Name.IsEmpty());
					TestTrue(TEXT("Bounty progress data currentObjectives objective's count should be greater than 0"), ObjProgressEntry.Objective.Count > 0);
					TestTrue(TEXT("Bounty progress data currentObjectives objective's condition should not be empty"), !ObjProgressEntry.Condition.IsEmpty());
				}

				// Test Bounty progress data's completedObjectives
				for (FBountyCompletedObjective CompletedObjEntry : DataEntry.CompletedObjectives)
				{
					TestTrue(TEXT("Bounty progress data completedObjectives's objectiveGroupId should not be empty"), !CompletedObjEntry.ObjectiveGroupId.IsEmpty());
					
					// Test Bounty progress data currentObjectives's objectives
					for (FBountyObjectiveProgress ObjProgressEntry : CompletedObjEntry.Objectives)
					{
						TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's id should not be empty"), !ObjProgressEntry.Id.IsEmpty());
						// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completed value count should be valid"), ObjProgressEntry.Completed);
						TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);

						// Test Bounty progress data currentObjectives' objective
						TestTrue(TEXT("Bounty progress data currentObjectives objective's id should not be empty"), !ObjProgressEntry.Objective.Id.IsEmpty());
						TestTrue(TEXT("Bounty progress data currentObjectives objective's name should not be empty"), !ObjProgressEntry.Objective.Name.IsEmpty());
						TestTrue(TEXT("Bounty progress data currentObjectives objective's count should be greater than 0"), ObjProgressEntry.Objective.Count > 0);
						TestTrue(TEXT("Bounty progress data currentObjectives objective's condition should not be empty"), !ObjProgressEntry.Condition.IsEmpty());
					}

					// Test Bounty progress data currentObjectives's rewards
					for (FBountyProgressRewards RewardEntry : CompletedObjEntry.Rewards)
					{
						TestTrue(TEXT("Bounty progress data completedObjectives reward's id should not be empty"), !RewardEntry.Id.IsEmpty());
						TestTrue(TEXT("Bounty progress data completedObjectives reward's name should not be empty"), !RewardEntry.Name.IsEmpty());
						TestTrue(TEXT("Bounty progress data completedObjectives reward's externalId should not be empty"), !RewardEntry.ExternalId.IsEmpty());
						// No need to test completed value -- TestTrue(TEXT("Bounty progress data completedObjectives reward's rewardCompleted should be valid"), RewardEntry.RewardCompleted);
						TestTrue(TEXT("Bounty progress data completedObjectives reward's rewardReferenceId should not be empty"), !RewardEntry.RewardReferenceId.IsEmpty());
					}					
				}

				// Test Bounty progress data's creator
				TestTrue(TEXT("Bounty progress data entry creator's id should not be empty"), !DataEntry.Creator.Id.IsEmpty());
				TestTrue(TEXT("Bounty progress data entry creator's playerId should not be empty"), !DataEntry.Creator.PlayerId.IsEmpty());
				TestTrue(TEXT("Bounty progress data entry creator's name should not be empty"), !DataEntry.Creator.Name.IsEmpty());

				// Test Bounty progress data's creator's slugs
				for (FString Slug : DataEntry.Creator.Slugs)
				{
					TestTrue(TEXT("Bounty progress data entry creator's slug should not be empty"), !Slug.IsEmpty());
				}
			}
			*/
			return true;
		});	

		// https://app.swaggerhub.com/apis-docs/nexus-gg/Bounty/1.0.0#/creator%20bounty%20progress/getCreatorBountiesByID
		It("A_GetBountyProgress by creatorId", [this]
		{
			/*
			bool bGetBountyProgressDone = false;
			bool bGetBountyProgressSuccess = false;
			NexusSDK::FGetBountyProgressResponse OutData;

			OnGetBountyProgressComplete.BindLambda(
				[this, &bGetBountyProgressDone, &bGetBountyProgressSuccess, &OutData](NexusSDK::FGetBountyProgressResponse Response, bool bWasSuccessful)
				{
					OutData = Response;
					bGetBountyProgressSuccess = bWasSuccessful;
					bGetBountyProgressDone = true;
				});

			NexusSDK::FFGetBountyProgressRequest GetFGetBountyProgressRequest;
			GetFGetBountyProgressRequest.CreatorId = TEXT("12345");
			
			// Request bounty progress
			NexusSDK::GetBountyProgress(GetBountyProgressRequest, OnGetBountyProgressComplete);

			// Wait for response
			WaitForResponse(bGetBountyProgressDone, 5.0f, TEXT("Waiting to retrieve bounty progress by creator id..."));

			// Test success
			TestTrue(TEXT("Get bounty progress should be successful"), bGetBountyProgressSuccess);

			// Test content (group name and Id)
			TestTrue(TEXT("GroupId should not be empty"), !OutData.GroupId.IsEmpty());
			TestTrue(TEXT("GroupName should not be empty"), !OutData.GroupName.IsEmpty());

			// Test content (page)
			TestTrue(TEXT("CurrentPageSize should be greater than 0"), OutData.CurrentPageSize > 0);
			TestTrue(TEXT("CurrentPage should be greater than 0"), OutData.CurrentPage > 0);
			TestTrue(TEXT("TotalCount of referrals should be greater than 0"), OutData.TotalCount > 0);

			// Test content (creator Id & playerId)
			TestTrue(TEXT("CreatorId should not be empty"), !OutData.CreatorId.IsEmpty());
			TestTrue(TEXT("PlayerId should not be empty"), !OutData.PlayerId.IsEmpty());

			// Test progress data
			for (FBountyProgressData DataEntry : OutData.Progress.Data)
			{
				TestTrue(TEXT("Bounty progress data entry's id should not be empty"), !DataEntry.Id.IsEmpty());
				// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry's completed value should be valid"), DataEntry.Completed);
				TestTrue(TEXT("Bounty progress data entry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);
				TestTrue(TEXT("Bounty progress data entry's lastProgressCheck should not be empty"), !DataEntry.LastProgressCheck.IsEmpty());
				TestTrue(TEXT("Bounty progress data entry's currentObjectiveGroupId should not be empty"), !DataEntry.CurrentObjectiveGroupId.IsEmpty());

				// Test Bounty progress data's currentObjectives
				for (FBountyObjectiveProgress ObjProgressEntry : DataEntry.CurrentObjectives)
				{
					TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's id should not be empty"), !ObjProgressEntry.Id.IsEmpty());
					// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completed value count should be valid"), ObjProgressEntry.Completed);
					TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);

					// Test Bounty progress data currentObjectives' objective
					TestTrue(TEXT("Bounty progress data currentObjectives objective's id should not be empty"), !ObjProgressEntry.Objective.Id.IsEmpty());
					TestTrue(TEXT("Bounty progress data currentObjectives objective's name should not be empty"), !ObjProgressEntry.Objective.Name.IsEmpty());
					TestTrue(TEXT("Bounty progress data currentObjectives objective's count should be greater than 0"), ObjProgressEntry.Objective.Count > 0);
					TestTrue(TEXT("Bounty progress data currentObjectives objective's condition should not be empty"), !ObjProgressEntry.Condition.IsEmpty());
				}

				// Test Bounty progress data's completedObjectives
				for (FBountyCompletedObjective CompletedObjEntry : DataEntry.CompletedObjectives)
				{
					TestTrue(TEXT("Bounty progress data completedObjectives's objectiveGroupId should not be empty"), !CompletedObjEntry.ObjectiveGroupId.IsEmpty());

					// Test Bounty progress data currentObjectives's objectives
					for (FBountyObjectiveProgress ObjProgressEntry : CompletedObjEntry.Objectives)
					{
						TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's id should not be empty"), !ObjProgressEntry.Id.IsEmpty());
						// No need to test completed value -- TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completed value count should be valid"), ObjProgressEntry.Completed);
						TestTrue(TEXT("Bounty progress data entry ObjProgressEntry's completion count should be greater than -1"), DataEntry.CompletionCount > -1);

						// Test Bounty progress data currentObjectives' objective
						TestTrue(TEXT("Bounty progress data currentObjectives objective's id should not be empty"), !ObjProgressEntry.Objective.Id.IsEmpty());
						TestTrue(TEXT("Bounty progress data currentObjectives objective's name should not be empty"), !ObjProgressEntry.Objective.Name.IsEmpty());
						TestTrue(TEXT("Bounty progress data currentObjectives objective's count should be greater than 0"), ObjProgressEntry.Objective.Count > 0);
						TestTrue(TEXT("Bounty progress data currentObjectives objective's condition should not be empty"), !ObjProgressEntry.Condition.IsEmpty());
					}

					// Test Bounty progress data currentObjectives's rewards
					for (FBountyProgressRewards RewardEntry : CompletedObjEntry.Rewards)
					{
						TestTrue(TEXT("Bounty progress data completedObjectives reward's id should not be empty"), !RewardEntry.Id.IsEmpty());
						TestTrue(TEXT("Bounty progress data completedObjectives reward's name should not be empty"), !RewardEntry.Name.IsEmpty());
						TestTrue(TEXT("Bounty progress data completedObjectives reward's externalId should not be empty"), !RewardEntry.ExternalId.IsEmpty());
						// No need to test completed value -- TestTrue(TEXT("Bounty progress data completedObjectives reward's rewardCompleted should be valid"), RewardEntry.RewardCompleted);
						TestTrue(TEXT("Bounty progress data completedObjectives reward's rewardReferenceId should not be empty"), !RewardEntry.RewardReferenceId.IsEmpty());
					}
				}
				
				TestTrue(TEXT("Bounty progress data entry's name should not be empty"), !DataEntry.Name.IsEmpty());
				TestTrue(TEXT("Bounty progress data entry's limit should be greater than 0"), DataEntry.Limit > 0);
			}
			*/
			return true;
		});
	});

	Describe("Z_Teardown", [this]
	{
		It("A_Should<DescriptionHere>", [this]
		{
			return true;
		});
	});
}