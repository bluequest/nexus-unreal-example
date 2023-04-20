// Fill out your copyright notice in the Description page of Project Settings.

#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/Public/NexusSampleProjectGlobals.h"
#include "NexusPrototype.h"
#include "NexusUnrealSDK.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNexusUESDKTest, Log, All);
DEFINE_LOG_CATEGORY(LogNexusUESDKTest);

BEGIN_DEFINE_SPEC(FNexusUESDKTestSpec, "Nexus.AutomationTests", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

// Add variables here 
NexusSDK::FOnGetCatFactsComplete OnGetCatFactsComplete;
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

			// Bind lambda and assign success & done appropriately
			OnGetCatFactsComplete.BindLambda(
				[this, &bGetCatFactsDone, &bGetCatFactsSuccess](const NexusSDK::FGetCatFactsResponse& Response)
				{
					bGetCatFactsSuccess = Response.bSuccess;
					bGetCatFactsDone = true;
				});

			// Request GetCatFacts 
			NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetCatFactsComplete);

			/*
			// #TODO We will need to move this sleep on the HTTP thread somehow or find a way to end this unit test function and wait for a callback
			// The looping below will just starve the main thread and not allow the http request to be processed
			//
			// Loop until a response from GetCatFacts is received 
			while (!bGetCatFactsDone) 
			{
				FPlatformProcess::Sleep(0.2f);
				UE_LOG(LogNexusUESDKTest, Log, TEXT("Waiting to retrieve cat facts..."));
			}
			*/

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