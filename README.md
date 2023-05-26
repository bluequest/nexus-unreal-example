# Nexus Unreal Engine Sample Project

## Overview
The Nexus Unreal Engine Sample Project showcases the Nexus Support-A-Creator, and Referral & Bounties programs. Included are example UI which have been integrated with the [Nexus API](https://docs.nexus.gg/reference/rest-api/api-reference) to provide a foundation for developers build off of. 

This project uses Unreal Engine version 5.1.

### Dependencies
The Nexus Unreal Engine Sample Project has a dependency on the [Nexus Unreal SDK Plugin](https://github.com/bluequest/nexus-unreal-sdk). For more information on setting up the Nexus Unreal SDK, please refer to [README.md](https://github.com/bluequest/nexus-unreal-sdk/blob/main/README.md) located in the nexus-unreal-sdk repository, or [SDK_Unreal.md](https://github.com/bluequest/nexus-sdk-generator/blob/docs-workshop/SDK_Unreal.md) located in the nexus-sdk-generator repository

## Setup
1) Clone the repository 
    * Note that downloading and extracting may not properly pull the required Nexus Unreal SDK Plugin submodule located in the NexusSampleProject/Plugins/nexus-unreal-sdk folder, and if so, will need to be setup manually. See the Dependencies section for more details.
2) Generate project files by right clicking ```NexusSampleProject.uproject``` and selecting Generate Visual Studio project files in the drop down.
3) Open the generated ```NexusSampleProject.sln``` file
4) Build and run the solution

## Controls
PC:
- ```P```: Toggle Pause
- ```Left Click```: Interact (Used to press pause button located at the top left of the screen in-game)

Consoles:
- ```Gamepad Face Button Top```: Toggle Pause

## Contents

### Widgets
The project contains the following widget classes used to house UI funcitonality:
- ```UNexusSampleProjectBaseWidget```: Widget base class to derive from for this sample project
- ```UBountiesEntryUserWidget```: Widget entry to display information about a referral bounty
- ```UBountiesUserWidget```: Widget used to display a list of player's referral bounties
- ```UCreatorSupportUserWidget```: Widget used to utilize Nexus Support-A-Creator functionality 
- ```UHUDUserWidget```: Widget used for HUD
- ```UItemShopMenuUserWidget```: Widget used for the item shop (purchasing menu)
- ```UItemShopEntryUserWidget```: Widget used to display an item shop entry
- ```ULinkAccountUserWidget```: Widget used to display information about how to link a user's nexus account with their referral code
- ```UPauseMenuUserWidget```: Widget used for the pause menu
- ```UReferralsBountiesMenuUserWidget```: Widget used to utilize Nexus Referrals & Bounties functionality

And the following HUD class: 
- ```ANexusSampleProjectHUD```: Contains a reference to each project specific widget class to keep track of

The project also contains Unreal BP widgets which derive from the respective widget class described in this section. Note that each required component of each widget is marked with a ```BindWidget``` meta tag. This allows the developer to take the C++ UI layout and just bind widgets to the various components needed with their own styles and looks, and ensures that these components are present in the child BP class. 

### Save Load Creator Code
The ```UCreatorSupportUserWidget```, and ```UReferralsBountiesMenuUserWidget``` widget uses the ```UNexusSampleProjectSaveGame``` class included in order to save the creator code input by the player which can then be loaded to be used for reference when necessary, such as in the ```UItemShopMenuUserWidget``` when attempting to pair a new sale attributed to a creator during shop/store integration. 

### Creator/Referral Code Input Validation
Code input is enforced in ```UCreatorSupportUserWidget```, and ```UReferralsBountiesMenuUserWidget```. Creators are retreived on the backend using ```FNexusAttributionAPI::GetCreators``` then queried using ``FNexusReferralAPI::GetReferralInfoByPlayerId``` to retreive the creator's code which is then cached in an array. Input is then checked against that array when the user submits their code.

### Example Project User
For this example project, the 1st creator found in the ```GetCreators``` call is used to mimic user login, since user implementation is not integrated. This said, the "Your Referral Code" section in ```UReferralsBountiesMenuUserWidget``` will just use this queried user to display the referral code visual on the front end.
