// Fill out your copyright notice in the Description page of Project Settings.

#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/Public/NexusSampleProjectGlobals.h"
#include "NexusPrototype.h"
#include "NexusUnrealSDK.h"
#include "HttpModule.h"
#include "HttpManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNexusUESDKTest, Log, All);
DEFINE_LOG_CATEGORY(LogNexusUESDKTest);

BEGIN_DEFINE_SPEC(FNexusUESDKTestSpec, "Nexus.AutomationTests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

// Add variables here 
NexusSDK::FOnGetCatFactsComplete OnGetCatFactsComplete;
float DeltaTime = 0.2f;
// Add variables here 

END_DEFINE_SPEC(FNexusUESDKTestSpec);

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

	Describe("B_Unreal SDK Prototype Tests", [this]
	{
		It("A_(GetCatFacts) Should retrieve cat facts with valid data", [this]
		{
			bool bGetCatFactsDone = false;
			bool bGetCatFactsSuccess = false;

			NexusSDK::FGetCatFactsRequest GetCatFactsRequest;
			GetCatFactsRequest.MaxLength = 32;
			GetCatFactsRequest.Limit = 32;

			// Bind lambda and assign flags appropriately
			OnGetCatFactsComplete.BindLambda(
				[this, &bGetCatFactsDone, &bGetCatFactsSuccess](const NexusSDK::FGetCatFactsResponse& Response)
				{
					bGetCatFactsSuccess = Response.bSuccess;
					bGetCatFactsDone = true;
				});

			// Request GetCatFacts 
			NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetCatFactsComplete);

			while (!bGetCatFactsDone)
			{
				FPlatformProcess::Sleep(DeltaTime);
				FHttpModule::Get().GetHttpManager().Tick(DeltaTime);
				UE_LOG(LogNexusUESDKTest, Log, TEXT("Waiting to retrieve cat facts..."));
			}

			TestEqual(TEXT("GetCatFacts should be true"), bGetCatFactsSuccess, true);
			return true;
		});
	});

	Describe("C_Test", [this]
	{
		It("A_Should A", [this]
		{
			return true;
		});

		It("B_Should B", [this]
		{
			return true;
		});
	});

	Describe("Z_Teardown", [this]
	{
		It("A_Should A", [this]
		{
			return true;
		});
	});
}